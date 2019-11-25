/*
** USBSlaveCDCACM.h
**
** Copyright © 2009-2010-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave CDC ACM driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave CDC ACM Driver
** Requires: vos.h ioctl.h usbslave.h
** Comments:
**
** History:
**  1 – Initial version
**
*/
#ifndef __USBSlaveCDCACM_h__
#define __USBSlaveCDCACM_h__

#include "ioctl.h"
#include "USB.h"
#include "USBCDC.h"
#include "USBSlave.h"

#define USBSLAVECDCACM_VERSION_STRING "2.0.2"

// USBSLAVECDCACM IOCTL definitions (share offset for USBSlaveFT232 IOCTLs)
#define VOS_IOCTL_USBSLAVECDCACM_ATTACH				  (VOS_IOCTL_USBSLAVEFT232_BASE + 1)
#define VOS_IOCTL_USBSLAVECDCACM_DETACH				  (VOS_IOCTL_USBSLAVEFT232_BASE + 2)
// allows device, config and string descriptors to be changed
#define VOS_IOCTL_USBSLAVECDCACM_SET_DESCRIPTORS	  (VOS_IOCTL_USBSLAVEFT232_BASE + 3)

// sets the active notification on the interrupt endpoint
#define VOS_IOCTL_USBSLAVECDCACM_SET_NOTIFICATION	  (VOS_IOCTL_USBSLAVEFT232_BASE + 4)
// queries current comm feature set by host driver
#define VOS_IOCTL_USBSLAVECDCACM_GET_COMM_FEATURE	  (VOS_IOCTL_USBSLAVEFT232_BASE + 5)
// queries current line coding set by host driver
#define VOS_IOCTL_USBSLAVECDCACM_GET_LINE_CODING	  (VOS_IOCTL_USBSLAVEFT232_BASE + 6)
// queries the control line state set by host driver
#define VOS_IOCTL_USBSLAVECDCACM_GET_CONTROL_LINE_STATE (VOS_IOCTL_USBSLAVEFT232_BASE + 7)

// IOCTLs from IOCTL.h used are:
// IOCTL VOS_IOCTL_COMMON_GET_RX_QUEUE_STATUS - receive number of bytes received waiting to be read
    
// structure used by VOS_IOCTL_USBSLAVECDCACM_SET_DESCRIPTORS
// memory allocated to these MUST be persistant (global variables or malloced memory)
typedef struct _usbSlaveCDCACM_ioctl_cb_descriptors_t {
    usb_deviceDescriptor_t			 *device_descriptor;
    usb_deviceConfigurationDescriptor_t *config_descriptor;
    usb_deviceStringDescriptorZero_t *zero_string;
    usb_deviceStringDescriptor_t	 *manufacturer_string;
    usb_deviceStringDescriptor_t	 *product_string;
    usb_deviceStringDescriptor_t	 *serial_number_string;
    usb_deviceStringDescriptor_t	 *control_interface_string;
    usb_deviceStringDescriptor_t	 *data_interface_string;
} usbSlaveCDCACM_ioctl_cb_descriptors_t;

// USBSLAVECDC USB String Descriptor Definitions
#define USBSLAVECDCACM_STRING_INDEX_ZERO_STRING 0		// default: English - UK
#define USBSLAVECDCACM_STRING_INDEX_MANUFACTURER 1		// default: "FTDI"
#define USBSLAVECDCACM_STRING_INDEX_PRODUCT 2			// default: "UART <-> CDC"
#define USBSLAVECDCACM_STRING_INDEX_SERIAL_NUMBER 3	// default: "12345678"
#define USBSLAVECDCACM_STRING_INDEX_CDC_CONTROL 4		// default: "CDC Control"
#define USBSLAVECDCACM_STRING_INDEX_CDC_DATA 5			// default: "CDC Data"
#define USBSLAVECDCACM_STRING_TOTAL 6 // include zero string

// Interface configuration: interface 1 is CDC Control, interface 2 is CDC Data
#define USBSLAVECDCACM_CONTROL_INTERFACE	1
#define USBSLAVECDCACM_DATA_INTERFACE		2

enum USBSLAVECDCACM_STATUS {
    USBSLAVECDCACM_OK = 0,
    USBSLAVECDCACM_INVALID_PARAMETER,
    USBSLAVECDCACM_NO_CHANGE,			// No change in COMM, LINE or CONTROL_LINE state
    USBSLAVECDCACM_NOT_ATTACHED,		// Driver is not attached to USBSlave driver
    USBSLAVECDCACM_ERROR
};

// initialisation struct
typedef struct _usbSlaveCDCACM_init_t {
    unsigned short dataInBufferLen;  // default 64 bytes
    unsigned short dataOutBufferLen; // default 64 bytes
} usbSlaveCDCACM_init_t;

// initialisation function
unsigned char usbSlaveCDCACM_init(unsigned char vos_dev_num, usbSlaveCDCACM_init_t *params);

// internal thread memory usage
#define SIZEOF_USBSLAVECDCACM_SETUP_MEMORY			1024
#define SIZEOF_USBSLAVECDCACM_CONTROL_IN_MEMORY		1024
#define SIZEOF_USBSLAVECDCACM_DATA_IN_MEMORY		1024
#define SIZEOF_USBSLAVECDCACM_DATA_OUT_MEMORY		1024

#endif // __USBSlaveCDCACM_h__

