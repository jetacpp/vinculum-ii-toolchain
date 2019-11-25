/*
** USBSlaveHID.h
**
** Copyright © 2009-2010-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave HID generic driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave HID Generic Driver
** Requires: vos.h ioctl.h usbslave.h
** Comments:
**
** History:
**  1 – Initial version
**
*/
#ifndef __USBSlaveHID_h__
#define __USBSlaveHID_h__

#define USBSLAVEHID_VERSION_STRING "2.0.2"

#include "ioctl.h"
#include "USB.h"
#include "USBHID.h"
#include "USBSlave.h"

// USBSLAVEHID IOCTL definitions
#define VOS_IOCTL_USBSLAVEHID_ATTACH               (VOS_IOCTL_USBSLAVEHID_BASE + 1)
#define VOS_IOCTL_USBSLAVEHID_DETACH               (VOS_IOCTL_USBSLAVEHID_BASE + 2)
// allows device, config and string descriptors to be changed
#define VOS_IOCTL_USBSLAVEHID_SET_DESCRIPTORS	  (VOS_IOCTL_USBSLAVEHID_BASE + 3)

// total number of strings stored by driver (including zero string)
#define USBSLAVEHID_STRING_TOTAL 4 // include zero string

// structure used by VOS_IOCTL_USBSLAVEHID_SET_DESCRIPTORS
// memory allocated to these MUST be persistant (global variables or malloced memory)
typedef struct _usbSlaveHID_ioctl_cb_descriptors_t {
	usb_deviceDescriptor_t			 *device_descriptor;
	usb_deviceConfigurationDescriptor_t *config_descriptor;
	usb_deviceStringDescriptor_t	 *strings[USBSLAVEHID_STRING_TOTAL];
	usb_hidDescriptor_t				 *report_descriptor;
} usbSlaveHID_ioctl_cb_descriptors_t;

// return values from driver
enum USBSLAVEHID_STATUS {
	USBSLAVEHID_OK = 0,
	USBSLAVEHID_INVALID_PARAMETER,
	USBSLAVEHID_NOT_SETUP,
	USBSLAVEHID_ERROR
};

// interrupt IN endpoint number
#define USBSLAVEHID_IN 1

// call to initialise driver (must specify IN endpoint size)
uint8 usbSlaveHID_init(uint8 vos_dev_num, uint8 in_ep_size);

// internal thread memory usage
#define SIZEOF_USBSLAVEHID_SETUP_MEMORY 1024
#define SIZEOF_USBSLAVEHID_IN_MEMORY	1024

#endif // __USBSlaveHID_h__

