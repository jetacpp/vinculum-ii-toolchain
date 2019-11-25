/*
** USBSlaveHIDKbd.h
**
** Copyright © 2009-2010-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave HID keyboard driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave HID Keyboard Driver
** Requires: vos.h ioctl.h usbslave.h
** Comments:
**
** History:
**  1 – Initial version
**
*/
#ifndef __USBSlaveHIDKbd_h__
#define __USBSlaveHIDKbd_h__

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
   idProduct:          0x0FED
   bcdDevice:          0x0101
   iManufacturer:        0x01
   0x0409: "FTDI"
   iProduct:             0x02
   0x0409: "USB Keyboard"
   iSerialNumber:        0x03
   bNumConfigurations:   0x01
 */
#define USBSLAVEHIDKEYBOARD_DEFAULT_DEVICE_DESCRIPTOR(A) \
unsigned char A[18] = { \
    0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x08, \
    0x03, 0x04, 0xed, 0x0f, 0x01, 0x01, 0x01, 0x02, \
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
   bInterfaceProtocol:   0x01 (Keyboard)
   iInterface:           0x00

   HID Descriptor:
   bcdHID:             0x0110
   bCountryCode:         0x00
   bNumDescriptors:      0x01
   bDescriptorType:      0x22
   wDescriptorLength:  0x0041

   Endpoint Descriptor:
   bEndpointAddress:     0x81  IN
   Transfer Type:   Interrupt
   wMaxPacketSize:     0x0008 (8)
   bInterval:            0x0A
 */
#define USBSLAVEHIDKEYBOARD_DEFAULT_CONFIG_DESCRIPTOR(A) \
unsigned char A[34] = { \
    0x09, 0x02, 0x22, 0x00, 0x01, 0x01, 0x00, 0xA0, 0x32, \
    0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, \
    0x09, 0x21, 0x10, 0x01, 0x00, 0x01, 0x22, 0x41, 0x00, \
    0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0x0A \
};
// string indexes defined in config descriptor
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_MANUFACTURER 1
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_PRODUCT 2
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_SERIALNUMBER 3

// English (US)
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_0(A) \
unsigned char A[4] = { \
    0x04, 0x03, 0x09, 0x04 \
};

// String 1: "FTDI"
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_1(A) \
unsigned char A[10] = { \
    0x0a, 0x03, 0x46, 0x00, 0x54, 0x00, 0x44, 0x00, 0x49, 0x00 \
};

// String 2: "USB Keyboard"
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_2(A) \
unsigned char A[26] = { \
    0x1a, 0x03, 0x55, 0x00, 0x53, 0x00, 0x42, 0x00, 0x20, 0x00, \
    0x4b, 0x00, 0x65, 0x00, 0x79, 0x00, 0x62, 0x00, 0x6f, 0x00, \
    0x61, 0x00, 0x72, 0x00, 0x64, 0x00 \
};

// String 3: "12345678"
#define USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_3(A) \
unsigned char A[18] = { \
    0x12, 0x03, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0x34, 0x00, \
    0x35, 0x00, 0x36, 0x00, 0x37, 0x00, 0x38, 0x00 \
};

/* See Device Class Definition for Human Interface Devices (HID) Version 1.11
   from USB Implementers’ Forum USB.org

    0x05, 0x01,				Usage Page: Generic Desktop Controls
    0x09, 0x06,				Usage: Keyboard
    0xA1, 0x01,				Collection: Application
    0x05, 0x07,				  Usage Page: Keyboard
    0x19, 0xE0,				  Usage Minimum: Keyboard LeftControl
    0x29, 0xE7,				  Usage Maximum: Keyboard Right GUI
    0x15, 0x00,				  Logical Minimum: 0
    0x25, 0x01,				  Logical Maximum: 1
    0x75, 0x01,				  Report Size: 1
    0x95, 0x08,				  Report Count: 8
    0x81, 0x02,				  Input: Data (2)
    0x95, 0x01,				  Report Count: 1
    0x75, 0x08,				  Report Size: 8
    0x81, 0x01,				  Input: Constant (1)
    0x95, 0x03,				  Report Count: 3
    0x75, 0x01,				  Report Size: 1
    0x05, 0x08,				  Usage Page: LEDs
    0x19, 0x01,				  Usage Minimum: Num Lock
    0x29, 0x03,				  Usage Maximum: Scroll Lock
    0x91, 0x02,				  Output: Data (2)
    0x95, 0x05,				  Report Count: 5
    0x75, 0x01,				  Report Size: 1
    0x91, 0x01,				  Output: Constant (1)
    0x95, 0x06,				  Report Count: 6
    0x75, 0x08,				  Report Size: 8
    0x15, 0x00,				  Logical Minimum: 0
    0x26, 0xFF, 0x00,		  Logical Maximum: 255
    0x05, 0x07,				  Usage Page: Keyboard/Keypad
    0x19, 0x00,				  Usage Minimum: 0
    0x2A, 0xFF, 0x00,		  Usage Maximum: 255
    0x81, 0x00,				  Input: Data (0)
    0xC0					End collection
*/
#define USBSLAVEHIDKEYBOARD_DEFAULT_REPORT_DESCRIPTOR(A) \
unsigned char A[65] = { \
    0x05, 0x01,	0x09, 0x06,	0xA1, 0x01,	0x05, 0x07,	0x19, 0xE0, \
    0x29, 0xE7,	0x15, 0x00,	0x25, 0x01,	0x75, 0x01,	0x95, 0x08, \
    0x81, 0x02,	0x95, 0x01,	0x75, 0x08,	0x81, 0x01,	0x95, 0x03,	\
    0x75, 0x01,	0x05, 0x08,	0x19, 0x01,	0x29, 0x03,	0x91, 0x02, \
    0x95, 0x05,	0x75, 0x01,	0x91, 0x01,	0x95, 0x06,	0x75, 0x08, \
    0x15, 0x00,	0x26, 0xFF, 0x00, 0x05, 0x07, 0x19, 0x00, 0x2A, \
    0xFF, 0x00,	0x81, 0x00,	0xC0, \
};

#define IMPORT_USBSLAVEHIDKEYBOARD_DEFAULT_CONFIGURATION \
USBSLAVEHIDKEYBOARD_DEFAULT_DEVICE_DESCRIPTOR(usbSlaveHIDKeyboard_default_device_descriptor) \
USBSLAVEHIDKEYBOARD_DEFAULT_CONFIG_DESCRIPTOR(usbSlaveHIDKeyboard_default_config_descriptor) \
USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_0(usbSlaveHIDKeyboard_default_string_descriptor_0) \
USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_1(usbSlaveHIDKeyboard_default_string_descriptor_1) \
USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_2(usbSlaveHIDKeyboard_default_string_descriptor_2) \
USBSLAVEHIDKEYBOARD_DEFAULT_STRING_DESCRIPTOR_3(usbSlaveHIDKeyboard_default_string_descriptor_3) \
USBSLAVEHIDKEYBOARD_DEFAULT_REPORT_DESCRIPTOR(usbSlaveHIDKeyboard_default_report_descriptor)

#define SET_USBSLAVEHIDKEYBOARD_DEFAULT_CONFIGURATION(A) \
    A.device_descriptor = usbSlaveHIDKeyboard_default_device_descriptor; \
    A.config_descriptor = usbSlaveHIDKeyboard_default_config_descriptor; \
    A.strings[0] = usbSlaveHIDKeyboard_default_string_descriptor_0; \
    A.strings[USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_MANUFACTURER] = usbSlaveHIDKeyboard_default_string_descriptor_1; \
    A.strings[USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_PRODUCT] = usbSlaveHIDKeyboard_default_string_descriptor_2; \
    A.strings[USBSLAVEHIDKEYBOARD_DEFAULT_STRING_INDEX_SERIALNUMBER] = usbSlaveHIDKeyboard_default_string_descriptor_3; \
    A.report_descriptor = usbSlaveHIDKeyboard_default_report_descriptor; 

typedef struct _usbSlaveHIDKbd_report_structure_t {
    unsigned char kbdLeftControl : 1;
    unsigned char kbdLeftShift : 1;
    unsigned char kbdLeftAlt : 1;
    unsigned char kbdLeftGUI : 1;
    unsigned char kbdRightControl : 1;
    unsigned char kbdRightShift : 1;
    unsigned char kbdRightAlt : 1;
    unsigned char kbdRightGUI : 1;

    unsigned char arrayNotUsed;  // [1]
    unsigned char arrayKeyboard; // [2]
    unsigned char arrayResv1;
    unsigned char arrayResv2;
    unsigned char arrayResv3;
    unsigned char arrayResv4;
    unsigned char arrayResv5;
} usbSlaveHIDKbd_report_structure_t;

#endif // __USBSlaveHIDKbd_h__

