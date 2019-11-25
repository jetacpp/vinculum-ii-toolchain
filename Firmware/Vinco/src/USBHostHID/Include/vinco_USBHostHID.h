/*
** vinco_USBHostHID.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the Vinco USB Host HID Library.
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

#ifndef _VN_USB_HOST_HID_H_
#define _VN_USB_HOST_HID_H_

typedef unsigned short VN_HANDLE;
typedef unsigned char VN_STATUS;


// function return status values
enum VINCO_USBHOSTHID_STATUS
{
	VINCO_USBHOSTHID_OK = 0,
	VINCO_USBHOSTHID_INVALID_PARAMETER,
	VINCO_USBHOSTHID_ERROR,
	VINCO_USBHOSTHID_NOT_FOUND,
	VINCO_USBHOSTHID_USBHOST_ERROR = 0x80,
	VINCO_USBHOSTHID_FATAL_ERROR = 0xFF
};


typedef unsigned char (*USB_HOST_HID_OPEN)(VN_HANDLE*  vnHandle, uint16 class,
											uint16 subClass, uint16 protocol);

typedef unsigned char (*USB_HOST_HID_GET_DESCRIPTOR)(VN_HANDLE vnHandle,
	uint8 descriptorType,uint8 descriptorIndex, uint8* descriptorBuffer,
	uint8* descriptorLength );

typedef unsigned char (*USB_HOST_HID_GET_REPORT)(VN_HANDLE vnHandle,
	uint8 reportType, uint8 reportID, uint8* reportBuffer, uint16 reportLength);

typedef unsigned char (*USB_HOST_HID_GET_IDLE)(VN_HANDLE vnHandle,
	uint8 reportID, uint8* idleDuration);

typedef unsigned char (*USB_HOST_HID_GET_PROTOCOL)(VN_HANDLE vnHandle,
	uint8* protocolType);

typedef unsigned char (*USB_HOST_HID_SET_REPORT)(VN_HANDLE vnHandle,
	uint8 reportType, uint8 reportID, uint8* reportBuffer, uint16 reportLength);


/*idleDuration is 0 (zero): the duration is indefinite,only reporting
when a change is detected in the report data.
idleDuration is 0x01 - 0xFF: the duration is (idleDuration x 4 msec)*/
typedef unsigned char (*USB_HOST_HID_SET_IDLE)(VN_HANDLE vnHandle,
	uint8 reportID,	uint8 idleDuration);

typedef unsigned char (*USB_HOST_HID_SET_PROTOCOL)(VN_HANDLE vnHandle,
	uint8 protocolType);

typedef unsigned char (*USB_HOST_HID_READ)(VN_HANDLE vnHandle,
	uint8* readBuffer, uint16 bytesToRead, uint16* bytesRead);

typedef unsigned char (*USB_HOST_HID_CLOSE)(VOS_HANDLE vnHandle);


typedef struct _usb_host_HID_st
{
	USB_HOST_HID_OPEN 			open;
	USB_HOST_HID_GET_DESCRIPTOR getDescriptor;
	USB_HOST_HID_GET_REPORT	   	getReport;
	USB_HOST_HID_GET_IDLE   	getIdle;
	USB_HOST_HID_GET_PROTOCOL	getProtocol;
	USB_HOST_HID_SET_REPORT	   	setReport;
	USB_HOST_HID_SET_IDLE   	setIdle;
	USB_HOST_HID_SET_PROTOCOL	setProtocol;
	USB_HOST_HID_READ			read;
	USB_HOST_HID_CLOSE			close;
} usb_host_HID_st;


void VN_USBHostHIDAttachUSBHostHandle(VOS_HANDLE hUsbHostMain);

/* this function must be called first while using this library */
void VN_USBHostHIDInit(unsigned char hostHIDDevNum, usb_host_HID_st *p);

#endif /* _VN_USB_HOST_HID_H_ */
