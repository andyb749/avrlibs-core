//***************************************************************************
//
//  File Name :		TimerPriv.h
//
//  Project :		Timer objects for the Atmel 8 bit AVR MCU
//
//  Purpose :		Fast access to the general purpose IO ports on
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

#ifndef TIMERPRIV_H_
#define TIMERPRIV_H_


#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
	// These tiny devices only have one timer, so the name of the registers changes :-(
	#define TIFR0	TIFR
	#define TIMSK0	TIMSK
#endif

// Clocking modes for timers 0, 1, 3, 4, 5
// Do not re-order these as they match the register bit order
//! \brief Enumeration of the clock mode sources
//! \details The counter/timer modules can be clocked from a number of sources. The
//! enumeration below details the various sources.
//! \notes Only validated for Mega2560, Mega1284, Mega644, Mega328, AT90CAN
typedef enum 
{
	//! \brief No clock source - the timer is disabled
	ClkNoSource,		// No clock source

	//! \brief Use the system clock - no prescaler
	ClkPre1,			// System clock 1 prescale

	//! \brief Use the system clock with a divide by 8 prescaler
	ClkPre8,			// System clock 8 prescale

	//! \brief Use the system clock with a divide by 64 prescaler
	ClkPre64,			// System clock 64 prescale

	//! \brief Use the system clock with a divide by 256 prescaler
	ClkPre256,			// System clock 256 prescale

	//! \brief Use the system clock with a divide by 1024 prescaler
	ClkPre1024,			// System clock 1024 prescale

	//! \brief Use the external Tn pin with a falling edge
	ClkExtFall,			// External clocking by pin Tn falling edge

	//! \brief Use the external Tn pin with a rising edge
	ClkExtRise,			// External clocking by pin Tn rising edge
} clockMode_t;


// Clocking modes for timers 2
// Do not re-order these as they match the register bit order
//! \brief Enumeration of the clock mode sources
//! \details The counter/timer modules can be clocked from a number of sources. The
//! enumeration below details the various sources.
//! \notes Validated for Mega2560, Mega1284, Mega644, Mega328 and AT90CAN Timer 2
typedef enum 
{
	//! \brief No clock source - the timer is disabled
	ClkT2NoSource,		// No clock source

	//! \brief Use the timer 2 clock - no prescaler
	ClkT2Pre1,			// System clock 1 prescale

	//! \brief Use the timer 2 clock with a divide by 8 prescaler
	ClkT2Pre8,			// System clock 8 prescale

	//! \brief Use the timer 2 clock with a divice by 32 prescaler
	ClkT2Pre32,

	//! \brief Use the timer 2 clock with a divide by 64 prescaler
	ClkT2Pre64,			// System clock 64 prescale

	//! \brief Use the timer 2 clock with a divive by 128 prescaler
	ClkT2Pre128,

	//! \brief Use the timer 2 clock with a divide by 256 prescaler
	ClkT2Pre256,			// System clock 256 prescale

	//! \brief Use the timer 2 clock with a divide by 1024 prescaler
	ClkT2Pre1024,			// System clock 1024 prescale
} clockModeT2_t;


