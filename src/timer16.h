//***************************************************************************
//
//  File Name :		Timer16.h
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


#ifndef TIMER16_H_
#define TIMER16_H_

#include <stdint.h>
#include <avr/io.h>
#include <commondefs.h>
#include <timerpriv.h>
#include <timer16priv.h>


template <class TTIMER16>
class Timer16
{
public:
	//! \brief Default Constructor
	//! \description Initialises a new instance of the Timer16 class
	inline Timer16 () __attribute__((always_inline)) {}	
		
	//! \brief Sets the source of the clock for the timer
	//! \param mode Set to one of the defined clock modes to determine
	//! the source of the clock for the timer
	inline void setClockMode (clockMode_t mode) __attribute__((always_inline))
	{
		*psfr8_t(TTIMER16::tccrbRegx) &= ~ 0x07;
		*psfr8_t(TTIMER16::tccrbRegx) |= mode;
	}

	
	//! \brief Sets the waveform generator mode
	//! \param mode Set to one of the defined waveform generation modes
	inline void setWavegenMode (wavegenMode16_t mode) __attribute__ ((always_inline))
	{
		*psfr8_t(TTIMER16::tccraRegx) &= ~0x03;
		*psfr8_t(TTIMER16::tccraRegx) |= (mode & 0x03);
		*psfr8_t(TTIMER16::tccrbRegx) &= ~(3 << WGM12);
		*psfr8_t(TTIMER16::tccrbRegx) |= ((mode & 0x0c) << (WGM12 - 2));
	}
	
	
	// Main Timer/Counter
	//! \brief Read the timer register
	//! \details Reads the TCNTn register returning the 16 bit value
	inline uint16_t read () { return *psfr16_t(TTIMER16::tcntRegx); }


	//! \brief Write the timer register
	//! \details Write the TCNTn register with the supplied 16 bit value
	inline void write (uint16_t value) { *psfr16_t(TTIMER16::tcntRegx) = value; }


	//! \brief Enables the timer overflow interrupt
	//! \details Sets the overflow bit in the Interrupt Mask Register.  The
	//! overflow interrupt is generated when the value in the counter/timer overflow and
	//! in normal counter mode acts as a pseudo seventeenth bit.
	inline void enableOverflowInt () { _sbi (TTIMER16::timskRegx, TOIE1); }


	//! \brief Disables the timer overflow interrupt
	//! \details Clear the overflow bit in the Interrupt Mask Register
	inline void disableOverflowInt () { _cbi (TTIMER16::timskRegx, TOIE1); }


