//***************************************************************************
//
//  File Name :		FastIOPort.h
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


#ifndef FASTIOPORT_H_
#define FASTIOPORT_H_


#ifndef FASTIO_H_
#error "Do not include FastIOPort.h, use FastIO.h"
#endif


// Some helper macros
//#define _readBit(value, bit) (((value) >> (bit)) & 0x01)
#define _setBit(value, bit) ((value) |= _BV(bit))
#define _clearBit(value, bit) ((value) &= ~_BV(bit))
#define _writeBit(value, bit, bitvalue) (bitvalue ? _setBit(value, bit) : _clearBit(value, bit))


//! \brief A class to represent one of more bits in an eight bit input port
//! \brief The startBit and numBit parameters specify the starting order and
//! number of bits.
//! \note The bits are contiguous in the port
template <class port, uint8_t startBit=0, uint8_t numBits=8>
class FastIOInputPort
{

	public:
	//! \brief Initialises a new instance of the FastIOInputPort class
	inline FastIOInputPort(bool pullup=true)  __attribute__ ((always_inline))
	{
		*port_t(port::ddrx) &= (~mask);			// set pins as input
		*port_t(port::portx) &= (~mask);		// clear pullups
		if (pullup)
		enablePullups();
	}

	//! \brief Reads the bits of the input port
	//! \details The input port is read and a mask is applied before
	//! shifting the bits right
	//! \returns An uint8_t value representing the bits
	inline uint8_t read() __attribute__ ((always_inline))
	{
		return (*port_t(port::pinx) & mask) >> startBit;
	}
	

	//! \brief An operator overload that returns the input port
	//! \details Performs the same as the read method
	inline operator uint8_t() __attribute__ ((always_inline))
	{
		return read();
	}

	inline void enablePullups ()
	{
		*port_t(port::portx) |= mask;		// set pullups as necessary
	}

	//private:
	static const uint8_t mask = ((uint8_t(1) << numBits) - 1) << startBit;
};


//! \brief A class to represent one of more bits of an eight bit output port
//! \brief The startBit and numBit parameters specify the starting order and
//! number of bits.
//! \note The bits are contiguous in the port
template <class port, uint8_t startBit=0, uint8_t numBits=8>
class FastIOOutputPort
{
	public:
	//! \brief Initialises a new instance of the FastIOOutputPort class
	inline FastIOOutputPort() __attribute__ ((always_inline))
	{
		// set port pin directions to output
		*port_t(port::ddrx) |= mask;
	}

	//! \brief Write the supplied value to the output port
	inline void write(uint8_t value) __attribute__ ((always_inline))
	{
		uint8_t v = *port_t(port::portx);
		uint8_t shifted = value << startBit;
		v |= shifted & mask;
		v &= (shifted | ~mask);
		*port_t(port::portx) = v;
	}
	

	//! \brief An operator overload that performs the same as the write method
	inline FastIOOutputPort& operator =(uint8_t value) __attribute__ ((always_inline))
	{
		write(value);
		return *this;
	}


	//! \brief Returns the current value of the output port
	inline uint8_t read() __attribute__ ((always_inline))
	{
		return (*port_t(port::pinx) & mask) >> startBit;
	}


	//! \brief An operator overload that performs the same as the read method
	inline operator uint8_t() __attribute__ ((always_inline))
	{
		return read();
	}

	private:
	static const uint8_t mask = ((uint8_t(1) << numBits) - 1) << startBit;
};


//! \brief A special case for the output port where all 8 pins are used
template <class port>
class FastIOOutputPort<port, 0, 8>
{
	public:
	//! \brief Initialises a new instance of the FastIOOutputPort object
	inline FastIOOutputPort() __attribute__ ((always_inline))
	{
		// set port pin directions to output
		*port_t(port::ddrx) = 0xFF;
	}

	//! \brief Sets the output pins to the value supplied
	//! \param value The value to write to the port pins
	inline void write(uint8_t value) __attribute__ ((always_inline))
	{
		*port_t(port::portx) = value;
	}

	//! \brief An operator overload than performs the same as the write method
	inline FastIOOutputPort& operator =(uint8_t value) __attribute__ ((always_inline))
	{
		write(value);
		return *this;
	}

	//! \brief Returns the value of the data port
	//! \returns The value of the data port
	inline uint8_t read() __attribute__ ((always_inline))
	{
		return *port_t(port::pinx);
	}

	//! \brief An operator overload that performs the same as the read method
	inline operator uint8_t() __attribute__ ((always_inline))
	{
		return read();
	}
	
	//! \brief Sets the specified bit to the supplied value
	//! \param bit The bit number to write to
	//! \param value The value to write to the pin
	inline void writeBit (uint8_t bit, bool value) __attribute__ ((always_inline))
	{
		_writeBit(*port_t(port::portx), bit, value);
	}
	
	//! \brief Sets the specified bit
	//! \param bit The bit number to write to
	inline void setBit (uint8_t bit) __attribute__ ((always_inline))
	{
		_setBit(*port_t(port::portx), bit);
	}
	
	//! \brief Clears the specified bit
	//! \param bit The bit number to write to
	inline void clearBit (uint8_t bit) __attribute__ ((always_inline))
	{
		_clearBit(*port_t(port::portx), bit);
	}
	
	//! \brief Toggles the specified bit
	//! \param bit The bit number to toggle
	inline void toggle(uint8_t bit) __attribute__ ((always_inline))
	{
		_setBit(*port_t(port::pinx), bit);
	}

};


#endif /* FASTIOPORT_H_ */