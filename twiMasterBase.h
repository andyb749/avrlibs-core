//***************************************************************************
//
//  File Name :		TwiMasterBase.h
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



#ifndef TWIMASTERBASE_H_
#define TWIMASTERBASE_H_

#include <stdint.h>


typedef enum
{
	TwiDirWrite = 0,
	TwiDirRead = 1
} twiDir_t;




class TwiMasterBase
{
// variables
public:
protected:
private:

// methods:
public:
	//! \brief Writes an array of bytes to the I2C device
	//! \details This method performs the start or restart condition and then sends the data bytes to the device.
	//! An optional parameter indicates if the stop condition should be sent to the device.  If false, then
	//! additional read and writes can take place.
	//! \param device I2C device to address
	//! \param data Pointer to the data bytes should be written
	//! \param sendStop True if the stop condition should be written on the bus, false to allow additional
	//! writes or reads to follow.
	//! \returns Number of bytes written
	bool writeBytes (uint8_t device, uint8_t * data, uint8_t count, bool sendStop=true);

	//! \brief Reads an array of bytes from the I2C device
	//! \details This method performs the start or restart condition and then reads the data bytes from the device.
	//! An optional parameter indicates if the stop condition should be sent to the device.  If false, then
	//! additional read and writes can take place.
	//! \param device I2C device to address
	//! \param data Pointer to the area where the data bytes should be read to
	//! \param sendStop True if the stop condition should be written on the bus, false to allow additional
	//! writes or reads to follow.
	//! \returns Number of bytes read
	bool readBytes(uint8_t device, uint8_t * data, uint8_t count, bool sendStop=true);

	//! \brief Write a single byte to the I2C device
	//! \details This method simply performs the start condition and then sends two bytes to the device.
	//! Most ICs have a notion of a register or address pointer that has to be set up before a write can
	//! take place.
	//! \param device I2C device to address
	//! \param address The address or register in the device
	//! \param data Data byte should be written
	//! \returns Number of bytes written
	bool writeRegister (uint8_t device, uint8_t address, uint8_t data);

	//! \brief Write a series of bytes to the I2C device
	//! \details This method simply performs the start condition and then a
	//! sends the address bytes followed by the data to the device.
	//! Most ICs have a notion of a register or address pointer that has to be set up before a write can
	//! take place.
	//! \param device I2C device to address
	//! \param address The address or register in the device
	//! \param data Data bytes to be written
	//! \param The number of data bytes to send after the address byte
	//! \returns Number of bytes written
	bool writeRegister (uint8_t device, uint8_t address, uint8_t * data, uint8_t count);

	//! \brief Read a single byte from the I2C device
	//! \details This method simply performs the start condition and then sends the address byte to the device before
	//! performing a single read.
	//! Most ICs have a notion of a register or address pointer that has to be set up before a read can
	//! take place.
	//! \param device I2C device to address
	//! \param address The address or register in the device
	//! \param data Pointer to a byte where the read byte will be placed.
	//! \returns Number of bytes read
	bool readRegister (uint8_t device, uint8_t address, uint8_t * data);

	//! \brief Read multiple bytes from the I2C device
	//! \details This method simply performs the start condition and then sends the address byte to the device before
	//! performing multiple reads.
	//! Most ICs have a notion of a register or address pointer that has to be set up before a read can
	//! take place.
	//! \param device I2C device to address
	//! \param address The address or register in the device
	//! \param data Pointer to the start of an array where the read bytes will be placed.
	//! \returns Number of bytes read
	bool readRegister (uint8_t device, uint8_t address, uint8_t * data, uint8_t count);

	//! \brief Scans the I2C bus looking for device
	//! \details This method addresses each device on the bus in turn and for each that device that
	//! responds to its address with an ACK the user supplied callback function will be called.
	//! \param function The user supplied callback which will be called for each slave address that
	//! responds
	void scanBus (void (*function)(uint8_t));


protected:
	//! \brief Performs the start condition on the bus.
	//! \details Implementers need to develop code to produce a start 
	//! condition on the bus and then clock out the device address and
	//! accept the ACK/NAK from the device
	//! \param device The 7 bit device address
	//! \param read One of the twiDir_t enumeration specifying a read or a write
	//! \returns True if the start condition and address was ACK'd by the device
	//! False on NACK.
	virtual bool start (uint8_t device, twiDir_t read) = 0;

	//! \brief Performs a restart condition
	//! \details Implementors should simply perform an inline call of the start
	//! \param device The 7 bit device address
	//! \param read One of the twiDir_t enumeration specifying a read or a write
	//! \returns True if the start condition and address was ACK'd by the device
	//! False on NACK.
	virtual bool repeatStart (uint8_t device, twiDir_t read) = 0;

	//! \brief Performs a stop on the I2C bus
	//! \details Implementors should develop code to cause a bus stop condition
	virtual void stop() = 0;

	//! \brief Writes one byte of data
	//! \details Implementors should develop code to clock out the supplied data byte
	//! to the previously addressed slave on the bus and read the acknowledge bit
	//! \param The data byte to be written
	//! \returns True for an ACK or false or NAK returned from the slave device
	virtual bool writeDevice (uint8_t data) = 0;

	//! \brief Read one byte of data with the ACK bit
	//! \details Implementors should develop code to clock in a byte of data from the
	//! bus and send an ACK bit
	//! \return The data byte read
	virtual uint8_t readDeviceWithAck() = 0;

	//! \brief Read one byte of data with the NAK bit
	//! \details Implementors should develop code to clock in a byte of data from the
	//! bus and send an NAK bit
	//! \return The data byte read
	virtual uint8_t readDeviceWithNak() = 0;
private:
};


#endif /* TWIMASTERBASE_H_ */