/*
** vinco_usb_slave_ft232.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source code for the Vinco USB Slave FT232 Library
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

#include "vinco_usb_slave_ft232.h"

VOS_HANDLE hUsbSlave;
unsigned char ft232DeviceNumber;

VN_STATUS VN_USBSlaveFT232Open(VN_HANDLE *vnHandle);
VN_STATUS VN_USBSlaveFT232GetRXStatus(VN_HANDLE vnHandle, unsigned short *status);
VN_STATUS VN_USBSlaveFT232SetLatency(VN_HANDLE vnHandle, unsigned char latency);
VN_STATUS VN_USBSlaveFT232SetDescriptors(VN_HANDLE vnHandle, ft232DevDescriptors *descriptors);
VN_STATUS VN_USBSlaveFT232SetOutTransferSize(VN_HANDLE vnHandle, unsigned long size);
VN_STATUS VN_USBSlaveFT232Write(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten);
VN_STATUS VN_USBSlaveFT232Read(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead);
VN_STATUS VN_USBSlaveFT232Close(VN_HANDLE vnHandle);

/*
** Function: VN_USBSlaveFT232Init()
** Description: Attach the USBSlaveFT232 device number (in vinco.h) to the library.
**				Initialize the function pointers for exported user APIs.
** Parameters:  ft232DevNum: The device number assigned to USBSlaveFT232 driver
**				p : pointer to a structure of type usb_slave_ft232_st
** Returns:	None
** Requirements:
** Comments:
*/
void VN_USBSlaveFT232Init(unsigned char ft232DevNum, usb_slave_ft232_st *p)
{
	ft232DeviceNumber = ft232DevNum;

	p->open = &VN_USBSlaveFT232Open;
	p->getRXStatus = &VN_USBSlaveFT232GetRXStatus;
	p->setLatency = &VN_USBSlaveFT232SetLatency;
	p->setDescriptors = &VN_USBSlaveFT232SetDescriptors;
	p->setOutTransferSize = &VN_USBSlaveFT232SetOutTransferSize;
	p->read = &VN_USBSlaveFT232Read;
	p->write = &VN_USBSlaveFT232Write;
	p->close = &VN_USBSlaveFT232Close;
}

/*
** Function: VN_USBSlaveFT232AttachUSBSlaveHandle()
** Description: Attach the USBSlave handle (created in main.c) to the library.
** Parameters:  hUsbSlaveMain: The USBSlave handle
** Returns:	void
** Requirements:
** Comments:
*/
void VN_USBSlaveFT232AttachUSBSlaveHandle(VOS_HANDLE hUsbSlaveMain)
{
	hUsbSlave = hUsbSlaveMain;
}

