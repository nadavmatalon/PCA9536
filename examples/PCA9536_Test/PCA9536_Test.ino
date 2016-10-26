/* 
  PCA9536 LIBRARY - BASIC DEVICE TESTING EXAMPLE
  ----------------------------------------------
  
  INTRODUCTION
  ------------
  This sketch offers a quick & simple code for testing that the PCA9536 is hooked-up and operating correctly.

  The sketch begins by searching for the PCA9536 on the I2C Bus. I then moves on to get the various Register data available from the device
  (Ambient Temperature, Limit, and Hysteresis). And finally, it verifies that the Alert functionality is working as it should (at least, 
  in default mode).
  
  INPORTANT: The current library depends on the Arduino IDE's native 'Wire' library for I2C communication between the Arduino (Master) and the PCA9536 (Slave).

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

  PIN 1 (IO0) - Connect LED (anode via appropriate series resistor to Arduino 5V output & cathode to PCA9536 Pin 1)
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

    PART                DEVICE I2C ADDRESS         PART
   NUMBER           (BIN)     (HEX)     (DEC)     MARKING
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

PCA9536 pca9536;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    while(!Serial);
    printDivider();
    Serial.print(F("\nPCA9536 DEVICE TESTING\n"));
    printDivider();
    Serial.print(F("\nINITIATING SERIAL COMMUNICATION\n"));  
    Serial.print(F("\nSerial Port is "));
    Serial.print(Serial ? "Open\n" : "Could not be opened\n"); 
    printDivider();
    pca9536.reset();
    delay(50);
    pca9536.setMode(IO0, IO_OUTPUT);
    delay(50);
    Serial.print(F("\nSEARCHING FOR DEVICE\n\nDevice "));
    pca9536.ping() ? Serial.print(F("Not Found\n")) : Serial.print(F("Found!\n"));
    printDivider();
    delay(50);
    Serial.print(F("\nBLINKING LED ON PIN IO0\n"));
    printDivider();
}

void loop() {
    pca9536.toggleState(IO0);
    delay(500);
}

void printDivider() {
    Serial.print(F("\n-----------------------------------------\n"));
}
