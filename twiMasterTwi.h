//***************************************************************************
//
//  File Name :		TwiMasterTwi.h
//
//  Project :		TWI (I2C) library for the Atmel 8 bit AVR MCU
//
//  Purpose :		Object orientated access to the Timer 16 bit timers T3, T4, T5 on
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



#ifndef TWITWIMASTER_H_
#define TWITWIMASTER_H_


#include <util/twi.h>
#include "twiMasterBase.h"


class TwiMaster : public TwiMasterBase
{
//variables
public:
protected:
private:
	FastIOOutputPin<SDAPIN> sdaPin;
	FastIOOutputPin<SCLPIN> sclPin;
	//static const bool released=true;
	//static const bool low=false;

//functions
	public:
	//! \brief Initialises a new instance of the TwiMaster object
	TwiMaster()
	{
		//	setSpeed(fast);
		//TWCR=0;
		// Enables the TWI, setting SDA/SCL as necessary
		TWCR = _BV(TWEN);
		setSpeed(false);
	}

	void pullups (bool enable)
	{
		// Once the pins are setup in TWI mode, a write to the relevant PORT/BIT will enable
		// the pullups
		if (enable)
		{
			sdaPin.set();
			sclPin.set();
//			sdaPin.enablePullups();
//			sclPin.enablePullups();
		}
		else
		{
			sdaPin.clear();
			sclPin.clear();
//			sdaPin.disablePullups();
//			sclPin.disablePullups();
		}
	}

	//! \brief Sets low or high speed on the I2C bus
	//! \details Enables a caller to set the I2C bus clock
	//! frequency to 100kHz or 400kHz
	//! \note This function works for CPU clock speeds between 1.8Mhz and 20MHz
	//! \param fast Sets 400kHz fast mode when true; otherwise 100kHz.
	inline void setSpeed (const bool fast) __attribute__((always_inline))
	{
		if (fast)
		{
			TWBR = ((F_CPU / 400000) - 16) / 2;
		}
		else
		{
			TWBR = ((F_CPU / 100000) - 16) / 2;
		}
	}

protected:
	//! \brief Issues start condition and sends SLA and transfer direction
	//! \details Issues the start condition on the I2C bus and sends the SLA
	//! address along with the read/write bit
	//! \param device The 7 bit SLA device address without shifting left
	//! \param read One of the values TW_READ or TW_WRITE
	//! \returns true if the start was successful and the address was acknowledged
	//! by the slave, otherwise false if any errors were detected
	bool start(uint8_t device, twiDir_t read)
	{
		uint8_t	slarw = (device << 1) | read;

		uint8_t twst;

		// send START condition
		TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

		// wait until transmission completed
		waitTransComplete();

		// check value of TWI Status Register
		twst = TW_STATUS;
		if ( (twst != TW_START) && (twst != TW_REP_START))
		{
			// Start condition failed, most likely bus arbitration
			//printf ("Start %02X: error %02X\n", device, twst);
			return false;
		}

		// send device address
		TWDR = slarw;
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

		// wait until transmission completed and ACK/NACK has been received
		waitTransComplete();

		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS;
		if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) )
		{
			// Failed to get an ACK - likely bus failure or device wasn't available
			//printf ("SLA %02X: error %02X\n", device, twst);
			return false;
		}
		return true;
	}	// start


	//! \brief Issues a repeated start condition on the bus
	//! \details Issues a repeated start condition on the I2C bus and sends the
	//! SLA address along with the direction of the transfer
	//! \returns True if successful; false if there was an error or the slave device
	//! could not be accessed.
	//! \param device The seven bit address of the I2C device - not shifted to eight
	//! bits.
	//! \param read One of the two constants TW_READ or TW_WRITE to specify a read
	//! or write.
	bool repeatStart(uint8_t device, twiDir_t read)
	{
		return start (device, read);
	}	// repeat_start


	//! \brief Terminates the data transfer and releases the I2C bus
	//! \details Call this method to complete any data transfers and
	//! release the bus to another master
	void stop()
	{
		// send stop condition
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

		// wait until stop condition is executed and bus released
		while (TWCR & _BV(TWSTO))
		continue;
	}	// stop


	//! \brief Sends one byte to the I2C device
	//! \details Sends the supplied byte to the device addressed on the I2C bus.
	//! A start condition and SLAr/w must have previously been sent.
	//! \param data The byte to send to the device
	//! \return True if the transfer was successful; otherwise false
	bool writeDevice (uint8_t data)
	{
		uint8_t   twst;

		// send data to the previously addressed device
		TWDR = data;
		TWCR = _BV(TWINT) | _BV(TWEN);

		waitTransComplete();

		// check value of TWI Status Register
		twst = TW_STATUS;
		if( twst != TW_MT_DATA_ACK)
		{
			//printf ("WR: %02X\n", twst);
			return false;
		}

		return true;
	}	// write


	//! \brief Reads one bytes and requests more data
	//! \details Reads one byte from the I2C device and sets the ACK flag so that
	//! the slave device knows that further data reads will follow
	//! \returns The byte received from the slave device
	uint8_t readDeviceWithAck()
	{
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
		waitTransComplete();

		return TWDR;
	}	// readAck


	//! \brief Reads one byte and signals no more data
	//! \details Reads on byte from the I2C device and clears the ACK flag so
	//! that the slave device knows that a stop condition or restart will follow
	//! \returns The byte read from the I2C device
	uint8_t readDeviceWithNak()
	{
		TWCR = _BV(TWINT) | _BV(TWEN);
		waitTransComplete();

		return TWDR;
	}	// readNak


	// waits for the bus transfer to complete
	// using polling
	void waitTransComplete ()
	{
		while (!(TWCR & _BV(TWINT)))
		continue;
	}

private:
	TwiMaster( const TwiMaster &c );
	TwiMaster& operator=( const TwiMaster &c );

}; //TwiMaster




#endif /* TWITWIMASTER_H_ */