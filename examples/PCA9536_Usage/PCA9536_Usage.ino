/* 
  PCA9536 LIBRARY - COMPLETE USAGE EXAMPLE SKETCH
  -----------------------------------------------

  This sketch exposes all the functions offered by the PCA9536 library as detailed below, thereby offering a quick & easy way of understanding 
  how the library works, as well as testing your PCA9536.

  INPORTANT: This library uses the 'WSWire' library (https://github.com/steamfire/WSWireLib/tree/master/Library/WSWire) for I2C communication with 
  the ADS1110, so it is NECESSARY to have it installed prior to using the current libraty. Alternatively, if you wish to use the 'Wire' library 
  (https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire) - or any other I2C library for that matter - simply change 
  the following line the the 'PCA9536.h' file:
      #include <WSWire.h>
  to this:
      #include <Wire.h>  // or to whatever I2C library name you are using.
  As noted above, whichever library you intend to use for this purpose must be alredy installed for the PCA9536 library to work.


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

   PIN 1 (IO0) - Used here as INPUT  - Connect pin to Arduino GND via 100R resistor.
   PIN 2 (IO1) - Used here as OUTPUT - Connect pin to a LED's Anode via 470R resistor. Other end goes to Arduino GND.
   PIN 3 (IO2) - Used here as INPUT  - Connect pin to Arduino 5V via 100R resistor.
   PIN 4 (GND) - Connect to Arduino GND
   PIN 5 (IO3) - Used here as OUTPUT - Connect pin to to a LED's Cathode via 470R resistor. Other end goes to Arduino 5V.
   PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 or 10K pull-up resistor (2K2 = 400MHz; 10K = 100MHz)
   PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 or 10K pull-up resistor.(2K2 = 400MHz; 10K = 100MHz)
   PIN 8 (VCC) - Connect to Arduino 5V output

   NOTE: PIN 1 Marked by • in the diagram above

   DECOUPING: Connect a 0.1uF Ceramic Capacitor between VCC & GND PINS.

 
  I2C ADDRESS
  -----------
  The PCA9536 has a single I2C address (factory hardwired):
 
        PART               DEVICE I2C ADDRESS          PART
       NUMBER          (BIN)      (HEX)     (DEC)     MARKING
      --------        --------    -----     -----     -------
      PCA9536D        01000001    0x41       65       PCA9536

  NOTE: The 'D' suffix of the Part Number denotes the SOIC-8 package
  

  LIBRARY INSTALLATION & SETUP
  ----------------------------

  Begin by installing the library either by using the Arduino IDE's installation wizard (Arduino Version >1.5) 
  or simply download the librarty ZIP folder from GITHUB (LINK), extract it, and copy the extraxcted folder 
  to your Arduino 'libraries' folder.
  
  Next, include the library at the top of the sketch as follows:

  #include <PCA9536.h>

  At this point you can construct a new PCA9536 object use the following line (at the top of the sketch after the 'include' line):

  PCA9536 DEVICE_NAME();

  NOTES: Replace 'DEVICE_NAME' above with a name of your choice

  
  LIBRARY FUNCTIONS
  -----------------
  With the library installed & included in the sketch, and an ADS1110 object initiallized, the following functions are available 
  (see the sketch itself for actual examples):
  
    FUNCTION (PARAMETERS)        NOTES
    ----------------------       -----
    ping();                      Params: None. Searches for the device at the defined I2C address. Returns byte with 0 (Success) or 1-6 (I2C Error Code)
    getMode();                   Params: IO1 / IO2 / IO3 / IO4. Returns byte with the selected pin's 'mode': 0 (OUTPUT_MODE) / 1 (INPUT_MODE)
    setMode();                   Params: IO1 / IO2 / IO3 / IO4 | OUTPUT_MODE / INPUT_MODE. Sets the selected pin's 'mode'. Returns: none.
    setModeAll();                Params: OUTPUT_MODE / INPUT_MODE. Sets All pins' 'mode' simultaniously. Returns: none.
    getState();                  Params: IO1 / IO2 / IO3 / IO4. Returns byte with the selected pin's 'state': 0 (LOW_STATE) / 1 (HIGH_STATE)
    setState();                  Params: IO1 / IO2 / IO3 / IO4 | LOW_STATE / HIGH_STATE. Sets the selected pin's 'state' (OUTPUT pins only). Returns: none.
    setStateAll();               Params: LOW_STATE / HIGH_STATE. Sets All pins' 'state' simultaniously  (OUTPUT pins only). Returns: none.
    getPolarity();               Params: IO1 / IO2 / IO3 / IO4. Returns byte with the selected pin's 'polarity' (INPUT pins only): 0 (NON-INVERTED) / 1 (INVERTED)
    setPolarity();               Params: IO1 / IO2 / IO3 / IO4 | NON_INVERTED / INVERTED. Sets the selected pin's 'polarity' (INPUT pins only). Returns: none.
    setPolarityAll();            Params: INVERTED / NON_INVERTED. Sets All pins' 'polarity' simultaniously  (INPUT pins only). Returns: none.
    getComResult();              Params: None. Returns byte with the result of the latest I2C communication transaction. Returns byte with 0 (Success) or 1-6 (I2C Error Code)

  And, lastly, if for whatever reason you wish to destruct an existing PCA9536 object, you can use the following line to do so:

    ~PCA9536 DEVICE_NAME();


  I2C COMMUNICATION RESULT CODES
  ------------------------------
    0 ... Success (no error)
    1 ... Buffer overflow
    2 ... Address sent, NACK received
    3 ... Data send, NACK received
    4 ... Other error (lost bus arbitration, bus error, etc.)
    5 ... Timed-out while trying to become Bus Master
    6 ... Timed-out while waiting for data to be sent


  RUNNING THE EXAMPLE SKETCH
  --------------------------
  1) Hook-up the PCA9536 to the Arduino as explained above.
  2) If you like, connect a 10K potentiometer to the ADS1110 V+ PIN (potentimeter's first pin goes to GND, 
     middle pin to V+, and third pin to 5V).
  3) Upload the sketch to the Arduino.
  4) Open the Serial Communications Window (make sure the baud-rate is set to 9600).
  5) You should be able to see detailed feedback from running each of the possible functions of the library 
     (when you get to the part where readings are carried out, play with the potentiomer to check out changes 
     in the readings based on the input voltage).


  BUG REPORTS
  -----------
  Please report any bugs/issues/suggestions at the GITHUB Repository of this library at:  _________________________.


  LICENSE
  -------
  This library is a free software; you can redistribute it and/or modify it under the terms of the 
  GNU General Public License as published by the Free Software Foundation; either version 3.0 of 
  the License, or any later version.This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
  PARTICULAR PURPOSE. See the GNU General Public License for more details.

*/

