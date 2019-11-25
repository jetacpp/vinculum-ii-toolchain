/*
** vinco_usb_host_printer.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the Vinco USB Host Printer Library.
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

#ifndef _VN_HOST_PRINTER_H_
#define _VN_HOST_PRINTER_H_

#include "vos.h"
#include "devman.h"

typedef VOS_HANDLE VN_HANDLE;
typedef unsigned char VN_STATUS;

typedef VN_STATUS (*OPEN)(VN_HANDLE* vnHandle);
typedef VN_STATUS (*GET_CAPABILITY)(VN_HANDLE vnHandle, unsigned char *devCaps);
typedef VN_STATUS (*PORT_STATUS)(VN_HANDLE vnHandle, unsigned char *bufStatus);
typedef VN_STATUS (*SOFT_RESET)(VN_HANDLE vnHandle);
typedef VN_STATUS (*WRITE)(VN_HANDLE vnHandle, uint8* data, uint16 numBytesToWrite, uint16* numBytesWritten);
typedef VN_STATUS (*CLOSE)(VN_HANDLE vnHandle);

typedef struct _usb_host_printer_st
{
	OPEN 			open;
	GET_CAPABILITY 	getCapability;
	PORT_STATUS	   	getPortStatus;
	SOFT_RESET   	softReset;
	WRITE	   		write;
	CLOSE			close;
} usb_host_printer_st;

void VN_USBHostPrinterInit(unsigned char printerDevNum, usb_host_printer_st *p);
void VN_USBHostPrinterAttachUSBHostHandle(VOS_HANDLE hUsbHostMain);

enum VINCO_USBHOSTPRINTER_STATUS
{
	VINCO_USBHOSTPRINTER_OK = 0,
	VINCO_USBHOSTPRINTER_UNSUCCESSFUL,
	VINCO_USBHOSTPRINTER_FATAL_ERROR = 0xFF
};

#endif /* _VN_HOST_PRINTER_H_ */
