/*
** ioctl.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Company Confidential
**
** Header file containing definitions for Vinculum II common IOCTL codes for UART, SPI Slave,
** SPI Master and FIFO interfaces.  Also defines unique IOCTL code offsets for each peripheral.
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II Common IOCTL Codes
** Requires: VOS
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __IOCTL_H__
#define __IOCTL_H__

// Common IOCTL definitions for UART, SPI Slave, SPI Master and FIFO interfaces
#define VOS_IOCTL_COMMON_RESET				 0x01 // reset the block
#define VOS_IOCTL_COMMON_GET_RX_QUEUE_STATUS 0x02 // get the number of bytes in the Rx buffer
#define VOS_IOCTL_COMMON_GET_TX_QUEUE_STATUS 0x03 // get the number of bytes in the Tx buffer
#define VOS_IOCTL_COMMON_ENABLE_DMA			 0x04 // acquire DMA channels and disable interrupts
#define VOS_IOCTL_COMMON_DISABLE_DMA		 0x05 // release DMA channels and enable interrupts

// Mode flags for the enable DMA IOCTL
#define DMA_ACQUIRE_AS_REQUIRED				 0x00
#define DMA_ACQUIRE_AND_RETAIN				 0x01

// UART specific IOCTL offset
#define VOS_IOCTL_UART_BASE					 0x20

// SPI Slave specific IOCTL offset
#define VOS_IOCTL_SPI_SLAVE_BASE			 0x40

// SPI Master specific IOCTL offset
#define VOS_IOCTL_SPI_MASTER_BASE			 0x60

// FIFO specific IOCTL offset
#define VOS_IOCTL_FIFO_BASE					 0x80

// USB host specific IOCTL offset
#define VOS_IOCTL_USBHOSTFT232_BASE			 0xA0

// USB slave specific IOCTL offset
#define VOS_IOCTL_USBSLAVEFT232_BASE		 0xC0

// USB slave specific IOCTL offset
#define VOS_IOCTL_USBSLAVEHID_BASE			 0xE0

// Common IOCTL structure for UART, SPI Slave, SPI Master and FIFO interfaces
typedef struct _common_ioctl_cb_t {
    unsigned char ioctl_code;
    union
    {
        unsigned long uart_baud_rate;
        unsigned long spi_master_sck_freq;
        unsigned char param;
        void		  *data;
    } set;
    union
    {
        unsigned long  spi_master_sck_freq;
        unsigned short queue_stat;
        unsigned char  param;
        void		   *data;
    } get;
} common_ioctl_cb_t;

#endif                                 /* __IOCTL_H__ */

