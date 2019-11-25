/*
** analog_IO.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Analog I/O Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 – initial version
*/

#include "vos.h"

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

void analogWrite(uint8 pin, uint8 value);
uint16 analogRead(uint8 pin);
