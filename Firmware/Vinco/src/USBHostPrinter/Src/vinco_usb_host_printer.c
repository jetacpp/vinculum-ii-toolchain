/*
** vinco_usb_host_printer.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source code for the Vinco USB Host Printer Library.
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

#include "vinco_usb_host_printer.h"
#include "USB.h"
#include "USBHost.h"
#include "USBPrinter.h"
#include "USBHostPrinter.h"


VOS_HANDLE hUsbHost;
unsigned char printerDeviceNumber;

VN_STATUS VN_USBHostPrinterOpen(VN_HANDLE* vnHandle);
VN_STATUS VN_USBHostPrinterGetDeviceCapability(VN_HANDLE vnHandle, unsigned char *devCaps);
VN_STATUS VN_USBHostPrinterPortStatus(VN_HANDLE vnHandle, unsigned char *bufStatus);
VN_STATUS VN_USBHostPrinterSoftReset(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostPrinterWrite(VN_HANDLE vnHandle, uint8* data, uint16 numBytesToWrite, uint16* numBytesWritten);
VN_STATUS VN_USBHostPrinterClose(VN_HANDLE vnHandle);

void VN_USBHostPrinterInit(unsigned char printerDevNum, usb_host_printer_st *p)
{
	printerDeviceNumber = printerDevNum;
	
	p->open = &VN_USBHostPrinterOpen;
	p->getCapability = &VN_USBHostPrinterGetDeviceCapability;
	p->getPortStatus = &VN_USBHostPrinterPortStatus;
	p->softReset = &VN_USBHostPrinterSoftReset;
	p->write = &VN_USBHostPrinterWrite;
	p->close = &VN_USBHostPrinterClose;
}

void VN_USBHostPrinterAttachUSBHostHandle(VN_HANDLE hUsbHostMain)
{
	hUsbHost = hUsbHostMain;
}

VN_STATUS VN_USBHostPrinterOpen(VN_HANDLE* vnHandle)
{
	unsigned char i, connectState;
	VOS_HANDLE hPrinter;
	unsigned char printerstatus;
	usbhost_device_handle_ex ifDev = 0;
	usbhost_ioctl_cb_t hc_iocb;
	usbhost_ioctl_cb_class_t hc_iocb_class;
	usbHostPrinter_ioctl_t printer_iocb;
	usbHostPrinter_ioctl_cb_attach_t printerAtt;

	for (i = 0; i < 5; i++)
	{
		// Wait for enumeration of the printer to complete
		vos_delay_msecs(500);

		hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_GET_CONNECT_STATE;
		hc_iocb.get = &connectState;
		vos_dev_ioctl(hUsbHost, &hc_iocb);

		if (connectState == PORT_STATE_ENUMERATED)
		{
			break;
		}
	}

	if (connectState == PORT_STATE_ENUMERATED)
	{
		// Find Printer class device
		hc_iocb_class.dev_class = USB_CLASS_PRINTER;
		hc_iocb_class.dev_subclass = USB_SUBCLASS_ANY;
		hc_iocb_class.dev_protocol = USB_PROTOCOL_ANY;

		hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_DEVICE_FIND_HANDLE_BY_CLASS;
		hc_iocb.handle.dif = NULL;
		hc_iocb.set = &hc_iocb_class;
		hc_iocb.get = &ifDev;

	 	if (vos_dev_ioctl(hUsbHost, &hc_iocb) == USBHOST_OK)
		{
			hPrinter = vos_dev_open(printerDeviceNumber);
			printerAtt.hc_handle = hUsbHost;
			printerAtt.ifDev = ifDev;

			printer_iocb.ioctl_code = VOS_IOCTL_USBHOSTPRINTER_ATTACH;
			printer_iocb.set.att = &printerAtt;
			printerstatus = vos_dev_ioctl(hPrinter, &printer_iocb);
			if (printerstatus == USBHOSTPRINTER_OK)
			{
				*vnHandle = hPrinter;
				return (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
			}
			else
			{
				return (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;
			}
		}
		else
		{
			return (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;
		}
	}
	else
	{
		return (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;
	}
}

VN_STATUS VN_USBHostPrinterGetDeviceCapability(VN_HANDLE vnHandle, unsigned char *devCaps)
{
	usbHostPrinter_ioctl_t printer_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;

	printer_iocb.ioctl_code = VOS_IOCTL_USBHOSTPRINTER_GET_DEVICE_ID;
	if (vos_dev_ioctl(vnHandle, &printer_iocb) == USBHOSTPRINTER_OK)
	{
		*devCaps = *(printer_iocb.get.data);
		ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostPrinterPortStatus(VN_HANDLE vnHandle, unsigned char *bufStatus)
{
	usbHostPrinter_ioctl_t printer_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;

	printer_iocb.ioctl_code = VOS_IOCTL_USBHOSTPRINTER_PORT_STATUS;
	if (vos_dev_ioctl(vnHandle, &printer_iocb) == USBHOSTPRINTER_OK)
	{
		*bufStatus = *(printer_iocb.get.data);
		ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostPrinterSoftReset(VN_HANDLE vnHandle)
{
	usbHostPrinter_ioctl_t printer_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;

	printer_iocb.ioctl_code = VOS_IOCTL_USBHOSTPRINTER_SOFT_RESET;
	if (vos_dev_ioctl(vnHandle, &printer_iocb) == USBHOSTPRINTER_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostPrinterWrite(VN_HANDLE vnHandle, uint8* data, uint16 numBytesToWrite, uint16* numBytesWritten)
{
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_UNSUCCESSFUL;

	if (vos_dev_write(vnHandle, data, numBytesToWrite, numBytesWritten) == USBHOSTPRINTER_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostPrinterClose(VN_HANDLE vnHandle)
{
	usbHostPrinter_ioctl_t printer_iocb;

	printer_iocb.ioctl_code = VOS_IOCTL_USBHOSTPRINTER_DETACH;
	vos_dev_ioctl(vnHandle, &printer_iocb);

	vos_dev_close(vnHandle);

	return (VN_STATUS) VINCO_USBHOSTPRINTER_OK;
}
