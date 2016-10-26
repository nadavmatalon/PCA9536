/*==============================================================================================================*
 
    @file     PCA9536InfoStr.h
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    A complemetary Device Information String Generator Debugging Function for the PCA9536 Library
 
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

#ifndef PCA9536InfoStr_h
#define PCA9536InfoStr_h

#include <avr/pgmspace.h>
#include "utility/PCA9536ComStr.h"

namespace Pca9536 {

    const int  INFO_BUFFER_SIZE = 60;
    const byte NUM_OF_INFO_STR  =  8;

    const char infoStr0[]  PROGMEM = "\nPCA9536 DEVICE INFORMATION";
    const char infoStr1[]  PROGMEM = "\n--------------------------";
    const char infoStr2[]  PROGMEM = "\nI2C ADDRESS:\t %d (%#X)";
    const char infoStr3[]  PROGMEM = "\nI2C COM STATUS:\t %sCONNECTED";
    const char infoStr4[]  PROGMEM = "\nPIN\tMODE\tSTATE\tPOLARITY";
    const char infoStr5[]  PROGMEM = "\n---\t----\t-----\t--------";
    const char infoStr6[]  PROGMEM = "\nIO%d\t%sPUT\t%s\t%sINVERTED";
    const char errStr[]    PROGMEM = "\nI2C ERROR:\t ";

    const char * const infoStrs[NUM_OF_INFO_STR] PROGMEM = {
        infoStr0,
        infoStr1,
        infoStr2,
        infoStr3,
        infoStr4,
        infoStr5,
        infoStr6,
        errStr
    };

/*==============================================================================================================*
    GENERATE DEVICE INFORMATION STRING (PRINTABLE FORMAT)
 *==============================================================================================================*/

    PCA9536_PString PCA9536InfoStr(const PCA9536& devParams) {
        char * ptr;
        char strBuffer[338];
        int  devAddr = DEV_ADDR;
        PCA9536 pca9536;
        pca9536.getMode(IO0);
        byte comErrCode = pca9536.getComResult();
        PCA9536_PString resultStr(strBuffer, sizeof(strBuffer));
        char devInfoBuffer[INFO_BUFFER_SIZE];
        for (byte i=0; i<4; i++) {
            ptr = (char *) pgm_read_word(&infoStrs[i]);
            if (i < 2)   snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, ptr);
            if (i == 2)  snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, ptr, devAddr, devAddr);
            if (i == 3)  snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, ptr, (comErrCode ? "NOT " : ""));
            resultStr += devInfoBuffer;
        }
        if (!comErrCode) {
            pin_t pins[4] = { IO0, IO1, IO2, IO3 };
            for (byte i=4; i<(NUM_OF_INFO_STR - 1); i++) {
                ptr = (char *) pgm_read_word(&infoStrs[i]);
                if (i < 6)  {
                    snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, ptr);
                    resultStr += devInfoBuffer;
                }
                if (i == 6)  {
                    for (byte j=0; j<4; j++) {
                        byte mode = pca9536.getMode(pins[j]);
                        byte state = pca9536.getState(pins[j]);
                        byte polarity = pca9536.getPolarity(pins[j]);
                        snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, ptr, j, (mode ? "IN" : "OUT"), (state ? "HIGH" : "LOW"), (polarity ? "" : "NON-"));
                        resultStr += devInfoBuffer;
                    }
                    resultStr += "\n";
                }
            }
        } else {
            snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, (char *) pgm_read_word(&infoStrs[7]));
            resultStr += devInfoBuffer;
            snprintf_P(devInfoBuffer, INFO_BUFFER_SIZE, (char *) pgm_read_word(&comCodes[comErrCode]));
            resultStr += devInfoBuffer;
            resultStr += "\n";
        }
        return resultStr;
    }
}

using namespace Pca9536;

#endif
