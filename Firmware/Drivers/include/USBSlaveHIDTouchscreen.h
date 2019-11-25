/*
** USBSlaveHIDTouchscreen.h
**
** Copyright © 2009-2010-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave HID touchscreen driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave HID Single Touch Driver
** Requires: vos.h ioctl.h usbslave.h
** Comments:
**
** History:
**  1 – Initial version
**
*/
#ifndef __USBSlaveHIDTouchscreen_h__
#define __USBSlaveHIDTouchscreen_h__

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
   idProduct:          0x0ACE
   bcdDevice:          0x0101
   iManufacturer:        0x01
   0x0409: "FTDI"
   iProduct:             0x02
   0x0409: "USB Touchscreen"
   iSerialNumber:        0x03
   bNumConfigurations:   0x01
 */
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_DEVICE_DESCRIPTOR(A) \
unsigned char A[18] = { \
    0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x08, \
    0x03, 0x04, 0xce, 0x0a, 0x01, 0x01, 0x01, 0x02, \
    0x03, 0x01 \
}; \

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
   bInterfaceSubClass:   0x00 (None)
   bInterfaceProtocol:   0x00 (None)
   iInterface:           0x00

   HID Descriptor:
   bcdHID:             0x0110
   bCountryCode:         0x00
   bNumDescriptors:      0x01
   bDescriptorType:      0x22
   wDescriptorLength:  0x0057

   Endpoint Descriptor:
   bEndpointAddress:     0x81  IN
   Transfer Type:   Interrupt
   wMaxPacketSize:     0x0010 (16)
   bInterval:            0x0A
 */
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_CONFIG_DESCRIPTOR(A) \
unsigned char A[34] = { \
    0x09, 0x02, 0x22, 0x00, 0x01, 0x01, 0x00, 0xA0, 0x32, \
    0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, \
    0x09, 0x21, 0x10, 0x01, 0x00, 0x01, 0x22, 0x57, 0x00, \
    0x07, 0x05, 0x81, 0x03, 0x10, 0x00, 0x0A \
}; 
// string indexes defined in config descriptor
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_MANUFACTURER 1
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_PRODUCT 2
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_SERIALNUMBER 3

// English (US)
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_0(A) \
unsigned char A[4] = { \
    0x04, 0x03, 0x09, 0x04 \
};

// String 1: "FTDI"
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_1(A) \
unsigned char A[10] = { \
    0x0a, 0x03, 0x46, 0x00, 0x54, 0x00, 0x44, 0x00, 0x49, 0x00 \
};

// String 2: "USB Touchscreen"
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_2(A) \
unsigned char A[32] = { \
    0x20, 0x03, 0x55, 0x00, 0x53, 0x00, 0x42, 0x00, 0x20, 0x00, \
    0x54, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x63, 0x00, 0x68, 0x00, \
    0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x65, 0x00, 0x65, 0x00, \
    0x6e, 0x00, \
};

// String 3: "12345678"
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_3(A) \
unsigned char A[18] = { \
    0x12, 0x03, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0x34, 0x00, \
    0x35, 0x00, 0x36, 0x00, 0x37, 0x00, 0x38, 0x00 \
};

