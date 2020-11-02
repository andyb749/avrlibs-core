//***************************************************************************
//
//  File Name :		uart.h
//
//  Project :		Library for the Atmel 8 bit AVR MCU
//
//  Purpose :		An object to wrap the UART hardware 
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


#ifndef UART_H_
#define UART_H_


#include <uartpriv.h>
#include <stdio.h>
#include <avr/io.h>
#include <commondefs.h>


#ifndef MAX_UARTBUF
#define MAX_UARTBUF 80
#endif


//typedef volatile uint8_t* uartport_t;


//! \brief An enumeration of the available data bits
enum uart_data_t
{
	databit5,	//!< 5 data bits
	databit6,	//!< 6 data bits
	databit7,	//!< 7 data bits
	databit8,	//!< 8 data bits
	databitx,	//!< reserved - do not use
	databity,	//!< reserved - do not use
	databitz,	//!< reserved - do not use
	databit9	//!< 9 data bits
};


//! \brief An enumeration of the available parity settings
enum uart_parity_t
{
	parityNone,		//!< no parity
	parityReserved,	//!< reserved - do no use
	parityEven,		//!< even parity
	parityOdd		//!< odd parity
};



//! \brief A template class to wrap the UART
//! \details A class that allows consistent high and low level operations
//! with the UART hardware onboard an Atmel 8 bit Mega and Tiny MCU
//! \tparam TUART One of the predefined objects UART_0, UART_1, UART_2 or UART_3
//! \note Not all UARTS are available on every platform.
template <class TUART>
class Uart
{
public:
protected:
private:
	char rxbuf [MAX_UARTBUF];

public:
	//! \brief Initialises a new instance of the uart class
	inline Uart () __attribute__((always_inline)) { }
	
	//! \brief Initialises the UART enabling RX and TX and set to
	//! 8 bits, 1 stop, no parity
	inline void init() __attribute__((always_inline))
	{
		enableRx();
		enableTx();
		setDataBits(databit8);
		setParity(parityNone);
	}


	//! \brief Enables the receiver
	inline void enableRx () __attribute__((always_inline))
	{
		//*psfr8_t (TUART::crsbx) |= _BV(RXEN0);
		_sbi(*psfr8_t (TUART::crsbx), RXEN0);
	}


	//! \brief Enables the transmitter
	inline void enableTx() __attribute__((always_inline))
	{
		//*psfr8_t (TUART::crsbx) |= _BV(TXEN0);
		_sbi(*psfr8_t (TUART::crsbx), TXEN0);
	}


	//! \brief Enables the receive byte interrupt
	//! \details The receive interrupt is raised when there is unread data
	//! in the receive buffer
	inline void enableRxInt() __attribute__((always_inline))
	{
		*psfr8_t (TUART::crsbx) |= _BV(RXCIE0);
	}


	//! \brief Enable the transmit byte interrupt
	//! \details The transmit interrupt is raised when the frame has been
	//! shifted out and there is no data in the transmit buffer
	inline void enableTxInt() __attribute__((always_inline))
	{
		*psfr8_t (TUART::crsbx) |= _BV(TXCIE0);
	}


	//! \brief Enables the transmitter buffer empty interrupt
	//! \details The buffer empty interrupt is raised when the transmit
	//! buffer can accept new data
	inline void enableTxEmptyInt() __attribute__((always_inline))
	{
		*psfr8_t (TUART::crsbx) |= _BV(UDRIE0);
	}


	//! \brief Indicates if the transmitter is ready
	//!
	//! \return true if the transmit buffer is empty and can accept a new character
	inline
	bool txReady() __attribute__((always_inline)) __attribute__((always_inline))
	{
		return bit_is_set(*psfr8_t (TUART::crsax), UDRE0);
	}


	//! \brief Writes the supplied byte to the UART
	//! \details The method will block whilst any previous byte
	//! is sent and the transmitter buffer is not ready
	//! \param data The data byte to write
	void write (uint8_t data)
	{
		while (!txReady())
			;

		*psfr8_t (TUART::datax) = data;
	}


	//! \brief Checks is the receiver has a byte ready
	//! \details When a byte is received from the port it is transferred in
	//! a buffer register and the ready flag is set
	//! \return true is the receiver has received a new byte
	inline
	bool rxReady() __attribute__((always_inline))
	{
		return bit_is_set (*psfr8_t (TUART::crsax), RXC0);
	}


	//! \brief Reads a byte from the UART
	//! \details Blocks until a byte has been read from the port and is available
	//! in the receiver buffer
	//! \return The data byte received
	uint8_t read ()
	{
		while (!rxReady())
			;
		
		return *psfr8_t (TUART::datax);
	}


