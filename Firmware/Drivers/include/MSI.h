/*
** MSI.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Company Confidential
**
** Header file containing definitions for Vinculum II Mass Storage Interface compatible Drivers
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II BOMS, SD Drivers
** Requires: VOS
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __MSI_H__
#define __MSI_H__

#ifndef __USBHOST_H__
#error The USBHost.h header file must be included before the file msi.h
#endif

enum MSI_STATUS {
    MSI_OK = 0,
    MSI_COMMAND_FAILED,
    MSI_NOT_FOUND,
    MSI_INVALID_PARAMETER,
    MSI_INVALID_BUFFER,
    MSI_NOT_ACCESSED,
    MSI_ERROR,
    // reserved error codes from 0x40 to 0x7f
    MSI_RESERVED = 0x40,
    // transport generated error codes from 0x80 to 0xff
    MSI_TRANSPORT_ERROR = 0x80,
};

// IOCTL definitions

// device operations
#define MSI_IOCTL_RESET					  0x10
#define MSI_IOCTL_GET_MAX_LUN			  0x11
#define MSI_IOCTL_GET_LUN				  0x12
#define MSI_IOCTL_SET_LUN				  0x13
#define MSI_IOCTL_GET_SECTOR_SIZE		  0x14
#define MSI_IOCTL_GET_DEV_INFO			  0x15
#define MSI_IOCTL_CAN_SPLIT				  0x16
#define MSI_IOCTL_RAW_TRANSFER			  0x17

// transport specific operations
#define MSI_IOCTL_TRANSPORT_SPECIFIC_BOMS 0x20

// IOCTL block
typedef struct _msi_ioctl_cb_t {
    unsigned char ioctl_code;
    // read buffer
    unsigned char *get;
    // write butter
    unsigned char *set;
} msi_ioctl_cb_t;

typedef struct _msi_ioctl_cb_info_t
{
    // device information
    unsigned char  vendorId[8];
    unsigned char  productId[16];
    unsigned char  rev[4];
    unsigned short vid;                // BOMS specific
    unsigned short pid;                // BOMS specific
} msi_ioctl_cb_info_t;

// Transfer structure
//
// Passed to a read or write operation containing instructions for the current
// xfer.
typedef struct _msi_xfer_cb_t {
    // sector number
    unsigned long	sector;

    // reference for report completion notification
    vos_semaphore_t *s;

    // buffer pointer
    unsigned char	*buf;
    // buffer length
    unsigned short	buf_len;

    // transaction total length (not the buffer size when transactions are split)
    unsigned short	total_len;

    // which command/data/status phases to use
    unsigned char	do_phases;

    // trasnfer completion status
    // if BOMS error will include completion code from host controller (4 bits)
    unsigned char	status;

    // storage for transport specific transfer structures
    // transfer structure for USB Host (BOMS specific)
    union
    {
        // transfer structure for USB Host (BOMS specific)
        usbhost_xfer_t usb;
    } transport;
} msi_xfer_cb_t;

#define MSI_PHASE_COMMAND_BIT	   0
#define MSI_PHASE_DATA_BIT		   1
#define MSI_PHASE_STATUS_BIT	   2
#define MSI_PHASE_DATA_NOBLOCK_BIT 4
#define MSI_PHASE_DATA_NOSTART_BIT 5

#define MSI_PHASE_COMMAND		   (1 << MSI_PHASE_COMMAND_BIT)
#define MSI_PHASE_DATA			   (1 << MSI_PHASE_DATA_BIT)
#define MSI_PHASE_STATUS		   (1 << MSI_PHASE_STATUS_BIT)
#define MSI_PHASE_DATA_NOBLOCK	   (1 << MSI_PHASE_DATA_NOBLOCK_BIT)
#define MSI_PHASE_DATA_NOSTART	   (1 << MSI_PHASE_DATA_NOSTART_BIT)

#define MSI_PHASE_ALL			   (MSI_PHASE_COMMAND | MSI_PHASE_DATA | MSI_PHASE_STATUS)

#endif                                 /* __MSI_H__ */
