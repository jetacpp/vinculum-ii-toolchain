/*
** Vinco_USBH.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
**
** Source file containing the implementation of the USB Host library APIs.
**
** Author: FTDI
** Project: Vinco Library
** Module: Vinco USB Host
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#include "vos.h"
#include "Vinco_USBH.h"

// struct instance to contain the function pointers
// USBHost_t USBHost;
VOS_HANDLE hUsbHost = 0;
uint8 vincoHostDeviceNumber;

// To enable PWREN
#define VII_GPIO_CNTRL_PORTB_1 0x182
port vII_gpio_cntrl_portb_1 @ VII_GPIO_CNTRL_PORTB_1;

/*
** Function: fn_usbhost_init
** Description: Initialize the USB host
** Parameters: ifCnt - number of interfaces (both USB hosts combined)
**             epCnt - number of endpoints (excluding control endpoints) expected
**             xferCnt - number of concurrent transaction expected
**			   isoxferCnt - number of concurrent isochronous transactions expected
** Returns:	void
** Requirements:
** Comments:
*/
void fn_usbhost_init(uint8 deviceNumber, uint8 ifCnt, uint8 epCnt, uint8 xferCnt, uint8 isoxferCnt)
{
	usbhost_context_t usb_ctx;
	vincoHostDeviceNumber = deviceNumber;
	usb_ctx.if_count = ifCnt;
	usb_ctx.ep_count = epCnt;
	usb_ctx.xfer_count = xferCnt;
	usb_ctx.iso_xfer_count = isoxferCnt;

	usbhost_init(USB_HOST_1, vincoHostDeviceNumber, &usb_ctx);

	vos_iomux_define_output(41, IOMUX_OUT_GPIO_PORT_B_6); // PWREN#, mapped to port B pin 6
	vII_gpio_cntrl_portb_1 .6 = 1;
}

/*
** Function: fn_open_host_dev
** Description: Open the host device
** Parameters: None
** Returns:	void
** Requirements:
** Comments:
*/
VOS_HANDLE fn_open_host_dev()
{
	hUsbHost = vos_dev_open(vincoHostDeviceNumber);

	return hUsbHost;
}

/*
** Function: fn_close_host_dev
** Description: Close the host device
** Parameters: None
** Returns:	void
** Requirements:
** Comments:
*/
void fn_close_host_dev(void)
{
	if (hUsbHost)
		vos_dev_close(hUsbHost);
}

/*
** Function: fn_hc_read
** Description: Read the data
** Parameters: xfer - transfer packet
**             num_bytes_to_read - number of bytes to read
**             num_bytes_read - points to the where the number of bytes
**                              read will be stored. This can be set to NULL
**                              if not needed.
** Returns: USBHOST_OK - success, USBHOST_ERROR - failure
** Requirements:
** Comments:
*/
uint8 fn_hc_read(uint8 *xfer, uint16 num_bytes_to_read, uint16 *num_bytes_read)
{
	int8 status = USBHOST_ERROR;

	if (xfer != NULL && num_bytes_to_read > 0)
	{
		status = vos_dev_read(hUsbHost, xfer, num_bytes_to_read, num_bytes_read);
	}

	return status;
}

/*
** Function: fn_hc_write
** Description: Writes the data
** Parameters: xfer - transfer packet
**             num_bytes_to_write - number of bytes to write
**             num_bytes_to_write - points to the where the number of bytes
**                              written will be stored. This can be set to NULL
**                              if not needed.
** Returns: USBHOST_OK - success, USBHOST_ERROR - failure
** Requirements:
** Comments:
*/
uint8 fn_hc_write(uint8 *xfer, uint16 num_bytes_to_write, uint16 *num_bytes_write)
{
	int8 status = USBHOST_ERROR;

	if (xfer != NULL && num_bytes_to_write > 0)
	{
		status = vos_dev_write(hUsbHost, xfer, num_bytes_to_write, num_bytes_write);
	}

	return status;
}

/*
** Function: fn_cmdctl
** Description: Sends a control request to the usb host device
** Parameters: hc_iocb - control request
** Returns:	USBHOST_OK - success, USBHOST_ERROR - failure
** Requirements:
** Comments:
*/
uint8 fn_cmdctl(usbhost_ioctl_cb_t *hc_iocb)
{
//sriram	usbhost_port_context_t *context = NULL;

	if (hc_iocb == NULL)
		return USBHOST_ERROR;

	return vos_dev_ioctl(hUsbHost, hc_iocb);
}

/*
** Function: fn_setup
** Description: Setup a transfer request
** Parameters: e - Endpoint handle
**             req - device request
**             data - setup data
** Returns:	USBHOST_OK - success, USBHOST_ERROR - failure
** Requirements:
** Comments:
*/
uint8 fn_setup(usbhost_ep_handle *e, usb_deviceRequest_t *req, uint8 *setup_data)
{
	int8 status = USBHOST_ERROR;
	usbhost_ioctl_cb_t hc_iocb;

	hc_iocb.ioctl_code = VOS_IOCTL_USBHOST_DEVICE_SETUP_TRANSFER;
	hc_iocb.handle.ep = e;
	hc_iocb.set = &req;
	hc_iocb.get = setup_data;

	status = vos_dev_ioctl(hUsbHost, hc_iocb);

	return status;
}

/*
** Function: usbh_init_fnptrs
** Description: Initialize the function pointers
** Parameters: USBHost - instance of the struct with function pointers
** Returns:	void
** Requirements:
** Comments:
*/
void usbh_init_fnptrs(USBHost_t *USBHost)
{
	USBHost->usbhost_init = &fn_usbhost_init;
	USBHost->open_host_dev = &fn_open_host_dev;
	USBHost->close_host_dev = &fn_close_host_dev;
	USBHost->read = &fn_hc_read;
	USBHost->write = &fn_hc_write;
	USBHost->setup = &fn_setup;
	USBHost->cmdctl = &fn_cmdctl;
}