	//! \brief Gets the status of the framing error
	//! \return True if framing error
	inline bool isFrameError () __attribute__((always_inline))
	{
		return bit_is_set (*psfr8_t (TUART::crsax), FE0);
	}


	//! \brief Gets the status of the overrun error
	//! \return True if overrun error
	inline bool isOverrun () __attribute__((always_inline))
	{
		return bit_is_set (*psfr8_t (TUART::crsax), DOR0);
	}
	
	
	//== BAUDRATE ==
	//! \brief Sets the baudrate
	//! \details This method and the setBaudX methods all
	//! use the AVR CLIB setbaud.h file to determine the
	//! baudrate settings.   To use this method, the programmer must
	//! #define \c BAUD to the required baudrate.  The header file
	//! generates values for the baudrate register and clock doubler
	//! bit.  The other baudrate setting methods use the same method 
	//! except that the process is hidden from the programmer.
	//! \warning If the baudrate cannot be acheived from the clock speed or
	//! the actual baudrate would be out of limits of accuracy the file
	//! will generate a warning
	inline void setBaud () __attribute__ ((always_inline))
	{
		#ifndef BAUD
		#define BAUD 9600
		#endif
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}


	//! \brief Sets the baudrate to 300
	inline void setBaud300 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 300
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 600
	inline void setBaud1200 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 1200
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 1200
	inline void setBaud2400 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 2400
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 4800
	inline void setBaud4800 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 4800
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 9600
	inline void setBaud9600 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 9600
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 19200
	inline void setBaud19200 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 19200
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 38400
	inline void setBaud38400 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 38400
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 57600
	inline void setBaud57600 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 57600
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//! \brief Sets the baudrate to 115200
	inline void setBaud115200 () __attribute__ ((always_inline))
	{
		#undef BAUD
		#define BAUD 115200
		#include <util/setbaud.h>
		*psfr16_t (TUART::ubrrx) = UBRR_VALUE;
		#if USE_2X
		*psfr8_t(TUART::crsax) |= _BV(U2X0);
		#else
		*psfr8_t(TUART::crsax) &= ~_BV(U2X0);
		#endif
	}

	//== DATABIT ==
	//! \brief Sets 8 data bits
//	inline void setDataBits8 () __attribute__((always_inline))
//	{
//		*psfr8_t (TUART::crscx) &= ~(databit8<<UCSZ00);
//		*psfr8_t (TUART::crscx) |= (databit8<<UCSZ00);
//	}
	
	//! \brief Sets the data bits to the supplied enumeration value
	inline void setDataBits (enum uart_data_t data) __attribute__((always_inline))
	{
		uint8_t temp = (data & 0x04) >> 2;
		*psfr8_t (TUART::crsbx) &= ~(1<<UCSZ02);
		*psfr8_t (TUART::crsbx) |= (temp<<UCSZ02);
		
		temp = (data & 0x03);
		*psfr8_t (TUART::crscx) &= ~(3<<UCSZ00);
		*psfr8_t (TUART::crscx) |= (temp<<UCSZ00);
	}


	//== PARITYBIT ==
	//! \brief Sets parity to the supplied enumeration value
	//! \param parity The parity setting
	inline void setParity (enum uart_parity_t parity) __attribute__((always_inline))
	{
		*psfr8_t (TUART::crscx) &= ~(parityOdd<<UPM00);
		*psfr8_t (TUART::crscx) |= parity;
	};


	//== STOPBIT ==
	//! \brief Sets 1 stop bit
	inline void setStopBit1 () __attribute__((always_inline))
	{
		*psfr8_t (TUART::crscx) &= ~_BV(USBS0);
	}


	//! \brief Sets 2 stop bits
	inline void setStopBit2 () __attribute__((always_inline))
	{
		*psfr8_t (TUART::crscx) |= _BV(USBS0);
	}
	
	
	// High Level Support
	//! STDIO support for writing a character
	//!
	//! This method allows the user to use the stdio library routines of the
	//! run time library including puts, putch, putchar and printf.
	//!
	//! The user add code as follows:
	//! \code
	//! static FILE mystdout;
	//! fdev_setup_stream(&mystdout, uart0_putchar, uart0_getchar, _FDEV_SETUP_RW);
	//! stdout=&mystdout;
	//! \endcode
	//! \return The character written if successful
	inline
	int putch(char c, FILE *stream) __attribute__((always_inline))
	{
		if (c == '\a')
		{
			fputs("*ring*\n", stderr);
			return 0;
		}
		
		if (c== '\n')
			putch('\r', stream);
		
		write(c);
		return c;
	}

