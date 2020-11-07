//***************************************************************************
//
//  File Name :		FastIOPin.h
//
//  Project :		FastIO library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Fast access to the general purpose IO ports on
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


#ifndef FASTIOPIN_H_
#define FASTIOPIN_H_


#ifndef FASTIO_H_
#error "Do not include FastIOPin.h, use FastIO.h"
#endif

#include <avr/io.h>
#undef bit
//const uint8_t NO_FASTIOPIN = 255;


//! \brief A class representing a single input or output pin
//! \details Declare a object as follows:
//! FastIOPin<FASTIOPIN_B13> led;
template <uint8_t TPIN>
class FastIOPin
{
	// A digital input/output with direct port I/O
	public:
	//! \brief Initialises a new instance of the FastIOPin object
	//! \details Initialises a new pin by setting initially creating an
	//! input pin.  The direction can be changed by using setOutputMode()
	//! and the pullups can be enabled/disabled by calling enablePullups()
	//! disablePullups()
	//inline FastIOPin(bool initValue=LOW) __attribute__ ((always_inline))
	inline FastIOPin() __attribute__ ((always_inline))
	{
	}

	//! \brief Set the pin direction as output
	inline void setOutputMode () __attribute__((always_inline))
	{
		*port_t(_pins<TPIN>::ddrx) |= _pins<TPIN>::mask;
	}

	//! \brief Set the pin direction as input
	inline void setInputMode () __attribute__((always_inline))
	{
		*port_t(_pins<TPIN>::ddrx) &=  ~_pins<TPIN>::mask;
	}


	//! \brief Writes the boolean value to the output pin
	//! \param value The value that should be written to the pin
	//! \details In output mode, this method will write the supplied value
	//! to the pin.  In input mode, this method will enable or disable the pullup
	//! resistors.
	inline void write(bool value) __attribute__ ((always_inline))
	{
		if (value)
			set();
		else
			clear();
	}
	

	//! \brief Sets the output pin - makes it high
	//! \details In output mode, this will set the pin high
	//! In input mode, enables the pullup resistors
	inline void set() __attribute__ ((always_inline))
	{
		*port_t(_pins<TPIN>::portx) |= _pins<TPIN>::mask;
	}


	//! \brief Clears the output pin - makes it low
	//! \details In output mode, this sets the pin low
	//! In input mode, disables the pullup resistors
	inline void clear() __attribute__ ((always_inline))
	{
		*port_t(_pins<TPIN>::portx) &= ~_pins<TPIN>::mask;
	}
	
	
	//! \brief Toggle the output pin
	//! \details Uses the PINx register to toggle the pin
	inline void toggle() __attribute__ ((always_inline))
	{
		*port_t(_pins<TPIN>::pinx) |= _pins<TPIN>::mask;
	}
	

	//! \brief Reads the current value of the output pin
	//! \returns The current value of the output pin, true if high; false if low
	//! \details This method will always return the value of the pin
	inline bool read() __attribute__ ((always_inline))
	{
		return *port_t(_pins<TPIN>::pinx) & _pins<TPIN>::mask;
	}
	

	//! \brief Gets a value which will set the output \b PORT high
	//! \description Gets a value by reading the port and OR'ing in
	//! the mask so that when the value is written back to the port
	//! the pin that this class represents will be written high
	//! \returns A value to write the pin high
	inline uint8_t getHigh() __attribute__((always_inline))
	{
		return *port_t(_pins<TPIN>::portx) | _pins<TPIN>::mask;
	}


	//! \brief Gets a value which will set the output \b PORT low
	//! \description Gets a value by reading the port and AND'ing in
	//! the mask so that when the value is written back to the port
	//! the pin that this class represents will be written low
	//! \returns A value to write the pin low
	inline uint8_t getLow() __attribute__((always_inline))
	{
		return *port_t(_pins<TPIN>::portx) & ~_pins<TPIN>::mask;
	}


	//! \brief Writes a value to the output \b PORT
	//! \description This method will allow a caller to write to the entire
	//! output port.  Use in conjuction with \sa getHigh() and \sa getLow()
	//! \param value The value to be written to the PORT register.
	inline void writePort (uint8_t value) __attribute__((always_inline))
	{
		*port_t(_pins<TPIN>::portx) = value;
	}


