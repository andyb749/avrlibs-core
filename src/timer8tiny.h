/*
 * timer8tiny.h
 *
 * Created: 20-Oct-2019 17:34:14
 *  Author: andyb
 */ 


#ifndef TIMER8TINY_H_
#define TIMER8TINY_H_


#include <stdint.h>
#include <avr/io.h>
#include <commondefs.h>
#include <timer8tinypriv.h>
#include <timerpriv.h>


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
		
	inline void setClockMode (uint8_t mode) __attribute__ ((always_inline))
	{
		*psfr8_t(TTIMER8::tccrbRegx) &= ~0x07;
		*psfr8_t(TTIMER8::tccrbRegx) |= mode;
	}

#if 0
	// not valid for timer0 for ATtiny861
	//! \brief Sets the waveform generator mode
	//! \param mode Set to one of the defined waveform generation modes
	inline void setWavegenMode (wavegenMode8_t mode) __attribute__ ((always_inline))
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~0x03;
		*psfr8_t(TTIMER8::tccraRegx) |= (mode & 0x03);
		*psfr8_t(TTIMER8::tccrbRegx) &= ~(1 << WGM02);
		*psfr8_t(TTIMER8::tccrbRegx) |= ((mode & 0x0c) << (WGM02 - WGM00));
	}
#endif

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

#if 0
	// not valid for ATtiny861 as no output pins
	// Output Compare A
	//! \brief Set the compare/match mode for output A
	//! \details If mode is zero, then OC0A pin can be used for normal port
	//! operations, otherwise it will be used for the OC0A function.
	inline void setCompareAMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~(3 << COM0A0);
		*psfr8_t(TTIMER8::tccraRegx) |= (mode << COM0A0);
	}
#endif

	//! \brief Set the output compare register A
	//! \details The output compare register contains an 8-bit value that is
	//! continuously compared to the counter value TCNT0. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OC0A pin.
	inline void writeCompareA (uint8_t value) { *psfr8_t(TTIMER8::ocraRegx) = value; }

	//! \brief Get the value of the output compare register A
	inline uint8_t readCompareA () { return *psfr8_t(TTIMER8::ocraRegx); }

#if 0
	// not valid for ATtiny861
	//! \brief Set the Force Compare A bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCR0A as TOP.
	inline void setForceCompareA () { _sbi (*psfr8_t(TTIMER8::tccrbRegx), FOC0A); }

	// Don't think this function will do anything as setForceCompareA is implemented as a strobe
	inline void clearForceCompareA () { _cbi (*psfr8_t(TTIMER8::tccrbRegx), FOC0A); }
#endif

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
	
#if 0
	// not valid for ATtiny861
	// Output Compare B
	//! \brief Set the compare/match mode for output B
	//! \details If mode is zero, then OC0B pin can be used for normal port
	//! operations, otherwise it will be used for the OC0B function.
	inline void setCompareBMode (compareMode_t mode)
	{
		*psfr8_t(TTIMER8::tccraRegx) &= ~(3 << COM0B0);
		*psfr8_t(TTIMER8::tccraRegx) |= (mode << COM0B0);
	}
#endif
	//! \brief Set the output compare register B
	//! \details The output compare register contains an 8-bit value that is
	//! continuously compared to the counter value TCNT0. A match can be used
	//! to generate an Output Compare interrupt, or to generate a waveform on
	//! the OC0B pin.
	inline void writeCompareB (uint8_t value) { *psfr8_t(TTIMER8::tccrbRegx) = value; }

	//! \brief Get the value of the output compare register B
	inline uint8_t readCompareB () { return *psfr8_t(TTIMER8::tccrbRegx); }

#if 0
	// not valid for ATtiny861
	// The ATtiny261/461/861 do not have a output match unit
	//! \brief Set the Force Compare B bit
	//! \details This bit is only active when the waveform generation bits specify a non PWM
	//! mode. When this method is called an immediate compare match is forced on the waveform
	//! generation unit.  The output pin is changed according to its setting.  This will not
	//! generate an interrupt nor will it clear the timer in CTC mode using OCR0B as TOP.
	inline void setForceCompareB () { _sbi (TTIMER8::tccrbRegx, FOC0B); }

	// Don't think this function will do anything as setForceCompareB is implemented as a strobe
	inline void clearForceCompareB () { _cbi (TTIMER8::tccrbRegx, FOC0B); }
#endif

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

#endif /* TIMER8TINY_H_ */