	//! \brief Receive a character from the UART Rx.
	//! \details This features a simple line-editor that allows to delete and
	//! re-edit the characters entered, until either CR or NL is entered.
	//! Printable characters entered will be echoed using uart_putchar().
	//!
	//! Editing characters:
	//!
	//! . \b (BS) or \177 (DEL) delete the previous character
	//! . ^u kills the entire input buffer
	//! . ^w deletes the previous word
	//! . ^r sends a CR, and then reprints the buffer
	//! . \t will be replaced by a single space
	//!
	//! All other control characters will be ignored.
	//!
	//! The internal line buffer is RX_BUFSIZE (80) characters long, which
	//! includes the terminating \n (but no terminating \0).  If the buffer
	//! is full (i. e., at RX_BUFSIZE-1 characters in order to keep space for
	//! the trailing \n), any further input attempts will send a \a to
	//! uart_putchar() (BEL character), although line editing is still
	//! allowed.
	//!
	//! Input errors while talking to the UART will cause an immediate
	//! return of -1 (error indication).  Notably, this will be caused by a
	//! framing error (e. g. serial line "break" condition), by an input
	//! overrun, and by a parity error (if parity was enabled and automatic
	//! parity recognition is supported by hardware).
	//!
	//! Successive calls to uart_getchar() will be satisfied from the
	//! internal buffer until that buffer is emptied again.
	int getch(FILE *stream)
	{
		#if 1
		
		if (!rxReady())
			return _FDEV_EOF;
			
		uint8_t ch = read();
		return ch;
		
		#else
		uint8_t c;
		char *cp, *cp2;
		static char *rxp;

		if (rxp == 0)
			for (cp = rxbuf;;)
			{
				//loop_until_bit_is_set(UCSR0A, RXC0);
				while (!rxReady())
					;

				//if (UCSR0A & _BV(FE0))
				if (isOverrun())
					return _FDEV_EOF;
				//if (UCSR0A & _BV(DOR0))
				if (isFrameError())
					return _FDEV_ERR;
			
				//c = *psfr8_t (TUART::datax);	//UDR0;
				c = read();
			
				/* behaviour similar to Unix stty ICRNL */
				if (c == '\r')
					c = '\n';
				if (c == '\n')
				{
					*cp = c;
					putch(c, stream);
					rxp = rxbuf;
					break;
				}
				else if (c == '\t')
					c = ' ';

				if ((c >= (uint8_t)' ' && c <= (uint8_t)'\x7e') || c >= (uint8_t)'\xa0')
				{
					if (cp == rxbuf + MAX_UARTBUF - 1)
						putch('\a', stream);
					else
					{
						*cp++ = c;
						putch(c, stream);
					}
					continue;
				}

				switch (c)
				{
					case 'c' & 0x1f:
						return -1;

					case '\b':
					case '\x7f':
						if (cp > rxbuf)
						{
							putch('\b', stream);
							putch(' ', stream);
							putch('\b', stream);
							cp--;
						}
						break;

					case 'r' & 0x1f:
						putch('\r', stream);
						for (cp2 = rxbuf; cp2 < cp; cp2++)
							putch(*cp2, stream);
						break;

					case 'u' & 0x1f:
						while (cp > rxbuf)
						{
							putch('\b', stream);
							putch(' ', stream);
							putch('\b', stream);
							cp--;
						}
						break;

					case 'w' & 0x1f:
						while (cp > rxbuf && cp[-1] != ' ')
						{
							putch('\b', stream);
							putch(' ', stream);
							putch('\b', stream);
							cp--;
						}
						break;
				}
			}

		c = *rxp++;
		if (c == '\n')
			rxp = 0;

		return c;
		#endif
	}
	

protected:
private:

};



//extern Uart<UART0> uart0;

//extern int uart0_putchar (char c, FILE * stream);
//extern int uart0_getchar (FILE * stream);


#if 1
#ifdef UDR0

Uart<UART0> uart0;

inline int uart0_putchar (char c, FILE * stream)
{
	return uart0.putch(c, stream);
}


inline int uart0_getchar (FILE * stream)
{
	return uart0.getch(stream);
}

#endif


#ifdef UDR1

Uart<UART1> uart1;

inline int uart1_putchar (char c, FILE * stream)
{
	return uart1.putch(c, stream);
}


inline int uart1_getchar (FILE * stream)
{
	return uart1.getch(stream);
}

#endif


#ifdef UDR2

Uart<UART2> uart2;

inline int uart2_putchar (char c, FILE * stream)
{
	return uart2.putch(c, stream);
}


inline int uart2_getchar (FILE * stream)
{
	return uart2.getch(stream);
}

#endif


#ifdef UDR3

Uart<UART3> uart3;

inline int uart3_putchar (char c, FILE * stream)
{
	return uart3.putch(c, stream);
}


inline int uart3_getchar (FILE * stream)
{
	return uart3.getch(stream);
}

#endif
#endif	// 0

#endif /* UART_H_ */