/*
** sdcard.h
**
** Copyright © 2010-2011 Future Technology Devices International Limited
**
** Header file for Vinculum II SD Card Driver
** Header File
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II Applications
** Requires: VOS, SPI Master, MSI
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef _SD_H_
#define _SD_H_

#define SDCARD_VERSION_STRING "2.0.2"

unsigned char sd_init(unsigned char devNum);

// ==============================================================================
//  SD Card attach structure
// ==============================================================================
typedef struct _sdcard_ioctl_cb_attach_t
{
    VOS_HANDLE	  spi_master_handle;
    VOS_HANDLE	  gpio_handle;
    unsigned char spi_master_dma_mode;
    unsigned char WP_Bit;              // GPIO bit to use for card write protect
    unsigned char CD_Bit;              // GPIO bit to use for card detect
} sdcard_ioctl_cb_attach_t;

// ==============================================================================
//  SD Card IOCTLS
// ==============================================================================
// TODO: Move this to the MSI header file?
#define     MSI_IOCTL_SD_CARD_ATTACH	  0x01 // Attach SPI Master driver to SD Card driver.
#define     MSI_IOCTL_SD_CARD_INIT		  0x02 // Init an SD Card in SPI mode.
#define     MSI_IOCTL_SD_GET_CARD_TYPE	  0x03 // Return Card type, as list below.
#define     MSI_IOCTL_SD_CARD_DETECT	  0x04 // Check for SD Card insertion.
#define     MSI_IOCTL_SD_CARD_WAIT_INSERT 0x05 // Wait for SD Card insertion.
#define     MSI_IOCTL_SD_WRITE_PROTECT	  0x06 // Check for SD Card write protection.
#define     MSI_IOCTL_SD_CARD_DETACH	  0x07 // Detach SPI Master driver from SD Card driver.

// SD Card Types
#define     SD_INV						  0xFF // Invalid SD Card
#define     SD_V1						  0x01 // v1.0 or less
#define     SD_V2						  0x02 // v2.0
#define     SD_HC						  0x03 // SD High Capacity card
#define     SD_MMC						  0x04 // MMC card not SD

#define     SD_CARD_PRESENT				  0x01 // SD Card is detected.
#define     SD_CARD_WRITE_PROTECTED		  0x01 // SD Card is write protected.

// ==============================================================================
//  SD Card Return Codes
// ==============================================================================
enum SD_CARD_STATUS {
    SD_OK = 0x00,
    SD_INVALID_PARAMETER,
    SD_INITIALIZATION_FAILED,
    SD_INVALID_CARD,
    SD_CMD_FAILED,
    SD_READ_FAILED,
    SD_WRITE_FAILED,
    SD_FRAME_ERROR,
    SD_WRITE_PROTECTED,
    SD_FATAL_ERROR = 0xFF
};

#endif                                 /* _SD_H_ */
