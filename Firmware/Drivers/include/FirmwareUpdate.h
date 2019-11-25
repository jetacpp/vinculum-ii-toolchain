/*
** FirmwareUpdate.h
**
** Copyright © 2010-2011 Future Technology Devices International Limited
**
**  C Header file for Vinculum II sample application
** Main module
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II Reflasher Library
** Requires: VOS BOMS FAT UART USBHost GPIO STDIO
** Comments: Update Flash from flash disk
**
** History:
**  1 – Initial version
**
*/
#ifndef FIRMWARE_UPDATE_H
#define FIRMWARE_UPDATE_H

#define FIRMWARE_UPDATE_VERSION_STRING "2.0.2"

#define FIRMWARE_UPDATE_OK				 0
#define FIRMWARE_UPDATE_INVALID_FILE	 1
#define FIRMWARE_UPDATE_NO_REFLASHER	 2

#define FIRMWARE_UPDATE_FEEDBACK_NONE	 0
#define FIRMWARE_UPDATE_FEEDBACK_UART	 (1 << 8)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A	 (2 << 8)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A0 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x01)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A1 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x02)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A2 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x04)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A3 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x08)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A4 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x10)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A5 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x20)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A6 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x40)
#define FIRMWARE_UPDATE_FEEDBACK_GPIO_A7 (FIRMWARE_UPDATE_FEEDBACK_GPIO_A | 0x80)

unsigned char FirmwareUpdateFATFile(file_context_t *file, unsigned int reflasherAddress);
unsigned char FirmwareUpdateFATFileFeedback(file_context_t *file, unsigned int reflasherAddress, unsigned short feedback);

#endif
