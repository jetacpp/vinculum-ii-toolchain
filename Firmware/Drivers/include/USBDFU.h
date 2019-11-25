/*
** USBDFU.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB DFU devices.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave and USB Host DFU Drivers
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBDFU_H__
#define __USBDFU_H__

//		Descriptor Types								Value
#define USB_DESCRIPTOR_TYPE_DFU_FUNCTIONAL 0x21

// Table 3.2 DFU Class-Specific Request Values
//		bRequest										Value
#define USB_DFU_REQUEST_CODE_DETACH		   0x00
#define USB_DFU_REQUEST_CODE_DNLOAD		   0x01
#define USB_DFU_REQUEST_CODE_UPLOAD		   0x02
#define USB_DFU_REQUEST_CODE_GET_STATUS	   0x03
#define USB_DFU_REQUEST_CODE_CLEAR_STATUS  0x04
#define USB_DFU_REQUEST_CODE_GET_STATE	   0x05
#define USB_DFU_REQUEST_CODE_ABORT		   0x06

// Table 4.1 Run-Time DFU Interface Descriptor
// Same format as standard interface descriptor with specific values for DFU:

/*
typedef struct _usb_dfuRuntimeDescriptor_t
{
    unsigned char bLength;					// 0x09 - size of this descriptor in bytes
    unsigned char bDescriptorType;			// 0x04 - USB_DESCRIPTOR_TYPE_INTERFACE from USB.h
    unsigned char bInterfaceNumber;			// number of this interface
    unsigned char bAlternateSetting;		// always 0 for DFU class
    unsigned char bNumEndpoints;			// always 0 for DFU class
    unsigned char bInterfaceClass;			// 0xFE - application specific class code
    unsigned char bInterfaceSubClass;		// 0x01 - Device Firmware Upgrade code
    unsigned char bInterfaceProtocol;		// 0x00 - the device does not use a class specific protocol on this interface.
    unsigned char iInterface;				// index of string descriptor for this interface
} usb_dfuRuntimeDescriptor_t;
*/

// Table 4.2 DFU Functional Descriptor
typedef struct _usb_dfuFunctionalDescriptor_t
{
    unsigned char  bLength;            // 0x07 - size of this descriptor in bytes
    unsigned char  bDescriptorType;    // 0x21 - USB_DESCRIPTOR_TYPE_DFU_FUNCTIONAL
    unsigned char  bmAttributes;       // DFU attributes
    unsigned short wDetachTimeOut;     // Time, in milliseconds, that the device will wait after receipt of the
                                       // DFU_DETACH request
    unsigned short wTransferSize;      // Maximum number of bytes that the device can accept per control-write
                                       // transaction.
} usb_dfuFunctionalDescriptor_t;

// DFU Functional descriptor bmAttributes values
#define USB_DFU_BMATTRIBUTES_CAN_DNLOAD				0x01
#define USB_DFU_BMATTRIBUTES_CAN_UPLOAD				0x02
#define USB_DFU_BMATTRIBUTES_MANIFESTATION_TOLERANT 0x04

#endif                                 /* __USBDFU_H__ */
