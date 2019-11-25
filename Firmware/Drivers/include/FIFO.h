/*
** FIFO.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II 245 parallel FIFO interface
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II 245 FIFO Driver
** Requires: vos.h ioctl.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __FIFO_H__
#define __FIFO_H__

#include "ioctl.h"

#define FIFO_VERSION_STRING "2.0.2"

// FIFO IOCTL definitions
#define VOS_IOCTL_FIFO_GET_STATUS (VOS_IOCTL_FIFO_BASE)     // get the status of the FIFO
#define VOS_IOCTL_FIFO_SET_MODE	  (VOS_IOCTL_FIFO_BASE + 1) // set the FIFO into synchronous or asynchronous mode

#define FIFO_MODE_ASYNCHRONOUS	  0
#define FIFO_MODE_SYNCHRONOUS	  1

#define FIFO_STATUS_READ_NOT_FULL 1

enum FIFO_STATUS {
    FIFO_OK = 0,
    FIFO_INVALID_PARAMETER,
    FIFO_DMA_NOT_ENABLED,
    FIFO_ERROR,
    FIFO_FATAL_ERROR = 0xFF
};

// Context for FIFO
typedef struct _fifo_context_t {
    unsigned char buffer_size;
} fifo_context_t;

// FIFO initialisation function
unsigned char fifo_init(
    unsigned char devNum,
    fifo_context_t *context
    );

#endif                                 /* __FIFO_H__ */

