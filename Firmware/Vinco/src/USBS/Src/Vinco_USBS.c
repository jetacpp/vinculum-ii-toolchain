/*
** Vinco_USBS.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** C Source file for Vinco USB Slave Library
** Main module
**
** Author: FTDI
** Project: Vinco
** Module: Vinco USB Slave Library
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#include "Vinco_USBS.h"
#include "Vinco.h"

/******************************************************************************/
/*								Global variables							  */
/******************************************************************************/
VOS_HANDLE hUSBS = NULL;

/******************************************************************************/
/*								   Functions							      */
/******************************************************************************/
/* USB Slave structure's functions */
uint8 usbslave_lib_init(void);
uint8 usbslave_getState(void);
uint8 usbslave_setConfiguration(uint8 configValue);
uint8 usbslave_getConfiguration(void);
uint8 usbslave_setAddress(uint8 addr);
uint8 usbslave_setupTransfer(usbslave_ep_handle_t epHandle, uint8 *buffer, int16 size, int16 *bytesTransferred);
uint8 usbslave_waitSetupRcvd(uint8 *buffer, int16 size, int16 *bytesTransferred);
uint8 usbslave_initEp(uint8 ep, usbslave_ep_handle_t *epHandle, uint8 epType);
uint8 usbslave_setEpMaxPcktSize(usbslave_ep_handle_t epHandle, uint32 maxPcktSize);
uint8 usbslave_transfer(usbslave_ep_handle_t epHandle, uint8 *buffer, int16 size, int16 *bytesTransferred);
uint8 usbslave_disconnect(void);
uint8 usbslave_stallEp(uint8 ep);
uint8 usbslave_clearEp(uint8 ep);
int8 usbslave_epState(uint8 ep);
uint8 usbslave_waitOnUSBSuspend(void);
uint8 usbslave_waitOnUSBResume(void);
uint8 usbslave_issueRemoteWakeup(void);
uint8 usbslave_enableInterrupts(void);
uint8 usbslave_disableInterrupts(void);
uint8 usbslave_setLowSpeed(void);

/*
** Function: usbslave_struct_init()
** Description: To provide Arduino-like APIs, a structure conataning pointers to USB Slave Library functions
**				needs to be defined. This function initialize those functions pointers.
** Parameters: USBSlave: the USB Slave structure that contains the function pointers
** Returns:
** Requirements: This function has to be called (in main.c) before any of the USB Slave Library APIs is used
** Comments:
*/
void usbslave_struct_init(stUSBSlave_t *USBSlave)
{
	USBSlave->init = &usbslave_lib_init;
	USBSlave->getState = &usbslave_getState;
	USBSlave->setConfiguration = &usbslave_setConfiguration;
	USBSlave->getConfiguration = &usbslave_getConfiguration;
	USBSlave->setAddress = &usbslave_setAddress;
	USBSlave->setupTransfer = &usbslave_setupTransfer;
	USBSlave->waitSetupRcvd = &usbslave_waitSetupRcvd;
	USBSlave->initEp = &usbslave_initEp;
	USBSlave->setEpMaxPcktSize = &usbslave_setEpMaxPcktSize;
	USBSlave->transfer = &usbslave_transfer;
	USBSlave->disconnect = &usbslave_disconnect;
	USBSlave->stallEp = &usbslave_stallEp;
	USBSlave->clearEp = &usbslave_clearEp;
	USBSlave->epState = &usbslave_epState;
	USBSlave->disableInterrupts = &usbslave_disableInterrupts;
	USBSlave->enableInterrupts = &usbslave_enableInterrupts;
	USBSlave->waitOnUSBSuspend = &usbslave_waitOnUSBSuspend;
	USBSlave->waitOnUSBResume = &usbslave_waitOnUSBResume;
	USBSlave->issueRemoteWakeup = &usbslave_issueRemoteWakeup;
	USBSlave->setLowSpeed = &usbslave_setLowSpeed;

	usbslave_init(0, USBSLAVE);
}

