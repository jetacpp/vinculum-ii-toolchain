/*
** USBSlave.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Slave driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave Driver
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBSLAVE_H__
#define __USBSLAVE_H__

#define USBSLAVE_VERSION_STRING "2.0.2"

#define NUMBER_OF_USBSLAVE_PORTS 2

// slave port definitions
#define USBSLAVE_PORT_A			 0
#define USBSLAVE_PORT_B			 1

// endpoint handle
typedef uint8 usbslave_ep_handle_t;

// IOCTL codes
#define VOS_IOCTL_USBSLAVE_GET_STATE					0
#define VOS_IOCTL_USBSLAVE_GET_CONTROL_ENDPOINT_HANDLE	1
#define VOS_IOCTL_USBSLAVE_GET_IN_ENDPOINT_HANDLE		2
#define VOS_IOCTL_USBSLAVE_GET_OUT_ENDPOINT_HANDLE		3
#define VOS_IOCTL_USBSLAVE_SET_ENDPOINT_MASKS			4
#define VOS_IOCTL_USBSLAVE_WAIT_SETUP_RCVD				5
#define VOS_IOCTL_USBSLAVE_SETUP_TRANSFER				6
#define VOS_IOCTL_USBSLAVE_TRANSFER						7
#define VOS_IOCTL_USBSLAVE_SET_ADDRESS					8
#define VOS_IOCTL_USBSLAVE_ENDPOINT_STALL				9
#define VOS_IOCTL_USBSLAVE_ENDPOINT_CLEAR				10
#define VOS_IOCTL_USBSLAVE_SET_LOW_SPEED				11
#define VOS_IOCTL_USBSLAVE_SET_CONFIGURATION			12
#define VOS_IOCTL_USBSLAVE_ENDPOINT_STATE				13
#define VOS_IOCTL_USBSLAVE_DISCONNECT					14
// extension
#define VOS_IOCTL_USBSLAVE_GET_BULK_IN_ENDPOINT_HANDLE	16
#define VOS_IOCTL_USBSLAVE_GET_BULK_OUT_ENDPOINT_HANDLE 17
#define VOS_IOCTL_USBSLAVE_GET_INT_IN_ENDPOINT_HANDLE	18
#define VOS_IOCTL_USBSLAVE_GET_INT_OUT_ENDPOINT_HANDLE	19
#define VOS_IOCTL_USBSLAVE_GET_ISO_IN_ENDPOINT_HANDLE	20
#define VOS_IOCTL_USBSLAVE_GET_ISO_OUT_ENDPOINT_HANDLE	21
#define VOS_IOCTL_USBSLAVE_SET_ENDPOINT_MAX_PACKET_SIZE 22
#define VOS_IOCTL_USBSLAVE_WAIT_ON_USB_SUSPEND			23
#define VOS_IOCTL_USBSLAVE_WAIT_ON_USB_RESUME			24
#define VOS_IOCTL_USBSLAVE_ISSUE_REMOTE_WAKEUP			25
#define VOS_IOCTL_USBSLAVE_GET_CONFIGURATION			26
#define VOS_IOCTL_USBSLAVE_CONNECT					27

// IOCTL control block
typedef struct _usbslave_ioctl_cb_t {
    uint8				 ioctl_code;
    uint8				 ep;
    usbslave_ep_handle_t handle;
    // read buffer
    void				 *get;
    // write butter
    void				 *set;
    union
    {
        struct {
            uint8 in_mask;
            uint8 out_mask;
        } set_ep_masks;
        struct {
            uint8 *buffer;
            int16 size;
            int16 bytes_transferred;
        }	   setup_or_bulk_transfer;
        uint32 ep_max_packet_size;     // valid values listed below
    } request;
} usbslave_ioctl_cb_t;

// VOS_IOCTL_USBSLAVE_GET_CONTROL_ENDPOINT_HANDLE
// control endpoint definitions
enum {
    USBSLAVE_CONTROL_SETUP,
    USBSLAVE_CONTROL_OUT,
    USBSLAVE_CONTROL_IN
};

#define USBSLAVE_EP_DIR_IN 0x80

// visible device states: 9.1.1
enum {
    usbsStateNotAttached,
    usbsStateAttached,
    usbsStatePowered,
    usbsStateDefault,
    usbsStateAddress,
    usbsStateConfigured,
    usbsStateSuspended
};

// events: 9.1.1 figure 9-1
enum {
    usbsEvReset,
    usbsEvAddressAssigned,
    usbsEvDeviceConfigured,
    usbsEvDeviceDeconfigured,
    usbsEvHubReset,
    usbsEvHubConfigured,
    usbsEvHubDeconfigured,
    usbsEvBusActivity,
    usbsEvBusInactive,
    usbsEvPowerInterruption
};

// status codes
enum USBSLAVE_STATUS {
    USBSLAVE_OK = 0,                   // 0
    USBSLAVE_INVALID_PARAMETER,        // 1
    USBSLAVE_ERROR,                    // 2
    USBSLAVE_FATAL_ERROR = 0xff,
};

unsigned char usbslave_init(uint8 s_num, uint8 d_num);

// Valid max packet size definitions for use with VOS_IOCTL_USBSLAVE_SET_ENDPOINT_MAX_PACKET_SIZE
#define USBSLAVE_MAX_PACKET_SIZE_8	0x00000000
#define USBSLAVE_MAX_PACKET_SIZE_16 0x20000000
#define USBSLAVE_MAX_PACKET_SIZE_32 0x40000000
#define USBSLAVE_MAX_PACKET_SIZE_64 0x60000000

#endif                                 /* __USBSLAVE_H__ */
