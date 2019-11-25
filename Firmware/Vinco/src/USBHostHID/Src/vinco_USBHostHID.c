/*
** vinco_USBHostHID.c
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

// include files
#include "vos.h"
#include "vinco_USBHostHID.h"
#include "USB.h"
#include "USBHost.h"
#include "USBHID.h"
#include "USBHostHID.h"

// definitions
#define DELAY_BETWEEN_ENUMERATION	500
#define TRY_ENUMERATION_COUNT		5

// variables
VOS_HANDLE hVincoUSBHostHID;
unsigned char vincoUSBHostHIDDeviceNumber;


// functions

VN_STATUS VN_USBHostHIDOpenWithClass(VN_HANDLE*  vnHandle, uint16 class,
	uint16 subClass, uint16 protocol);

VN_STATUS VN_USBHostHIDGetDescriptor(VN_HANDLE vnHandle, uint8 descriptorType,
	uint8 descriptorIndex, uint8* descriptorBuffer,uint8* descriptorLength );

VN_STATUS VN_USBHostHIDGetReport(VN_HANDLE vnHandle,uint8 reportType,
	uint8 reportID, uint8* reportBuffer, uint16 reportLength);

VN_STATUS VN_USBHostHIDGetIdle(VN_HANDLE vnHandle, uint8 reportID, uint8* idleDuration);

VN_STATUS VN_USBHostHIDGetProtocol(VN_HANDLE vnHandle, uint8* protocolType);

VN_STATUS VN_USBHostHIDSetReport(VN_HANDLE vnHandle, uint8 reportType,
	uint8 reportID, uint8* reportBuffer, uint16 reportLength );

VN_STATUS VN_USBHostHIDSetIdle(VN_HANDLE vnHandle, uint8 reportID,
	uint8 idleDuration);

VN_STATUS VN_USBHostHIDSetProtocol(VN_HANDLE vnHandle, uint8 protocolType);

VN_STATUS VN_USBHostHIDRead(VN_HANDLE vnHandle, uint8* readBuffer,
	uint16 bytesToRead, uint16* bytesRead);

VN_STATUS VN_USBHostHIDClose(VOS_HANDLE vnHandle);


/*
** Function: VN_USBHostHIDInit()
** Description: Initialize the USBHostHID driver and register's VincoUSBHostHID Library
** Parameters:  hostHIDDevNum: The device number to USBHostHID driver
**				p : pointer to structure of type usb_host_HID_st containing
**					function pointers
** Returns:	None
** Requirements:
** Comments:
*/
void VN_USBHostHIDInit(unsigned char hostHIDDevNum, usb_host_HID_st *p)
{
	vincoUSBHostHIDDeviceNumber = hostHIDDevNum;
	usbHostHID_init(hostHIDDevNum);

	p->open = &VN_USBHostHIDOpenWithClass;
	p->getDescriptor = &VN_USBHostHIDGetDescriptor;
	p->getReport = &VN_USBHostHIDGetReport;
	p->getIdle = &VN_USBHostHIDGetIdle;
	p->getProtocol = &VN_USBHostHIDGetProtocol;
	p->setReport = &VN_USBHostHIDSetReport;
	p->setIdle = &VN_USBHostHIDSetIdle;
	p->setProtocol = &VN_USBHostHIDSetProtocol;
	p->read = &VN_USBHostHIDRead;
	p->close = &VN_USBHostHIDClose;
}


/*
** Function: VN_USBHostHIDAttachUSBHostHandle()
** Description: Get the USBHost handle to access the USBHost
** Parameters:  hUsbHostMain: USBHost handle
**
** Returns:	None
** Requirements:
** Comments:
*/
void VN_USBHostHIDAttachUSBHostHandle(VOS_HANDLE hUsbHostMain)
{
	hVincoUSBHostHID = hUsbHostMain;
}


/*
** Function: VN_USBHostHIDOpenWithClass()
** Description: Finds a USBdevice based on class returns a handle
** Parameters:  vnHandle: handle to the HID device
**				class: USB class code
**				subClass: USB sub class code
**				protocol: USB protocol code
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDOpenWithClass(VN_HANDLE*  vnHandle, uint16 class,
									uint16 subClass, uint16 protocol)
{
	usbhost_device_handle_ex ifDev = 0;
	usbhost_ioctl_cb_t hc_iocb;
	usbhost_ioctl_cb_class_t hc_iocb_class;
	usbHostHID_ioctl_cb_attach_t hid_att;
	usbHostHID_ioctl_t hid_iocb;
	VOS_HANDLE hHID = NULL;
	unsigned char i, connectStatus;

	for (i = 0; i < TRY_ENUMERATION_COUNT; i++)
	{
		// Wait for enumeration of the HID device to complete
		vos_delay_msecs(DELAY_BETWEEN_ENUMERATION);

		hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_GET_CONNECT_STATE;
		hc_iocb.get = &connectStatus;
		vos_dev_ioctl(hVincoUSBHostHID, &hc_iocb);

		if (connectStatus == PORT_STATE_ENUMERATED)
		{
			// find class, subclass and protocol of the device
			hc_iocb_class.dev_class = class;
			hc_iocb_class.dev_subclass = subClass;
			hc_iocb_class.dev_protocol = protocol;

			// user ioctl to find USBHost device
			hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_DEVICE_FIND_HANDLE_BY_CLASS;
			hc_iocb.handle.dif = NULL;
			hc_iocb.set = &hc_iocb_class;
			hc_iocb.get = &ifDev;

			if (vos_dev_ioctl(hVincoUSBHostHID,&hc_iocb))
			{
				*vnHandle = NULL;
				return (VN_STATUS) VINCO_USBHOSTHID_ERROR;
			}

			// open a handle to the HID device
			hHID = vos_dev_open(vincoUSBHostHIDDeviceNumber);

			// now we have a device, Check whether the device is HID
			hid_att.hc_handle = hVincoUSBHostHID;
			hid_att.ifDev = ifDev;
			hid_iocb.set.att = &hid_att;
			hid_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_ATTACH;

			if (vos_dev_ioctl(hHID, &hid_iocb))
			{
				vos_dev_close(hHID);
				*vnHandle = NULL;
				return (VN_STATUS) VINCO_USBHOSTHID_ERROR;
			}
			else
			{
				*vnHandle = hHID;
				return (VN_STATUS) VINCO_USBHOSTHID_OK;
			}
			break;
		} /* end of if PORT_STATE_ENUMERATED */
	} /* end of for loop */

	return (VN_STATUS) VINCO_USBHOSTHID_ERROR;


}