/*
** Function: usbslave_init()
** Description: Initialization function
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_lib_init(void)
{
	hUSBS = vos_dev_open(USBSLAVE);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_getState()
** Description: Returns the current state of the USB Slave hardware interface
** Parameters:
** Returns:	The current status. Possible values and their respective meanings are:
            usbsStateNotAttached	Not attached to a host controller.
            usbsStateAttached		Attached to a host controller which is not configured.
            usbsStatePowered		Attached to a host controller which is configured. Configuration of device can commence.
            usbsStateDefault		Default mode where configuration sequence has performed a device reset operation.
            usbsStateAddress		Address has been assigned by host.
            usbsStateConfigured		Device is fully configured by host.
            usbsStateSuspended		Device has been suspended by host.
** Requirements:
** Comments:
*/
uint8 usbslave_getState(void)
{
	usbslave_ioctl_cb_t iocb;
	uint8 state;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_STATE;
	iocb.get = &state;
	vos_dev_ioctl(hUSBS, &iocb);

	return state;
}

/*
** Function: usbslave_setConfiguration()
** Description: Set the USB device configuration. This API should be used when processing the USB standard device request, SET_CONFIGURATION.
** Parameters: configValue: A configuration value
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_setConfiguration(uint8 configValue)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_SET_CONFIGURATION;
	iocb.set = (void *) configValue;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_getConfiguration()
** Description: Get the USB device configuration. This API should be used when processing the USB standard device request, GET_CONFIGURATION.
** Parameters:
** Returns:	The configuration value
** Requirements:
** Comments:
*/
uint8 usbslave_getConfiguration(void)
{
	usbslave_ioctl_cb_t iocb;
	uint8 configValue;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_CONFIGURATION;
	iocb.get = &configValue;
	vos_dev_ioctl(hUSBS, &iocb);

	return configValue;
}

