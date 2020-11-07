//***************************************************************************
//
//  File Name :		FastIOPorts.h
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


#ifndef FASTIOPORTS_H_
#define FASTIOPORTS_H_

#ifndef FASTIO_H_
#error "Do not include FastIOPorts.h, use FastIO.h"
#endif

// We need to undef these because we want to redefine _SFR_ASM_COMPAT macro
// and include avr/io.h again to get numbers from the sfr registers
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT

#define _SFR_ASM_COMPAT 1
#include <avr/io.h>


//! \brief Macro to define a structure for a particular port
//! \param NAME The final name of the structure
//! \param PINREG The PIN SFR of this port
//! \param DATAREG The PORT SFR of this port
//! \param DDRREG The DDR SFR of this port
#ifdef __AVR_ATmega4808__

#define _defPort(NAME, NUM) \
struct NAME { \
	static const uint8_t pinx = NUM * 4 + 2; \
	static const uint8_t portx = NUM * 4 + 1; \
	static const uint8_t ddrx = NUM * 4; \
}

#else

#define _defPort(NAME, PINREG, DATAREG, DDRREG) \
struct NAME { \
	static const uint16_t pinx = PINREG; \
	static const uint16_t portx = DATAREG; \
	static const uint16_t ddrx = DDRREG; \
}

#endif

// Define a structure for each IO port that physically exists on a processor
#ifdef __AVR_ATmega4808__

#ifdef VPORTA
_defPort(FASTIOPORT_A, 0);
#endif

#ifdef VPORTB
_defPort(FASTIOPORT_B, 1);
#endif

#ifdef VPORTC
_defPort(FASTIOPORT_C, 2);
#endif

#ifdef VPORTD
_defPort(FASTIOPORT_D, 3);
#endif

#ifdef VPORTE
_defPort(FASTIOPORT_E, 4);
#endif

#ifdef VPORTF
_defPort(FASTIOPORT_F, 5);
#endif

#else

#ifdef PINA
_defPort(FASTIOPORT_A, PINA, PORTA, DDRA);
#endif

#ifdef PINB
_defPort(FASTIOPORT_B, PINB, PORTB, DDRB);
#endif

#ifdef PINC
_defPort(FASTIOPORT_C, PINC, PORTC, DDRC);
#endif

#ifdef PIND
_defPort(FASTIOPORT_D, PIND, PORTD, DDRD);
#endif

#ifdef PINE
_defPort(FASTIOPORT_E, PINE, PORTE, DDRE);
#endif

#ifdef PINF
_defPort(FASTIOPORT_F, PINF, PORTF, DDRF);
#endif

#ifdef PING
_defPort(FASTIOPORT_G, PING, PORTG, DDRG);
#endif

#ifdef PINH
_defPort(FASTIOPORT_H, PINH, PORTH, DDRH);
#endif

#ifdef PINJ
_defPort(FASTIOPORT_J, PINJ, PORTJ, DDRJ);
#endif

#ifdef PINK
_defPort(FASTIOPORT_K, PINK, PORTK, DDRK);
#endif

#ifdef PINL
_defPort(FASTIOPORT_L, PINL, PORTL, DDRL);
#endif

#ifdef PINM
_defPort(FASTIOPORT_M, PINM, PORTM, DDRM);
#endif

#ifdef PINN
_defPort(FASTIOPORT_N, PINN, PORTN, DDRN);
#endif

#ifdef PINP
_defPort(FASTIOPORT_P, PINP, PORTP, DDRP);
#endif

#endif

// cleanup - we've finished with the SFR definitions for now
#undef _AVR_COMMON_H
#undef _AVR_IO_H_
#undef _AVR_IOXXX_H_
#undef _AVR_SFR_DEFS_H_
#undef _SFR_ASM_COMPAT


//! \brief A template structure to describe a pin
//! \details Internal use only, forward declaration.  
template <uint8_t pin> struct _pins {};


