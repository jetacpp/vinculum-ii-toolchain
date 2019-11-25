/*
** mp3.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the MP3 Library.
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef _MP3_H_
#define _MP3_H_

#include "vos.h"

typedef void (*MP3_BEGIN)(void);
typedef void (*SET_VOLUME)(uint8 leftVolume, uint8 rightVolume);
typedef void (*SET_BASS)(uint8 amplitude, uint8 freqLimit);
typedef void (*SET_TREBLE)(uint8 amplitude, uint8 freqLimit);
typedef uint16 (*SEND)(uint8 *buffer, uint16 numBytesToWrite);
typedef void (*SENT)(void);
typedef void (*CANCEL)(void);
typedef void (*SOFT_RESET)(void);
typedef void (*HARD_RESET)(void);

typedef struct _mp3_st
{
	MP3_BEGIN 		begin;
	SET_VOLUME 		setVolume;
	SET_BASS	   	setBass;
	SET_TREBLE   	setTreble;
	SEND	   		send;
	SENT  			sent;
	CANCEL   		cancel;
	SOFT_RESET   	softReset;
	HARD_RESET   	hardReset;
} mp3_st;

void mp3_init_func_ptrs(mp3_st *m);
void mp3_attach_MP3_VS1053b_driver_handle(VOS_HANDLE hMP3Main);
void mp3_attach_SPI_master_driver_handle(VOS_HANDLE hSpiMasterMain);

#endif /*_MP3_H_*/
