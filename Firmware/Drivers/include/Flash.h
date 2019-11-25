/*
** Flash.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II Flash API
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II Flash API
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __FLASH_H__
#define __FLASH_H__

#define FLASH_VERSION_STRING "2.0.2"

enum FLASH_STATUS {
    FLASH_OK = 0,
    FLASH_INVALID_PAGE,
    FLASH_ERASE_ERROR,
    FLASH_PROGRAM_ERROR,
};

#define FLASH_PAGESIZE_WORDS 64        // Data on the flash is organized in 64 word sectors.
#define FLASH_PAGESIZE_BYTES 128       // For convenience that's 128 bytes in a sector
#define FLASH_LOCKEDPAGES	 15        // Locked pages are reserved and may not be used

// dataBuffer size on both flash_writePage and flash_readPage must be large enough for a whole page
unsigned char flash_writePage(unsigned short page, unsigned char *dataBuffer);
unsigned char flash_readPage(unsigned short page, unsigned char *dataBuffer);

#endif                                 /* __FLASH_H__ */

