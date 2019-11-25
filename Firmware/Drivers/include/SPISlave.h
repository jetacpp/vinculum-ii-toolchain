/*
** SPISlave.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II SPI Slave interface
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II SPI Slave Driver
** Requires: vos.h ioctl.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __SPI_SLAVE_H__
#define __SPI_SLAVE_H__

#include "ioctl.h"

#define SPISLAVE_VERSION_STRING "2.0.2"

// SPI Slave port definitions
#define SPI_SLAVE_0						0
#define SPI_SLAVE_1						1

// SPISlave IOCTL definitions
#define VOS_IOCTL_SPI_SLAVE_GET_STATUS	(VOS_IOCTL_SPI_SLAVE_BASE)     // get the status
#define VOS_IOCTL_SPI_SLAVE_SCK_CPHA	(VOS_IOCTL_SPI_SLAVE_BASE + 1) // set the phase of the SCK pin
#define VOS_IOCTL_SPI_SLAVE_SCK_CPOL	(VOS_IOCTL_SPI_SLAVE_BASE + 2) // set the polarity of the SCK pin
#define VOS_IOCTL_SPI_SLAVE_DATA_ORDER	(VOS_IOCTL_SPI_SLAVE_BASE + 3) // data transmitted MSB or LSB
#define VOS_IOCTL_SPI_SLAVE_SET_ADDRESS (VOS_IOCTL_SPI_SLAVE_BASE + 4) // set the 3-bit address for the SPI slave
#define VOS_IOCTL_SPI_SLAVE_SET_MODE	(VOS_IOCTL_SPI_SLAVE_BASE + 5) // set the SPI mode - 000 - Full Duplex; 001 -
                                                                       // 4-pin Half Duplex; 010 - 3-pin Half Duplex,
                                                                       // 011 - Unmanaged, 100 - Vinculum I compatible

// SPI clock phase
#define SPI_SLAVE_SCK_CPHA_0 0                                         // Data is latched from SDI on the SPI clk
                                                                       // leading edge and loaded onto SDO on the SPI
                                                                       // clk trailing edge
#define SPI_SLAVE_SCK_CPHA_1 1                                         // Data is latched from SDI on the SPI clk
                                                                       // trailing edge and loaded onto SDO on the SPI
                                                                       // clk leading edge

// SPI clock polarity
#define SPI_SLAVE_SCK_CPOL_0			 0                             // Active high clk, SCK low in idle
#define SPI_SLAVE_SCK_CPOL_1			 1                             // Active low clk, SCK high in idle

// SPI data transmission order
#define SPI_SLAVE_DATA_ORDER_MSB		 0                             // Transmit data MSB
#define SPI_SLAVE_DATA_ORDER_LSB		 1                             // Transmit data LSB

// Supported SPI modes - 000 - Full Duplex; 001 - Half Duplex, 4 pin; 010 - Half Duplex, 3 pin, 011 - Unmanaged, 100 -
// Vinculum I compatible
#define SPI_SLAVE_MODE_FULL_DUPLEX		 0
#define SPI_SLAVE_MODE_HALF_DUPLEX_4_PIN 1
#define SPI_SLAVE_MODE_HALF_DUPLEX_3_PIN 2
#define SPI_SLAVE_MODE_UNMANAGED		 3
#define SPI_SLAVE_MODE_VI_COMPATIBLE	 4

enum SPISLAVE_STATUS {
    SPISLAVE_OK = 0,
    SPISLAVE_INVALID_PARAMETER,
    SPISLAVE_DMA_NOT_ENABLED,
    SPISLAVE_ERROR,
    SPISLAVE_FATAL_ERROR = 0xFF
};

// Context for SPI slaves
typedef struct _spislave_context_t {
    unsigned char slavenumber;
    unsigned char buffer_size;
} spislave_context_t;

// SPISlave initialisation function
unsigned char spislave_init(
    unsigned char devNum,
    spislave_context_t *context
    );

#endif                                 /* __SPI_SLAVE_H__ */

