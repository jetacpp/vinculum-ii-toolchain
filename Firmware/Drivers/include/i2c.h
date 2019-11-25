/*
** i2c.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
**  File containning I2C specific declarations
**
** Author: FTDI
** Project: Vinculum II I2C Driver
** Module: Vinculum II I2C Library
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
**
**	@Note: The I2C driver supports only 7-bit device addressing mode.
*/

#ifndef __I2C_H__
#define __I2C_H__

#define I2C_VERSION_STRING "2.0.2"

/*I2C return codes*/
#define I2C_SUCCESS				0
#define I2C_ERROR				1
#define I2C_INVALID_ADDRESS		2
#define I2C_DEVICE_NACK			3



/*read from the current address,some devices
  may not support this options, check the device for this option
*/
#define I2C_OPTIONS_READ_SEQUENTIAL			1
/*read from the given address, default settings*/
#define I2C_OPTIONS_READ_ADDRESS			0


/*i2c ioctls */
/* set the options to read the next address or the supplied address */
#define VOS_IOCTL_I2C_SET_OPTIONS			0x01
/* set the slave device address */
#define VOS_IOCTL_I2C_SET_DEVICE_ADDRESS	0x02

/*IOTCL to set the read and address, the VOS_IOCTL_I2C_SET_OPTIONS will
  take precedance over this setting */
#define VOS_IOCTL_I2C_SET_RDWR_ADDRESS		0x03



/*i2c device operation context*/
typedef struct _i2c_ioctl_cb_t
{
	uint8	ioctl_code; /* ioctl code*/

	uint8 	data;		/* ioctl data, its used for options and
						  set the device address*/
}i2c_ioctl_cb_t;

/*I2C port numbers*/
#define I2C_PORT_A		GPIO_PORT_A
#define I2C_PORT_B		GPIO_PORT_B
#define I2C_PORT_C		GPIO_PORT_C
#define I2C_PORT_D		GPIO_PORT_D
#define I2C_PORT_E		GPIO_PORT_E

/*i2c port setting structure*/
typedef struct _i2c_port_t
{
     uint8  clkPort;	/* specify the port used for I2C clock*/
	 uint8  clkPortNo;	/* specify the zero index pin number of the clock
							 i.e for 0 for pin 1*/
	 uint8  dataPort;	/* port used for I2C data */
	 uint8  dataPortNo;	/*specify the zero index pin number of the data line */
}i2c_port_t;


/*!
  @fn	i2c_device_init
	function initialize the I2C bus to its initial state,i.e. data high, clock low

  DeviceNum:	device number
  stI2CPort: specifies the ports and port pins used for
			   I2C clock and data.

	returns:
		I2C_SUCCESS: everything good,else
		I2C_ERROR.
*/

uint8 i2c_device_init(uint8 DeviceNum, i2c_port_t *stI2CPort);
#endif