//! \brief A macro to describe a single IO pin Arduino style
//! \details When used, will create a templated struct that will store
//! all required data to perform operations on a IO port or pin.
//! \param PIN the Arduino pin number
//! \param PORT one of the ports PORT_A to PORT_L defined above
//! \param BIT the bit of the IO port
#define _defPin(PIN, PORT, BIT) \
template <> struct _pins<PIN> : public PORT { \
	static const uint8_t mask = _BV(BIT); \
	static const uint8_t bit = BIT; \
}


#ifdef PORTA
	#define FASTIOPIN_A0 0
	#define FASTIOPIN_A1 1
	#define FASTIOPIN_A2 2
	#define FASTIOPIN_A3 3
	#define FASTIOPIN_A4 4
	#define FASTIOPIN_A5 5
	#define FASTIOPIN_A6 6
	#define FASTIOPIN_A7 7
	_defPin(FASTIOPIN_A0, FASTIOPORT_A, 0);
	_defPin(FASTIOPIN_A1, FASTIOPORT_A, 1);
	_defPin(FASTIOPIN_A2, FASTIOPORT_A, 2);
	_defPin(FASTIOPIN_A3, FASTIOPORT_A, 3);
	_defPin(FASTIOPIN_A4, FASTIOPORT_A, 4);
	_defPin(FASTIOPIN_A5, FASTIOPORT_A, 5);
	_defPin(FASTIOPIN_A6, FASTIOPORT_A, 6);
	_defPin(FASTIOPIN_A7, FASTIOPORT_A, 7);
#endif

#ifdef PORTB
	#define FASTIOPIN_B0 8
	#define FASTIOPIN_B1 9
	#define FASTIOPIN_B2 10
	#define FASTIOPIN_B3 11
	#define FASTIOPIN_B4 12
	#define FASTIOPIN_B5 13
	#define FASTIOPIN_B6 14
	#define FASTIOPIN_B7 15
	_defPin(FASTIOPIN_B0, FASTIOPORT_B, 0);
	_defPin(FASTIOPIN_B1, FASTIOPORT_B, 1);
	_defPin(FASTIOPIN_B2, FASTIOPORT_B, 2);
	_defPin(FASTIOPIN_B3, FASTIOPORT_B, 3);
	_defPin(FASTIOPIN_B4, FASTIOPORT_B, 4);
	_defPin(FASTIOPIN_B5, FASTIOPORT_B, 5);
	_defPin(FASTIOPIN_B6, FASTIOPORT_B, 6);
	_defPin(FASTIOPIN_B7, FASTIOPORT_B, 7);
#endif

#ifdef PORTC
	#define FASTIOPIN_C0 16
	#define FASTIOPIN_C1 17
	#define FASTIOPIN_C2 18
	#define FASTIOPIN_C3 19
	#define FASTIOPIN_C4 20
	#define FASTIOPIN_C5 21
	#define FASTIOPIN_C6 22
	#define FASTIOPIN_C7 23
	_defPin(FASTIOPIN_C0, FASTIOPORT_C, 0);
	_defPin(FASTIOPIN_C1, FASTIOPORT_C, 1);
	_defPin(FASTIOPIN_C2, FASTIOPORT_C, 2);
	_defPin(FASTIOPIN_C3, FASTIOPORT_C, 3);
	_defPin(FASTIOPIN_C4, FASTIOPORT_C, 4);
	_defPin(FASTIOPIN_C5, FASTIOPORT_C, 5);
	_defPin(FASTIOPIN_C6, FASTIOPORT_C, 6);
	_defPin(FASTIOPIN_C7, FASTIOPORT_C, 7);
#endif

