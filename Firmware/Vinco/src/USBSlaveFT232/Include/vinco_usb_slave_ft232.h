/*
** vinco_usb_slave_ft232.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the Vinco USB Slave FT232 Library
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

#ifndef _VN_USBSLAVEFT232_H_
#define _VN_USBSLAVEFT232_H_

#include "vos.h"
#include "devman.h"
#include "USB.h"
#include "USBSlave.h"
#include "USBSlaveFT232.h"

typedef VOS_HANDLE VN_HANDLE;
typedef unsigned char VN_STATUS;

typedef usbslaveft232_ioctl_cb_descriptors_t ft232DevDescriptors;

typedef VN_STATUS (*FT232DEV_OPEN)(VN_HANDLE *vnHandle);
typedef VN_STATUS (*FT232DEV_GET_RX_STATUS)(VN_HANDLE vnHandle, unsigned short *status);
typedef VN_STATUS (*FT232DEV_SET_LATENCY)(VN_HANDLE vnHandle, unsigned char latency);
typedef VN_STATUS (*FT232DEV_SET_DESCRIPTORS)(VN_HANDLE vnHandle, ft232DevDescriptors *descriptors);
typedef VN_STATUS (*FT232DEV_SET_OUT_TRANSFER_SIZE)(VN_HANDLE vnHandle, unsigned long size);
typedef VN_STATUS (*FT232DEV_WRITE)(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten);
typedef VN_STATUS (*FT232DEV_READ)(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead);
typedef VN_STATUS (*FT232DEV_CLOSE)(VN_HANDLE vnHandle);

typedef struct _usb_slave_ft232_st
{
	FT232DEV_OPEN 						open;
	FT232DEV_GET_RX_STATUS				getRXStatus;
	FT232DEV_SET_LATENCY				setLatency;
	FT232DEV_SET_DESCRIPTORS 			setDescriptors;
	FT232DEV_SET_OUT_TRANSFER_SIZE	   	setOutTransferSize;
	FT232DEV_READ   					read;
	FT232DEV_WRITE	   					write;
	FT232DEV_CLOSE						close;
} usb_slave_ft232_st;

void VN_USBSlaveFT232Init(unsigned char ft232DevNum, usb_slave_ft232_st *p);
void VN_USBSlaveFT232AttachUSBSlaveHandle(VOS_HANDLE hUsbSlaveMain);

enum VINCO_USBSLAVEFT232_STATUS
{
	VINCO_USBSLAVEFT232_OK = 0,
	VINCO_USBSLAVEFT232_UNSUCCESSFUL,
	VINCO_USBSLAVEFT232_INVALID_PARAMETER,
	VINCO_USBSLAVEFT232_FATAL_ERROR = 0xFF
};

#endif /* _VN_USBSLAVEFT232_H_ */
