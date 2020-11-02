//***************************************************************************
//
//  File Name :		ExtInterrupts.h
//
//  Project :		External Interrupts library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Easy access to EXTINT input pins on Atmel 8 bit AVR MCUs
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


#ifndef EXTINTS_H_
#define EXTINTS_H_

#include <avr/io.h>
#include "ExtInterruptsPriv.h"
#include "CommonDefs.h"


//! \brief Enumeration of the external interrupt sense control
//! \detail The External interrupts INT0/INT1/INT2 can interrupt
//! the processor on either a low level, any edge, rising edge or
//! falling edge.
typedef enum 
{
	//! \brief A low level interrupt
	ExtIntLowLevel,

	//! \brief Interrupt on both edges
	ExtIntAnyEdge,

	//! \brief Interrupt on falling edge only
	ExtIntFalling,

	//! \brief Interrupt on rising edge only
	ExtIntRising
} extIntSense_t;


typedef volatile uint8_t* extint_t;


//! \brief A class representing an external interrupt
//! \details A class to represent any of the external interrupt pins.  To use, declare
//! an object as follows:
//! \code
//! ExtInterrupt<EXTINT0> int0(ExtIntLowLevel);
//! \endcode
//! The template parameter depends on the AVR8 chip targetted.  Select one of the extIntSense_t
//! enumeration for the type of interrupt
//! \tparam TEXTINT The external interrupt for this instance
template <class TEXTINT>
class ExtInterrupt
{
public:
	//! \brief Initialises a new instance of the \a ExtInterrupt class
	//! \description Initialises a new instance of the \a ExtInterrupt class with the specified interrupt sense
	//! \param[in] sense One of the \a extIntSense_t enumeration that determines the sense of the interrupt.
	inline ExtInterrupt (extIntSense_t sense) __attribute__ ((always_inline))
	{
		setSense(sense);
	}

	//! \brief Sets up the sense for the interrupt pin
	//! \param[in] sense One of the \a extIntSense_t enumeration that determines the sense of the interrupt.
	//! \detail Sets the sense of the interrupt pin, to none, rising, falling or any
	inline void setSense(extIntSense_t sense) __attribute__((always_inline))
	{
		*extint_t(TEXTINT::ctlregx) &= ~(3<<TEXTINT::bit1x);
		*extint_t(TEXTINT::ctlregx) |= sense<<TEXTINT::bit1x;
	}

	//! \brief Gets the sense of the interrupt pin
	//! \detail Returns the sensor of the interrupt pin: none, rising, falling, any
	inline extIntSense_t getSense() __attribute__((always_inline))
	{
		return (extIntSense_t) ((*extint_t(TEXTINT::ctlregx) >> TEXTINT::bit1x) & 0x03);
	}
	
	//! \brief Enable this external interrupt
	//! \description Enables this external interrupt instance by setting the 
	//! required bit in the mask register
	inline void enableInt () __attribute__ ((always_inline))
	{
		_sbi(TEXTINT::mskregx, TEXTINT::bit2x);
	}


	//! \brief Disable this external interrupt
	//! \description Disables this external interrupt instance by clearing the
	//! required bit in the mask register
	inline void disableInt() __attribute__ ((always_inline))
	{
		_cbi(TEXTINT::mskregx, TEXTINT::bit2x);
	}


	//! \brief Gets the status of this interrupt's flag
	//! \description This method returns the state of the interrupt, to allow a caller
	//! to determine if the interrupt would have been triggered.
	//! \returns True if the interrupt flag in the flags register is true indicating that the
	//! interrupt would be activated
	inline bool getIntFlag() __attribute__ ((always_inline))
	{
		return TEXTINT::flgregx & _BV(1<<TEXTINT::bit2x);
	}


	//! \brief Clears the interrupt flag
	//! \description Clears the interrupt flag for this external interrupt.  Use before
	//! setting the global interrupt enable to ensure that old interrupts are not triggered.
	inline void clearIntFlag() __attribute__ ((always_inline))
	{
		_sbi (TEXTINT::flgregx, TEXTINT::bit2x);
	}
protected:
private:

};

#endif /* EXTINTS_H_ */