#ifdef PORTD
	#define FASTIOPIN_D0 24
	#define FASTIOPIN_D1 25
	#define FASTIOPIN_D2 26
	#define FASTIOPIN_D3 27
	#define FASTIOPIN_D4 28
	#define FASTIOPIN_D5 29
	#define FASTIOPIN_D6 30
	#define FASTIOPIN_D7 31
	_defPin(FASTIOPIN_D0, FASTIOPORT_D, 0);
	_defPin(FASTIOPIN_D1, FASTIOPORT_D, 1);
	_defPin(FASTIOPIN_D2, FASTIOPORT_D, 2);
	_defPin(FASTIOPIN_D3, FASTIOPORT_D, 3);
	_defPin(FASTIOPIN_D4, FASTIOPORT_D, 4);
	_defPin(FASTIOPIN_D5, FASTIOPORT_D, 5);
	_defPin(FASTIOPIN_D6, FASTIOPORT_D, 6);
	_defPin(FASTIOPIN_D7, FASTIOPORT_D, 7);
#endif

#ifdef PORTE
	#define FASTIOPIN_E0 32
	#define FASTIOPIN_E1 33
	#define FASTIOPIN_E2 34
	#define FASTIOPIN_E3 35
	#define FASTIOPIN_E4 36
	#define FASTIOPIN_E5 37
	#define FASTIOPIN_E6 38
	#define FASTIOPIN_E7 39
	_defPin(FASTIOPIN_E0, FASTIOPORT_E, 0);
	_defPin(FASTIOPIN_E1, FASTIOPORT_E, 1);
	_defPin(FASTIOPIN_E2, FASTIOPORT_E, 2);
	_defPin(FASTIOPIN_E3, FASTIOPORT_E, 3);
	_defPin(FASTIOPIN_E4, FASTIOPORT_E, 4);
	_defPin(FASTIOPIN_E5, FASTIOPORT_E, 5);
	_defPin(FASTIOPIN_E6, FASTIOPORT_E, 6);
	_defPin(FASTIOPIN_E7, FASTIOPORT_E, 7);
#endif

#ifdef PORTF
	#define FASTIOPIN_F0 40
	#define FASTIOPIN_F1 41
	#define FASTIOPIN_F2 42
	#define FASTIOPIN_F3 43
	#define FASTIOPIN_F4 44
	#define FASTIOPIN_F5 45
	#define FASTIOPIN_F6 46
	#define FASTIOPIN_F7 47
	_defPin(FASTIOPIN_F0, FASTIOPORT_F, 0);
	_defPin(FASTIOPIN_F1, FASTIOPORT_F, 1);
	_defPin(FASTIOPIN_F2, FASTIOPORT_F, 2);
	_defPin(FASTIOPIN_F3, FASTIOPORT_F, 3);
	_defPin(FASTIOPIN_F4, FASTIOPORT_F, 4);
	_defPin(FASTIOPIN_F5, FASTIOPORT_F, 5);
	_defPin(FASTIOPIN_F6, FASTIOPORT_F, 6);
	_defPin(FASTIOPIN_F7, FASTIOPORT_F, 7);
#endif

#ifdef PORTG
	#define FASTIOPIN_G0 48
	#define FASTIOPIN_G1 49
	#define FASTIOPIN_G2 50
	#define FASTIOPIN_G3 51
	#define FASTIOPIN_G4 52
	#define FASTIOPIN_G5 53
	#define FASTIOPIN_G6 54
	#define FASTIOPIN_G7 55
	_defPin(FASTIOPIN_G0, FASTIOPORT_G, 0);
	_defPin(FASTIOPIN_G1, FASTIOPORT_G, 1);
	_defPin(FASTIOPIN_G2, FASTIOPORT_G, 2);
	_defPin(FASTIOPIN_G3, FASTIOPORT_G, 3);
	_defPin(FASTIOPIN_G4, FASTIOPORT_G, 4);
	_defPin(FASTIOPIN_G5, FASTIOPORT_G, 5);
	_defPin(FASTIOPIN_G6, FASTIOPORT_G, 6);
	_defPin(FASTIOPIN_G7, FASTIOPORT_G, 7);
#endif