#include <PCA9536.h>

PCA9536 EXPANDER;

const byte NUM_IO_PINS =   4;                 // Number of GPIO pins of the PCA9536
const int  DELAY_TIME  = 750;                 // In ms. A quick break between function testing

String testResult;                            // Test feedback container in a String format
pin_t pins[4]    = { IO0, IO1, IO2, IO3 };    // Array with pin names to facilitate testing
pin_t inputs[2]  = { IO0, IO2 };              // Array with pin names to facilitate testing
pin_t outputs[2] = { IO1, IO3 };              // Array with pin names to facilitate testing

void setup() {
    Serial.begin(9600);                       // Initiallizes the Serial Port (at 9600bd)
    Wire.begin();                             // Initiallizes the I2C communications bus
    while(!Serial);                           // Waits for Serial Port to initialize
    Serial.print("\nSerial Open\n");          // Notifies that the Serial Sort is open
    pingTest();                               // Pings the PCA9536 to check if I2C communication has been established
    getPreConfigModeTest();                   // Checks the mode of each of the IO pins (INPUT/OUTPUT) before configuring the device (=default settings)
    getPreConfigStateTest();                  // Checks the state of each of the IO pins (INPUT/OUTPUT) before configuring the device (=default settings)
    getPreConfigPolarrityTest();              // Checks the polarity (NON-INVERTED / INVERTED) of all pins (currently: INPUTS) before configuring the device (=default settings)
    configDevice();                           // Configure PCA9536 pins as INPUTS/OUTPUTS and sets the latter as LOW/HIGH
    getPostConfigModeTest();                  // Checks the mode of each of the IO pins (INPUT/OUTPUT) after configuring the device
    getPostConfigStateTest();                 // Checks the state of each of the IO pins (INPUT/OUTPUT) after configuring the device
    changePolarityTest();                     // Checks the state of each of the INPUT pins after inverting their polarity


    
    Serial.print("\nDone Testing\n");
}