// Definition of the various wave generation modes
// Do not re-order these as they match the register bit order
//! \brief Enumeration of the various wave generation modes
//! \details Each output compare pin can be individually set.
//! In the descriptions below, BOTTOM always means the counter
//! reaches the BOTTOM when it becomes 0x00. The counter reaches
//! it MAXimum when it becomes 0xff. The counter reaches the TOP
//! when it becomes equal to the highest value in the count sequence.
//! The top value can be assigned to be the fixed value of 0xff (MAX)
//! or the value stored in the OCR0A register. This assignment is
//! dependent on the mode of operation.
typedef enum
{
	//! \brief Normal Mode
	//! \detail In normal mode the counting mode is always up and no counter
	//! clear is performed. The counter simply overruns when the it passes the
	//! the maximum 8 bit value (TOP=0xff) and then restarts from the BOTTOM (0x00).
	//! The output compare unit can still be used to generate interrupts at some point.
	WgenTinyNormal8,		// Normal 8 bit mode - 0

	//! \brief Clear Timer on Compare Match
	//! \detail In CTC mode, the OCR0A register is used to manipulate the counter
	//! resolution.  In CTC mode the counter is cleared to zero when the counter value
	//! matches the output compare A register.  The output compare A register defines
	//! the top value for the counter, hence also the resolution. This mode allows greater
	//! control of the compare match output frequency. It also simplifies the operation of
	//! counting external events.
	//! An interrupt can be enabled for each compare match.
	WgenTinyCtcO,			// Clear timer on compare Output Compare - 1

	//! \brief Normal Mode
	//! \detail In normal mode the counting mode is always up and no counter
	//! clear is performed. The counter simply overruns when the it passes the
	//! the maximum 16 bit value (TOP=0xffff) and then restarts from the BOTTOM (0x00).
	//! The output compare unit can still be used to generate interrupts at some point.
	WgenTinyNormal16,		// Normal 16 bit mode - 2

	//! \brief Reserved - do not use
	WgenTinyReserved1,		// Reserved - this will do the same as WgenTinyNormal16- 3

	//! \brief Input Capture Mode 8 bit
	WgenTinyCapture8,		// Input capture mode, 8 bit - 4

	WgenTinyReserved2,		// Reserved - this will do the same as WgenTinyCapture8 - 5

	WgenTinyCapture16,		// Input capture mode, 16 bit - 6

	WgenTinyReserved3,		// Reserved - this will do the same as WgenTinyCapture16 - 7
} wavegenTiny_t;


// Definition of the various wave generation modes
// Do not re-order these as they match the register bit order
//! \brief Enumeration of the various wave generation modes
//! \details Each output compare pin can be individually set.
//! In the descriptions below, BOTTOM always means the counter
//! reaches the BOTTOM when it becomes 0x00. The counter reaches
//! it MAXimum when it becomes 0xff. The counter reaches the TOP
//! when it becomes equal to the highest value in the count sequence.
//! The top value can be assigned to be the fixed value of 0xff (MAX)
//! or the value stored in the OCR0A register. This assignment is 
//! dependent on the mode of operation.
typedef enum 
{
	//! \brief Normal Mode
	//! \detail In normal mode the counting mode is always up and no counter
	//! clear is performed. The counter simply overruns when the it passes the
	//! the maximum 8 bit value (TOP=0xff) and then restarts from the BOTTOM (0x00).
	//! The output compare unit can still be used to generate interrupts at some point.
	Wgen8Normal,			// Normal mode - 0

	//! \brief PWM 8 bit Phase Correct Mode
	//! \detail In PWM 8 bit Phase Correct Mode, the counter is dual slope with
	//! the counter counting up from BOTTOM to TOP and back to BOTTOM.  The output is
	//! changed when the count matches OCR0A or OCR0B.
	Wgen8PwmPhase8,			// PWM Phase correct 8 bit - 1
	
	//! \brief Clear Timer on Compare Match
	//! \detail In CTC mode, the OCR0A register is used to manipulate the counter
	//! resolution.  In CTC mode the counter is cleared to zero when the counter value
	//! matches the output compare A register.  The output compare A register defines
	//! the top value for the counter, hence also the resolution. This mode allows greater
	//! control of the compare match output frequency. It also simplifies the operation of
	//! counting external events.
	//! An interrupt can be enabled for each compare match.
	Wgen8CtcO,				// Clear timer on compare Output Compare - 2

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform 
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM. 
	//! TOP is defined as 0xff when in fast PWM mode, and as OCR0A when in fast PWM mode with 
	//! capture. In non inverting compare output mode, the output compare  is cleared on the
	//! compare match between TCNT0 and OCR0x and set at BOTTOM. In inverting compare mode, the
	//! output is set on compare match and cleared at BOTTOM. Due to the single slope operation
	//! the operating frequency of the fast PWM can be twice at fast as the phase correct PWM
	//! mode that uses dual slope operation. This high frequency makes the fast PWM mode well
	//! suited for power regulation, rectification and DAC applications. High frequency allows
	//! physically small sized external components (coils, capacitors) and therefore reduces
	//! total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle 
	Wgen8FastPwm8,			// Fast PWM 8 bit - 3

	//! \brief Reserved - do not use
	Wgen8Reserved1,			// Reserved - do not use - 4

	//! \brief The PWM Phase Correct Output Capture
	//! \detail The PWM Phase Correct Output Capture Mode is similar to Wgen8Phase8 mode except that the
	//! counter counts from BOTTOM to OCRnA and down to BOTTOM.  This means that the frequency can 
	//! be defined with greater definition, however only OCRnB can be used to generate a usable PWM waveform.
	Wgen8PwmPhaseO,			// PWM Phase correct Output Compare - 5

	//! \brief Reserved - do not use
	Wgen8Reserved2,			// Reserved - do not use - 6

	//! \brief The Fast PWM Output Mode
	//! \detail The Fast PWM Output Capture Mode is similar to Wgen8FastPWM mode except that the
	//! counter counter from BOTTOM to OCR0A.  This means that the frequency can be defined with
	//! greater definition, however only OCR0B can be used to generate a usuable PWM waveform.
	Wgen8FastPwmO,			// Fast PWM Output capture - 7
} wavegenMode8_t;


