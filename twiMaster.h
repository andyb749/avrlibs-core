//***************************************************************************
//
//  File Name :		TwiMaster.h
//
//  Project :		TWI (I2C) library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Object orientated access to the Timer 16 bit timers T3, T4, T5 on
//					Atmel 8 bit AVR MCUs
//
// The MIT License (MIT)
//
// Copyright (c) 2013-2016 Andy Burgess
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Revisions :
//
//      see rcs below
//
//***************************************************************************


#ifndef TWIMASTER_H_
#define TWIMASTER_H_


#include <avr/io.h>

#include "FastIO.h"


#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__) | \
defined(__AVR_AT90Tiny26__) | defined(__AVR_ATtiny26__)
#define SDAPIN		FASTIOPIN_B0
#define SCLPIN		FASTIOPIN_B2
#define _HAS_USI_TWI
#endif

#if defined(__AVR_ATtiny24__) | defined(__AVR_ATtiny44__) | defined(__AVR_ATtiny84A__)
#define SDAPIN		FASTIOPIN_A6
#define SCLPIN		FASTIOPIN_A4
#define _HAS_USI_TWI
#endif

#if defined(__AVR_ATtiny261__) | defined(__AVR_ATtiny461__) | defined(__AVR_ATtiny861__) | \
defined(__AVR_ATtiny261V__) | defined(__AVR_ATtiny461V__) | defined(__AVR_ATtiny861V__) | \
defined(_AVR_ATtiny861A_H_)
#define SDAPIN		FASTIOPIN_B0
#define SCLPIN		FASTIOPIN_B2
#define _HAS_USI_TWI
#endif

#if defined(__AVR_AT90Mega169__) | defined(__AVR_ATmega169PA__) | \
defined(__AVR_AT90Mega165__) | defined(__AVR_ATmega165__) | \
defined(__AVR_ATmega325__) | defined(__AVR_ATmega3250__) | \
defined(__AVR_ATmega645__) | defined(__AVR_ATmega6450__) | \
defined(__AVR_ATmega329__) | defined(__AVR_ATmega3290__) | \
defined(__AVR_ATmega649__) | defined(__AVR_ATmega6490__)
#define SDAPIN		FASTIOPIN_E5
#define SCLPIN		FASTIOPIN_E4
#define _HAS_USI_TWI
#endif

#if defined(__AVR_AT90Tiny2313__) | defined(__AVR_ATtiny2313__)
#define SDAPIN		FASTIOPIN_B5
#define SCLPIN		FASTIOPIN_B7
#define _HAS_USI_TWI
#endif

#if defined(__AVR_ATtiny48__) | defined(__AVR_ATtiny88__) | defined(__AVR_ATmega168P) | defined(__AVR_ATmega328P__)
#define SDAPIN		FASTIOPIN_C4
#define SCLPIN		FASTIOPIN_C5
#define _HAS_TWI
#endif

#if defined(__AVR_ATmega644P__) | defined(__AVR_ATmega1284P__) | defined(__AVR_ATmega644__) | defined(__AVR_ATmega1284__)
#define SDAPIN		FASTIOPIN_C1
#define SCLPIN		FASTIOPIN_C0
#define _HAS_TWI
#endif

#if defined(__AVR_AT90CAN32__) | defined(__AVR_AT90CAN64__) | defined(__AVR_AT90CAN128__)
#define SDAPIN		FASTIOPIN_D1
#define SCLPIN		FASTIOPIN_D0
#define _HAS_TWI
#endif

#if defined(__AVR_ATmega640__) | defined(__AVR_ATmega1280__) | defined(__AVR_ATmega2560__)
#define SDAPIN		FASTIOPIN_D1
#define SCLPIN		FASTIOPIN_D0
#define _HAS_TWI
#endif


#if defined (__AVR_ATmega169P__)
#define SDAPIN		FASTIOPIN_E5
#define SCLPIN		FASTIOPIN_E4
#define _HAS_USI_TWI
#endif


#if defined(__AVR_ATmega8U2__)
#warning "ATmega8U2 has no TWI or USI module"
#endif


#if defined(__AVR_ATmega16M1__)
#warning "ATmega16M1 has no TWI or USI module"
#endif


#if defined (_HAS_USI_TWI)
#include "twiMasterUsi.h"
#endif

#if defined (_HAS_TWI)
#include "twiMasterTwi.h"
#endif


extern TwiMaster twiMaster;


#endif /* TWIMASTER_H_ */