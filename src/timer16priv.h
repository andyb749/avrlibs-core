//***************************************************************************
//
//  File Name :		Timer16Priv.h
//
//  Project :		16 bit timer objects for the Atmel 8 bit AVR MCU
//
//  Purpose :		Object orientated access to the Timer 16 bit timers T1, T3, T4, T5 on
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


#ifndef TIMER16PRIV_H_
#define TIMER16PRIV_H_


#ifndef TIMER16_H_
#error "Do not include timer16priv.h, use timer16.h"
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
#define _defTimer16(NAME, TCCRAREG, TCCRBREG, TCCRCREG, TCNTREG, OCRAREG, OCRBREG, OCRCREG, ICRREG, TIMSKREG, TIFRREG) \
struct NAME { \
	static const uint16_t tccraRegx = TCCRAREG; \
	static const uint16_t tccrbRegx = TCCRBREG; \
	static const uint16_t tccrcRegx = TCCRCREG; \
	static const uint16_t tcntRegx = TCNTREG; \
	static const uint16_t ocraRegx = OCRAREG; \
	static const uint16_t ocrbRegx = OCRBREG; \
	static const uint16_t ocrcRegx = OCRCREG; \
	static const uint16_t icrRegx = ICRREG; \
	static const uint16_t timskRegx = TIMSKREG; \
	static const uint16_t tifrRegx = TIFRREG; \
}

#if defined OCR1C
_defTimer16(TIMER1, TCCR1A, TCCR1B, TCCR1C, TCNT1, OCR1A, OCR1B, OCR1C, ICR1, TIMSK1, TIFR1);
#else
_defTimer16(TIMER1, TCCR1A, TCCR1B, TCCR1C, TCNT1, OCR1A, OCR1B, 0, ICR1, TIMSK1, TIFR1);
#endif

#if defined TCCR3A
#if defined OCR3C
_defTimer16(TIMER3, TCCR3A, TCCR3B, TCCR3C, TCNT3, OCR3A, OCR3B, OCR3C, ICR3, TIMSK3, TIFR3);
#else
_defTimer16(TIMER3, TCCR3A, TCCR3B, TCCR3C, TCNT3, OCR3A, OCR3B, 0, ICR3, TIMSK3, TIFR3);
#endif
#endif

#if defined TCCR4A
_defTimer16(TIMER4, TCCR4A, TCCR4B, TCCR4C, TCNT4, OCR4A, OCR4B, OCR4C, ICR4, TIMSK4, TIFR4);
#endif

#if defined TCCR5A
_defTimer16(TIMER5, TCCR5A, TCCR5B, TCCR5C, TCNT5, OCR5A, OCR5B, OCR5C, ICR5, TIMSK5, TIFR5);
#endif

// cleanup - we've finished with the SFR definitions
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT


#endif /* TIMER16PRIV_H_ */