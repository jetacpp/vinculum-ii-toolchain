/*
** USBPrinter.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Printer devices.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave and USB Host Printer Drivers
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBPRINTER_H__
#define __USBPRINTER_H__

#define USBPRINTER_VERSION_STRING "2.0.2"

// Table 1 Printer Class-Specific Request Values
//		bRequest										Value
#define USB_PRINTER_REQUEST_CODE_GET_DEVICE_ID 0x00
#define USB_PRINTER_REQUEST_CODE_GET_STATUS	   0x01
#define USB_PRINTER_REQUEST_CODE_SOFT_RESET	   0x02

// Table 3 Printer Port Status Bitmask Values
#define USB_PRINTER_STATUS_PAPER_EMPTY		   0x20
#define USB_PRINTER_STATUS_SELECT			   0x10
#define USB_PRINTER_STATUS_NOT_ERROR		   0x08

#endif                                 /* __USBPRINTER_H__ */
