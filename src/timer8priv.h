//***************************************************************************
//
//  File Name :		Timer8Priv.h
//
//  Project :		8 bit timer objects for the Atmel 8 bit AVR MCU
//
//  Purpose :		Object orientated access to the Timer 8 bit timers T0, T2 on
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



#ifndef TIMER8PRIV_H_
#define TIMER8PRIV_H_

#ifndef TIMER8_H_
#error "Do not include timer8priv.h, use timer8.h"
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


//! \brief Macro to define a structure for a particular TIMER16
//! \param NAME The final name of the structure
//! \param CTLREG The MCU or EI Control Register
//! \param MSGREG The External Interrupt Control Register
//! \param MASKBIT1 The bit position within the EICRA
//! \param MASKBIT2 The bit position with the EIMSK and EIFR
#define _defTimer8(NAME, TCCRAREG, TCCRBREG, TCNTREG, OCRAREG, OCRBREG, TIMSKREG, TIFRREG) \
struct NAME { \
	static const uint16_t tccraRegx = TCCRAREG; \
	static const uint16_t tccrbRegx = TCCRBREG; \
	static const uint16_t tcntRegx = TCNTREG; \
	static const uint16_t ocraRegx = OCRAREG; \
	static const uint16_t ocrbRegx = OCRBREG; \
	static const uint16_t timskRegx = TIMSKREG; \
	static const uint16_t tifrRegx = TIFRREG; \
}

#ifdef TCCR0A
_defTimer8(TIMER0, TCCR0A, TCCR0B, TCNT0, OCR0A, OCR0B, TIMSK0, TIFR0);
#endif

#ifdef TCCR2A
_defTimer8(TIMER2, TCCR2A, TCCR2B, TCNT2, OCR2A, OCR2B, TIMSK2, TIFR2);
#endif

// cleanup - we've finished with the SFR definitions
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT



#endif /* TIMER8PRIV_H_ */