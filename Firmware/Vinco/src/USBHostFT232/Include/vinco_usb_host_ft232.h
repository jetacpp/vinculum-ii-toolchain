/*
** vinco_usb_host_printer.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the Vinco USB Host FT232 Library.
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef _VN_HOST_FT232_H_
#define _VN_HOST_FT232_H_

#include "vos.h"
#include "devman.h"

typedef VOS_HANDLE VN_HANDLE;
typedef unsigned char VN_STATUS;

typedef VN_STATUS (*FT232_OPEN)(VN_HANDLE *vnHandle);
typedef VN_STATUS (*RESET)(VN_HANDLE vnHandle);
typedef VN_STATUS (*GET_RX_STATUS)(VN_HANDLE vnHandle, unsigned short *queueStatus);
typedef VN_STATUS (*GET_TX_STATUS)(VN_HANDLE vnHandle, unsigned short *queueStatus);
typedef VN_STATUS (*GET_MODEM_STATUS)(VN_HANDLE vnHandle, unsigned char *modemStatus);
typedef VN_STATUS (*GET_LINE_STATUS)(VN_HANDLE vnHandle, unsigned char *lineStatus);
typedef VN_STATUS (*SET_BAUD_RATE)(VN_HANDLE vnHandle, unsigned long baudRate);
typedef VN_STATUS (*SET_FLOW_CONTROL)(VN_HANDLE vnHandle, unsigned char flowControl);
typedef VN_STATUS (*SET_DATA_BITS)(VN_HANDLE vnHandle, unsigned char dataBits);
typedef VN_STATUS (*SET_STOP_BITS)(VN_HANDLE vnHandle, unsigned char stopBits);
typedef VN_STATUS (*SET_PARITY)(VN_HANDLE vnHandle, unsigned char parity);
typedef VN_STATUS (*SET_RTS)(VN_HANDLE vnHandle);
typedef VN_STATUS (*CLEAR_RTS)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_DTR)(VN_HANDLE vnHandle);
typedef VN_STATUS (*CLEAR_DTR)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_BREAK_ON)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_BREAK_OFF)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_XON)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_XOFF)(VN_HANDLE vnHandle);
typedef VN_STATUS (*SET_LATENCY)(VN_HANDLE vnHandle, unsigned char latency);
typedef VN_STATUS (*GET_LATENCY)(VN_HANDLE vnHandle, unsigned char *latency);
typedef VN_STATUS (*SET_BIT_MODE)(VN_HANDLE vnHandle, unsigned char mode, unsigned char mask);
typedef VN_STATUS (*GET_BIT_MODE)(VN_HANDLE vnHandle, unsigned char *mode);
typedef VN_STATUS (*EEPROM_READ)(VN_HANDLE vnHandle, unsigned short addr, unsigned short *data);
typedef VN_STATUS (*EEPROM_WRITE)(VN_HANDLE vnHandle, unsigned short addr, unsigned short data);
typedef VN_STATUS (*EEPROM_ERASE)(VN_HANDLE vnHandle);
typedef VN_STATUS (*START_POLL)(VN_HANDLE vnHandle);
typedef VN_STATUS (*STOP_POLL)(VN_HANDLE vnHandle);
typedef VN_STATUS (*FT232_WRITE)(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten);
typedef VN_STATUS (*FT232_READ)(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead);
typedef VN_STATUS (*FT232_CLOSE)(VN_HANDLE vnHandle);

typedef struct _usb_host_ft232_st
{
	FT232_OPEN 			open;
	RESET 				reset;
	GET_RX_STATUS		getRXStatus;
	GET_TX_STATUS 		getTXStatus;
	GET_MODEM_STATUS	getModemStatus;
	GET_LINE_STATUS		getLineStatus;
	SET_BAUD_RATE		setBaudRate;
	SET_FLOW_CONTROL	setFlowControl;
	SET_DATA_BITS		setDataBits;
	SET_STOP_BITS		setStopBits;
	SET_PARITY			setParity;
	SET_RTS				setRTS;
	CLEAR_RTS			clearRTS;
	SET_DTR				setDTR;
	CLEAR_DTR			clearDTR;
	SET_BREAK_ON		setBreakOn;
	SET_BREAK_OFF		setBreakOff;
	SET_XON				setXON;
	SET_XOFF			setXOFF;
	SET_LATENCY			setLatency;
	GET_LATENCY			getLatency;
	SET_BIT_MODE		setBitMode;
	GET_BIT_MODE		getBitMode;
	EEPROM_READ			readEEPROM;
	EEPROM_WRITE		writeEEPROM;
	EEPROM_ERASE		eraseEEPROM;
	START_POLL			startPoll;
	STOP_POLL			stopPoll;
	FT232_WRITE	   		write;
	FT232_READ			read;
	FT232_CLOSE			close;
} usb_host_ft232_st;

void VN_USBHostFT232Init(unsigned char HostFT232DevNum, usb_host_ft232_st *p);
void VN_USBHostFT232AttachUSBHostHandle(VOS_HANDLE hUsbHostMain);

enum VINCO_USBHOSTFT232_STATUS
{
	VINCO_USBHOSTFT232_OK = 0,
	VINCO_USBHOSTFT232_UNSUCCESSFUL,
	VINCO_USBHOSTFT232_FATAL_ERROR = 0xFF
};

#endif /* _VN_HOST_FT232_H_ */