#ifdef PORTH
	#define FASTIOPIN_H0 56
	#define FASTIOPIN_H1 57
	#define FASTIOPIN_H2 58
	#define FASTIOPIN_H3 59
	#define FASTIOPIN_H4 60
	#define FASTIOPIN_H5 61
	#define FASTIOPIN_H6 62
	#define FASTIOPIN_H7 63
	_defPin(FASTIOPIN_H0, FASTIOPORT_H, 0);
	_defPin(FASTIOPIN_H1, FASTIOPORT_H, 1);
	_defPin(FASTIOPIN_H2, FASTIOPORT_H, 2);
	_defPin(FASTIOPIN_H3, FASTIOPORT_H, 3);
	_defPin(FASTIOPIN_H4, FASTIOPORT_H, 4);
	_defPin(FASTIOPIN_H5, FASTIOPORT_H, 5);
	_defPin(FASTIOPIN_H6, FASTIOPORT_H, 6);
	_defPin(FASTIOPIN_H7, FASTIOPORT_H, 7);
#endif

#ifdef PORTJ
	#define FASTIOPIN_J0 64
	#define FASTIOPIN_J1 65
	#define FASTIOPIN_J2 66
	#define FASTIOPIN_J3 67
	#define FASTIOPIN_J4 68
	#define FASTIOPIN_J5 69
	#define FASTIOPIN_J6 70
	#define FASTIOPIN_J7 71
	_defPin(FASTIOPIN_J0, FASTIOPORT_J, 0);
	_defPin(FASTIOPIN_J1, FASTIOPORT_J, 1);
	_defPin(FASTIOPIN_J2, FASTIOPORT_J, 2);
	_defPin(FASTIOPIN_J3, FASTIOPORT_J, 3);
	_defPin(FASTIOPIN_J4, FASTIOPORT_J, 4);
	_defPin(FASTIOPIN_J5, FASTIOPORT_J, 5);
	_defPin(FASTIOPIN_J6, FASTIOPORT_J, 6);
	_defPin(FASTIOPIN_J7, FASTIOPORT_J, 7);
#endif

#ifdef PORTK
	#define FASTIOPIN_K0 72
	#define FASTIOPIN_K1 73
	#define FASTIOPIN_K2 74
	#define FASTIOPIN_K3 75
	#define FASTIOPIN_K4 76
	#define FASTIOPIN_K5 77
	#define FASTIOPIN_K6 78
	#define FASTIOPIN_K7 79
	_defPin(FASTIOPIN_K0, FASTIOPORT_K, 0);
	_defPin(FASTIOPIN_K1, FASTIOPORT_K, 1);
	_defPin(FASTIOPIN_K2, FASTIOPORT_K, 2);
	_defPin(FASTIOPIN_K3, FASTIOPORT_K, 3);
	_defPin(FASTIOPIN_K4, FASTIOPORT_K, 4);
	_defPin(FASTIOPIN_K5, FASTIOPORT_K, 5);
	_defPin(FASTIOPIN_K6, FASTIOPORT_K, 6);
	_defPin(FASTIOPIN_K7, FASTIOPORT_K, 7);
#endif

#ifdef PORTL
	#define FASTIOPIN_L0 80
	#define FASTIOPIN_L1 81
	#define FASTIOPIN_L2 82
	#define FASTIOPIN_L3 83
	#define FASTIOPIN_L4 84
	#define FASTIOPIN_L5 85
	#define FASTIOPIN_L6 86
	#define FASTIOPIN_L7 87
	_defPin(FASTIOPIN_L0, FASTIOPORT_L, 0);
	_defPin(FASTIOPIN_L1, FASTIOPORT_L, 1);
	_defPin(FASTIOPIN_L2, FASTIOPORT_L, 2);
	_defPin(FASTIOPIN_L3, FASTIOPORT_L, 3);
	_defPin(FASTIOPIN_L4, FASTIOPORT_L, 4);
	_defPin(FASTIOPIN_L5, FASTIOPORT_L, 5);
	_defPin(FASTIOPIN_L6, FASTIOPORT_L, 6);
	_defPin(FASTIOPIN_L7, FASTIOPORT_L, 7);
#endif

