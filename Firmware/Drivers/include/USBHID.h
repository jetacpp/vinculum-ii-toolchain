/*
** USBHID.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB HID devices.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave and USB Host HID Drivers
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBHID_H__
#define __USBHID_H__

// Section 7.1. Descriptor Types
//		Descriptor Types								Value
#define USB_DESCRIPTOR_TYPE_HID			  0x21
#define USB_DESCRIPTOR_TYPE_REPORT		  0x22
#define USB_DESCRIPTOR_TYPE_PHYSICAL	  0x23

// Section 7.2. USB HID Class Request Codes
//		bRequest										Value
#define USB_HID_REQUEST_CODE_GET_REPORT	  0x01
#define USB_HID_REQUEST_CODE_GET_IDLE	  0x02
#define USB_HID_REQUEST_CODE_GET_PROTOCOL 0x03
#define USB_HID_REQUEST_CODE_SET_REPORT	  0x09
#define USB_HID_REQUEST_CODE_SET_IDLE	  0x0A
#define USB_HID_REQUEST_CODE_SET_PROTOCOL 0x0B

// Section 6.2.1. USB HID Descriptor
typedef struct _usb_hidDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned short bcdHID;
    unsigned char  bCountryCode;
    unsigned char  bNumDescriptors;
    // a HID device has at least 1 report descriptor
    unsigned char  bDescriptorType_0;
    unsigned short wDescriptorLength_0;
    // from this point on there are variable size fields depending
    // on bNumDescriptors
} usb_hidDescriptor_t;

// Section 6.2.1. USB HID Language Codes
#define USB_HID_LANG_NOT_SUPPORTED		 0
#define USB_HID_LANG_ARABIC				 1
#define USB_HID_LANG_BELGIAN			 2
#define USB_HID_LANG_CANADIAN_BILINGUAL	 3
#define USB_HID_LANG_CANADIAN_FRENCH	 4
#define USB_HID_LANG_CZECH_REPUBLIC		 5
#define USB_HID_LANG_DANISH				 6
#define USB_HID_LANG_FINNISH			 7
#define USB_HID_LANG_FRENCH				 8
#define USB_HID_LANG_GERMAN				 9
#define USB_HID_LANG_GREEK				 10
#define USB_HID_LANG_HEBREW				 11
#define USB_HID_LANG_HUNGARY			 12
#define USB_HID_LANG_INTERNATIONAL		 13
#define USB_HID_LANG_ITALIAN			 14
#define USB_HID_LANG_JAPAN				 15
#define USB_HID_LANG_KOREAN				 16
#define USB_HID_LANG_LATIN_AMERICAN		 17
#define USB_HID_LANG_NETHERLANDS		 18
#define USB_HID_LANG_NORWEGIAN			 19
#define USB_HID_LANG_PERSIAN			 20
#define USB_HID_LANG_POLAND				 21
#define USB_HID_LANG_PORTUGUESE			 22
#define USB_HID_LANG_RUSSIA				 23
#define USB_HID_LANG_SLOVAKIA			 24
#define USB_HID_LANG_SPANISH			 25
#define USB_HID_LANG_SWEDISH			 26
#define USB_HID_LANG_SWISS_FRENCH		 27
#define USB_HID_LANG_SWISS_GERMAN		 28
#define USB_HID_LANG_SWITZERLAND		 29
#define USB_HID_LANG_TAIWAN				 30
#define USB_HID_LANG_TURKISH_Q			 31
#define USB_HID_LANG_UK					 32
#define USB_HID_LANG_US					 33
#define USB_HID_LANG_YUGOSLAVIA			 34
#define USB_HID_LANG_TURKISH_F			 35

// Section 6.2.3. USB HID Physical Descriptor Bias Values
#define USB_HID_BIAS_NOT_APPLICABLE		 0x00
#define USB_HID_BIAS_RIGHT_HAND			 0x10
#define USB_HID_BIAS_LEFT_HAND			 0x20
#define USB_HID_BIAS_BOTH_HANDS			 0x30
#define USB_HID_BIAS_EITHER_HAND		 0x40

// Section 6.2.3. USB HID Physical Descriptor Designator Values
#define USB_HID_DESIGNATOR_NONE			 0x00
#define USB_HID_DESIGNATOR_HAND			 0x01
#define USB_HID_DESIGNATOR_EYEBALL		 0x02
#define USB_HID_DESIGNATOR_EYEBROW		 0x03
#define USB_HID_DESIGNATOR_EYELID		 0x04
#define USB_HID_DESIGNATOR_EAR			 0x05
#define USB_HID_DESIGNATOR_NOSE			 0x06
#define USB_HID_DESIGNATOR_MOUTH		 0x07
#define USB_HID_DESIGNATOR_UPPER_LIP	 0x08
#define USB_HID_DESIGNATOR_LOWER_LIP	 0x09
#define USB_HID_DESIGNATOR_JAW			 0x0A
#define USB_HID_DESIGNATOR_NECK			 0x0B
#define USB_HID_DESIGNATOR_UPPER_ARM	 0x0C
#define USB_HID_DESIGNATOR_ELBOW		 0x0D
#define USB_HID_DESIGNATOR_FOREARM		 0x0E
#define USB_HID_DESIGNATOR_WRIST		 0x0F
#define USB_HID_DESIGNATOR_PALM			 0x10
#define USB_HID_DESIGNATOR_THUMB		 0x11
#define USB_HID_DESIGNATOR_INDEX_FINGER	 0x12
#define USB_HID_DESIGNATOR_MIDDLE_FINGER 0x13
#define USB_HID_DESIGNATOR_RING_FINGER	 0x14
#define USB_HID_DESIGNATOR_LITTLE_FINGER 0x15
#define USB_HID_DESIGNATOR_HEAD			 0x16
#define USB_HID_DESIGNATOR_SHOULDER		 0x17
#define USB_HID_DESIGNATOR_HIP			 0x18
#define USB_HID_DESIGNATOR_WAIST		 0x19
#define USB_HID_DESIGNATOR_THIGH		 0x1A
#define USB_HID_DESIGNATOR_KNEE			 0x1B
#define USB_HID_DESIGNATOR_CALF			 0x1C
#define USB_HID_DESIGNATOR_ANKLE		 0x1D
#define USB_HID_DESIGNATOR_FOOT			 0x1E
#define USB_HID_DESIGNATOR_HEEL			 0x1F
#define USB_HID_DESIGNATOR_BALL_OF_FOOT	 0x20
#define USB_HID_DESIGNATOR_BIG_TOE		 0x21
#define USB_HID_DESIGNATOR_SECOND_TOE	 0x22
#define USB_HID_DESIGNATOR_THIRD_TOE	 0x23
#define USB_HID_DESIGNATOR_FOURTH_TOE	 0x24
#define USB_HID_DESIGNATOR_LITTLE_TOE	 0x25
#define USB_HID_DESIGNATOR_BROW			 0x26
#define USB_HID_DESIGNATOR_CHEEK		 0x27

#endif                                 /* __USBHID_H__ */
