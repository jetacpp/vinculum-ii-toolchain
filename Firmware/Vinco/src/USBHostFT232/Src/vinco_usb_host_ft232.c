/*
** vinco_usb_host_printer.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source code for the Vinco USB Host FT232 Library.
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

#include "vinco_usb_host_ft232.h"
#include "USB.h"
#include "USBHost.h"
#include "USBHostFT232.h"

VOS_HANDLE hUsbHost;
unsigned char hostFT232DeviceNumber;

VN_STATUS VN_USBHostFT232Open(VN_HANDLE *vnHandle);
VN_STATUS VN_USBHostFT232Reset(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232GetRxQueueStatus(VN_HANDLE vnHandle, unsigned short *queueStatus);
VN_STATUS VN_USBHostFT232GetTxQueueStatus(VN_HANDLE vnHandle, unsigned short *queueStatus);
VN_STATUS VN_USBHostFT232GetModemStatus(VN_HANDLE vnHandle, unsigned char *modemStatus);
VN_STATUS VN_USBHostFT232GetLineStatus(VN_HANDLE vnHandle, unsigned char *lineStatus);
VN_STATUS VN_USBHostFT232SetBaudRate(VN_HANDLE vnHandle, unsigned long baudRate);
VN_STATUS VN_USBHostFT232SetFlowControl(VN_HANDLE vnHandle, unsigned char flowControl);
VN_STATUS VN_USBHostFT232SetDataBits(VN_HANDLE vnHandle, unsigned char dataBits);
VN_STATUS VN_USBHostFT232SetStopBits(VN_HANDLE vnHandle, unsigned char stopBits);
VN_STATUS VN_USBHostFT232SetParity(VN_HANDLE vnHandle, unsigned char parity);
VN_STATUS VN_USBHostFT232SetRTS(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232ClearRTS(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetDTR(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232ClearDTR(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetBreakOn(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetBreakOff(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetXONChar(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetXOFFChar(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232SetLatency(VN_HANDLE vnHandle, unsigned char latency);
VN_STATUS VN_USBHostFT232GetLatency(VN_HANDLE vnHandle, unsigned char *latency);
VN_STATUS VN_USBHostFT232SetBitMode(VN_HANDLE vnHandle, unsigned char mode, unsigned char mask);
VN_STATUS VN_USBHostFT232GetBitMode(VN_HANDLE vnHandle, unsigned char *mode);
VN_STATUS VN_USBHostFT232EEPROMRead(VN_HANDLE vnHandle, unsigned short addr, unsigned short *data);
VN_STATUS VN_USBHostFT232EEPROMWrite(VN_HANDLE vnHandle, unsigned short addr, unsigned short data);
VN_STATUS VN_USBHostFT232EEPROMErase(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232StartPoll(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232StopPoll(VN_HANDLE vnHandle);
VN_STATUS VN_USBHostFT232Write(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten);
VN_STATUS VN_USBHostFT232Read(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead);
VN_STATUS VN_USBHostFT232Close(VN_HANDLE vnHandle);

void VN_USBHostFT232Init(unsigned char HostFT232DevNum, usb_host_ft232_st *p)
{
	hostFT232DeviceNumber = HostFT232DevNum;

	p->open = &VN_USBHostFT232Open;
	p->reset = &VN_USBHostFT232Reset;
	p->getRXStatus = &VN_USBHostFT232GetRxQueueStatus;
	p->getTXStatus = &VN_USBHostFT232GetTxQueueStatus;
	p->getModemStatus = &VN_USBHostFT232GetModemStatus;
	p->getLineStatus = &VN_USBHostFT232GetLineStatus;
	p->setBaudRate = &VN_USBHostFT232SetBaudRate;
	p->setFlowControl = &VN_USBHostFT232SetFlowControl;
	p->setDataBits = &VN_USBHostFT232SetDataBits;
	p->setStopBits = &VN_USBHostFT232SetStopBits;
	p->setParity = &VN_USBHostFT232SetParity;
	p->setRTS = &VN_USBHostFT232SetRTS;
	p->clearRTS = &VN_USBHostFT232ClearRTS;
	p->setDTR = &VN_USBHostFT232SetDTR;
	p->clearDTR = &VN_USBHostFT232ClearDTR;
	p->setBreakOn = &VN_USBHostFT232SetBreakOn;
	p->setBreakOff = &VN_USBHostFT232SetBreakOff;
	p->setXON = &VN_USBHostFT232SetXONChar;
	p->setXOFF = &VN_USBHostFT232SetXOFFChar;
	p->setLatency = &VN_USBHostFT232SetLatency;
	p->getLatency = &VN_USBHostFT232GetLatency;
	p->setBitMode = &VN_USBHostFT232SetBitMode;
	p->getBitMode = &VN_USBHostFT232GetBitMode;
	p->readEEPROM = &VN_USBHostFT232EEPROMRead;
	p->writeEEPROM = &VN_USBHostFT232EEPROMWrite;
	p->eraseEEPROM = &VN_USBHostFT232EEPROMErase;
	p->startPoll = &VN_USBHostFT232StartPoll;
	p->stopPoll = &VN_USBHostFT232StopPoll;
	p->write = &VN_USBHostFT232Write;
	p->read = &VN_USBHostFT232Read;
	p->close = &VN_USBHostFT232Close;

	return;
}

void VN_USBHostFT232AttachUSBHostHandle(VOS_HANDLE hUsbHostMain)
{
	hUsbHost = hUsbHostMain;
}

VN_STATUS VN_USBHostFT232Open(VN_HANDLE *vnHandle)
{
	unsigned char i;
	unsigned char connectState = PORT_STATE_DISCONNECTED;
	VOS_HANDLE hHostFT232;
	unsigned char ft232Status;
	usbhost_ioctl_cb_t hc_iocb;
	usbhost_ioctl_cb_vid_pid_t hc_iocb_vendor;
	common_ioctl_cb_t ft232_iocb;
	usbhostft232_ioctl_cb_attach_t ft232_att;
	usbhost_device_handle_ex ifFT232;

	for (i = 0; i < 5; i++)
	{
		// Wait for enumeration of the printer to complete
		vos_delay_msecs(500);

		hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_GET_CONNECT_STATE;
		hc_iocb.get = &connectState;
		vos_dev_ioctl(hUsbHost, &hc_iocb);

		if (connectState == PORT_STATE_ENUMERATED)
		{
			break;
		}
	}

	if (connectState == PORT_STATE_ENUMERATED)
	{
		// Find FT232 class device
		hc_iocb_vendor.vid = USB_VID_FTDI;
		hc_iocb_vendor.pid = USB_PID_FTDI_FT232;

		// Find first FT232 device
		hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_DEVICE_FIND_HANDLE_BY_VID_PID;
		hc_iocb.handle.dif = NULL;
		hc_iocb.set = &hc_iocb_vendor;
		hc_iocb.get = &ifFT232;

		if (vos_dev_ioctl(hUsbHost, &hc_iocb) == USBHOST_OK)
		{
			hHostFT232 = vos_dev_open(hostFT232DeviceNumber);

			// Perform attach
			ft232_att.hc_handle = hUsbHost;
			ft232_att.ifDev = ifFT232;
			ft232_att.ftPort = USBHOSTFT232_PORTA;	/* Risk */

			ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_ATTACH;
			ft232_iocb.set.data = &ft232_att;
			ft232_iocb.get = NULL;
			ft232Status = vos_dev_ioctl(hHostFT232, &ft232_iocb);
			if (ft232Status == USBHOSTFT232_OK)
			{
				*vnHandle = hHostFT232;
				return (VN_STATUS) VINCO_USBHOSTFT232_OK;
			}
			else
			{
				return (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;
			}
		}
		else
		{
			return (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;
		}
	}
	else
	{
		return (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;
	}
}