// Definition of the various wave generation modes
// Do not re-order these as they match the register bit order
//! \brief Enumeration of the various wave generation modes
//! \details Each output compare pin can be individually set.
//! In the descriptions below, BOTTOM always means the counter
//! reaches the BOTTOM when it becomes 0x00. The counter reaches
//! it MAXimum when it becomes 0xff. The counter reaches the TOP
//! when it becomes equal to the highest value in the count sequence.
//! The top value can be assigned to be the fixed value of 0xffff (MAX)
//! or the value stored in the OCRnA register. This assignment is
//! dependent on the mode of operation.
typedef enum 
{
	//! \brief Normal Mode
	//! \detail In normal mode the counting mode is always up and no counter
	//! clear is performed. The counter simply overruns when the it passes the
	//! the maximum 16 bit value (TOP=0xffff) and then restarts from the BOTTOM (0x00).
	//! The output compare unit can still be used to generate interrupts at some point.
	Wgen16Normal,			// Normal mode

	//! \brief PWM 8 bit Phase Correct Mode
	//! \detail In PWM 8 bit Phase Correct Mode, the counter is dual slope with
	//! the counter counting up from BOTTOM to TOP and back to BOTTOM.  The output is
	//! changed when the count matches OCRnA or OCRnB.
	Wgen16PwmPhase8,		// PWM Phase correct 8 bit

	//! \brief PWM 9 bit Phase Correct Mode
	//! \detail In PWM 9 bit Phase Correct Mode, the counter is dual slope with
	//! the counter counting up from BOTTOM to TOP and back to BOTTOM.  The output is
	//! changed when the count matches OCRnA or OCRnB.
	Wgen16PwmPhase9,		// PWM Phase correct 9 bit

	//! \brief PWM 10 bit Phase Correct Mode
	//! \detail In PWM 10 bit Phase Correct Mode, the counter is dual slope with
	//! the counter counting up from BOTTOM to TOP and back to BOTTOM.  The output is
	//! changed when the count matches OCRnA or OCRnB.
	Wgen16PwmPhase10,		// PWM Phase correct 10 bit

	//! \brief Clear Timer on Compare Match
	//! \detail In CTC mode, the OCRnA register is used to manipulate the counter
	//! resolution.  In CTC mode the counter is cleared to zero when the counter value
	//! matches the output compare A register.  The output compare A register defines
	//! the top value for the counter, hence also the resolution. This mode allows greater
	//! control of the compare match output frequency. It also simplifies the operation of
	//! counting external events.
	//! An interrupt can be enabled for each compare match.
	Wgen16CtcO,				// Clear timer on compare Output Compare

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM.
	//! TOP is defined as 0xff (8 bit), 0x1ff (9 bit) or 0x3ff (10 bit) when in fast PWM mode, 
	//! and as OCRnA when in fast PWM mode with capture or ICRn when in fast mode with input
	//! capture. In non inverting compare output mode, 
	//! the output compare  is cleared on the compare match between TCNT0 and OCR0x and set at 
	//! BOTTOM. In inverting compare mode, the output is set on compare match and cleared at 
	//! BOTTOM. Due to the single slope operation the operating frequency of the fast PWM can 
	//! be twice at fast as the phase correct PWM mode that uses dual slope operation. This 
	//! high frequency makes the fast PWM mode well suited for power regulation, rectification 
	//! and DAC applications. High frequency allows physically small sized external components 
	//!(coils, capacitors) and therefore reduces total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle
	Wgen16FastPwm8,			// Fast PWM 8 bit

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM.
	//! TOP is defined as 0xff (8 bit), 0x1ff (9 bit) or 0x3ff (10 bit) when in fast PWM mode,
	//! and as OCRnA when in fast PWM mode with capture or ICRn when in fast mode with input
	//! capture. In non inverting compare output mode,
	//! the output compare  is cleared on the compare match between TCNT0 and OCR0x and set at
	//! BOTTOM. In inverting compare mode, the output is set on compare match and cleared at
	//! BOTTOM. Due to the single slope operation the operating frequency of the fast PWM can
	//! be twice at fast as the phase correct PWM mode that uses dual slope operation. This
	//! high frequency makes the fast PWM mode well suited for power regulation, rectification
	//! and DAC applications. High frequency allows physically small sized external components
	//!(coils, capacitors) and therefore reduces total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle
	Wgen16FastPwm9,			// Fast PWM 9 bit

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM.
	//! TOP is defined as 0xff (8 bit), 0x1ff (9 bit) or 0x3ff (10 bit) when in fast PWM mode,
	//! and as OCRnA when in fast PWM mode with capture or ICRn when in fast mode with input
	//! capture. In non inverting compare output mode,
	//! the output compare  is cleared on the compare match between TCNT0 and OCR0x and set at
	//! BOTTOM. In inverting compare mode, the output is set on compare match and cleared at
	//! BOTTOM. Due to the single slope operation the operating frequency of the fast PWM can
	//! be twice at fast as the phase correct PWM mode that uses dual slope operation. This
	//! high frequency makes the fast PWM mode well suited for power regulation, rectification
	//! and DAC applications. High frequency allows physically small sized external components
	//!(coils, capacitors) and therefore reduces total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle
	Wgen16FastPwm10,		// Fast PWM 10 bit

	//! \brief PWM Phase and frequency correct Input Capture
	//! \details This mode is similiar to the PWM Phase correct input capture mode except
	//! that the loading of OCRxA and ICRx are always at BOTTOM so the rising and falling slopes
	//! are always equal giving symmetrical output pulses
	Wgen16PwmPhaseFreqI,	// PWM Phase and frequency correct Input Capture

	//! \brief PWM Phase and frequency correct Output Compare
	//! \details This mode is similiar to the PWM Phase correct input capture mode except
	//! that the loading of OCRxA and ICRx are always at BOTTOM so the rising and falling slopes
	//! are always equal giving symmetrical output pulses
	Wgen16PwmPhaseFreqO,	// PWM Phase and frequency correct Output Compare

	//! \brief The PWM Phase Correct Input Capture
	//! \detail The PWM Phase Correct Input Capture Mode is similar to Wgen16Phase8 mode except that the
	//! counter counts from BOTTOM to ICRn and down to BOTTOM.  This means that the frequency can
	//! be defined with greater definition.
	Wgen16PwmPhaseI,		// PWM Phase correct Input Capture

	//! \brief The PWM Phase Correct Output Capture
	//! \detail The PWM Phase Correct Output Capture Mode is similar to Wgen16Phase8 mode except that the
	//! counter counts from BOTTOM to OCRnA and down to BOTTOM.  This means that the frequency can
	//! be defined with greater definition, however only OCRnB can be used to generate a usable PWM waveform.
	Wgen16PwmPhaseO,		// PWM Phase correct Output Compare

	//! \brief Clear Timer on Compare Match
	//! \detail In CTC mode, the ICRn register is used to manipulate the counter
	//! resolution.  In CTC mode the counter is cleared to zero when the counter value
	//! matches the output compare A register.  The input compare register defines
	//! the top value for the counter, hence also the resolution. This mode allows greater
	//! control of the compare match output frequency. It also simplifies the operation of
	//! counting external events.
	//! An interrupt can be enabled for each compare match.
	Wgen16CtcI,				// Clear timer on compare Input Capture

	//! \brief Reserved
	Wgen16Reserved,			// Reserved

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM.
	//! TOP is defined as 0xff (8 bit), 0x1ff (9 bit) or 0x3ff (10 bit) when in fast PWM mode,
	//! and as OCRnA when in fast PWM mode with capture or ICRn when in fast mode with input
	//! capture. In non inverting compare output mode,
	//! the output compare  is cleared on the compare match between TCNT0 and OCR0x and set at
	//! BOTTOM. In inverting compare mode, the output is set on compare match and cleared at
	//! BOTTOM. Due to the single slope operation the operating frequency of the fast PWM can
	//! be twice at fast as the phase correct PWM mode that uses dual slope operation. This
	//! high frequency makes the fast PWM mode well suited for power regulation, rectification
	//! and DAC applications. High frequency allows physically small sized external components
	//!(coils, capacitors) and therefore reduces total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle
	Wgen16FastPwmI,			// Fast PWM Input Capture

	//! \brief Fast PWM Mode
	//! \detail The fast pulse width modulation mode provides a high frequency PWM waveform
	//! generation option. The fast PWM differs from the other PWM option by its single
	//! slope operation. The counter counts from BOTTOM to TOP then restarts from BOTTOM.
	//! TOP is defined as 0xff (8 bit), 0x1ff (9 bit) or 0x3ff (10 bit) when in fast PWM mode,
	//! and as OCRnA when in fast PWM mode with capture or ICRn when in fast mode with input
	//! capture. In non inverting compare output mode,
	//! the output compare  is cleared on the compare match between TCNT0 and OCR0x and set at
	//! BOTTOM. In inverting compare mode, the output is set on compare match and cleared at
	//! BOTTOM. Due to the single slope operation the operating frequency of the fast PWM can
	//! be twice at fast as the phase correct PWM mode that uses dual slope operation. This
	//! high frequency makes the fast PWM mode well suited for power regulation, rectification
	//! and DAC applications. High frequency allows physically small sized external components
	//!(coils, capacitors) and therefore reduces total system cost.
	//! In fast PWM mode, the counter is incremented until the counter value matches the TOP
	//! value. The counter is then cleared at the following clock cycle
	Wgen16FastPwmO,			// Fast PWM Output capture
} wavegenMode16_t;