/*
** Function: usbslave_setAddress()
** Description: Sets the USB address for the device
                The USB host assigns the device address during enumeration and this API is used to set the USB slave port hardware to respond to that address.
                This API should be used when processing the USB standard device request, SET_ADDRESS.
** Parameters: addr: A device address
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_setAddress(uint8 addr)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_SET_ADDRESS;
	iocb.set = (void *) addr;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_setupTransfer()
** Description: Performs a data phase or ACK phase for a SETUP transaction
** Parameters: epHandle: The handle of the endpoint used for the SETUP transaction.
               buffer: Pointer to the buffer containing data for the transfer
               size: The size of the buffer containing data for the transfer
               bytes_transferred: The number of bytes that are actually transferred
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_setupTransfer(usbslave_ep_handle_t epHandle, uint8 *buffer, int16 size, int16 *bytesTransferred)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_SETUP_TRANSFER;
	iocb.handle = epHandle;
	iocb.request.setup_or_bulk_transfer.buffer = buffer;
	iocb.request.setup_or_bulk_transfer.size = size;
	vos_dev_ioctl(hUSBS, &iocb);

	*bytesTransferred = iocb.request.setup_or_bulk_transfer.bytes_transferred;

	return USBSLAVE_OK;
}

/*
** Function: usbslave_waitSetupRcvd()
** Description: Receives a SETUP packet. This call blocks until a SETUP packet is received from the host.
** Parameters: buffer: Pointer to the buffer to receive the SETUP packet
               size: The size of the buffer
               bytes_transferred: The number of bytes that are actually transferred
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_waitSetupRcvd(uint8 *buffer, int16 size, int16 *bytesTransferred)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_WAIT_SETUP_RCVD;
	iocb.request.setup_or_bulk_transfer.buffer = buffer;
	iocb.request.setup_or_bulk_transfer.size = size;
	vos_dev_ioctl(hUSBS, &iocb);

	*bytesTransferred = iocb.request.setup_or_bulk_transfer.bytes_transferred;

	return USBSLAVE_OK;
}

/*
** Function: usbslave_initEp()
** Description: Associate an endpoint address with a non-control endpoint
** Parameters: ep: An endpoint address.  Valid endpoint addresses are in the range 0-7.
               epHandle; The handle of the endpoint which is being initialized
               epType: The type of endpoint to be associated to the endpoint address. Possible values:
                    USBSLAVE_BULK_IN_ENDPOINT
                    USBSLAVE_BULK_OUT_ENDPOINT
                    USBSLAVE_INT_IN_ENDPOINT
                    USBSLAVE_INT_OUT_ENDPOINT
                    USBSLAVE_ISO_IN_ENDPOINT
                    USBSLAVE_ISO_OUT_ENDPOINT
                    USBSLAVE_CONTROL_IN_ENDPOINT
                    USBSLAVE_CONTROL_OUT_ENDPOINT
** Returns:	USBSLAVE_OK / USBSLAVE_INVALID_PARAMETER / USBSLAVE_FATAL_ERROR
** Requirements:
** Comments:
*/
uint8 usbslave_initEp(uint8 ep, usbslave_ep_handle_t *epHandle, uint8 epType)
{
	usbslave_ioctl_cb_t iocb;

	if (epHandle == NULL)
	{
		return USBSLAVE_FATAL_ERROR;
	}

	switch (epType)
	{
	case USBSLAVE_CONTROL_IN_ENDPOINT:

		if (ep != 0)
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_CONTROL_ENDPOINT_HANDLE;
		iocb.ep = USBSLAVE_CONTROL_IN;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_CONTROL_OUT_ENDPOINT:

		if (ep != 0)
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_CONTROL_ENDPOINT_HANDLE;
		iocb.ep = USBSLAVE_CONTROL_OUT;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_BULK_IN_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_BULK_IN_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_INT_IN_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_INT_IN_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_BULK_OUT_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_BULK_OUT_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_INT_OUT_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_INT_OUT_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_ISO_IN_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_ISO_IN_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;

	case USBSLAVE_ISO_OUT_ENDPOINT:

		if ((ep < 1) || (ep > 7))
		{
			return USBSLAVE_INVALID_PARAMETER;
		}

		iocb.ioctl_code = VOS_IOCTL_USBSLAVE_GET_ISO_OUT_ENDPOINT_HANDLE;
		iocb.ep = ep;
		iocb.get = epHandle;
		vos_dev_ioctl(hUSBS, &iocb);
		break;
	}

	return USBSLAVE_OK;
}