/*
** Function: VN_USBHostHIDGetDescriptor()
** Description: Gets the descriptor from the USB HID device
** Parameters:  vnHandle: USB HID device handle
**				descriptorType: descriptor type
**				descriptorIndex: index for the selected descriptor type
**				descriptorBuffer: pointer to the buffer to receive the descriptor
**				descriptorLength: length of the descriptor
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDGetDescriptor(VN_HANDLE vnHandle, uint8 descriptorType,
	uint8 descriptorIndex, uint8* descriptorBuffer,uint8* descriptorLength )
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.descriptorType = descriptorType;
	HID_iocb.descriptorIndex = descriptorIndex;
	HID_iocb.Length = descriptorLength;
	HID_iocb.get.data = descriptorBuffer;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_GET_DESCRIPTOR;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDGetReport()
** Description: Gets the report of the selected report type and report index
** Parameters:  vnHandle: USB HID device handle
**				reportType: report type can be input , output and feature
**				reportID: report ID for the selected report type
**				reportBuffer: pointer to the buffer to receive the report
**				reportLength: length of the report
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDGetReport(VN_HANDLE vnHandle,uint8 reportType,
	uint8 reportID, uint8* reportBuffer, uint16 reportLength)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.reportType = reportType;
	HID_iocb.reportID = reportID;
	HID_iocb.Length = reportLength;
	HID_iocb.get.data = reportBuffer;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_GET_REPORT;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDGetIdle()
** Description: Gets the idle duration of the selected input report
** Parameters:  vnHandle: USB HID device handle
**				reportID: report ID for the input report type
**				idleDuration:  idle duration
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDGetIdle(VN_HANDLE vnHandle, uint8 reportID, uint8* idleDuration)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.reportID = reportID;
	HID_iocb.get.data = idleDuration;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_GET_IDLE;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDGetProtocol()
** Description: Gets the currently active protocol
** Parameters:  vnHandle: USB HID device handle
**				protocolType: pointer to the buffer to receive the current active protocol
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDGetProtocol(VN_HANDLE vnHandle, uint8* protocolType)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.get.data = protocolType;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_GET_PROTOCOL;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDSetReport()
** Description: Gets the report of the selected report type and report index
** Parameters:  vnHandle: USB HID device handle
**				reportType: report type can be input , output and feature
**				reportID: report ID for the selected report type
**				reportBuffer: pointer to the input buffer to send the report
**				reportLength: length of the report
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDSetReport(VN_HANDLE vnHandle, uint8 reportType,
	uint8 reportID, uint8* reportBuffer, uint16 reportLength )
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.reportType = reportType;
	HID_iocb.reportID = reportID;
	HID_iocb.Length = reportLength;
	HID_iocb.set.data = reportBuffer;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_SET_REPORT;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDSetIdle()
** Description: Set the value of the idle duration for the input report type
** Parameters:  vnHandle: USB HID device handle
**				reportID: report ID for the selected report type
**				idleDuration: idle duration for the input report
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDSetIdle(VN_HANDLE vnHandle, uint8 reportID,
	uint8 idleDuration)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.reportID = reportID;
	HID_iocb.idleDuration = idleDuration;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_SET_IDLE;
	return (VN_STATUS) vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDSetProtocol()
** Description: Sets the current active protocol
** Parameters:  vnHandle: USB HID device handle
**				protocolType: value of the active protocol ( boot or report)
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDSetProtocol(VN_HANDLE vnHandle, uint8 protocolType)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.protocolType = protocolType;
	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_SET_PROTOCOL;
	return (VN_STATUS)vos_dev_ioctl(vnHandle, &HID_iocb);
}


/*
** Function: VN_USBHostHIDRead()
** Description: read the data from the INT IN endpoint
** Parameters:  vnHandle: USB HID device handle
**				readBuffer: pointer to the buffer to receive the data from INT IN endpoint
**				bytesToRead: number of bytes to read
**				bytesRead: number of bytes actually read
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDRead(VN_HANDLE vnHandle, uint8* readBuffer,
							uint16 bytesToRead, uint16* bytesRead)
{
	return (VN_STATUS)vos_dev_read(vnHandle, readBuffer, bytesToRead, bytesRead);
}


/*
** Function: VN_USBHostHIDClose()
** Description: close the HID device
** Parameters:  vnHandle: USB HID device handle
** Returns:	VN_STATUS
** Requirements:
** Comments:
*/
VN_STATUS VN_USBHostHIDClose(VOS_HANDLE vnHandle)
{
	usbHostHID_ioctl_t HID_iocb;

	HID_iocb.ioctl_code = VOS_IOCTL_USBHOSTHID_DETACH;
	vos_dev_ioctl(vnHandle, &HID_iocb);

	vos_dev_close(vnHandle);

	return (VN_STATUS) VINCO_USBHOSTHID_OK;
}