#ifdef PORTM
	#define FASTIOPIN_M0 88
	#define FASTIOPIN_M1 89
	#define FASTIOPIN_M2 90
	#define FASTIOPIN_M3 91
	#define FASTIOPIN_M4 92
	#define FASTIOPIN_M5 93
	#define FASTIOPIN_M6 94
	#define FASTIOPIN_M7 95
	_defPin(FASTIOPIN_M0, FASTIOPORT_M, 0);
	_defPin(FASTIOPIN_M1, FASTIOPORT_M, 1);
	_defPin(FASTIOPIN_M2, FASTIOPORT_M, 2);
	_defPin(FASTIOPIN_M3, FASTIOPORT_M, 3);
	_defPin(FASTIOPIN_M4, FASTIOPORT_M, 4);
	_defPin(FASTIOPIN_M5, FASTIOPORT_M, 5);
	_defPin(FASTIOPIN_M6, FASTIOPORT_M, 6);
	_defPin(FASTIOPIN_M7, FASTIOPORT_M, 7);
#endif

#ifdef PORTN
	#define FASTIOPIN_N0 96
	#define FASTIOPIN_N1 97
	#define FASTIOPIN_N2 98
	#define FASTIOPIN_N3 99
	#define FASTIOPIN_N4 100
	#define FASTIOPIN_N5 101
	#define FASTIOPIN_N6 102
	#define FASTIOPIN_N7 103
	_defPin(FASTIOPIN_N0, FASTIOPORT_N, 0);
	_defPin(FASTIOPIN_N1, FASTIOPORT_N, 1);
	_defPin(FASTIOPIN_N2, FASTIOPORT_N, 2);
	_defPin(FASTIOPIN_N3, FASTIOPORT_N, 3);
	_defPin(FASTIOPIN_N4, FASTIOPORT_N, 4);
	_defPin(FASTIOPIN_N5, FASTIOPORT_N, 5);
	_defPin(FASTIOPIN_N6, FASTIOPORT_N, 6);
	_defPin(FASTIOPIN_N7, FASTIOPORT_N, 7);
#endif


// Handle the ARDUINO environment
// This will ensure that the defines of HIGH/LOW/INPUT/OUPUT etc are
// all included
#ifdef ARDUINO
	#warning "An Arduino board type"

	#if ARDUINO >=100
	 #include "Arduino.h"
	#else
	 #include "WProgram.h"
	#endif

#else

	// For non Arduino environments we need these defined
	#ifndef LOW
	 #define LOW 0
	#endif
	#ifndef HIGH
	 #define HIGH 1
	#endif

#endif	// ARDUINO


#if 0
// The ARDUINO environment will define one of these from the boards.txt file
// If your board is not defined then it can be added here
#if defined(ARDUINO_AVR_MEGA2560)

#ifndef ARDUINO

static const uint8_t SS   = 53;
static const uint8_t MOSI = 51;
static const uint8_t MISO = 50;
static const uint8_t SCK  = 52;

static const uint8_t SDAPIN = 20;
static const uint8_t SCLPIN = 21;
static const uint8_t LED_BUILTIN = 13;

static const uint8_t A0 = 54;
static const uint8_t A1 = 55;
static const uint8_t A2 = 56;
static const uint8_t A3 = 57;
static const uint8_t A4 = 58;
static const uint8_t A5 = 59;
static const uint8_t A6 = 60;
static const uint8_t A7 = 61;
static const uint8_t A8 = 62;
static const uint8_t A9 = 63;
static const uint8_t A10 = 64;
static const uint8_t A11 = 65;
static const uint8_t A12 = 66;
static const uint8_t A13 = 67;
static const uint8_t A14 = 68;
static const uint8_t A15 = 69;

#endif	// ARDUINO

