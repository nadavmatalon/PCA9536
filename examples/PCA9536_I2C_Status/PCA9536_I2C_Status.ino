/* 
  PCA9536 LIBRARY - I2C COMMUNICATION STATUS STRING EXAMPLE
  ---------------------------------------------------------

  INTRODUCTION
  ------------
  This sketch presents a minimal example of extending the PCA9536 Library to include an additional function
  for generating a printable I2C Communications Status string which may be useful, for example, during debugging sessions.

  As can be seen in the sketch below, implementation of this extended functionality only requires adding a single 'include'
  to the code, namely that of the relevant *.h file (PCA9536ComStr.h).
  
  Note that this functional extension does come at the cost of an increased memory usage, and therefore it seemed preferable to maintain it 
  as an optional add-on rather than include it in the core PCA9536 Library itself.
  
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
#include "utility/PCA9536ComStr.h"

PCA9536 pca9536;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    while(!Serial);
    Serial.print(F("\nPCA9536 GPIO I2C EXPANDER"));
    Serial.print(F("\n-------------------------\n"));
    Serial.print(F("\nSENDING COMMAND TO DEVICE..."));
    pca9536.setMode(IO0, IO_OUTPUT);
    Serial.print(F("DONE\n\nI2C STATUS:   ")); 
    Serial.print(PCA9536ComStr(pca9536));
    Serial.print(F("\n\n"));
}

void loop() {}