/* See Device Class Definition for Human Interface Devices (HID) Version 1.11
   from USB Implementers’ Forum USB.org
   http://msdn.microsoft.com/en-us/library/windows/hardware/ff553722(v=vs.85).aspx

    0x05, 0x0d,                        Usage Page: digitizers
    0x09, 0x04,                        Usage: touch screen
    0xa1, 0x01,                        Collection: application
    0x85, 0x01,                          Report ID: touch
    0x09, 0x20,                          Usage: stylus
    0xa1, 0x00,                          Collection: physical
    0x09, 0x42,                            Usage: tip switch
    0x15, 0x00,                            Logical Minimum: 0
    0x25, 0x01,                            Logical Maximum: 1
    0x75, 0x01,                            Report Size: 1
    0x95, 0x01,                            Report Count: 1
    0x81, 0x02,                            Input: data,var,abs
    0x95, 0x03,                            Report Count: 3
    0x81, 0x03,                            Input: cnst,ary,abs
    0x09, 0x32,                            Usage: in range
    0x09, 0x47,                            Usage: confidence
    0x95, 0x02,                            Report Count: 2
    0x81, 0x02,                            Input: data,var,abs
    0x95, 0x0a,                            Report Count: 10
    0x81, 0x03,                            Input: cnst,ary,abs
    0x05, 0x01,                            Usage Page: generic desk top
    0x26, 0xff, 0x7f,                      Logical Maximum: 32767
    0x75, 0x10,                            Report Size: 16
    0x95, 0x01,                            Report Count: 1
    0xa4,                                  Push
    0x55, 0x0d,                            Unit Exponent: -3
    0x65, 0x00,                            Unit: none
    0x09, 0x30,                            Usage: x
    0x35, 0x00,                            Physical Minimum: 0
    0x46, 0x00, 0x00,                      Physical Maximum: 0
    0x81, 0x02,                            Input: data,var,abs
    0x09, 0x31,                            Usage: y
    0x46, 0x00, 0x00,                      Physical Maximum: 0
    0x81, 0x02,                            Input: data,var,abs
    0xb4,                                  Pop
    0x05, 0x0d,                            Usage page: digitizers
    0x09, 0x48,                            Usage: width
    0x09, 0x49,                            Usage: height
    0x95, 0x02,                            Report Count: 2
    0x81, 0x02,                            Input: data,var,abs
    0x95, 0x01,                            Report Count: 1
    0x81, 0x03,                            Input: cnst,ary,abs
    0xc0,                                End Collection
    0xc0,                              End Collection
*/
#define USBSLAVEHIDTOUCHSCREEN_DEFAULT_REPORT_DESCRIPTOR(A) \
unsigned char A[] = { \
    0x05, 0x0d, 0x09, 0x04, 0xa1, 0x01, 0x85, 0x01, 0x09, 0x20, \
    0xa1, 0x00, 0x09, 0x42, 0x15, 0x00, 0x25, 0x01, 0x75, 0x01, \
    0x95, 0x01, 0x81, 0x02, 0x95, 0x03, 0x81, 0x03, 0x09, 0x32, \
    0x09, 0x47, 0x95, 0x02, 0x81, 0x02, 0x95, 0x0a, 0x81, 0x03, \
    0x05, 0x01, 0x26, 0xff, 0x7f, 0x75, 0x10, 0x95, 0x01, 0xa4, \
    0x55, 0x0d, 0x65, 0x00, 0x09, 0x30, 0x35, 0x00, 0x46, 0x00, \
    0x00, 0x81, 0x02, 0x09, 0x31, 0x46, 0x00, 0x00, 0x81, 0x02, \
    0xb4, 0x05, 0x0d, 0x09, 0x48, 0x09, 0x49, 0x95, 0x02, 0x81, \
    0x02, 0x95, 0x01, 0x81, 0x03, 0xc0, 0xc0, \
}; 


#define IMPORT_USBSLAVEHIDTOUCHSCREEN_DEFAULT_CONFIGURATION \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_DEVICE_DESCRIPTOR(usbSlaveHIDTouchscreen_default_device_descriptor) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_CONFIG_DESCRIPTOR(usbSlaveHIDTouchscreen_default_config_descriptor) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_0(usbSlaveHIDTouchscreen_default_string_descriptor_0) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_1(usbSlaveHIDTouchscreen_default_string_descriptor_1) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_2(usbSlaveHIDTouchscreen_default_string_descriptor_2) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_DESCRIPTOR_3(usbSlaveHIDTouchscreen_default_string_descriptor_3) \
USBSLAVEHIDTOUCHSCREEN_DEFAULT_REPORT_DESCRIPTOR(usbSlaveHIDTouchscreen_default_report_descriptor)

#define SET_USBSLAVEHIDTOUCHSCREEN_DEFAULT_CONFIGURATION(A) \
    A.device_descriptor = usbSlaveHIDTouchscreen_default_device_descriptor; \
    A.config_descriptor = usbSlaveHIDTouchscreen_default_config_descriptor; \
    A.strings[0] = usbSlaveHIDTouchscreen_default_string_descriptor_0; \
    A.strings[USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_MANUFACTURER] = usbSlaveHIDTouchscreen_default_string_descriptor_1; \
    A.strings[USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_PRODUCT] = usbSlaveHIDTouchscreen_default_string_descriptor_2; \
    A.strings[USBSLAVEHIDTOUCHSCREEN_DEFAULT_STRING_INDEX_SERIALNUMBER] = usbSlaveHIDTouchscreen_default_string_descriptor_3; \
    A.report_descriptor = usbSlaveHIDTouchscreen_default_report_descriptor; 

// report definition structure
typedef struct _usbSlaveHIDTouchscreen_report_structure_t {
    unsigned char reportID;
    unsigned char tipSwitch:1;
    unsigned char resv1:3;
    unsigned char inRange:1;
    unsigned char confidence:1;
    unsigned char resv2:2;
    unsigned char resv3;

    unsigned short xData;
    unsigned short yData;

    unsigned short height;
    unsigned short width;
    unsigned short resv5;
} usbSlaveHIDTouchscreen_report_structure_t;

#endif // __USBSlaveHIDTouchscreen_h__

