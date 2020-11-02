//***************************************************************************
//
//  File Name :		SPIMasterUSI.h
//
//  Project :		SPI Master library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Encapsulates the SPI Master functions using the USI module on
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


#ifndef USISPIMASTER_H_
#define USISPIMASTER_H_

#include <avr/io.h>

//! \brief SPI Master utility class
//! \param mode One of the 4 SPI modes, SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
//! \param order One of the 2 SPI bit order modes, SPI_MSBFIRST or SPI_LSBFIRST
class SpiMaster 
//: public SpiMasterBase<mode, order>
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
		FastIOOutputPin<SSPIN> ss;
		FastIOOutputPin<SCKPIN> sck;
		FastIOOutputPin<MOSIPIN> mosi;
		FastIOInputPin<MOSIPIN> miso;
	//functions
	public:
	//! \brief Initialises a new instance of the SPIMaster template class
	//! \details Initialises the SPI hardware and caches the desired SPI mode for later.
	//! The SPI mode is cached so that the user can request the SPI mode is set before
	//! every data exchange by calling the setMode() method.
	SpiMaster(spiModes_t mode = SPI_MODE0, spiOrder_t order = SPI_MSBFIRST) : spiMode(mode), spiOrder(order)
	{
		#ifdef USE_ALTUSI
		USIPP = _BV(USIPOS);	// If defined, then the alternative USI pins (PORT A) are used
		#endif
		// TODO: SPI for USI
		sck = false;
		mosi = false;
		ss = true;

		USICR = (1<<USIWM0);	// Set SPI Mode
		USICR |= (2<<USICS0);	// Set the clock
//		USICR &= ~(3<<USICS0);	// Set No clock (Software strobe)
		
	}


	//! \brief Exchanges a single byte of data
	//! \details Exchanges a single byte of data with a slave.  The caller is
	//! responsible for setting up any slave select (SS) necessary. The supplied
	//! data byte will be sent to the slave and the one received from the slave
	//! will be returned to the caller.
	//! \param data The data to transmit to the slave
	//! \param setup True to set the SPI mode prior to transmission; false otherwise.
	//! \returns The data received from the slave
	//! \note The data is transmitted MSB first when the data order bit is clear, and
	//! LSB first when the data order bit is set.
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
	SpiMaster( const SpiMaster &c );
	SpiMaster& operator=( const SpiMaster &c );


	// setup the SPI mode prior to a transfer
	inline void setMode ()
	{
		//SPCR &= ~(_BV(DORD) | _BV(CPOL) | _BV(CPHA));	// Clear the bits using the mask
		//SPCR |=
		//(modeVals[this->spiMode] | dirVals[this->spiOrder]);		// Before setting them
	}

}; //SpiMaster


#endif /* USISPIMASTER_H_ */