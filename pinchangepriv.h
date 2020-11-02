//***************************************************************************
//
//  File Name :		PinChangePriv.h
//
//  Project :		Library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Fast access to the pin change interrupts on
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


#ifndef PINCHANGEPRIV_H_
#define PINCHANGEPRIV_H_

#ifndef PINCHANGEINTS_H_
#error "Do not include PinChangePriv.h, use PinChangeInts.h"
#endif

// We need to under these because we want to redefine _SFR_ASM_COMPAT macro
// and include avr/io.h to get numbers from the sfr registers
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT

#define _SFR_ASM_COMPAT 1
#include <avr/io.h>


//! \brief Macro to define a structure for a particular PCINT
//! \param NAME The final name of the structure
//! \param MSGREG The Pin Change Mask Register
#define _defPCInt(NAME, MASKREG, MASKBIT) \
struct NAME { \
	static const uint16_t maskx = MASKREG; \
	static const uint8_t bitx = MASKBIT; \
}


// Define a structure for each PCINT mask register that exists

_defPCInt(PCINT0_7, PCMSK0, PCIE0);
_defPCInt(PCINT8_15, PCMSK1, PCIE1);
#ifdef PCMSK2
_defPCInt(PCINT16_23, PCMSK2, PCIE2);
#endif
#ifdef PCMSK3
_defPCInt(PCINT24_31, PCMSK3, PCIE3);
#endif

// cleanup - we've finished with the SFR definitions
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT


#endif /* PINCHANGEPRIV_H_ */