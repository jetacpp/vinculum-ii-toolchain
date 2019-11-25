/*
** SPIMaster.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II SPI Master interface
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II SPI Master Driver
** Requires: vos.h ioctl.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __SPI_MASTER_H__
#define __SPI_MASTER_H__

#include "ioctl.h"

#define SPIMASTER_VERSION_STRING "2.0.2"

// SPIMaster IOCTL definitions
#define VOS_IOCTL_SPI_MASTER_GET_STATUS		   (VOS_IOCTL_SPI_MASTER_BASE)     // get the status
#define VOS_IOCTL_SPI_MASTER_SCK_CPHA		   (VOS_IOCTL_SPI_MASTER_BASE + 1) // set the phase of the SCK pin
#define VOS_IOCTL_SPI_MASTER_SCK_CPOL		   (VOS_IOCTL_SPI_MASTER_BASE + 2) // set the polarity of the SCK pin
#define VOS_IOCTL_SPI_MASTER_DATA_ORDER		   (VOS_IOCTL_SPI_MASTER_BASE + 3) // data transmitted MSB or LSB
#define VOS_IOCTL_SPI_MASTER_SS_0			   (VOS_IOCTL_SPI_MASTER_BASE + 4) // assert slave select 0 signal
#define VOS_IOCTL_SPI_MASTER_SS_1			   (VOS_IOCTL_SPI_MASTER_BASE + 5) // assert slave select 1 signal
#define VOS_IOCTL_SPI_MASTER_SET_SCK_FREQUENCY (VOS_IOCTL_SPI_MASTER_BASE + 6) // set SCK frequency.  Based on system
                                                                               // clock value.
#define VOS_IOCTL_SPI_MASTER_SET_DATA_DELAY	   (VOS_IOCTL_SPI_MASTER_BASE + 7) // delay in SCK periods after SS_n
                                                                               // becomes before the first SCK cycle
#define VOS_IOCTL_SPI_MASTER_AUTO_TOGGLE_SS	   (VOS_IOCTL_SPI_MASTER_BASE + 8) // automatically toggle specified SS
                                                                               // lines when writing
#define VOS_IOCTL_SPI_MASTER_RESET_FIFO_BUFFER (VOS_IOCTL_SPI_MASTER_BASE + 9) // resets the FIFO buffer in the SPI 
                                                                               // driver flushing data from buffers

// SPI clock phase
#define SPI_MASTER_SCK_CPHA_0				   0                               // Data is latched from SDI on the SPI
                                                                               // clk leading edge and loaded onto SDO
                                                                               // on the SPI clk trailing edge
#define SPI_MASTER_SCK_CPHA_1				   1                               // Data is latched from SDI on the SPI
                                                                               // clk trailing edge and loaded onto SDO
                                                                               // on the SPI clk leading edge

// SPI clock polarity
#define SPI_MASTER_SCK_CPOL_0				   0                               // Active high clk, SCK low in idle
#define SPI_MASTER_SCK_CPOL_1				   1                               // Active low clk, SCK high in idle

// SPI data transmission order
#define SPI_MASTER_DATA_ORDER_MSB			   0                               // Transmit data MSB
#define SPI_MASTER_DATA_ORDER_LSB			   1                               // Transmit data LSB

// SPI Slave select signals
#define SPI_MASTER_SS_ENABLE				   0                               // Enable slave select signal (active
                                                                               // low)
#define SPI_MASTER_SS_DISABLE				   1                               // Disable slave select signal

// SPI Slave select auto-toggle mask values
#define SPI_MASTER_SS_AUTO_TOGGLE_ENABLE_SS_0  1                               // Toggle slave select 0 when
                                                                               // reading/writing
#define SPI_MASTER_SS_AUTO_TOGGLE_ENABLE_SS_1  2                               // Toggle slave select 1 when
                                                                               // reading/writing
#define SPI_MASTER_SS_AUTO_TOGGLE_DISABLE_SS_0 4                               // Do not toggle slave select 0 when
                                                                               // reading/writing
#define SPI_MASTER_SS_AUTO_TOGGLE_DISABLE_SS_1 8                               // Do not toggle slave select 1 when
                                                                               // reading/writing

enum SPIMASTER_STATUS {
    SPIMASTER_OK = 0,
    SPIMASTER_INVALID_PARAMETER,
    SPIMASTER_DMA_NOT_ENABLED,
    SPIMASTER_ERROR,
    SPIMASTER_FATAL_ERROR = 0xFF
};

// Context for SPIMaster
typedef struct _spimaster_context_t {
    unsigned char buffer_size;
} spimaster_context_t;

// SPIMaster initialisation function
unsigned char spimaster_init(
    unsigned char devNum,
    spimaster_context_t *context
    );

#endif                                 /* __SPI_MASTER_H__ */

