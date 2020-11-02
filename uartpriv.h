//***************************************************************************
//
//  File Name :		uartPriv.h
//
//  Project :		Library for the Atmel 8 bit AVR MCU
//
//  Purpose :		An object to wrap the UART hardware
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

#ifndef UARTPRIV_H_
#define UARTPRIV_H_


#ifndef UART_H_
#error "Do not include uartpriv.h, use uart.h"
#endif

// We need to undef these because we want to redefine _SFR_ASM_COMPAT macro
// and include avr/io.h again to get numbers from the sfr registers
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT

#define _SFR_ASM_COMPAT 1
#include <avr/io.h>


//! \brief Macro to define a structure for a particular port
//! \param NAME The final name of the structure
//! \param PINREG The PIN SFR of this port
//! \param DATAREG The PORT SFR of this port
//! \param DDRREG The DDR SFR of this port
#define _defUart(NAME, DATAREG, CSRAREG, CSRBREG, CSRCREG, UBRRREG) \
struct NAME { \
	static const uint16_t datax = DATAREG; \
	static const uint16_t crsax = CSRAREG; \
	static const uint16_t crsbx = CSRBREG; \
	static const uint16_t crscx = CSRCREG; \
	static const uint16_t ubrrx = UBRRREG; \
}


// Define a structure for each IO port that physically exists on a processor

#ifdef UDR0
_defUart(UART0, UDR0, UCSR0A, UCSR0B, UCSR0C, UBRR0);
#endif

#ifdef UDR1
_defUart(UART1, UDR1, UCSR1A, UCSR1B, UCSR1C, UBRR1);
#endif

#ifdef UDR2
_defUart(UART2, UDR2, UCSR2A, UCSR2B, UCSR2C, UBRR2);
#endif

#ifdef UDR3
_defUart(UART3, UDR3, UCSR3A, UCSR3B, UCSR3C, UBRR3);
#endif



// cleanup - we've finished with the SFR definitions for now
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT


#endif /* UARTPRIV_H_ */