/*
** Function: usbslave_setEpMaxPcktSize()
** Description: Set the max packet size for the specified endpoint.
                The endpoint max packet size can be set to 8, 16, 32 or 64 bytes for a bulk IN, bulk OUT, interrupt IN or interrupt OUT endpoint.
                Isochronous endpoints do not use this API.
** Parameters: epHandle: The handle of the endpoint whose max packet size is being set. It has to be initialized with initEp before.
               maxPcktSize: The maximum packet size for the specified endpoint. Possible values:
                    USBSLAVE_MAX_PACKET_SIZE_8
                    USBSLAVE_MAX_PACKET_SIZE_16
                    USBSLAVE_MAX_PACKET_SIZE_32
                    USBSLAVE_MAX_PACKET_SIZE_64
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_setEpMaxPcktSize(usbslave_ep_handle_t epHandle, uint32 maxPcktSize)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_SET_ENDPOINT_MAX_PACKET_SIZE;
	iocb.handle = epHandle;
	iocb.request.ep_max_packet_size = maxPcktSize;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_setEpMaxPcktSize()
** Description: Performs a transfer to a non-control endpoint.  This function works on both IN and OUT endpoints.
                When used on an OUT endpoint, this function blocks until data is received from the host.
                When used on an IN endpoint, this function blocks until data is sent to the host (in response to an IN request sent from the host).
** Parameters: epHandle: The handle of the endpoint on which data transfer is performed.
               buffer: Pointer to the buffer containing data for the transfer
               size: The size of the buffer containing data for the transfer
               bytes_transferred: The number of bytes that are actually transferred
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_transfer(usbslave_ep_handle_t epHandle, uint8 *buffer, int16 size, int16 *bytesTransferred)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_TRANSFER;
	iocb.handle = epHandle;
	iocb.request.setup_or_bulk_transfer.buffer = buffer;
	iocb.request.setup_or_bulk_transfer.size = size;
	vos_dev_ioctl(hUSBS, &iocb);

	*bytesTransferred = iocb.request.setup_or_bulk_transfer.bytes_transferred;

	return USBSLAVE_OK;
}

/*
** Function: usbslave_setEpMaxPcktSize()
** Description: Sets the USB slave into an un-addressed state and resets the hardware needed to allow the device to be reconnected to a USB host at a later time.
                This function can also be used to force a disconnection from a USB host.
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_disconnect(void)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_DISCONNECT;
	iocb.set = (void *) 0;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_stallEp()
** Description: Force an endpoint to stall on the USB Slave device. An IN, OUT or control endpoint may be stalled.
                This may be used on the control endpoint when a device does not support a certain SETUP request or on other endpoints as required.
                If an endpoint it halted then it will return a STALL to a request from the host.
** Parameters: ep: The endpoint to be stalled
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_stallEp(uint8 ep)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_ENDPOINT_STALL;
	iocb.ep = ep;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_clearEp()
** Description: Remove a halt state on the USB Slave device.
                An IN, OUT or control endpoint may be stalled but only IN and OUT endpoints can be cleared by this function.
** Parameters: ep: The endpoint to be cleared
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_clearEp(uint8 ep)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_ENDPOINT_CLEAR;
	iocb.ep = ep;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_epState()
** Description: Returns the halt state of an endpoint on the USB Slave device.
                If an endpoint it halted then it will return a STALL to a request from the host.
** Parameters: ep: The endpoint to be checked
** Returns:	The return value is zero if the endpoint it not halted and non-zero if it is halted.
** Requirements:
** Comments:
*/
uint8 usbslave_epState(uint8 ep)
{
	usbslave_ioctl_cb_t iocb;
	uint8 state;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_ENDPOINT_STATE;
	iocb.ep = ep;
	iocb.get = &state;
	vos_dev_ioctl(hUSBS, &iocb);

	return state;
}

/*
** Function: usbslave_waitOnUSBSuspend()
** Description: This call blocks until a SUSPEND signal is received from the host.
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_waitOnUSBSuspend(void)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_WAIT_ON_USB_SUSPEND;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_waitOnUSBResume()
** Description: This call blocks until a RESUME signal is received from the host.
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_waitOnUSBResume(void)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_WAIT_ON_USB_RESUME;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_issueRemoteWakeup()
** Description: Issues a remote wakeup request to the host
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_issueRemoteWakeup(void)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_ISSUE_REMOTE_WAKEUP;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_enableInterrupts()
** Description: Enable Interrupt
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_enableInterrupts(void)
{
	vos_enable_interrupts(VOS_USB_0_DEV_INT_IEN);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_disableInterrupts()
** Description: Disable Interrupt
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_disableInterrupts(void)
{
	vos_disable_interrupts(VOS_USB_0_DEV_INT_IEN);

	return USBSLAVE_OK;
}

/*
** Function: usbslave_setLowSpeed()
** Description: Set the speed of the device to low speed. This function has to be called right after device initialization
** Parameters:
** Returns:	USBSLAVE_OK
** Requirements:
** Comments:
*/
uint8 usbslave_setLowSpeed(void)
{
	usbslave_ioctl_cb_t iocb;

	iocb.ioctl_code = VOS_IOCTL_USBSLAVE_SET_LOW_SPEED;
	vos_dev_ioctl(hUSBS, &iocb);

	return USBSLAVE_OK;
}

