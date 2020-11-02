//***************************************************************************
//
//  File Name :		Timer8.h
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


#ifndef TIMER8_H_
#define TIMER8_H_

#include <stdint.h>
#include <avr/io.h>
#include <commondefs.h>
#include <timerpriv.h>
#include <timer8priv.h>


//! \brief A class describing timer Timer0
//! \details Declare a object as follows:
//! Timer0 timer(clksrc, wavegen);
template<class TTIMER8>
class Timer8
{
//variables
public:
protected:
private:

//functions
public:
	//! \brief Initialises a new instance of the Timer0 class
	inline Timer8() __attribute__((always_inline)) {}
	
	//! \brief Sets the source of the clock for the timer
	//! \param mode Set to one of the defined clock modes to determine
	//! the source of the clock for the timer
//#if (TTIMER8==TIMER2)
//	inline void setClockMode (clockModeT2_t mode) __attribute__((always_inline))
//	{
//		*psfr8_t(TTIMER8::tccrbRegx) &= ~0x07;
//		*psfr8_t(TTIMER8::tccrbRegx) |= mode;
//	}
//#else
//	inline void setClockMode (clockMode_t mode) __attribute__ ((always_inline))
//	{
//		*psfr8_t(TTIMER8::tccrbRegx) &= ~0x07;
//		*psfr8_t(TTIMER8::tccrbRegx) |= mode;
//	}
//#endif
	inline void setClockMode (uint8_t mode) __attribute__ ((always_inline))
	{
		*psfr8_t(TTIMER8::tccrbRegx) &= ~0x07;
		*psfr8_t(TTIMER8::tccrbRegx) |= mode;
	}

