//***************************************************************************
//
//  File Name :		SPIMasterSPI.h
//
//  Project :		SPI Master library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Encapsulates the SPI Master functions on
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


#ifndef SPISPIMASTER_H_
#define SPISPIMASTER_H_

#include <avr/io.h>
#include <avr/cpufunc.h>


static const uint8_t modeVals[] =
{
	0x00,					//	SPI_MODE0
	_BV(CPHA),				//	SPI_MODE1
	_BV(CPOL),				//	SPI_MODE2
	_BV(CPOL) | _BV(CPHA)	//	SPI_MODE3
};

static const uint8_t dirVals[] =
{
	0x00,					// MSB First
	_BV(DORD)				// LSB First
};



//! \brief SPI Master utility class
//! \param mode One of the 4 SPI modes, SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
//! \param order One of the 2 SPI bit order modes, SPI_MSBFIRST or SPI_LSBFIRST
class SpiMaster 
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

	//functions
	public:
	//! \brief Initialises a new instance of the SPIMaster template class
	//! \details Initialises the SPI hardware and caches the desired SPI mode for later.
	//! The SPI mode is cached so that the user can request the SPI mode is set before
	//! every data exchange by calling the setMode() method.
	//SpiMaster(spiModes_t mode = SPI_MODE0, spiOrder_t order = SPI_MSBFIRST) : spiMode(mode), spiOrder(order)
	SpiMaster();


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
	uint8_t transfer (uint8_t data);

	void transfer (uint8_t * const txBuf, uint8_t * rxBuf, uint8_t count);

	//! \brief Exchanges a word of data
	//! \details Exchanges a 16 bit word of data with a slave.  The caller is responsible for setting
	//! up any slave select (SS) necessary.  The supplied data byte will be sent to the slave and the
	//! one received will be returned to the caller.
	//! \param data The data to transmit to the slave
	//! \param setup True to set the SPI mode prior to transmission; false otherwise.
	//! \returns The data received from the slave
	//! \note The data is transmitted MSB first when the data order bit is clear, and
	//! LSB first when the data order bit is set.  The byte ordering will also follow this ordering.
	uint16_t transfer16 (uint16_t data);


	//! \brief Exchanges blocks of data
	//! \details Exchanges a data block with a slave.  The data sent to by
	//! the slave is pointed to by inPtr, with outPtr pointing to a users'
	//! data location to store the data received by the slave.   Both
	//! areas are the same size - numBytes.
	//! \param inPtr Pointer to a data area to be sent to a slave
	//! \param outPtr Pointer to a data area for received bytes from a slave
	//! \param setup True to set the SPI mode prior to transmission; false otherwise.
	//! \param numBytes The size of each data block in bytes
	//! \note The data is transmitted MSB first when the data order bit is clear, and
	//! LSB first when the data order bit is set.
	void transferWithAddress(uint8_t addr, uint8_t * const txBuf, uint8_t * rxBuf, uint8_t count);	
	
	inline spiModes_t getMode () __attribute__((always_inline))
	{
		return (spiModes_t)((SPCR & (CPHA | CPOL)) >> CPHA);
	}

	// setup the SPI mode prior to a transfer
	inline spiModes_t setMode (spiModes_t mode)
	{
		spiModes_t savedMode = getMode();
		SPCR &= ~(_BV(CPOL) | _BV(CPHA));		// Clear the bits using the mask
		SPCR |=	modeVals[mode];					// Before setting them
		return savedMode;
	}

	protected:
	private:
		SpiMaster( const SpiMaster &c );
		SpiMaster& operator=( const SpiMaster &c );
		inline uint8_t transferOne (uint8_t data)
		{
			// Start transmission by sending the data
			SPDR = data;

			// Wait for the transmission to complete
			//asm volatile("nop");
			_NOP();
			loop_until_bit_is_set(SPSR, SPIF);

			// return the received byte
			return SPDR;
		}

}; //SpiMaster


#endif /* SPISPIMASTER_H_ */