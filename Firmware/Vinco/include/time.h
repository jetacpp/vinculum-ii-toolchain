/*
** time.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Time Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
**
** History:
**  1 – initial version
*/

#ifndef __TIME_H__
#define __TIME_H__

#include "vos.h"

uint32 millis();
uint32 micros();
void delay(uint16 ms);
void delayMicroseconds48Mhz(uint32 duration);
void delayMicroseconds24Mhz(uint32 duration);
void delayMicroseconds12Mhz(uint32 duration);

#endif

