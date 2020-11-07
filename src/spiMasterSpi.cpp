//***************************************************************************
//
//  File Name :		SPIMasterSPI.cpp
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


#include "spiMaster.h"
#include <avr/cpufunc.h>


SpiMaster::SpiMaster () : spiMode(SPI_MODE0), spiOrder(SPI_MSBFIRST)
{
	ss = true;
	mosi = false;
	sck = false;
	
	// Enable SPI, Master Mode, clock rate fck/16 and data order MSB first
	// We could do this more elegantly with variable clock rates
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}


uint8_t SpiMaster::transfer (uint8_t data)
{
	return transferOne(data);
}


void SpiMaster::transfer (uint8_t * const txBuf, uint8_t * rxBuf, uint8_t count)
{
	for (uint8_t i = 0; i < count; i++)
		rxBuf[i] = transferOne (txBuf[i]);
}


void SpiMaster::transferWithAddress(uint8_t addr, uint8_t * const txBuf, uint8_t * rxBuf, uint8_t count)
{
	transferOne(addr);
	transfer(txBuf, rxBuf, count);
}


uint16_t SpiMaster::transfer16 (uint16_t data)
{
	// Union to allow us to quickly extract the lsb and msb bytes of the word
	union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } in, out;

	in.val = data;
	if (this->spiOrder == 0)
	{
		// MSB First
		out.msb = transferOne(in.msb);
		out.lsb = transferOne(in.lsb);
	}
	else
	{
		// LSB First
		out.lsb = transferOne(in.lsb);
		out.msb = transferOne(in.msb);
	}

	return out.val;
}


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


SpiMaster spiMaster;