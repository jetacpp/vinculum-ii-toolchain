/*
** USBSlaveHIDMouse.h
**
** Copyright © 2009-2010-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave HID mouse driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave HID Mouse Driver
** Requires: vos.h ioctl.h usbslave.h
** Comments:
**
** History:
**  1 – Initial version
**
*/
#ifndef __USBSlaveHIDMouse_h__
#define __USBSlaveHIDMouse_h__

#include "ioctl.h"
#include "USB.h"
#include "USBHID.h"
#include "USBSlave.h"
#include "USBSlaveHID.h"

/*
   Device Descriptor:
   bcdUSB:             0x0110
   bDeviceClass:         0x00
   bDeviceSubClass:      0x00
   bDeviceProtocol:      0x00
   bMaxPacketSize0:      0x08 (8)
   idVendor:           0x0403 (Future Technology Devices International Limited)
   idProduct:          0x0EEE
   bcdDevice:          0x0101
   iManufacturer:        0x01
   0x0409: "FTDI"
   iProduct:             0x02
   0x0409: "USB Mouse"
   iSerialNumber:        0x03
   bNumConfigurations:   0x01
 */
#define USBSLAVEHIDMOUSE_DEFAULT_DEVICE_DESCRIPTOR(A) \
unsigned char A[18] = { \
    0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x08, \
    0x03, 0x04, 0xee, 0x0e, 0x01, 0x01, 0x01, 0x02, \
    0x03, 0x01 \
};

/*
   Configuration Descriptor:
   wTotalLength:       0x0022
   bNumInterfaces:       0x01
   bConfigurationValue:  0x01
   iConfiguration:       0x00
   bmAttributes:         0xA0 (Bus Powered Remote Wakeup)
   MaxPower:             0x32 (100 Ma)

   Interface Descriptor:
   bInterfaceNumber:     0x00
   bAlternateSetting:    0x00
   bNumEndpoints:        0x01
   bInterfaceClass:      0x03 (HID)
   bInterfaceSubClass:   0x01 (Boot Protocol)
   bInterfaceProtocol:   0x02 (Mouse)
   iInterface:           0x00

   HID Descriptor:
   bcdHID:             0x0110
   bCountryCode:         0x00
   bNumDescriptors:      0x01
   bDescriptorType:      0x22
   wDescriptorLength:  0x0034

   Endpoint Descriptor:
   bEndpointAddress:     0x81  IN
   Transfer Type:   Interrupt
   wMaxPacketSize:     0x0008 (8)
   bInterval:            0x0A
 */
#define USBSLAVEHIDMOUSE_DEFAULT_CONFIG_DESCRIPTOR(A) \
unsigned char A[34] = { \
    0x09, 0x02, 0x22, 0x00, 0x01, 0x01, 0x00, 0xA0, 0x32, \
    0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x02, 0x00, \
    0x09, 0x21, 0x10, 0x01, 0x00, 0x01, 0x22, 0x34, 0x00, \
    0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0x0A \
};
// string indexes defined in config descriptor
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_MANUFACTURER 1
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_PRODUCT 2
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_SERIALNUMBER 3

// English (US)
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_0(A) \
unsigned char A[4] = { \
    0x04, 0x03, 0x09, 0x04 \
};

// String 1: "FTDI"
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_1(A) \
unsigned char A[10] = { \
    0x0a, 0x03, 0x46, 0x00, 0x54, 0x00, 0x44, 0x00, 0x49, 0x00 \
};

// String 2: "USB Mouse"
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_2(A) \
unsigned char A[26] = { \
    0x1a, 0x03, 0x56, 0x00, 0x32, 0x00, 0x45, 0x00,	0x56, 0x00, \
    0x41, 0x00, 0x4c, 0x00, 0x20, 0x00, 0x4d, 0x00,	0x6f, 0x00, \
    0x75, 0x00, 0x73, 0x00, 0x65, 0x00, \
};

// String 3: "12345678"
#define USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_3(A) \
unsigned char A[18] = { \
    0x12, 0x03, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0x34, 0x00, \
    0x35, 0x00, 0x36, 0x00, 0x37, 0x00, 0x38, 0x00 \
};

