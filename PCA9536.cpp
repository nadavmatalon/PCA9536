/*==============================================================================================================*

    @file     PCA9536.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    PCA9536 Driver (4-Channel GPIO I2C Expander)

    Ver. 1.0.0 - First release (24.10.16)
 
 *===============================================================================================================*
    LICENSE
 *===============================================================================================================*
 
    The MIT License (MIT)
    Copyright (c) 2016 Nadav Matalon

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without
    limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 *==============================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#include "PCA9536.h"

/*==============================================================================================================*
    CONSTRUCTOR
 *==============================================================================================================*/

PCA9536::PCA9536() {
    _comBuffer = ping();
}

/*==============================================================================================================*
    DESTRUCTOR
 *==============================================================================================================*/

PCA9536::~PCA9536() {}

/*==============================================================================================================*
    PING (0 = SUCCESS / 1, 2... = ERROR CODE)
 *==============================================================================================================*/

// See meaning of I2C error codes in the README

byte PCA9536::ping() {
    Wire.beginTransmission(DEV_ADDR);
    return Wire.endTransmission();
}

/*==============================================================================================================*
    GET PIN MODE (0 = OUTPUT / 1 = INPUT)
 *==============================================================================================================*/

byte PCA9536::getMode(pin_t pin) {
    return bitRead(getData(REG_CONFIG), pin);
}

/*==============================================================================================================*
    GET PIN STATE (0 = LOW / 1 = HIGH)
 *==============================================================================================================*/

byte PCA9536::getState(pin_t pin) {
    byte state = (getMode(pin) ? getData(REG_INPUT) : getData(REG_OUTPUT));
    return bitRead(state, pin);
}

/*==============================================================================================================*
    GET PIN POLARITY: INPUT PINS ONLY (0 = NON-INVERTED / 1 = INVERTED)
 *==============================================================================================================*/

byte PCA9536::getPolarity(pin_t pin) {
    return bitRead(getData(REG_POLARITY), pin);
}

/*==============================================================================================================*
    SET PIN MODE
 *==============================================================================================================*/

void PCA9536::setMode(pin_t pin, mode_t newMode) {                           // PARAMS: IO0 / IO1 / IO2 / IO3
    setPin(REG_CONFIG, newMode, ALL_INPUT);                                  //         IO_INPUT / IO_OUTPUT
}

/*==============================================================================================================*
    SET ALL PINS MODE
 *==============================================================================================================*/

void PCA9536::setMode(mode_t newMode) {                                      // PARAMS: IO_INPUT / IO_OUTPUT
    setData(REG_CONFIG, (newMode ? ALL_INPUT : ALL_OUTPUT));
}

/*==============================================================================================================*
    SET PIN STATE (OUTPUT PINS ONLY)
 *==============================================================================================================*/

void PCA9536::setState(pin_t pin, state_t newState) {                        // PARAMS: IO0 / IO1 / IO2 / IO3
    setPin(REG_OUTPUT, newState, ALL_HIGH);                                  //         IO_LOW / IO_HIGH
}

/*==============================================================================================================*
    SET ALL PINS STATE (OUTPUT PINS ONLY)
 *==============================================================================================================*/

void PCA9536::setState(state_t newState) {                                   // PARAMS: IO_LOW / IO_HIGH
    setData(REG_OUTPUT, (newState ? ALL_HIGH : ALL_LOW));
}

/*==============================================================================================================*
    SET PIN POLARITY (INPUT PINS ONLY)
 *==============================================================================================================*/

void PCA9536::setPolarity(pin_t pin, polarity_t newPolarity) {          // PARAMS: IO0 / IO1 / IO2 / IO3
    setPin(REG_POLARITY, newPolarity, ALL_NON_INVERTED);                //         IO_NON_INVERTED / IO_INVERTED
}

/*==============================================================================================================*
    SET ALL PINS POLARITY (INPUT PINS ONLY)
 *==============================================================================================================*/

void PCA9536::setPolarity(polarity_t newPolarity) {                     // PARAMS: IO_NON_INVERTED / IO_INVERTED
    setData(REG_POLARITY, (newPolarity ? ALL_INVERTED : ALL_NON_INVERTED));
}

/*==============================================================================================================*
    RESET
 *==============================================================================================================*/

void PCA9536::reset() {
    setMode(IO_INPUT);
    setState(IO_HIGH);
    setPolarity(IO_NON_INVERTED);
    initCall(REG_INPUT);
    endCall();
}

/*==============================================================================================================*
    GET REGISTER DATA
 *==============================================================================================================*/

byte PCA9536::getData(reg_ptr_t regPtr) {
    byte data = 0;
    initCall(regPtr);
    endCall();
    if (_comBuffer == COM_SUCCESS) {
        Wire.requestFrom(DEV_ADDR, NUM_BYTES);
        if (Wire.available() == NUM_BYTES) data = Wire.read();
        else {
            while (Wire.available()) Wire.read();
            _comBuffer = ping();
        }
    }
    return data;
}

/*==============================================================================================================*
    SET REGISTER DATA
 *==============================================================================================================*/

void PCA9536::setData(reg_ptr_t regPtr, byte newData) {
    initCall(regPtr);
    Wire.write(newData);
    endCall();
}

/*==============================================================================================================*
    SET PIN (MODE / STATE / POLARITY)
 *==============================================================================================================*/

void PCA9536::setPin(reg_ptr_t regPtr, byte newSetting, byte bitMask) {
    setData(regPtr, ((getData(regPtr) & ~bitMask) | (newSetting & bitMask)));
}

/*==============================================================================================================*
    INITIATE I2C COMMUNICATION
 *==============================================================================================================*/

void PCA9536::initCall(reg_ptr_t regPtr) {
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(regPtr);
}

/*==============================================================================================================*
    END I2C COMMUNICATION
 *==============================================================================================================*/

void PCA9536::endCall() {
    _comBuffer = Wire.endTransmission();
}

/*==============================================================================================================*
    GET COMMUNICATION RESULT
 *==============================================================================================================*/

byte PCA9536::getComResult() {
    return _comBuffer;
}
