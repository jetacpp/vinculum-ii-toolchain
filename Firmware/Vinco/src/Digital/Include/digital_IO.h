/*
** digital_IO.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Digital I/O Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 – initial version
*/

#ifndef _DIGITAL_IO_H_
#define _DIGITAL_IO_H_

#include "vos.h"

/* Pin Numbers. Users can use 2 formats to specify a pin, either Jx_y or numeric value */
#define J3_1		  0
#define J3_2		  1
#define J3_3		  2
#define J3_4		  3
#define J3_5		  4
#define J3_6		  5
#define J3_7		  6
#define J3_8		  7

#define J4_1		  8
#define J4_2		  9
#define J4_3		  10
#define J4_4		  11
#define J4_5		  12
#define J4_6		  13
#define J4_7		  14
#define J4_8		  15

#define J5_1		  16
#define J5_2		  17
#define J5_3		  18
#define J5_4		  19
#define J5_5		  20
#define J5_6		  21
#define J5_7		  22
#define J5_8		  23

#define J6_1		  24
#define J6_2		  25
#define J6_3		  26
#define J6_4		  27
#define J6_5		  28
#define J6_6		  29
#define J6_7		  30
#define J6_8		  31

#define LED1		  32
#define LED2		  33

/* Vinco port names */
#define J3			  1
#define J4			  2
#define J5			  3
#define J6			  4

/* Possible values */
#ifndef HIGH
	#define HIGH	  1
#endif
#ifndef LOW
	#define LOW		  0
#endif

/* Modes */
#define INPUT		  0
#define OUTPUT		  1

/* Returned Messages */
#define SUCCESSFUL	  0
#define INVALID_PIN	  -1
#define INVALID_MODE  -2
#define INVALID_VALUE -3
#define INVALID_PORT  -4

/* APIs for pin access */
int8 pinMode(uint8 pin, uint8 mode);
uint8 digitalRead(uint8 pin);
int8 digitalWrite(uint8 pin, uint8 value);

/* APIs for port access */

/* It should be noted that "port" on Vinco means "jumper" (J3, J4, J6, J7),
   not "GPIO port" on the Vinculum II (i.e. port A, B, C, D, E) */
int8 portMode(uint8 portName, uint8 mode);
uint8 portRead(uint8 portName);
int8 portWrite(uint8 portName, uint8 value);

#endif                                 /* _DIGITAL_IO_H_ */
