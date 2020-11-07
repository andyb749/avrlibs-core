//***************************************************************************
//
//  File Name :		TwiMasterBase.cpp
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


#include "twiMasterBase.h"


bool TwiMasterBase::writeBytes (uint8_t device, uint8_t * data, uint8_t count, bool sendStop)
{
	if (start (device, TwiDirWrite))
	{
		do
		{
			if (!writeDevice (*(data++)))
				break;
		} while(--count);

		if (sendStop)
			stop();

		return true;
	}
	return false;
}


bool TwiMasterBase::readBytes(uint8_t device, uint8_t * data, uint8_t count, bool sendStop)
{
	// send the start condition and address byte
	if (start (device, TwiDirRead))
	{
		do
		{
			if (count == 1)
				*(data++) = readDeviceWithNak();
			else
				*(data++) = readDeviceWithAck();
		} while (--count);

		if (sendStop)
			stop();

		return true;
	}
	return false;
}


bool TwiMasterBase::writeRegister (uint8_t device, uint8_t address, uint8_t data)
{
	if (start (device, TwiDirWrite))
	{
		if (writeDevice (address))
		{
			if (writeDevice (data))
			{
				stop();
				return true;
			}
		}
	}
	return false;
}


//! \brief Writes multiple bytes to the I2C device
//! \details Addresses the device and performs a write with address, followed
//! by a multiple data bytes
//! \param device I2C device to address
//! \param address A byte to write to the device
//! \param data Pointer to the location that the data byte to be written
//! \param count Number of data bytes to write
//! \returns Number of bytes written
bool TwiMasterBase::writeRegister (uint8_t device, uint8_t address, uint8_t * data, uint8_t count)
{
	bool ret = true;

	if (start (device, TwiDirWrite))
	{
		if (writeDevice (address))
		{
			for (uint8_t i = 0; i < count; i++)
			{
				if (!writeDevice (data[i]))
					ret = false;
			}
			stop();
			return ret;
		}
	}
	return false;
}


//! \brief Read a single byte from the I2C device
//! \details Addresses the device and performs a write with address, followed
//! by a single read
//! \param device I2C device to address
//! \param address A byte to write to the device
//! \param data Pointer to the location that the data byte should be returned in
//! \returns Number of bytes read
bool TwiMasterBase::readRegister(uint8_t device, uint8_t address, uint8_t * data)
{
	// send the start condition and address byte
	if (start (device, TwiDirWrite))
	{
		if (writeDevice (address))
		{
			if (repeatStart (device, TwiDirRead))
			{
				uint8_t readData = readDeviceWithNak();
				stop();
				*data = readData;
				return true;
			}
		}
	}
	return false;
}


//! \brief Reads multiple bytes from the I2C device
//! \details Addresses the device and performs a write with address, followed by
//! multiple reads
//! \param device I2C device to address
//! \param address A byte to write to the device
//! \param data Pointer to the location that the data byte should be returned in
//! \returns Number of bytes read
bool TwiMasterBase::readRegister(uint8_t device, uint8_t address, uint8_t * data, uint8_t count)
{
	// send the start condition and address byte
	if (start (device, TwiDirWrite))
	{
		if (writeDevice (address))
		{
			if (repeatStart (device, TwiDirRead))
			{
				// read all the bytes
				do {
						if (count == 1)
						{
							*(data++) = readDeviceWithNak();
						}
						else
						{
							*(data++) = readDeviceWithAck();

						}
				} while (--count);
				stop();
				return true;
			}
		}
	}
	return false;
}


//! \brief Scans the I2C bus for devices
//! \details Scans the I2C bus for devices by checking the returned
//! ACK bit.  Calls the user supplied function for each device found with
//! the device number.
//! \param function A user supplied function that will be called for each
//! device found.
void TwiMasterBase::scanBus(void (*function)(uint8_t device))
{
	for (uint8_t device = 1; device < 0x80; device++)
	{
		bool rc = start (device, TwiDirRead);
		if (rc)
		{
			readDeviceWithNak();
			stop();
			(*function) (device);
		}
	}
}
