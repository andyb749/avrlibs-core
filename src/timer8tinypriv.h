/*
 * timer8tinypriv.h
 *
 * Created: 20-Oct-2019 17:35:30
 *  Author: andyb
 */ 


#ifndef TIMER8TINYPRIV_H_
#define TIMER8TINYPRIV_H_

#ifndef TIMER8TINY_H_
#error "Do not include timer8tinypriv.h, use timer8tiny.h"
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
_defTimer8(TIMER0, TCCR0A, TCCR0B, TCNT0L, OCR0A, OCR0B, TIMSK, TIFR);
#endif

#ifdef TCCR2A
//_defTimer8(TIMER2, TCCR2A, TCCR2B, TCNT2, OCR2A, OCR2B, TIMSK2, TIFR2);
#endif

// cleanup - we've finished with the SFR definitions
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT







#endif /* TIMER8TINYPRIV_H_ */