/*
** StillImage.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II Still Image Driver
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II Still Image Driver
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __STILLIMAGE_H__
#define __STILLIMAGE_H__

#define STILLIMAGE_VERSION_STRING "2.0.2"

enum STILLIMAGE_STATUS {
    STILLIMAGE_OK = 0,
    STILLIMAGE_NOT_FOUND,
    STILLIMAGE_READ_ONLY,
    STILLIMAGE_PENDING,
    STILLIMAGE_INVALID_PARAMETER,
    STILLIMAGE_INVALID_BUFFER,
    STILLIMAGE_INVALID_FILE_TYPE,
    STILLIMAGE_EXISTS,
    STILLIMAGE_NOT_OPEN,
    STILLIMAGE_EOF,
    STILLIMAGE_DIRECTORY_TABLE_FULL,
    STILLIMAGE_DISK_FULL,
    STILLIMAGE_ERROR,
    STILLIMAGE_HC_ERROR = 0x40,
    STILLIMAGE_FATAL_ERROR = 0xff,
};

#define STILLIMAGE_IOCTL_ATTACH			  0x01
#define STILLIMAGE_IOCTL_DETACH			  0x02
#define STILLIMAGE_IOCTL_GET_FIRST_OBJECT 0x10
#define STILLIMAGE_IOCTL_GET_OBJECT_INFO  0x18
#define STILLIMAGE_IOCTL_OPEN_OBJECT	  0x20
#define STILLIMAGE_IOCTL_CLOSE_OBJECT	  0x21
#define STILLIMAGE_IOCTL_DELETE_OBJECT	  0x30
#define STILLIMAGE_IOCTL_INITIATE_CAPTURE 0x80

unsigned char stillimage_init(unsigned char vos_dev_num);

typedef struct _stillimage_ioctl_cb_t {
    unsigned char ioctl_code;
    // read buffer
    unsigned char *get;
    // write butter
    unsigned char *set;
} stillimage_ioctl_cb_t;

typedef struct _stillimage_ioctl_cb_attach_t
{
    VOS_HANDLE				 hc_handle;
    usbhost_device_handle_ex ifDev;
} stillimage_ioctl_cb_attach_t;

typedef struct _stillimage_ioctl_cb_object_info_t
{
    unsigned int   len;
    char		   name[11];
    unsigned short format;             // 0x3801 for JPG
} stillimage_ioctl_cb_object_info_t;

#endif /* __STILLIMAGE_H__ */