// Manually define the pins
_defPin(0, FASTIOPORT_E, 0);
_defPin(1, FASTIOPORT_E, 1);
_defPin(2, FASTIOPORT_E, 4);
_defPin(3, FASTIOPORT_E, 5);
_defPin(4, FASTIOPORT_G, 5);
_defPin(5, FASTIOPORT_E, 3);
_defPin(6, FASTIOPORT_H, 3);
_defPin(7, FASTIOPORT_H, 4);
_defPin(8, FASTIOPORT_H, 5);
_defPin(9, FASTIOPORT_H, 6);
_defPin(10, FASTIOPORT_B, 4);
_defPin(11, FASTIOPORT_B, 5);
_defPin(12, FASTIOPORT_B, 6);
_defPin(13, FASTIOPORT_B, 7);
_defPin(14, FASTIOPORT_J, 1);
_defPin(15, FASTIOPORT_J, 0);
_defPin(16, FASTIOPORT_H, 1);
_defPin(17, FASTIOPORT_H, 0);
_defPin(18, FASTIOPORT_D, 3);
_defPin(19, FASTIOPORT_D, 2);
_defPin(20, FASTIOPORT_D, 1);
_defPin(21, FASTIOPORT_D, 0);
_defPin(22, FASTIOPORT_A, 0);
_defPin(23, FASTIOPORT_A, 1);
_defPin(24, FASTIOPORT_A, 2);
_defPin(25, FASTIOPORT_A, 3);
_defPin(26, FASTIOPORT_A, 4);
_defPin(27, FASTIOPORT_A, 5);
_defPin(28, FASTIOPORT_A, 6);
_defPin(29, FASTIOPORT_A, 7);
_defPin(30, FASTIOPORT_C, 7);
_defPin(31, FASTIOPORT_C, 6);
_defPin(32, FASTIOPORT_C, 5);
_defPin(33, FASTIOPORT_C, 4);
_defPin(34, FASTIOPORT_C, 3);
_defPin(35, FASTIOPORT_C, 2);
_defPin(36, FASTIOPORT_C, 1);
_defPin(37, FASTIOPORT_C, 0);
_defPin(38, FASTIOPORT_D, 7);
_defPin(39, FASTIOPORT_G, 2);
_defPin(40, FASTIOPORT_G, 1);
_defPin(41, FASTIOPORT_G, 0);
_defPin(42, FASTIOPORT_L, 7);
_defPin(43, FASTIOPORT_L, 6);
_defPin(44, FASTIOPORT_L, 5);
_defPin(45, FASTIOPORT_L, 4);
_defPin(46, FASTIOPORT_L, 3);
_defPin(47, FASTIOPORT_L, 2);
_defPin(48, FASTIOPORT_L, 1);
_defPin(49, FASTIOPORT_L, 0);
_defPin(50, FASTIOPORT_B, 3);
_defPin(51, FASTIOPORT_B, 2);
_defPin(52, FASTIOPORT_B, 1);
_defPin(53, FASTIOPORT_B, 0);
_defPin(54, FASTIOPORT_F, 0);
_defPin(55, FASTIOPORT_F, 1);
_defPin(56, FASTIOPORT_F, 2);
_defPin(57, FASTIOPORT_F, 3);
_defPin(58, FASTIOPORT_F, 4);
_defPin(59, FASTIOPORT_F, 5);
_defPin(60, FASTIOPORT_F, 6);
_defPin(61, FASTIOPORT_F, 7);
_defPin(62, FASTIOPORT_K, 0);
_defPin(63, FASTIOPORT_K, 1);
_defPin(64, FASTIOPORT_K, 2);
_defPin(65, FASTIOPORT_K, 3);
_defPin(66, FASTIOPORT_K, 4);
_defPin(67, FASTIOPORT_K, 5);
_defPin(68, FASTIOPORT_K, 6);
_defPin(69, FASTIOPORT_K, 7);

#elif defined(ARDUINO_AVR_UNO) || \
	defined(ARDUINO_AVR_YUN) || \
	defined(ARDUINO_AVR_DUEMILANOVE) || \
	defined(ARDUINO_AVR_NANO) || \
	defined(ARDUINO_AVR_MINI) || \
	defined(ARDUINO_AVR_ETHERNET) || \
	defined(ARDUINO_AVR_FIO) || \
	defined(ARDUINO_AVR_BT) || \
	defined(ARDUINO_AVR_LILYPAD) || \
	defined(ARDUINO_AVR_PRO) || \
	defined(ARDUINO_AVR_NG)

