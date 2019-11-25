/*
** USBSlaveFT232.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave FT232 driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave FT232 Driver
** Requires: vos.h ioctl.h usb.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBSLAVEFT232_H__
#define __USBSLAVEFT232_H__

#define USBSLAVEFT232_VERSION_STRING "2.0.2"

#include "ioctl.h"
#include "usb.h"

// USBSLAVEFT232 IOCTL definitions
#define VOS_IOCTL_USBSLAVEFT232_ATTACH				  (VOS_IOCTL_USBSLAVEFT232_BASE + 1)
#define VOS_IOCTL_USBSLAVEFT232_DETACH				  (VOS_IOCTL_USBSLAVEFT232_BASE + 2)
#define VOS_IOCTL_USBSLAVEFT232_SET_LATENCY			  (VOS_IOCTL_USBSLAVEFT232_BASE + 3)
#define VOS_IOCTL_USBSLAVEFT232_SET_DESCRIPTORS		  (VOS_IOCTL_USBSLAVEFT232_BASE + 4)
#define VOS_IOCTL_USBSLAVEFT232_SET_OUT_TRANSFER_SIZE (VOS_IOCTL_USBSLAVEFT232_BASE + 5)
#define VOS_IOCTL_USBSLAVEFT232_GET_RTS               (VOS_IOCTL_USBSLAVEFT232_BASE + 6)
#define VOS_IOCTL_USBSLAVEFT232_GET_DTR               (VOS_IOCTL_USBSLAVEFT232_BASE + 7)
#define VOS_IOCTL_USBSLAVEFT232_SET_CTS               (VOS_IOCTL_USBSLAVEFT232_BASE + 8)
#define VOS_IOCTL_USBSLAVEFT232_CLEAR_CTS             (VOS_IOCTL_USBSLAVEFT232_BASE + 9)
#define VOS_IOCTL_USBSLAVEFT232_SET_DSR               (VOS_IOCTL_USBSLAVEFT232_BASE + 10)
#define VOS_IOCTL_USBSLAVEFT232_CLEAR_DSR             (VOS_IOCTL_USBSLAVEFT232_BASE + 11)
#define VOS_IOCTL_USBSLAVEFT232_SET_DCD               (VOS_IOCTL_USBSLAVEFT232_BASE + 12)
#define VOS_IOCTL_USBSLAVEFT232_CLEAR_DCD             (VOS_IOCTL_USBSLAVEFT232_BASE + 13)
#define VOS_IOCTL_USBSLAVEFT232_SET_RI                (VOS_IOCTL_USBSLAVEFT232_BASE + 14)
#define VOS_IOCTL_USBSLAVEFT232_CLEAR_RI              (VOS_IOCTL_USBSLAVEFT232_BASE + 15)

// structure used by VOS_IOCTL_USBSLAVEFT232_SET_DESCRIPTORS
typedef struct _usbslaveft232_ioctl_cb_descriptors_t {
    struct {
        unsigned char  use;
        unsigned short idVendor;
        unsigned short idProduct;
        unsigned char  iManufacturer;
        unsigned char  iProduct;
        unsigned char  iSerialNumber;
    } device_descriptor;
    struct {
        unsigned char use;
        unsigned char bmAttributes;
        unsigned char bMaxPower;
    }								 config_descriptor;
    usb_deviceStringDescriptorZero_t *zero_string;
    usb_deviceStringDescriptor_t	 *manufacturer_string;
    usb_deviceStringDescriptor_t	 *product_string;
    usb_deviceStringDescriptor_t	 *serial_number_string;
} usbslaveft232_ioctl_cb_descriptors_t;

// string descriptor index definitions
enum USBSLAVEFT232_STRING_DESCRIPTOR_INDEX {
    FT232_STRING_INDEX_NONE,
    FT232_STRING_INDEX_MANUFACTURER,
    FT232_STRING_INDEX_PRODUCT,
    FT232_STRING_INDEX_SERIAL_NUMBER
};

enum USBSLAVEFT232_STATUS {
    USBSLAVEFT232_OK = 0,
    USBSLAVEFT232_INVALID_PARAMETER,
    USBSLAVEFT232_ERROR
};

// initialisation struct
typedef struct _usbSlaveFt232_init_t {
    unsigned short in_ep_buffer_len;
    unsigned short out_ep_buffer_len;
} usbSlaveFt232_init_t;

// USBSLAVEFT232 initialisation function
unsigned char usbslaveft232_init(unsigned char vos_dev_num, usbSlaveFt232_init_t *params);

#endif                                 /* __USBSLAVEFT232_H__ */