void loop() {}

void pingTest() {
    testResult = (EXPANDER.ping() ? "No Response (Error code:" + String(EXPANDER.getComResult())  + ")" : "Pong");
    Serial.print("\nPing device: " + testResult + "\n");
    takeAquickBreak();
}

void getPreConfigModeTest() {
    Serial.println("\nPin Modes:");
    for (byte i=0; i<sizeof(pins); i++) { 
        testResult = (EXPANDER.getMode(pins[i]) ? "INPUT" : "OUTPUT");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: INPUT)\n");
    }
    takeAquickBreak();
}

void getPreConfigStateTest() {
    Serial.println("\nPin States:");
    for (byte i=0; i<sizeof(pins); i++) { 
        testResult = (EXPANDER.getState(pins[i]) ? "HIGH" : "LOW");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: ");
        (i < 1) ? Serial.print("LOW)\n") : Serial.print("HIGH)\n");
    }
    takeAquickBreak();
}

void getPreConfigPolarrityTest() {
    Serial.println("\nPin Polarity:");
    for (byte i=0; i<sizeof(pins); i++) { 
        testResult = (EXPANDER.getPolarity(pins[i]) ? "INVERTED" : "NON-INVERTED");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: NON-INVERTED)\n");
    }
    takeAquickBreak();
}

void configDevice() {  
    Serial.println("\nConfiguring device:");      
    EXPANDER.setMode(IO1, OUTPUT_MODE);   // Sets pin IO1 as an OUTPUT
    EXPANDER.setMode(IO3, OUTPUT_MODE);   // Sets pin IO3 as an OUTPUT
    EXPANDER.setState(IO0, LOW_STATE);    // Sets pin IO0 output to LOW
    EXPANDER.setState(IO2, HIGH_STATE);   // Sets pin IO0 output to HIGH
    Serial.println("  Device configured\n");
    takeAquickBreak();
}

void getPostConfigModeTest() {
    Serial.println("\nPin Modes:");
    for (byte i=0; i<sizeof(pins); i++) { 
        testResult = (EXPANDER.getMode(pins[i]) ? "INPUT" : "OUTPUT");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: ");
        i%2 ? Serial.print("INPUT)\n") : Serial.print("OUTPUT)\n");
    }
    takeAquickBreak();
}

void getPostConfigStateTest() {
    Serial.println("\nPin States:");
    for (byte i=0; i<sizeof(pins); i++) { 
        testResult = (EXPANDER.getState(pins[i]) ? "HIGH" : "LOW");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: ");
        (i < 2) ? Serial.print("LOW)\n") : Serial.print("HIGH)\n");
    }
    takeAquickBreak();
}

void changePolarityTest() {
    Serial.println("\nPin Polarity (INVERTED):");
    for (byte i=0; i<sizeof(inputs); i++) {
        EXPANDER.setPolarity(inputs[i], INVERTED_POLARITY);
        testResult = (EXPANDER.getPolarity(inputs[i]) ? "INVERTED" : "NON-INVERTED");
        Serial.print("\n PIN IO" + String(inputs[i]) + ": " + testResult + "  (Expected: INVERTED\n");
    }
    Serial.println("\nPin State (INVERTED):");
    for (byte i=0; i<sizeof(inputs); i++) {
        testResult = (EXPANDER.getState(inputs[i]) ? "HIGH" : "LOW");
        Serial.print("\n PIN IO" + String(pins[i]) + ": " + testResult + "  (Expected: ");
        (i < 1) ? Serial.print("HIGH)\n") : Serial.print("LOW)\n");   
    }
    takeAquickBreak();
}

void takeAquickBreak() {
    delay(DELAY_TIME);
    Serial.println();
}


