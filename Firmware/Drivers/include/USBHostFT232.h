/*
** USBHostFT232.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for the USB Host FT232 driver.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Host FT232 Driver
** Requires: vos.h ioctl.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBHOSTFT232_H__
#define __USBHOSTFT232_H__

#include "ioctl.h"

#define USBHOSTFT232_VERSION_STRING "2.0.2"

// thread memory size required by this driver
#define USBHOSTFT232_POLL_MEMORY						0x200

// USBHOSTFT232 IOCTL definitions (same as UART/SPI/FIFO IOCTL codes)
// UART IOCTL definitions
#define VOS_IOCTL_USBHOSTFT232_GET_MODEM_STATUS			(VOS_IOCTL_UART_BASE)         // get the modem status
#define VOS_IOCTL_USBHOSTFT232_GET_LINE_STATUS			(VOS_IOCTL_UART_BASE + 1)     // get the line status
#define VOS_IOCTL_USBHOSTFT232_SET_BAUD_RATE			(VOS_IOCTL_UART_BASE + 2)     // set the baud rate
#define VOS_IOCTL_USBHOSTFT232_SET_FLOW_CONTROL			(VOS_IOCTL_UART_BASE + 3)     // set flow control
#define VOS_IOCTL_USBHOSTFT232_SET_DATA_BITS			(VOS_IOCTL_UART_BASE + 4)     // set the number of data bits
#define VOS_IOCTL_USBHOSTFT232_SET_STOP_BITS			(VOS_IOCTL_UART_BASE + 5)     // set the number of stop bits
#define VOS_IOCTL_USBHOSTFT232_SET_PARITY				(VOS_IOCTL_UART_BASE + 6)     // set the parity
#define VOS_IOCTL_USBHOSTFT232_SET_RTS					(VOS_IOCTL_UART_BASE + 7)     // assert the RTS line
#define VOS_IOCTL_USBHOSTFT232_CLEAR_RTS				(VOS_IOCTL_UART_BASE + 8)     // deassert the RTS line
#define VOS_IOCTL_USBHOSTFT232_SET_DTR					(VOS_IOCTL_UART_BASE + 9)     // assert the DTR line
#define VOS_IOCTL_USBHOSTFT232_CLEAR_DTR				(VOS_IOCTL_UART_BASE + 10)    // deassert the DTR line
#define VOS_IOCTL_USBHOSTFT232_SET_BREAK_ON				(VOS_IOCTL_UART_BASE + 11)    // set line break condition
#define VOS_IOCTL_USBHOSTFT232_SET_BREAK_OFF			(VOS_IOCTL_UART_BASE + 12)    // clear line break condition
#define VOS_IOCTL_USBHOSTFT232_SET_XON_CHAR				(VOS_IOCTL_UART_BASE + 13)    // set the XOn character
#define VOS_IOCTL_USBHOSTFT232_SET_XOFF_CHAR			(VOS_IOCTL_UART_BASE + 14)    // set the XOff character
#define VOS_IOCTL_USBHOSTFT232_WAIT_ON_MODEM_STATUS_INT (VOS_IOCTL_UART_BASE + 15)    // wait on a Tx status interrupt
                                                                                      // (CTS, DSR, RI, DCD, BUSY)
#define VOS_IOCTL_USBHOSTFT232_WAIT_ON_LINE_STATUS_INT	(VOS_IOCTL_UART_BASE + 16)    // wait on a line status interrupt
                                                                                      // (OE, PE, SE, BI)

#define VOS_IOCTL_USBHOSTFT232_SET_LATENCY				(VOS_IOCTL_USBHOSTFT232_BASE) // set FT232 latency
#define VOS_IOCTL_USBHOSTFT232_GET_LATENCY				(VOS_IOCTL_USBHOSTFT232_BASE + 1)
#define VOS_IOCTL_USBHOSTFT232_SET_BIT_MODE				(VOS_IOCTL_USBHOSTFT232_BASE + 2)
#define VOS_IOCTL_USBHOSTFT232_GET_BIT_MODE				(VOS_IOCTL_USBHOSTFT232_BASE + 3)

#define VOS_IOCTL_USBHOSTFT232_EEPROM_READ				(VOS_IOCTL_USBHOSTFT232_BASE + 4)
#define VOS_IOCTL_USBHOSTFT232_EEPROM_WRITE				(VOS_IOCTL_USBHOSTFT232_BASE + 5)
#define VOS_IOCTL_USBHOSTFT232_EEPROM_ERASE				(VOS_IOCTL_USBHOSTFT232_BASE + 6)

#define VOS_IOCTL_USBHOSTFT232_ATTACH					(VOS_IOCTL_USBHOSTFT232_BASE + 7)
#define VOS_IOCTL_USBHOSTFT232_DETACH					(VOS_IOCTL_USBHOSTFT232_BASE + 8)
#define VOS_IOCTL_USBHOSTFT232_START_POLL				(VOS_IOCTL_USBHOSTFT232_BASE + 9)  // start polling device for
                                                                                           // status and data
#define VOS_IOCTL_USBHOSTFT232_STOP_POLL				(VOS_IOCTL_USBHOSTFT232_BASE + 10) // stop polling device for
                                                                                           // status

typedef struct _usbhostft232_ioctl_cb_attach_t
{
    VOS_HANDLE				 hc_handle;
    usbhost_device_handle_ex ifDev;
    unsigned char			 ftPort;
} usbhostft232_ioctl_cb_attach_t;

// Bit-mode struct
typedef struct _usbhostft232_bitmode_t
{
    unsigned char mode;
    unsigned char mask;
} usbhostft232_bitmode_t;

// EEPROM data struct
typedef struct _usbhostft232_eeprom_t
{
    unsigned short ee_address;
    unsigned short ee_data;
} usbhostft232_eeprom_t;

// Standard USBHOSTFT232 baud rates
// USBHOSTFT232_BAUD_0, USBHOSTFT232_BAUD_1, USBHOSTFT232_BAUD_2
#define USBHOSTFT232_BAUD_300						 300
#define USBHOSTFT232_BAUD_600						 600
#define USBHOSTFT232_BAUD_1200						 1200
#define USBHOSTFT232_BAUD_2400						 2400
#define USBHOSTFT232_BAUD_4800						 4800
#define USBHOSTFT232_BAUD_9600						 9600
#define USBHOSTFT232_BAUD_19200						 19200
#define USBHOSTFT232_BAUD_38400						 38400
#define USBHOSTFT232_BAUD_57600						 57600
#define USBHOSTFT232_BAUD_115200					 115200
#define USBHOSTFT232_BAUD_256000					 256000
#define USBHOSTFT232_BAUD_500000					 500000
#define USBHOSTFT232_BAUD_1000000					 1000000
#define USBHOSTFT232_BAUD_1500000					 1500000
#define USBHOSTFT232_BAUD_2000000					 2000000
#define USBHOSTFT232_BAUD_3000000					 3000000
#define USBHOSTFT232_BAUD_8000000					 8000000
#define USBHOSTFT232_BAUD_12000000					 12000000

// Data Bits
#define USBHOSTFT232_DATA_BITS_7					 0
#define USBHOSTFT232_DATA_BITS_8					 1

// Stop Bits
#define USBHOSTFT232_STOP_BITS_1					 0
#define USBHOSTFT232_STOP_BITS_2					 1

// Parity
#define USBHOSTFT232_PARITY_NONE					 0
#define USBHOSTFT232_PARITY_ODD						 1
#define USBHOSTFT232_PARITY_EVEN					 2
#define USBHOSTFT232_PARITY_MARK					 3
#define USBHOSTFT232_PARITY_SPACE					 4

// Flow Control
#define USBHOSTFT232_FLOW_NONE						 0
#define USBHOSTFT232_FLOW_RTS_CTS					 1
#define USBHOSTFT232_FLOW_DTR_DSR					 2
#define USBHOSTFT232_FLOW_XON_XOFF					 3

// Bit Modes
#define USBHOSTFT232_BIT_MODE_RESET					 0x00
#define USBHOSTFT232_BIT_MODE_ASYNCHRONOUS_BIT_BANG	 0x01
#define USBHOSTFT232_BIT_MODE_MPSSE					 0x02
#define USBHOSTFT232_BIT_MODE_SYNCHRONOUS_BIT_BANG	 0x04
#define USBHOSTFT232_BIT_MODE_MCU_HOST_BUS_EMULATION 0x08
#define USBHOSTFT232_BIT_MODE_FAST_SERIAL			 0x10
#define USBHOSTFT232_BIT_MODE_CBUS_BIT_BANG			 0x20
#define USBHOSTFT232_BIT_MODE_SYNCHRONOUS_FIFO		 0x40

// Modem Status
#define USBHOSTFT232_MODEM_STATUS_CTS				 1
#define USBHOSTFT232_MODEM_STATUS_DSR				 2
#define USBHOSTFT232_MODEM_STATUS_DCD				 4
#define USBHOSTFT232_MODEM_STATUS_RI				 8

// Line Status
#define USBHOSTFT232_LINE_STATUS_OE					 2
#define USBHOSTFT232_LINE_STATUS_PE					 4
#define USBHOSTFT232_LINE_STATUS_FE					 8
#define USBHOSTFT232_LINE_STATUS_BI					 16

// Device Types
#define USBHOSTFT232_DEVICE_FT8U232AM				 0x0200
#define USBHOSTFT232_DEVICE_FT232B					 0x0400
#define USBHOSTFT232_DEVICE_FT2232					 0x0500
#define USBHOSTFT232_DEVICE_FT232R					 0x0600
#define USBHOSTFT232_DEVICE_FT2232H					 0x0700
#define USBHOSTFT232_DEVICE_FT4232H					 0x0800
#define USBHOSTFT232_DEVICE_FT232H					 0x0900

// device interfaces
#define USBHOSTFT232_PORTA							 0x00
#define USBHOSTFT232_PORTB							 0x02
#define USBHOSTFT232_PORTC							 0x03
#define USBHOSTFT232_PORTD							 0x04

enum USBHOSTFT232_STATUS {
    USBHOSTFT232_OK = 0,
    USBHOSTFT232_INVALID_PARAMETER,
    USBHOSTFT232_DMA_NOT_ENABLED,
    USBHOSTFT232_ERROR,
    USBHOSTFT232_NOT_FOUND,
    USBHOSTFT232_USBHOST_ERROR = 0x80,
    USBHOSTFT232_FATAL_ERROR = 0xFF
};

// USBHOSTFT232 initialisation function
unsigned char usbHostFt232_init(unsigned char vos_dev_num);

#endif                                 /* __USBHOSTFT232_H__ */
