//***************************************************************************
//
//  File Name :		ExtInterruptsPriv.h
//
//  Project :		External Interrupts library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Part of the easy access to EXTINT input pins on Atmel 8 bit AVR MCUs
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


#ifndef EXTINTSPRIV_H_
#define EXTINTSPRIV_H_


#ifndef EXTINTS_H_
#error "Do not include ExtInterruptsPriv.h, use ExtInterrupts.h"
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


//! \brief Macro to define a structure for a particular INT
//! \param NAME The final name of the structure
//! \param CTLREG The MCU or EI Control Register
//! \param MSGREG The External Interrupt Control Register
//! \param MASKBIT1 The bit position within the EICRA
//! \param MASKBIT2 The bit position with the EIMSK and EIFR
#define _defExtInt(NAME, CTLREG, MASKREG, FLAGREG, MASKBIT1, MASKBIT2) \
struct NAME { \
	static const uint16_t ctlregx = CTLREG; \
	static const uint16_t mskregx = MASKREG; \
	static const uint16_t flgregx = FLAGREG; \
	static const uint8_t bit1x = MASKBIT1; \
	static const uint8_t bit2x = MASKBIT2; \
}


// Define a structure for each PCINT mask register that exists

#ifdef INT0
#if defined (__AVR_ATtiny24__) | defined(__AVR_ATtiny44__) | defined(__AVR_ATtiny84A__) | defined (__AVR_ATtiny25__) | defined (__AVR_ATtiny45__) | defined (__AVR_ATtiny85__)
_defExtInt(EXTINT0, MCUCR, GIMSK, GIFR, ISC00, INTF0);
#else
_defExtInt(EXTINT0, EICRA, EIMSK, EIFR, ISC00, INTF0);
#endif
#endif

#ifdef INT1
_defExtInt(EXTINT1, EICRA, EIMSK, EIFR, ISC10, INTF1);
#endif
#ifdef INT2
_defExtInt(EXTINT2, EICRA, EIMSK, EIFR, ISC20, INTF2);
#endif

#ifdef INT3
_defExtInt(EXTINT3, EICRA, EIMSK, EIFR, ISC30, INTF3);
#endif

#ifdef INT4
_defExtInt(EXTINT4, EICRB, EIMSK, EIFR, ISC40, INTF4);
#endif

#ifdef INT5
_defExtInt(EXTINT5, EICRB, EIMSK, EIFR, ISC50, INTF5);
#endif

#ifdef INT6
_defExtInt(EXTINT6, EICRB, EIMSK, EIFR, ISC60, INTF6);
#endif

#ifdef INT7
_defExtInt(EXTINT7, EICRB, EIMSK, EIFR, ISC70, INTF7);
#endif

// cleanup - we've finished with the SFR definitions
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT



#endif /* EXTINTSPRIV_H_ */