/*
** Function: VN_USBSlaveFT232Open()
** Description: Open a handle to USBSlaveFT232 and return it.
** Parameters: vnHandle: Pointer to an un-initialized handle created by the sketch
** Returns:	If successful, the handle is returned in "vnHandle".
**			Besides, one of the following status messages is also returned:
**				VINCO_USBSLAVEFT232_UNSUCCESSFUL
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232Open(VN_HANDLE* vnHandle)
{
	VOS_HANDLE hFT232;
	common_ioctl_cb_t iocb;
	VN_STATUS retVal = (VN_STATUS) VINCO_USBSLAVEFT232_OK;

	// Open FT232
	hFT232 = vos_dev_open(ft232DeviceNumber);
	// Attach FT232BM to USB Slave port A
	iocb.ioctl_code = VOS_IOCTL_USBSLAVEFT232_ATTACH;
	iocb.set.data = (void *) hUsbSlave;
	if (vos_dev_ioctl(hFT232, &iocb) == USBSLAVEFT232_OK)
	{
		// Return the handle
		*vnHandle = hFT232;
	}
	else
	{
		retVal = (VN_STATUS) VINCO_USBSLAVEFT232_UNSUCCESSFUL;
	}

	return retVal;
}

/*
** Function: VN_USBSlaveFT232GetRXStatus()
** Description: Get the number of bytes available to read in the receiving buffer.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
**			   status: Variable to contain the returned value.
** Returns:	The number of bytes available is returned in "status".
**			The status message returned is always VINCO_USBSLAVEFT232_OK.
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232GetRXStatus(VN_HANDLE vnHandle, unsigned short *status)
{
	common_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_COMMON_GET_RX_QUEUE_STATUS;
	vos_dev_ioctl(vnHandle, &iocb);
	*status = iocb.get.queue_stat;

	return (VN_STATUS) VINCO_USBSLAVEFT232_OK;
}

/*
** Function: VN_USBSlaveFT232SetLatency()
** Description: Set the latency timer period.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
**			   latency: The latency time. Valide values are in the range 2-255.
** Returns:	One of the following status messages is returned:
**				VINCO_USBSLAVEFT232_INVALID_PARAMETER
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232SetLatency(VN_HANDLE vnHandle, unsigned char latency)
{
	common_ioctl_cb_t iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_INVALID_PARAMETER;;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVEFT232_SET_LATENCY;
	iocb.set.data = (void *) latency;
	if (vos_dev_ioctl(vnHandle, &iocb) == USBSLAVEFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_OK;
	}

	return ret_val;
}

/*
** Function: VN_USBSlaveFT232SetDescriptors()
** Description: Set user-specified descriptors for an FT232 device.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open.
**			   descriptors: A pointer to a usbslaveft232_ioctl_cb_descriptors_t struct.
** Returns:	One of the following status messages is returned:
**				VINCO_USBSLAVEFT232_UNSUCCESSFUL
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments: ft232DevDescriptors is just another name of usbslaveft232_ioctl_cb_descriptors_t
*/
VN_STATUS VN_USBSlaveFT232SetDescriptors(VN_HANDLE vnHandle, ft232DevDescriptors *descriptors)
{
	common_ioctl_cb_t iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_UNSUCCESSFUL;

	// Set descriptors for FT232 device
	iocb.ioctl_code = VOS_IOCTL_USBSLAVEFT232_SET_DESCRIPTORS;
	iocb.set.data = descriptors;
	if (vos_dev_ioctl(vnHandle, &iocb) == USBSLAVEFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_OK;
	}

	return ret_val;
}

/*
** Function: VN_USBSlaveFT232SetOutTransferSize()
** Description: set max packet size for out transfer (for customers who want better performance).
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
**			   size: The max packet size.
** Returns:	One of the following status messages is returned:
**				VINCO_USBSLAVEFT232_UNSUCCESSFUL
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232SetOutTransferSize(VN_HANDLE vnHandle, unsigned long size)
{
	common_ioctl_cb_t iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_UNSUCCESSFUL;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVEFT232_SET_OUT_TRANSFER_SIZE;
	iocb.set.data = (void *) size;
	if (vos_dev_ioctl(vnHandle, &iocb) == USBSLAVEFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_OK;
	}

	return ret_val;
}

/*
** Function: VN_USBSlaveFT232Write()
** Description: write data to a FT232 device.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
**			   data: Pointer to the buffer containing the data.
**			   numBytesToWrite: number of bytes to write.
**			   numBytesWritten: number of bytes actually written.
** Returns:	One of the following status messages is returned:
**				VINCO_USBSLAVEFT232_UNSUCCESSFUL
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232Write(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten)
{
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_UNSUCCESSFUL;

	if (vos_dev_write(vnHandle, data, numBytesToWrite, numBytesWritten) == USBSLAVEFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_OK;
	}

	return ret_val;
}

/*
** Function: VN_USBSlaveFT232Read()
** Description: read data from a FT232 device.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
**			   data: Pointer to the buffer that will contain the data.
**			   numBytesToRead: number of bytes to read.
**			   numBytesRead: number of bytes actually read.
** Returns:	One of the following status messages is returned:
**				VINCO_USBSLAVEFT232_UNSUCCESSFUL
**				VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232Read(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead)
{
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_UNSUCCESSFUL;

	if (vos_dev_read(vnHandle, data, numBytesToRead, numBytesRead) == USBSLAVEFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBSLAVEFT232_OK;
	}

	return ret_val;
}

/*
** Function: VN_USBSlaveFT232Close()
** Description: close the FT232 device handle.
** Parameters: vnHandle: The USBSlaveFT232 handle created by VN_USBSlaveFT232Open
** Returns:	VINCO_USBSLAVEFT232_OK
** Requirements:
** Comments:
*/
VN_STATUS VN_USBSlaveFT232Close(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVEFT232_DETACH;
	vos_dev_ioctl(vnHandle, &iocb);

	vos_dev_close(vnHandle);

	return (VN_STATUS) VINCO_USBSLAVEFT232_OK;
}
