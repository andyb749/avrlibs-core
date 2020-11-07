//***************************************************************************
//
//  File Name :		SPISlaveUSI.h
//
//  Project :		SPI Slave library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Encapsulates the SPI Master functions using USI module on
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


#ifndef SPIUSISLAVE_H_
#define SPIUSISLAVE_H_


#include <avr/io.h>

class SpiSlave
{
	//variables
	public:
	protected:
	private:
		const spiModes_t spiMode;
		const spiOrder_t spiOrder;
		// The AVR sets up MISO as in input
		// We need to setup MOSI and SCK
		// We also need to make sure that SS is an output kept high before setting master mode
		// otherwise it falls back into slave mode
		FastIOInputPin<SSPIN> ss;
		FastIOInputPin<SCKPIN> sck;
		FastIOInputPin<MOSIPIN> mosi;
		FastIOOutputPin<MOSIPIN> miso;

	//functions
	public:
	SpiSlave(spiModes_t mode = SPI_MODE0, spiOrder_t order = SPI_MSBFIRST) : spiMode(mode), spiOrder(order)
	{
		#ifdef USE_ALTUSI
		USIPP = _BV(USIPOS);	// If defined, then the alternative USI pins (PORT A) are used
		#endif
		miso = false;

		USICR = (1<<USIWM0);	// Set SPI Mode
		USICR |= (2<<USICS0);	// Set the clock
		//		USICR &= ~(3<<USICS0);	// Set No clock (Software strobe)
		
	}
	
	uint8_t transfer (uint8_t data, bool setup=false)
	{
		ss = false;
		
		USIDR = data;		// pre-load the USI data register
		USISR &= ~_BV(USIOIF);	// clear the counter overflow flag

		// Repeat until the counter overflows
		while (bit_is_clear(USISR, USIOIF))
		{
			USICR = (1<<USIWM0) | (2<<USICS0) | _BV(USICLK) | _BV(USITC);
		}

		ss = true;
		return USIBR;
	}
	
	protected:
	private:
	SpiSlave( const SpiSlave &c );
	SpiSlave& operator=( const SpiSlave &c );

}; //spiSlave




#endif /* SPIUSISLAVE_H_ */