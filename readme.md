# AVR Libraries - Core Functions

avrlibs are libraries of functions for the Atmel AVR Mega and Tiny microcontrollers.  Written in C/C++
yet highly optimized to give speed comparable with assembly.

In this library are the following functions:

* analoginput.h - methods to configure and read the analogue inputs 
* CommonDefs.h - common methods used by other files
* exinterrupts.h - methods for use with the Extenal Interrupt pins
* fastio.h - fast access for the general input/output pins and ports (GPIO)
* pinchangeints.h - methods for use with the Pin Change Interrupts
* spiMaster.h - methods for using the SPI or USI interface in master mode
* spiSlave.h - methods for using the SPI or USI interface in slave mode
* timer8.h - methods for manipulating the 8 bit timers: timer0, timer2
* timer16.h - methods for manipulating the 16 bit timers: timer1, timer3, timer4, timer5
* twiMaster.h - methods for using the TWI or USI interface in master mode
* uart.h - methods for interfacing to the onboard UARTs