	//! \brief Sets the waveform generator mode
	//! \param mode Set to one of the defined waveform generation modes
	inline void setWavegenMode (wavegenMode8_t mode) __attribute__ ((always_inline))
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~0x03;
		*psfr8_t(TTIMER8::tccraRegx) |= (mode & 0x03);
		*psfr8_t(TTIMER8::tccrbRegx) &= ~(1 << WGM02);
		*psfr8_t(TTIMER8::tccrbRegx) |= ((mode & 0x0c) << (WGM02 - WGM00));
	}

	// Main Timer/Counter
	//! \brief Read the timer register
	//! \details Reads the TCNT0 register returning the 8 bit value
	inline uint8_t read () { return *psfr8_t(TTIMER8::tcntRegx); }

	//! \brief Write the timer register
	//! \details Write the TCNT0 register with the supplied 8 bit value
	inline void write (uint8_t value) { *psfr8_t(TTIMER8::tcntRegx) = value; }

	//! \brief Enables the timer overflow interrupt
	//! \details Sets the overflow bit in the Interrupt Mask Register.  The
	//! overflow interrupt is generated when the value in the counter/timer overflow and
	//! in normal counter mode acts as a pseudo ninth bit.
	inline void enableOverflowInt () { _sbi(TTIMER8::timskRegx, TOIE0); }

	//! \brief Disables the timer overflow interrupt
	//! \details Clear the overflow bit in the Interrupt Mask Register
	inline void disableOverflowInt () { _cbi(TTIMER8::timskRegx, TOIE0); }

	//! \brief Clears the timer overflow interrupt status
	//! \details Clear the overflow bit in the Interrupt Status Register by setting
	//! to 1. Use when not the interrupt is not enabled
	inline void clearOverflow() { _sbi(TTIMER8::tifrRegx, TOV0); }
	
	//! \brief Gets the state of the overflow status bit
	//! \details Get the status of the overflow bit in the Interrupt Status Register.
	//! For use when not the interrupt is not enabled
	inline bool isOverFlow () { return bit_is_set (TTIMER8::tifrRegx, TOV0); }

	// Output Compare A
	//! \brief Set the compare/match mode for output A
	//! \details If mode is zero, then OC0A pin can be used for normal port
	//! operations, otherwise it will be used for the OC0A function.
	inline void setCompareAMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~(3 << COM0A0);
		*psfr8_t(TTIMER8::tccraRegx) |= (mode << COM0A0);
	}

	//! \brief Set the output compare register A
	//! \details The output compare register contains an 8-bit value that is
	//! continuously compared to the counter value TCNT0. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OC0A pin.
	inline void writeCompareA (uint8_t value) { *psfr8_t(TTIMER8::ocraRegx) = value; }

	//! \brief Get the value of the output compare register A
	inline uint8_t readCompareA () { return *psfr8_t(TTIMER8::ocraRegx); }

	//! \brief Set the Force Compare A bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCR0A as TOP.
	inline void setForceCompareA () { _sbi (*psfr8_t(TTIMER8::tccrbRegx), FOC0A); }

	// Don't think this function will do anything as setForceCompareA is implemented as a strobe
	inline void clearForceCompareA () { _cbi (*psfr8_t(TTIMER8::tccrbRegx), FOC0A); }

	inline bool isCompareA () { return bit_is_set (TTIMER8::tifrRegx, OCF0A); }

	//! \brief Enables the Output Match A interrupt
	//! \details Sets the output match A interrupt bit in the Interrupt Mask Register.
	//! A output match interrupt is generated when the value in the counter/timer register matches
	//! the output compare register.
	inline void enableOutputMatchAInt () { _sbi (TTIMER8::timskRegx, OCIE0A); }

	//! \brief Disables the Output Match A interrupt
	//! \details Clears the output match A interrupt bit in the Interrupt Mask Register.
	inline void disableOutputMatchAInt () { _cbi (TTIMER8::timskRegx, OCIE0A); }

	//! \brief Clears the Output Match A interrupt status
	//! \details Clear the output match A bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearOutputMatchA() { _sbi(TTIMER8::tifrRegx, OCF0A); }
	
	// Output Compare B
	//! \brief Set the compare/match mode for output B
	//! \details If mode is zero, then OC0B pin can be used for normal port
	//! operations, otherwise it will be used for the OC0B function.
	inline void setCompareBMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~(3 << COM0B0);
		*psfr8_t(TTIMER8::tccraRegx) |= (mode << COM0B0);
	}

	//! \brief Set the output compare register B
	//! \details The output compare register contains an 8-bit value that is
	//! continuously compared to the counter value TCNT0. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OC0B pin.
	inline void writeCompareB (uint8_t value) { *psfr8_t(TTIMER8::ocrbRegx) = value; }

	//! \brief Get the value of the output compare register B
	inline uint8_t readCompareB () { return *psfr8_t(TTIMER8::tccrbRegx); }

	// The ATtiny261/461/861 do not have a output match unit
	//! \brief Set the Force Compare B bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCR0B as TOP.
	inline void setForceCompareB () { _sbi (TTIMER8::tccrbRegx, FOC0B); }

	// Don't think this function will do anything as setForceCompareB is implemented as a strobe
	inline void clearForceCompareB () { _cbi (TTIMER8::tccrbRegx, FOC0B); }

	inline bool isCompareB () { return bit_is_set (TTIMER8::tifrRegx, OCF0B); }

	//! \brief Enables the Output Match B interrupt
	//! \details Sets the output match B interrupt bit in the Interrupt Mask Register.
	//! A output match interrupt is generated when the value in the counter/timer register matches
	//! the output compare register.
	inline void enableOutputMatchBInt () { _sbi (TTIMER8::timskRegx, OCIE0B); }

	//! \brief Disables the Output Match B interrupt
	//! \details Clears the output match B interrupt bit in the Interrupt Mask Register.
	inline void disableOutputMatchBInt () { _cbi (TTIMER8::timskRegx, OCIE0B); }

	//! \brief Clears the Output Match B interrupt status
	//! \details Clear the output match B bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearOutputMatchB() { _sbi(TTIMER8::tifrRegx, OCF0B); }

	//! \brief Operator overload that performs the same as the read method
	inline operator uint8_t() __attribute__((always_inline))
	{
		return read();
	}
	
	//! \brief An operator overload that performs the same as the write method
	inline Timer8& operator =(uint8_t value) __attribute__((always_inline))
	{
		write(value);
		return *this;
	}
	
protected:
private:

};


#endif /* TIMER8_H_ */