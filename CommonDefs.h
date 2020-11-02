//***************************************************************************
//
//  File Name :		CommonDefs.h
//
//  Project :		Libraries for the Atmel 8 bit AVR MCU
//
//  Purpose :		Common definitions 
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


#ifndef COMMONDEFS_H_
#define COMMONDEFS_H_

//! \file
//! \brief Common Definitions for AVR Mega microcontrollers

#ifndef _cbi
//! \def _cbi(sfr, bit)
//! \brief Emulates the cbi instruction and clears the
//! specified bit of the special function register.
//! \param sfr Special function register
//! \param bit Bit number
#define _cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif


#ifndef _sbi
//! \def _sbi(sft, bit)
//! \brief Emulates the sbi instruction and sets the
//! specified bit of the special function register.
//! \param sfr Special function register
//! \param bit Bit number
#define _sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


// pointer to an 8 bit special function register
typedef volatile uint8_t* psfr8_t;

// pointer to a 16 bit special function register
typedef volatile uint16_t* psfr16_t;


#endif /* COMMONDEFS_H_ */