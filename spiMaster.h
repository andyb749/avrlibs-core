//***************************************************************************
//
//  File Name :		SPIMaster.h
//
//  Project :		SPI Master library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Encapsulates the SPI Master functions on
//					Atmel 8 bit AVR MCUs
//
// The MIT License (MIT)
//
// Copyright (c) 2013-2015 Andy Burgess
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

#ifndef __SPIMASTER_H__
#define __SPIMASTER_H__


#include "FastIO.h"
//#include "SpiMasterBase.h"


#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__) | \
defined(__AVR_AT90Tiny26__) | defined(__AVR_ATtiny26__)
#define MOSIPIN		FASTIOPIN_B1
#define MISOPIN		FASTIOPIN_B0
#define SCKPIN		FASTIOPIN_B2
//#define SSPIN		-1
#define _HAS_USI_SPI
#endif

#if defined(__AVR_ATtiny24__) | defined(__AVR_ATtiny44__) | defined(__AVR_ATtiny84__) | (defined(__AVR_ATtiny84A__))
#define MOSIPIN		FASTIOPIN_A5
#define MISOPIN		FASTIOPIN_A6
#define SCKPIN		FASTIOPIN_A4
//#define SSPIN		-1
#define _HAS_USI_SPI
#endif

#if defined(__AVR_ATtiny261__) | defined(__AVR_ATtiny461__) | defined(__AVR_ATtiny861__) | \
defined(__AVR_ATtiny261V__) | defined(__AVR_ATtiny461V__) | defined(__AVR_ATtiny861V__) | defined(__AVR_ATtiny861A__)
#ifdef USE_ALTUSI
 #define MOSIPIN		FASTIOPIN_A1
 #define MISOPIN		FASTIOPIN_A0
 #define SCKPIN			FASTIOPIN_A2
// #define SSPIN		-1
#else
 #define MOSIPIN		FASTIOPIN_B1
 #define MISOPIN		FASTIOPIN_B0
 #define SCKPIN			FASTIOPIN_B2
// #define SSPIN		-1
#endif
#define _HAS_USI_SPI
#endif

#if defined(__AVR_ATtiny48__) | defined(__AVR_ATtiny88__) | defined(__AVR_ATmega168P) | defined(__AVR_ATmega328P__)
#define MOSIPIN		FASTIOPIN_B3
#define MISOPIN		FASTIOPIN_B4
#define SCKPIN		FASTIOPIN_B5
#define SSPIN		FASTIOPIN_B2
#define _HAS_SPI
#endif

#if defined(__AVR_AT90Mega169__) | defined(__AVR_ATmega169PA__) |  defined(__AVR_ATmega169P__) | \
defined(__AVR_AT90Mega165__) | defined(__AVR_ATmega165__) | \
defined(__AVR_ATmega325__) | defined(__AVR_ATmega3250__) | \
defined(__AVR_ATmega645__) | defined(__AVR_ATmega6450__) | \
defined(__AVR_ATmega329__) | defined(__AVR_ATmega3290__) | \
defined(__AVR_ATmega649__) | defined(__AVR_ATmega6490__)
#define MISOPIN		FASTIOPIN_B3
#define MOSIPIN		FASTIOPIN_B2
#define SCKPIN		FASTIOPIN_B1
#define SSPIN		FASTIOPIN_B0
#define _HAS_SPI
#endif

#if defined(__AVR_ATTiny2313__) | defined(__AVR_ATtiny2313__)
#define MISOPIN		FASTIOPIN_B6
#define MOSIPIN		FASTIOPIN_B5
#define SCKPIN		FASTIOPIN_B7
#define SSPIN		-1
#define _HAS_USI_SPI
#endif

#if defined(__AVR_ATmega644P__) | defined(__AVR_ATmega1284P__) | defined(__AVR_ATmega644__) | defined(__AVR_ATmega1284__)
#define MISOPIN		FASTIOPIN_B6
#define MOSIPIN		FASTIOPIN_B5
#define SCKPIN		FASTIOPIN_B7
#define SSPIN		FASTIOPIN_B4
#define _HAS_SPI
#endif

#if defined(__AVR_AT90CAN32__) | defined(__AVR_AT90CAN64__) | defined(__AVR_AT90CAN128__)
#define MISOPIN		FASTIOPIN_B3
#define MOSIPIN		FASTIOPIN_B2
#define SCKPIN		FASTIOPIN_B1
#define SSPIN		FASTIOPIN_B0
#define _HAS_SPI
#endif

#if defined(__AVR_ATmega640__) | defined(__AVR_ATmega1280__) | defined(__AVR_ATmega2560__)
#define MISOPIN		FASTIOPIN_B3
#define MOSIPIN		FASTIOPIN_B2
#define SCKPIN		FASTIOPIN_B1
#define SSPIN		FASTIOPIN_B0
#define _HAS_SPI
#endif


//! \brief Enumeration of SPI modes
//! \details Enumeration that controls the clock polarity and
//! clock phase to determine when and what edge that the data
//! is sampled.
//! \para When CPOL is 0 the clock idles at 0 and pulses on when clocked.
//! If CPOL is 1 the clock idles at 1 and pulses off when clocked.
//! \para When CPHA is 0 the "out" side changes the data on the trailing edge
//! of the preceding clock cycle while the "in" side samples the data on the leading edge
//! of the clock cycle
typedef enum
{
	// FIXME: these need a SPI interface
	SPI_MODE0 = 0,		// CPOL = 0, CPHA = 0 
	SPI_MODE1 = 1,		// CPOL = 0, CPHA = 1 
	SPI_MODE2 = 2,		// CPOL = 1, CPHA = 0
	SPI_MODE3 = 3,		// CPOL = 1, CPHA = 1
} spiModes_t;


//! \brief Enumeration of SPI bit ordering
//! \details Enumeration that controls the order that bits are
//! clocked in and out of the SPI port.
typedef enum
{
	SPI_MSBFIRST = 0,
	SPI_LSBFIRST = 1
} spiOrder_t;



#if defined (_HAS_USI_SPI)
#include "spiMasterUsi.h"
#endif

#if defined (_HAS_SPI)
#include "spiMasterSpi.h"
#endif


extern SpiMaster spiMaster;


#endif //__SPIMASTER_H__