#ifndef ARDUINO

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

static const uint8_t SDA = 18;
static const uint8_t SCL = 19;
#define LED_BUILTIN 13

#endif	// ARDUINO

_defPin(0, FASTIOPORT_D, 0);
_defPin(1, FASTIOPORT_D, 1);
_defPin(2, FASTIOPORT_D, 2);
_defPin(3, FASTIOPORT_D, 3);
_defPin(4, FASTIOPORT_D, 4);
_defPin(5, FASTIOPORT_D, 5);
_defPin(6, FASTIOPORT_D, 6);
_defPin(7, FASTIOPORT_D, 7);
_defPin(8, FASTIOPORT_B, 0);
_defPin(9, FASTIOPORT_B, 1);
_defPin(10, FASTIOPORT_B, 2);
_defPin(11, FASTIOPORT_B, 3);
_defPin(12, FASTIOPORT_B, 4);
_defPin(13, FASTIOPORT_B, 5);
_defPin(14, FASTIOPORT_C, 0);
_defPin(15, FASTIOPORT_C, 1);
_defPin(16, FASTIOPORT_C, 2);
_defPin(17, FASTIOPORT_C, 3);
_defPin(18, FASTIOPORT_C, 4);
_defPin(19, FASTIOPORT_C, 5);

#elif defined(ARDUINO_AVR_SANGUINO)

#ifndef ARDUINO

static const uint8_t SS   = 4;
static const uint8_t MOSI = 5;
static const uint8_t MISO = 6;
static const uint8_t SCK  = 7;

static const uint8_t SDA = 17;
static const uint8_t SCL = 16;
static const uint8_t LED_BUILTIN = 0;

static const uint8_t A0 = 31;
static const uint8_t A1 = 30;
static const uint8_t A2 = 29;
static const uint8_t A3 = 28;
static const uint8_t A4 = 27;
static const uint8_t A5 = 26;
static const uint8_t A6 = 25;
static const uint8_t A7 = 24;

#endif

_defPin(0, FASTIOPORT_B, 0);
_defPin(1, FASTIOPORT_B, 1);
_defPin(2, FASTIOPORT_B, 2);
_defPin(3, FASTIOPORT_B, 3);
_defPin(4, FASTIOPORT_B, 4);
_defPin(5, FASTIOPORT_B, 5);
_defPin(6, FASTIOPORT_B, 6);
_defPin(7, FASTIOPORT_B, 7);
_defPin(8, FASTIOPORT_D, 0);
_defPin(9, FASTIOPORT_D, 1);
_defPin(10, FASTIOPORT_D, 2);
_defPin(11, FASTIOPORT_D, 3);
_defPin(12, FASTIOPORT_D, 4);
_defPin(13, FASTIOPORT_D, 5);
_defPin(14, FASTIOPORT_D, 6);
_defPin(15, FASTIOPORT_D, 7);
_defPin(16, FASTIOPORT_C, 0);
_defPin(17, FASTIOPORT_C, 1);
_defPin(18, FASTIOPORT_C, 2);
_defPin(19, FASTIOPORT_C, 3);
_defPin(20, FASTIOPORT_C, 4);
_defPin(21, FASTIOPORT_C, 5);
_defPin(22, FASTIOPORT_C, 6);
_defPin(23, FASTIOPORT_C, 7);
_defPin(24, FASTIOPORT_A, 0);
_defPin(25, FASTIOPORT_A, 1);
_defPin(26, FASTIOPORT_A, 2);
_defPin(27, FASTIOPORT_A, 3);
_defPin(28, FASTIOPORT_A, 4);
_defPin(29, FASTIOPORT_A, 5);
_defPin(30, FASTIOPORT_A, 6);
_defPin(31, FASTIOPORT_A, 7);

