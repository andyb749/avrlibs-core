//***************************************************************************
//
//  File Name :		PinChangeInts.h
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


#ifndef PINCHANGEINTS_H_
#define PINCHANGEINTS_H_


#include "PinChangePriv.h"
#include "avr/io.h"
#include <util/atomic.h>
#include "CommonDefs.h"


typedef volatile uint8_t* pcint_t;


//! \brief A Class to represent a group of PCINT pins
//! \details Each group of PCINT pins can generate an interrupt.
//! The supplied mask will determine which pins in the group can
//! generate the interrupt
template <class pcint, uint8_t mask=0xff>
class PinChangeInt
{
	public:
	//! \brief Initialises a new instance of the PinChangeInt class
	//! \details The PinChangeInt class is for use by a single pin change pin
	inline PinChangeInt () __attribute__ ((always_inline))
	{
		*pcint_t(pcint::maskx) |= mask;	// set the Pin Change mask
		enableInt();
	}


	//! \brief Enables the Pin Change Interrupt
	inline void enableInt () __attribute__ ((always_inline))
	{
		_sbi(PCICR, pcint::bitx);
	};


	//! \brief Disables the Pin Change Interrupt
	inline void disableInt () __attribute__ ((always_inline))
	{
		_cbi(PCICR, pcint::bitx);
	};


	//! \brief Gets the state of the pin change interrupt flag
	//! \details This method can be used when operating in polling mode
	//! The status can be cleared by calling ClearInterruptFlag();
	inline bool getIntFlag () __attribute__ ((always_inline))
	{
		return PCIFR & _BV(1<<pcint::bitx);
	}

	//! \brief Clears the pin change interrupt flag
	//! \details When using interrupts, the interrupt flag is automatically
	//! reset when the interrupt routine is executed.  This method can be
	//! used when not using interrupts.
	inline void clearIntFlag() __attribute__ ((always_inline))
	{
		_sbi (PCIFR, pcint::bitx);
	}
};


#endif /* PINCHANGEINTS_H_ */