	//! \brief Reads the entire PORT
	//! \description This method will allow a caller to read the entire
	//! PORT.
	//! \returns The current value of the PORT register
	inline uint8_t readPort () __attribute__((always_inline))
	{
		return *port_t(_pins<TPIN>::portx);
	}


	//! \brief Gets the mask for this pin.
	//! \description Returns the mask for this pin.   Example: if pin is 6, then mask is 2^6 = 64
	//! \returns The mask for this pin instance
	inline uint8_t mask () __attribute__((always_inline))
	{
		return _pins<TPIN>::mask;
	}

	//! \brief Gets the port address for this pin
	//! \description Returns the port address for this pin.
	//! \returns The port address for this pin instance
	inline uint16_t portAddr () __attribute__((always_inline))
	{
		return _pins<TPIN>::portx;
	}
	
	
	//! \brief Gets the bit for this pin
	//! \description Returns the bit for this pin
	//! \returns The bit number for this pin instance
	inline uint8_t bit () __attribute__((always_inline))
	{
		return _pins<TPIN>::bit;
	}
	
	////////////
	// operators

	//! \brief An operator overload that performs the same as the write method
	inline FastIOPin& operator =(bool value)  __attribute__ ((always_inline))
	{
		write(value);
		return *this;
	}
	
	//! \brief Operator overload that performs the same as the read method
	inline operator bool()  __attribute__ ((always_inline))
	{
		return read();
	}
};


//! \brief A class representing a single output pin
//! \details A class representing a single output pin.  To use, declare a object as follows:
//! \code
//! FastIOOutputPin<FASTIOPIN_B7> led;
//! \endcode
//! \tparam TPIN One of the pre-defined FASTIOPIN_xn structures
template <uint8_t TPIN>
class FastIOOutputPin : public FastIOPin<TPIN>
{
	public:
	//! \brief Initialises a new instance of the FastIOOutputPin object
	//! \details Initialises a new output pin by setting
	//! the data direction pin and writing the initial value
	inline FastIOOutputPin(bool initValue=false) __attribute__ ((always_inline))
	//inline FastIOOutputPin() __attribute__ ((always_inline))
	{
		this->setOutputMode();
		this->write(initValue);
	}
	
	////////////
	// operators

	//! \brief An operator overload that performs the same as the write method
	inline FastIOOutputPin& operator =(bool value)  __attribute__ ((always_inline))
	{
		this->write(value);
		return *this;
	}
	
};


//! \brief A class describing an single input pint
//! \details A class to describe a single input pin.  To use, declare a object as follows:
//! \code
//! FastIOInputPin<FASTIOPIN_B0> button;
//! \endcode
//! \tparam TPIN One of the pre-defined FASTIOPIN_xn structures
template <uint8_t TPIN>
class FastIOInputPin : public FastIOPin<TPIN>
{
	public:
	//! \brief Initialises a new instance of the FastIOInputPin class
	//! \details The FastIOInputPin class is for use with a single input pin
	//! and can optionally set pullups
	//! \param pullup Set true to enable the pullup resistor
	inline FastIOInputPin(bool pullup=false) __attribute__ ((always_inline))
//	inline FastIOInputPin() __attribute__ ((always_inline))
	{
		this->setInputMode();
		setPullups(pullup);
	}

	//! \brief Sets the pullups to the supplied value
	//! \param pullup Set true to enable the pullup resistor
	inline void setPullups(bool value) __attribute__((always_inline))
	{
		if (value)
			enablePullups();
		else
			disablePullups();
	}

	//! \brief Enables the pullup resistors
	inline void enablePullups() __attribute__((always_inline))
	{
		*port_t(_pins<TPIN>::portx) |= _pins<TPIN>::mask;
	}

	//! \brief Disables the pullup resistors
	inline void disablePullups() __attribute__((always_inline))
	{
		*port_t(_pins<TPIN>::portx) &= ~_pins<TPIN>::mask;
	}
};



#endif /* FASTIOPIN_H_ */