#elif defined(__AVR_AT90CAN128xxxx__)
// This is a non Arduino board, so normal pin numbers
// 

static const uint8_t SS   = 8;
static const uint8_t MOSI = 10;
static const uint8_t MISO = 11;
static const uint8_t SCK  = 9;

static const uint8_t SDA = 25;
static const uint8_t SCL = 24;
static const uint8_t LED_BUILTIN = 0;

static const uint8_t A0 = 40;
static const uint8_t A1 = 41;
static const uint8_t A2 = 42;
static const uint8_t A3 = 43;
static const uint8_t A4 = 44;
static const uint8_t A5 = 45;
static const uint8_t A6 = 46;
static const uint8_t A7 = 47;

_defPin(0, FASTIOPORT_A, 0);
_defPin(1, FASTIOPORT_A, 1);
_defPin(2, FASTIOPORT_A, 2);
_defPin(3, FASTIOPORT_A, 3);
_defPin(4, FASTIOPORT_A, 4);
_defPin(5, FASTIOPORT_A, 5);
_defPin(6, FASTIOPORT_A, 6);
_defPin(7, FASTIOPORT_A, 7);
_defPin(8, FASTIOPORT_B, 0);
_defPin(9, FASTIOPORT_B, 1);
_defPin(10, FASTIOPORT_B, 2);
_defPin(11, FASTIOPORT_B, 3);
_defPin(12, FASTIOPORT_B, 4);
_defPin(13, FASTIOPORT_B, 5);
_defPin(14, FASTIOPORT_B, 6);
_defPin(15, FASTIOPORT_B, 7);
_defPin(16, FASTIOPORT_C, 0);
_defPin(17, FASTIOPORT_C, 1);
_defPin(18, FASTIOPORT_C, 2);
_defPin(19, FASTIOPORT_C, 3);
_defPin(20, FASTIOPORT_C, 4);
_defPin(21, FASTIOPORT_C, 5);
_defPin(22, FASTIOPORT_C, 6);
_defPin(23, FASTIOPORT_C, 7);
_defPin(24, FASTIOPORT_D, 0);
_defPin(25, FASTIOPORT_D, 1);
_defPin(26, FASTIOPORT_D, 2);
_defPin(27, FASTIOPORT_D, 3);
_defPin(28, FASTIOPORT_D, 4);
_defPin(29, FASTIOPORT_D, 5);
_defPin(30, FASTIOPORT_D, 6);
_defPin(31, FASTIOPORT_D, 7);
_defPin(32, FASTIOPORT_E, 0);
_defPin(33, FASTIOPORT_E, 1);
_defPin(34, FASTIOPORT_E, 2);
_defPin(35, FASTIOPORT_E, 3);
_defPin(36, FASTIOPORT_E, 4);
_defPin(37, FASTIOPORT_E, 5);
_defPin(38, FASTIOPORT_E, 6);
_defPin(39, FASTIOPORT_E, 7);
_defPin(40, FASTIOPORT_F, 0);
_defPin(41, FASTIOPORT_F, 1);
_defPin(42, FASTIOPORT_F, 2);
_defPin(43, FASTIOPORT_F, 3);
_defPin(44, FASTIOPORT_F, 4);
_defPin(45, FASTIOPORT_F, 5);
_defPin(46, FASTIOPORT_F, 6);
_defPin(47, FASTIOPORT_F, 7);
_defPin(48, FASTIOPORT_G, 0);
_defPin(49, FASTIOPORT_G, 1);
_defPin(50, FASTIOPORT_G, 2);
_defPin(51, FASTIOPORT_G, 3);
_defPin(52, FASTIOPORT_G, 4);

// END OF AT90CAN128

#else

#endif

#endif

//#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__)
//#define LED_BUILTIN FASTIOPIN_B0		// Sanguino Compatibles
//#endif
//
//#ifdef __AVR_ATmega2560__
//static const uint8_t LED_BUILTIN = 15;	// Arduino Mega
//#endif

#endif /* FASTIOPORTS_H_ */