	//! \brief Clears the timer overflow interrupt status
	//! \details Clear the overflow bit in the Interrupt Status Register by setting
	//! to 1. Use when not the interrupt is not enabled
	inline void clearOverflow() { _sbi(TTIMER16::tifrRegx, TOV1); }

	
	//! \brief Gets the state of the overflow status bit
	//! \details Get the status of the overflow bit in the Interrupt Status Register.
	//! For use when not the interrupt is not enabled
	inline bool getOverFlow () { return bit_is_set (TTIMER16::tifrRegx, TOV1); }

	
	// Output Compare A
	//! \brief Set the compare/match mode for output A
	//! \details If mode is zero, then OCnA pin can be used for normal port
	//! operations, otherwise it will be used for the OCnA function.
	inline void setCompareAMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER16::tccraRegx) &= ~(3 << COM1A0);
		*psfr8_t(TTIMER16::tccraRegx) |= (mode << COM1A0);
	}


	//! \brief Set the output compare register A
	//! \details The output compare register contains an 16-bit value that is
	//! continuously compared to the counter value TCNTn. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OCnA pin.
	inline void writeCompareA (uint16_t value) { *psfr16_t(TTIMER16::ocraRegx) = value; }


	//! \brief Get the value of the output compare register A
	inline uint16_t readCompareA () { return *psfr16_t(TTIMER16::ocraRegx); }


	//! \brief Set the Force Compare A bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCRnA as TOP.
	inline void setForceCompareA () { _sbi (TTIMER16::tccrcRegx, FOC1A); }

	
	// Don't think this function will do anything as setForceCompareA is implemented as a strobe
	inline void clearForceCompareA () { _cbi (TTIMER16::tccrcRegx, FOC1A); }


	inline bool isCompareA () { return bit_is_set (TTIMER16::tifrRegx, OCF1A); }


	//! \brief Enables the Output Match A interrupt
	//! \details Sets the output match A interrupt bit in the Interrupt Mask Register.
	//! A output match interrupt is generated when the value in the counter/timer register matches
	//! the output compare register.
	inline void enableOutputMatchAInt () { _sbi (TTIMER16::timskRegx, OCIE1A); }


	//! \brief Disables the Output Match A interrupt
	//! \details Clears the output match A interrupt bit in the Interrupt Mask Register.
	inline void disableOutputMatchAInt () { _cbi (TTIMER16::timskRegx, OCIE1A); }


	//! \brief Clears the Output Match A interrupt status
	//! \details Clear the output match A bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearOutputMatchA() { _sbi(TTIMER16::tifrRegx, OCF1A); }


	// Output Compare B
	//! \brief Set the compare/match mode for output B
	//! \details If mode is zero, then OCnB pin can be used for normal port
	//! operations, otherwise it will be used for the OCnB function.
	inline void setCompareBMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER16::tccraRegx) &= ~(3 << COM1B0);
		*psfr8_t(TTIMER16::tccraRegx) |= (mode << COM1B0);
	}


	//! \brief Set the output compare register B
	//! \details The output compare register contains an 16-bit value that is
	//! continuously compared to the counter value TCNTn. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OCnB pin.
	inline void writeCompareB (uint16_t value) { *psfr16_t(TTIMER16::ocrbRegx) = value; }


	//! \brief Get the value of the output compare register B
	inline uint16_t readCompareB () { return *psfr16_t(TTIMER16::ocrbRegx); }


	//! \brief Set the Force Compare B bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCRnB as TOP.
	inline void setForceCompareB () { _sbi (TTIMER16::tccrcRegx, FOC1B); }


	// Don't think this function will do anything as setForceCompareB is implemented as a strobe
	inline void clearForceCompareB () { _cbi (TTIMER16::tccrcRegx, FOC1B); }


	inline bool isCompareB () { return bit_is_set (TTIMER16::tifrRegx, OCF1B); }


	//! \brief Enables the Output Match B interrupt
	//! \details Sets the output match B interrupt bit in the Interrupt Mask Register.
	//! A output match interrupt is generated when the value in the counter/timer register matches
	//! the output compare register.
	inline void enableOutputMatchBInt () { _sbi (TTIMER16::timskRegx, OCIE1B); }


	//! \brief Disables the Output Match B interrupt
	//! \details Clear the output match B interrupt bit in the Interrupt Mask Register.
	inline void disableOutputMatchBInt () { _cbi (TTIMER16::timskRegx, OCIE1B); }


	//! \brief Clears the Output Match B interrupt status
	//! \details Clear the output match B bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearOutputMatchB() { _sbi(TTIMER16::tifrRegx, OCF1B); }


	#ifdef COM1C0
	// Output Compare C
	//! \brief Set the compare/match mode for output C
	//! \details If mode is zero, then OCnC pin can be used for normal port
	//! operations, otherwise it will be used for the OCnC function.
	inline void setCompareCMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER16::tccraRegx) &= ~(3 << COM1C0);
		*psfr8_t(TTIMER16::tccraRegx) |= (mode << COM1C0);
	}


	//! \brief Set the output compare register C
	//! \details The output compare register contains an 16-bit value that is
	//! continuously compared to the counter value TCNTn. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OCnC pin.
	inline void writeCompareC (uint16_t value) { *psfr16_t(TTIMER16::ocrcRegx) = value; }


	//! \brief Get the value of the output compare register C
	inline uint16_t readCompareC () { return *psfr16_t(TTIMER16::ocrcRegx); }


	//! \brief Set the Force Compare C bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCRnC as TOP.
	inline void setForceCompareC () { _sbi (TTIMER16::tccrcRegx, FOC1C); }


	// Don't think this function will do anything as setForceCompareC is implemented as a strobe
	inline void clearForceCompareC () { _cbi (TTIMER16::tccrcRegx, FOC1C); }


	inline bool isCompareC () { return bit_is_set (TTIMER16::tifrRegx, OCF1C); }


	//! \brief Enables the Output Match C interrupt
	//! \details Sets the output match C interrupt bit in the Interrupt Mask Register.
	//! A output match interrupt is generated when the value in the counter/timer register matches
	//! the output compare register.
	inline void enableOutputMatchCInt () { _sbi (TTIMER16::timskRegx, OCIE1C); }


	//! \brief Enables the Output Match C interrupt
	//! \details Sets the output match C interrupt bit in the Interrupt Mask Register.
	inline void disableOutputMatchCInt () { _cbi (TTIMER16::timskRegx, OCIE1C); }

	
	//! \brief Clears the Output Match C interrupt status
	//! \details Clear the output match C bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearOutputMatchC() { _sbi(TTIMER16::tifrRegx, OCF1C); }
	#endif


	// Input Capture
	//! \brief Set the capture mode
	//! \param mode One of the capture mode enumerations - fall or rising edge
	//! \param noiseC If true the noise canceller will be activated
	inline void setCaptureMode (captureMode_t mode, bool noiseC=false)
	{
		uint8_t temp = (noiseC << ICNC1) | (mode << ICES1);
		*psfr8_t(TTIMER16::tccrbRegx) &= ~(3 << ICES1);
		*psfr8_t(TTIMER16::tccrbRegx) |= temp;
	}

	
	captureMode_t getCaptureMode() { return (captureMode_t) bit_is_set (TTIMER16::tccrbRegx, ICES1); }


	//! \brief Writes the input capture register
	inline void writeInputCapture(uint16_t value) { *psfr16_t(TTIMER16::icrRegx) = value; }


	//! \brief Reads the input capture register
	inline uint16_t readInputCapture () { return *psfr16_t(TTIMER16::icrRegx); }
	//		void setInputCaptureFilter(bool flag);


	//! \brief Enables the input capture interrupt
	//! \details Set the input capture interrupt bit in the Interrupt Mask Register
	inline void enableInputCaptureInt () { _sbi (TTIMER16::timskRegx, ICIE1); }


	//! \brief Disables the input capture interrupt
	//! \details Clears the input capture interrupt bit in the Interrupt Mark Register
	inline void disableInputCaptureInt () { _cbi (TTIMER16::timskRegx, ICIE1); }


	//! \brief Clears the Input Capture interrupt status
	//! \details Clear the input capture bit in the interrupt status register by setting
	//! to 1. Use when the interrupt is not enabled
	inline void clearInputCapture() { _sbi(TTIMER16::tifrRegx, ICF1); }

	//! \brief Operator overload that performs the same as the read method
	inline operator uint16_t() __attribute__((always_inline))
	{
		return read();
	}
	
	//! \brief An operator overload that performs the same as the write method
	inline Timer16& operator =(uint16_t value) __attribute__((always_inline))
	{
		write(value);
		return *this;
	}
};


#endif /* TIMER16_H_ */