VN_STATUS VN_USBHostFT232Reset(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_COMMON_RESET;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232GetRxQueueStatus(VN_HANDLE vnHandle, unsigned short *queueStatus)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_COMMON_GET_RX_QUEUE_STATUS;
	vos_dev_ioctl(vnHandle, &ft232_iocb);
	*queueStatus = ft232_iocb.get.queue_stat;

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232GetTxQueueStatus(VN_HANDLE vnHandle, unsigned short *queueStatus)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_COMMON_GET_TX_QUEUE_STATUS;
	vos_dev_ioctl(vnHandle, &ft232_iocb);
	*queueStatus = ft232_iocb.get.queue_stat;

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232GetModemStatus(VN_HANDLE vnHandle, unsigned char *modemStatus)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_GET_MODEM_STATUS;
	vos_dev_ioctl(vnHandle, &ft232_iocb);
	*modemStatus = ft232_iocb.get.param;

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232GetLineStatus(VN_HANDLE vnHandle, unsigned char *lineStatus)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_GET_LINE_STATUS;
	vos_dev_ioctl(vnHandle, &ft232_iocb);
	*lineStatus = ft232_iocb.get.param;

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232SetBaudRate(VN_HANDLE vnHandle, unsigned long baudRate)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_BAUD_RATE;
	ft232_iocb.set.uart_baud_rate = baudRate;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetFlowControl(VN_HANDLE vnHandle, unsigned char flowControl)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_FLOW_CONTROL;
	ft232_iocb.set.param = flowControl;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetDataBits(VN_HANDLE vnHandle, unsigned char dataBits)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_DATA_BITS;
	ft232_iocb.set.param = dataBits;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetStopBits(VN_HANDLE vnHandle, unsigned char stopBits)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_STOP_BITS;
	ft232_iocb.set.param = stopBits;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetParity(VN_HANDLE vnHandle, unsigned char parity)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_PARITY;
	ft232_iocb.set.param = parity;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetRTS(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_RTS;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232ClearRTS(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_CLEAR_RTS;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetDTR(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_DTR;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232ClearDTR(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_CLEAR_DTR;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetBreakOn(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_BREAK_ON;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetBreakOff(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_BREAK_OFF;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetXONChar(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_XON_CHAR;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetXOFFChar(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_XOFF_CHAR;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetLatency(VN_HANDLE vnHandle, unsigned char latency)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_LATENCY;
	ft232_iocb.set.param = latency;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232GetLatency(VN_HANDLE vnHandle, unsigned char *latency)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_GET_LATENCY;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		*latency = ft232_iocb.get.param;
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232SetBitMode(VN_HANDLE vnHandle, unsigned char mode, unsigned char mask)
{
	common_ioctl_cb_t ft232_iocb;
	usbhostft232_bitmode_t ft232_bitmode;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_bitmode.mode = mode;
	ft232_bitmode.mask = mask;
	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_SET_BIT_MODE;
	ft232_iocb.set.data = &ft232_bitmode;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232GetBitMode(VN_HANDLE vnHandle, unsigned char *mode)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_GET_BIT_MODE;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		*mode = ft232_iocb.get.param;
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232EEPROMRead(VN_HANDLE vnHandle, unsigned short addr, unsigned short *data)
{
	common_ioctl_cb_t ft232_iocb;
	usbhostft232_eeprom_t ft232_eeprom;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_eeprom.ee_address = addr;
	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_EEPROM_READ;
	ft232_iocb.get.data = &ft232_eeprom;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		*data = ft232_eeprom.ee_data;
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232EEPROMWrite(VN_HANDLE vnHandle, unsigned short addr, unsigned short data)
{
	common_ioctl_cb_t ft232_iocb;
	usbhostft232_eeprom_t ft232_eeprom;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_eeprom.ee_address = addr;
	ft232_eeprom.ee_data = data;
	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_EEPROM_WRITE;
	ft232_iocb.set.data = &ft232_eeprom;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232EEPROMErase(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_EEPROM_ERASE;
	if (vos_dev_ioctl(vnHandle, &ft232_iocb) == USBHOST_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232StartPoll(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_START_POLL;
	vos_dev_ioctl(vnHandle, &ft232_iocb);

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232StopPoll(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_STOP_POLL;
	vos_dev_ioctl(vnHandle, &ft232_iocb);

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}

VN_STATUS VN_USBHostFT232Write(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToWrite, unsigned short *numBytesWritten)
{
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	if (vos_dev_write(vnHandle, data, numBytesToWrite, numBytesWritten) == USBHOSTFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232Read(VN_HANDLE vnHandle, unsigned char *data, unsigned short numBytesToRead, unsigned short *numBytesRead)
{
	VN_STATUS ret_val = (VN_STATUS) VINCO_USBHOSTFT232_UNSUCCESSFUL;

	if (vos_dev_read(vnHandle, data, numBytesToRead, numBytesRead) == USBHOSTFT232_OK)
	{
		ret_val = (VN_STATUS) VINCO_USBHOSTFT232_OK;
	}

	return ret_val;
}

VN_STATUS VN_USBHostFT232Close(VN_HANDLE vnHandle)
{
	common_ioctl_cb_t ft232_iocb;

	ft232_iocb.ioctl_code = VOS_IOCTL_USBHOSTFT232_DETACH;
	vos_dev_ioctl(vnHandle, &ft232_iocb);

	vos_dev_close(vnHandle);

	return (VN_STATUS) VINCO_USBHOSTFT232_OK;
}
