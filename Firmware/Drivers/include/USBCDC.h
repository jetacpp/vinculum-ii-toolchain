/*
** USBCDC.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** THIS SOFTWARE IS PROVIDED BY FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED
** ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FUTURE TECHNOLOGY DEVICES
** INTERNATIONAL LIMITED BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
** OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
** STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
** DAMAGE.
**
** Header file containing definitions for the USB CDC driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB CDC Driver
** Requires: vos.h ioctl.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBCDC_H__
#define __USBCDC_H__

// class requests for Abstract Control Model
#define USB_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND 0x00 // Issues a command in the format of the supported control protocol.
#define USB_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE 0x01 // Requests a response in the format of the supported control protocol.
#define USB_CDC_REQUEST_SET_COMM_FEATURE 0x02 // Controls the settings for a particular communication feature.
#define USB_CDC_REQUEST_GET_COMM_FEATURE 0x03 // Returns the current settings for the communication feature.
#define USB_CDC_REQUEST_CLEAR_COMM_FEATURE 0x04 // Clears the settings for a particular communication feature.
#define USB_CDC_REQUEST_SET_LINE_CODING 0x20 // Configures DTE rate, stop-bits, parity, and number-of-character bits.
#define USB_CDC_REQUEST_GET_LINE_CODING 0x21 // Requests current DTE rate, stop-bits, parity, and number-of-character bits.
#define USB_CDC_REQUEST_SET_CONTROL_LINE_STATE 0x22 // RS-232 signal used to tell the DCE device the DTE device is now present.
#define USB_CDC_REQUEST_SEND_BREAK 0x23 // Sends special carrier modulation used to specify RS-232 style break.

// Line Coding Structure
typedef struct _usbHostCDC_line_coding_t
{
	unsigned long dwDTERate;           // Data terminal rate, in bits per second
	unsigned char bCharFormat;         // Stop bits: 0 - 1 Stop bit; 1 - 1.5 Stop bit; 2 - 2 Stop bits
	unsigned char bParityType;         // Parity: 0 - None; 1 - Odd; 2 - Even; 3 - Mark; 4 - Space
	unsigned char bDataBits;           // Data bites (5,6,7,8 or 16)
} usbHostCDC_line_coding_t;

// Data Bits
#define USBHOSTCDC_DATA_BITS_5		5
#define USBHOSTCDC_DATA_BITS_6		6
#define USBHOSTCDC_DATA_BITS_7		7
#define USBHOSTCDC_DATA_BITS_8		8

// Stop Bits
#define USBHOSTCDC_STOP_BITS_1		0
#define USBHOSTCDC_STOP_BITS_1PT5	1
#define USBHOSTCDC_STOP_BITS_2		2

// Parity
#define USBHOSTCDC_PARITY_NONE		0
#define USBHOSTCDC_PARITY_ODD		1
#define USBHOSTCDC_PARITY_EVEN		2
#define USBHOSTCDC_PARITY_MARK		3
#define USBHOSTCDC_PARITY_SPACE		4

// Control Line State
#define USBHOSTCDC_DTE_PRESENT		1
#define USBHOSTCDC_ACTIVATE_CARRIER 	2

// class notifications for Abstract Control Model
#define USB_CDC_NOTIFICATION_NETWORK_CONNECTION 0x00 // Notification to host of network connection status. Optional
#define USB_CDC_NOTIFICATION_RESPONSE_AVAILABLE 0x01 // Notification to host to issue a GET_ENCAPSULATED_RESPONSE request.
#define USB_CDC_NOTIFICAITON_SERIAL_STATE 0x20 // Returns the current state of the carrier detect, DSR, break, and ring signal.

typedef struct _usb_cdcNotification_t
{
	unsigned char bmRequestType;
	unsigned char bNotificationCode;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} usb_cdcNotification_t;

// USRT State bitmap for USB_CDC_NOTIFICAITON_SERIAL_STATE
typedef	struct _usb_cdcUartStateBitmap
{
	unsigned short bRxCarrier:1;
	unsigned short bTxCarrier:1;
	unsigned short bBreak:1;
	unsigned short bRingSignal:1;
	unsigned short bFraming:1;
	unsigned short bParity:1;
	unsigned short bOverRun:1;
	unsigned short reserved:9;
} usb_cdcUartStateBitmap;

#define CDC_DESCRIPTOR_TYPE_CS_INTERFACE 0x24
#define CDC_DESCRIPTOR_SUBTYPE_HEADER_FUNCTIONAL_DESCRIPTOR 0x00
#define CDC_DESCRIPTOR_SUBTYPE_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR 0x01
#define CDC_DESCRIPTOR_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR 0x02
#define CDC_DESCRIPTOR_SUBTYPE_UNION_FUNCTIONAL_DESCRIPTOR 0x06

// CDC Class-Specific Descriptor Header Format
typedef struct _usb_cdcClassSpecificDescriptorHeaderFormat_t
{
	unsigned char  bFunctionLength;
	unsigned char  bDescriptorType; // CDC_DESCRIPTOR_TYPE_CS_INTERFACE
	unsigned char  bDescriptorSubtype; // CDC_DESCRIPTOR_SUBTYPE_HEADER_FUNCTIONAL_DESCRIPTOR
	unsigned short  bcdCDC;
} usb_cdcClassSpecificDescriptorHeaderFormat_t;
	
// CDC Call Management Functional Descriptor
typedef struct _usb_cdcCallManagementFunctionalDescriptor_t
{
	unsigned char  bFunctionLength;
	unsigned char  bDescriptorType; // CDC_DESCRIPTOR_TYPE_CS_INTERFACE
	unsigned char  bDescriptorSubtype; // CDC_DESCRIPTOR_SUBTYPE_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR
	unsigned char  bmCapabilities;
	unsigned char  bDataInterface;
} usb_cdcCallManagementFunctionalDescriptor_t;
#define CDC_CM_CAPABILITIES_NONE 0x00
#define CDC_CM_CAPABILITIES_HANDLES_CALL_MANAGEMENT 0x01
#define CDC_CM_CAPABILITIES_HANDLES_CALL_MANAGEMENT_OVER_DATA_INTERFACE 0x02

// CDC Abtract Control Management Functional Descriptor
typedef struct _usb_cdcAbstractControlManagementFunctionalDescriptor_t
{
	unsigned char  bFunctionLength;
	unsigned char  bDescriptorType; // CDC_DESCRIPTOR_TYPE_CS_INTERFACE
	unsigned char  bDescriptorSubtype; // CDC_DESCRIPTOR_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR
	unsigned char  bmCapabilities;
} usb_cdcAbstractControlManagementFunctionalDescriptor_t;
#define CDC_ACM_CAPABILITIES_NONE 0x00
#define CDC_ACM_CAPABILITIES_COMM_FEATURE 0x01
#define CDC_ACM_CAPABILITIES_LINE_STATE_CODING 0x02
#define CDC_ACM_CAPABILITIES_SEND_BREAK 0x04
#define CDC_ACM_CAPABILITIES_NETWORK_CONNECTION 0x08
	
// CDC Union Interface Functional Descriptor
typedef struct _usb_cdcUnionInterfaceFunctionalDescriptor_t
{
	unsigned char  bFunctionLength;
	unsigned char  bDescriptorType; // CDC_DESCRIPTOR_TYPE_CS_INTERFACE
	unsigned char  bDescriptorSubtype; // CDC_DESCRIPTOR_SUBTYPE_UNION_FUNCTIONAL_DESCRIPTOR
	unsigned char  bControlInterface;
	unsigned char  bSubordinateInterface0;
} usb_cdcUnionInterfaceFunctionalDescriptor_t;
	
#endif // __USBCDC_H__
