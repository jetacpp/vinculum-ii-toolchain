/*
** Vinco_USBH.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
**
** Header file containing the list of APIs for the USB Host library.
**
** Author: FTDI
** Project: Vinco Library
** Module: Vinco USB Host
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef _USBH_CORE
#define _USBH_CORE


#include "USB.h"
#include "USBHost.h"

#define USB_HOST_1 -1


#define USB_PORT_1 0
#define USB_PORT_2 1

typedef unsigned char  uchar;
typedef unsigned short ushort;

typedef VOS_HANDLE (*OPEN_HOST_DEV)(void);
typedef void (*CLOSE_HOST_DEV)(void);
typedef void (*USBHOST_INIT)(uchar deviceNumber, uchar ifCnt, uchar epCnt, uchar xferCnt, uchar isoxferCnt);
typedef uchar (*HC_READ)(uint8 *xfer, uint16 num_bytes_to_read, uint16 *num_bytes_read);
typedef uchar (*HC_WRITE)(uint8 *xfer, uint16 num_bytes_to_write, uint16 *num_bytes_write);
typedef uchar (*SETUP)(usbhost_ep_handle *e, usb_deviceRequest_t *req, uchar *setup_data);
typedef uchar (*CMDCTL)(struct _usbhost_ioctl_cb_t *hc_iocb);

typedef struct {
	USBHOST_INIT   usbhost_init;
	OPEN_HOST_DEV  open_host_dev;
	CLOSE_HOST_DEV close_host_dev;
	SETUP		   setup;
	HC_READ		   read;
	HC_WRITE	   write;
	CMDCTL		   cmdctl;
} USBHost_t;

extern void usbh_init_fnptrs(USBHost_t *USBHost);

extern USBHost_t USBHost;

#endif                                 /*_USBH_CORE*/