/* See Device Class Definition for Human Interface Devices (HID) Version 1.11
   from USB Implementers’ Forum USB.org

    0x05, 0x01,        Usage Page: Generic Desktop Controls 
    0x09, 0x02,        Usage: Mouse (2)
    0xA1, 0x01,        Collection: Application
    0x09, 0x01,          Usage: Pointer (1)
    0xA1, 0x00,          Collection: Physical
    0x05, 0x09,            Usage Page: Button (9)
    0x19, 0x01,            Usage Minimum: Button 1
    0x29, 0x03,            Usage Maximum: Button 3
    0x15, 0x00,            Logical Minimum: 0
    0x25, 0x01,            Logical Maximum: 1
    0x95, 0x03,            Report Count: 3
    0x75, 0x01,            Report Size: 1
    0x81, 0x02,            Input: Data (2)
    0x95, 0x01,            Report Count: 1
    0x75, 0x05,            Report Size: 5
    0x81, 0x01,            Input: Constant (1)
    0x05, 0x01,            Usage Page: Generic Desktop Controls 
    0x09, 0x30,            Usage: X
    0x09, 0x31,            Usage: Y
    0x09, 0x38,            Usage: Wheel
    0x15, 0x81,            Logical Minimum: -127
    0x25, 0x7f,            Logical Maximum: 127
    0x75, 0x08,            Report Size: 8
    0x95, 0x03,            Report Count: 3
    0x81, 0x06,            Input: Data (6)
    0xC0,                End collection
    0xC0               End collection
*/
#define USBSLAVEHIDMOUSE_DEFAULT_REPORT_DESCRIPTOR(A) \
unsigned char A[] = { \
    0x05, 0x01, 0x09, 0x02, 0xA1, 0x01,	0x09, 0x01,	0xA1, 0x00, \
    0x05, 0x09,	0x19, 0x01,	0x29, 0x03,	0x15, 0x00,	0x25, 0x01, \
    0x95, 0x03,	0x75, 0x01,	0x81, 0x02,	0x95, 0x01,	0x75, 0x05, \
    0x81, 0x01,	0x05, 0x01,	0x09, 0x30,	0x09, 0x31,	0x09, 0x38, \
    0x15, 0x81,	0x25, 0x7f,	0x75, 0x08,	0x95, 0x03,	0x81, 0x06, \
    0xC0, 0xC0 \
};

#define IMPORT_USBSLAVEHIDMOUSE_DEFAULT_CONFIGURATION \
USBSLAVEHIDMOUSE_DEFAULT_DEVICE_DESCRIPTOR(usbSlaveHIDMouse_default_device_descriptor) \
USBSLAVEHIDMOUSE_DEFAULT_CONFIG_DESCRIPTOR(usbSlaveHIDMouse_default_config_descriptor) \
USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_0(usbSlaveHIDMouse_default_string_descriptor_0) \
USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_1(usbSlaveHIDMouse_default_string_descriptor_1) \
USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_2(usbSlaveHIDMouse_default_string_descriptor_2) \
USBSLAVEHIDMOUSE_DEFAULT_STRING_DESCRIPTOR_3(usbSlaveHIDMouse_default_string_descriptor_3) \
USBSLAVEHIDMOUSE_DEFAULT_REPORT_DESCRIPTOR(usbSlaveHIDMouse_default_report_descriptor)

#define SET_USBSLAVEHIDMOUSE_DEFAULT_CONFIGURATION(A) \
    A.device_descriptor = usbSlaveHIDMouse_default_device_descriptor; \
    A.config_descriptor = usbSlaveHIDMouse_default_config_descriptor; \
    A.strings[0] = usbSlaveHIDMouse_default_string_descriptor_0; \
    A.strings[USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_MANUFACTURER] = usbSlaveHIDMouse_default_string_descriptor_1; \
    A.strings[USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_PRODUCT] = usbSlaveHIDMouse_default_string_descriptor_2; \
    A.strings[USBSLAVEHIDMOUSE_DEFAULT_STRING_INDEX_SERIALNUMBER] = usbSlaveHIDMouse_default_string_descriptor_3; \
    A.report_descriptor = usbSlaveHIDMouse_default_report_descriptor; 

typedef struct _usbSlaveHIDMouse_report_structure_t {
    unsigned char mouseB1 : 1;
    unsigned char mouseB2 : 1;
    unsigned char mouseB3 : 1;
    unsigned char mouseResv : 5;
    unsigned char mouseX;
    unsigned char mouseY;
    unsigned char mouseWheel;
} usbSlaveHIDMouse_report_structure_t;
    
#endif // __USBSlaveHIDMouse_h__