// Definition of the compare modes
// Do not re-order these as they match the register bit order
// Explanations are for non PWM mode. Fast PWM and other modes similar
//! \brief Enumeration of the compare modes
typedef enum 
{
	//! \brief Normal port operation - OCnA/OCnB/OCnC disconnected
	CmpNormal,			// Normal port operation, OCnA/OCnB/OCnC disconnected

	//! \brief Toggle OCnA/OCnB/OCnC on compare match
	CmpToggle,			// Toggle OCnA/OCnB/OCnC on compare match

	//! \brief Clear OCnA/OCnB/OCnC on compare match - non inverting mode in PWM modes
	CmpClear,			// Clear OCnA/OCnB/OCnC on compare match - non inverting mode in PWM modes

	//! \brief Set OCnA/OCnB/OCnC on compare match - non inverting mode in PWM modes
	CmpSet,				// Set OCnA/OCnB/OCnC on compare match - inverting mode in Fast PWM modes
} compareMode_t;


// Definition of input capture modes
// Do not re-order as they match the register bit order
//! \brief Enumeration of the Capture Input Modes
typedef enum 
{
	//! \brief Capture on the falling edge
	Fall,				// Falling edge

	//! \brief Capture on the rising edge
	Rise,				// Rising edge
} captureMode_t;


#endif /* TIMERPRIV_H_ */