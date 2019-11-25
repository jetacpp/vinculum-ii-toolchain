/*
** BOMS.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II BOMS Driver
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II BOMS Driver
** Requires: vos.h msi.h usb.h usbhost.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __BOMS_H__
#define __BOMS_H__

#define BOMS_VERSION_STRING "2.0.2"

#include "msi.h"

enum BOMS_STATUS {
    BOMS_HC_CC_ERROR = MSI_RESERVED,
    BOMS_CLEAR_HALT,
    BOMS_FATAL_ERROR = 0xff,
}

#define MSI_IOCTL_BOMS_ATTACH (MSI_IOCTL_TRANSPORT_SPECIFIC_BOMS + 0x01)
#define MSI_IOCTL_BOMS_DETACH (MSI_IOCTL_TRANSPORT_SPECIFIC_BOMS + 0x02)

unsigned char boms_init(unsigned char vos_dev_num);

typedef struct _boms_ioctl_cb_attach_t
{
    VOS_HANDLE				 hc_handle;
    usbhost_device_handle_ex ifDev;
} boms_ioctl_cb_attach_t;

#endif                                 /* __BOMS_H__ */
