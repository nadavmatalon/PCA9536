/* 
  PCA9536 LIBRARY - COMPLETE USAGE EXAMPLE
  ----------------------------------------

  INTRODUCTION
  ------------ 

  The PCA9536 is a 4-Channel GPIO Expander with a hardware I2C interface.

  The device's 4 channels (i.e. I/O pins) may be controlled all at the same time or individually in terms
  of their: [1] Mode (INPUT / OUTPUT), [2] State (for output pin mode only: HIGH / LOW), and [3] Polarity
  (for input pin mode only: NON-INVERTED INPUT / INVERTED INPUT). The State (LOW / HIGH) of pins in input
  mode may be read, whereas thoat of pins in output mode may be either read or written to.

  This library contains a complete driver for the PCA9536 exposing all the above functionality, as well as
  allowing uses to toggle the state of pins in input mode, and recieve verbose information re the device's
  current settings and/or I2C communication results.

  INPORTANT: The current library depends on the Arduino IDE's native 'Wire' library for I2C communication
             between the Arduino (Master) and the PCA9536 (Slave).

  WIRING DIAGRAM
  --------------
                       PCA9536
                       -------
                IO0 --| •     |-- VCC
                      |       |
                IO1 --|       |-- SDA
                      |       |
                IO2 --|       |-- SCL
                      |       |
                GND --|       |-- IO3
                       -------

   This hookup can be used with the following sketch:

   PIN 1 (IO0) - Leave unconnected for the purpose of this sketch
   PIN 2 (IO1) - Leave unconnected for the purpose of this sketch
   PIN 3 (IO2) - Leave unconnected for the purpose of this sketch
   PIN 4 (GND) - Connect to Arduino GND
   PIN 5 (IO3) - Leave unconnected for the purpose of this sketch
   PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
   PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
   PIN 8 (VCC) - Connect to Arduino 5V output
   DECOUPING   - Connect a 0.1uF Ceramic Capacitor between the PCA9536's VCC & GND pins

  I2C ADDRESS
  -----------
  The PCA9536 has a single I2C address (factory hardwired):
 
        PART               DEVICE I2C ADDRESS          PART
       NUMBER          (BIN)      (HEX)     (DEC)     MARKING
      --------        --------    -----     -----     -------
      PCA9536D        01000001    0x41       65       PCA9536

  Note: The 'D' suffix of the Part Number denotes the SOIC-8 package

  BUG REPORTS
  -----------
  Please report any bugs/issues/suggestions in the Github Repository of this library at: https://github.com/nadavmatalon/PCA9536/issues

  LICENSE
  -------
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
*/

#include "PCA9536.h"

PCA9536 pca9536;                              // construct a new PCA9536 instance

void setup() {
    Serial.begin(9600);                       // initiallize the Serial Port (at 9600bd)
    Wire.begin();                             // initiallize the I2C Communications Bus
    while(!Serial);                           // wait for Serial Port to open
    pca9536.reset();                          // make sure device testing starts with default settings
    runTests();                               // run the tests
}

void loop() {}

void runTests() {
    printDivider();
    Serial.print(F("\nPCA9536 LIBRARY USAGE & TESTING\n"));
    testPingDevice();
    printDivider();
    Serial.print(F("\nGETTING PIN DATA\n"));
    testGetPinData();
    printDivider();
    Serial.print(F("\nSETTING MODE OF ALL PINS\n"));
    testSetPinModeAll();
    printDivider();
    Serial.print(F("\nSETTING MODE OF INDIVIDUAL PINS\n"));
    testSetPinMode();
    printDivider();
    Serial.print(F("\nSETTING STATE OF ALL OUTPUT PINS\n"));
    testSetPinStateAll();
    printDivider();
    Serial.print(F("\nSETTING STATE OF INDIVIDUAL OUTPUT PINS\n"));
    testSetPinState();
    printDivider();
    Serial.print(F("\nTOGGLING STATE OF ALL OUTPUT PINS\n"));
    testTogglePinAll();
    printDivider();
    Serial.print(F("\nTOGGLING STATE OF INDIVIDUAL OUTPUT PINS\n"));
    testTogglePin();
    printDivider();
    Serial.print(F("\nSETTING POLARITY OF ALL INPUT PINS\n"));
    testSetPinPolarityAll();
    printDivider();
    Serial.print(F("\nSETTING POLARITY OF INDIVIDUAL INPUT PINS\n"));
    testSetPinPolarity();
    printDivider();
    Serial.print(F("\nTESTING DEVICE RESET\n"));
    testReset();
    printDivider();
    Serial.print(F("\nGETTING I2C COMMUNICATION RESULT\n"));
    testGetComResult();
    printDivider();
    Serial.print(F("\nDONE TESTING\n"));
    printDivider();
}

void testPingDevice() {
    Serial.print(F("\nSearching for device...Device "));
    Serial.print(pca9536.ping() ? "Not Found\n" : "Found!\n");
    quickDelay();
}

void testGetPinData() {
    pin_t pins[4] = { IO0, IO1, IO2, IO3 };
    for (byte i=0; i<4; i++) {
        Serial.print(F("\nPIN IO"));
        Serial.print(i);
        Serial.print(F(":     "));
        Serial.print(pca9536.getMode(pins[i]) ? "INPUT" : "OUTPUT");
        Serial.print(F("\t"));
        Serial.print(pca9536.getState(pins[i]) ? "HIGH" : "LOW");
        Serial.print(F("\t"));
        Serial.print(pca9536.getPolarity(pins[i]) ? "INVERTED\n" : "NON-INVERTED\n");
        quickDelay();
    }
}

void testSetPinModeAll() {
    Serial.print(F("\nSetting all pins as OUTPUT..."));
    pca9536.setMode(IO_OUTPUT);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testSetPinMode() {
    Serial.print(F("\nSetting pins IO1 & IO3 as INPUT..."));
    pca9536.setMode(IO1, IO_INPUT);
    pca9536.setMode(IO3, IO_INPUT);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testSetPinStateAll() {
    Serial.print(F("\nSetting all output pins to LOW..."));
    pca9536.setState(IO_LOW);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testSetPinState() {
    Serial.print(F("\nSetting pin IO2 to HIGH..."));
    pca9536.setState(IO2, IO_HIGH);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testTogglePinAll() {
    Serial.print(F("\nToggling STATE of all output pin..."));
    pca9536.toggleState();
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testTogglePin() {
    Serial.print(F("\nToggling STATE of pin IO0..."));
    pca9536.toggleState(IO0);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testSetPinPolarityAll() {
    Serial.print(F("\nSetting all input pins to INVERTED polarity..."));
    pca9536.setPolarity(IO_INVERTED);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testSetPinPolarity() {
    Serial.print(F("\nSetting input pin IO1 to NON-INVERTED polarity..."));
    pca9536.setPolarity(IO1, IO_NON_INVERTED);
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testReset() {
    Serial.print(F("\nResetting Device..."));
    pca9536.reset();
    Serial.print(F("DONE\n"));
    testGetPinData();
}

void testGetComResult() {
    Serial.print(F("\nCalling Device..."));
    pca9536.ping();
    Serial.print(F("DONE\n\nI2C COMMUNICATION CODE RESULT:  "));
    Serial.print(pca9536.getComResult());
    Serial.print(F("\n\n(See README for meaning of I2C Communication Codes)\n"));
}

void printDivider() {
    Serial.print(F("\n-----------------------------------------------------\n"));
}

void quickDelay() {
    delay(50);
}
