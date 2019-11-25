/*
** mp3.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** MP3 Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 - initial version
*/

#include "vinco_mp3.h"
#include "MP3_VS1053.h"

VOS_HANDLE hMP3, hGpio;
#define VII_GPIO_CNTRL_PORTB_1 0x182
port vII_gpio_cntrl_portb_1 @ VII_GPIO_CNTRL_PORTB_1;

void mp3Begin(void);
void mp3SetVolume(uint8 leftVolume, uint8 rightVolume);
void mp3SetBass(uint8 amplitude, uint8 freqLimit);
void mp3SetTreble(uint8 amplitude, uint8 freqLimit);
uint16 mp3Send(uint8 *buffer, uint16 numBytesToWrite);
void mp3Sent(void);
void mp3Cancel(void);
void mp3SoftReset(void);
void mp3HardReset(void);

/*
** mp3_init_func_ptrs
**
** Initialize the function pointers of mp3_st structure
**
** Parameters: m - mp3_st instance
**
** Returns: void
** Requirements:
** Comments:
*/
void mp3_init_func_ptrs(mp3_st *m)
{
	m->begin = &mp3Begin;
	m->setVolume = &mp3SetVolume;
	m->setBass = &mp3SetBass;
	m->setTreble = &mp3SetTreble;
	m->send = &mp3Send;
	m->sent = &mp3Sent;
	m->cancel = &mp3Cancel;
	m->softReset = &mp3SoftReset;
	m->hardReset = &mp3HardReset;

	/* Additional steps that need to be done: */
	// Declare SPI pins
	vos_iomux_define_output(19, IOMUX_OUT_SPI_MASTER_CLK);
	vos_iomux_define_output(20, IOMUX_OUT_SPI_MASTER_MOSI);
	vos_iomux_define_input(22, IOMUX_IN_SPI_MASTER_MISO);
	vos_iomux_define_output(27, IOMUX_OUT_SPI_MASTER_CS_0);
	vos_iomux_define_output(24, IOMUX_OUT_SPI_MASTER_CS_1);

	// On Vinco, VS1053b's XRESET# pin is connected to VNC2's pin 24.
	// In order to reset the VS1053b, first set VNC2's pin 24 to output
	vos_iomux_define_output(25, IOMUX_OUT_GPIO_PORT_B_5);
	// On Vinco, VS1053b's DREQ pin is connected to VNC2's pin 25.
	// In order to read the pin, first set VNC2's pin 25 to input
	vos_iomux_define_input(26, IOMUX_IN_GPIO_PORT_B_6);

	// Set the direction register of GPIO port B, bit 5 as output (1), bit 6 as input (0)
	vII_gpio_cntrl_portb_1 &= 0xBF;
	vII_gpio_cntrl_portb_1 |= 0x20;

	return;
}

void mp3_attach_MP3_VS1053b_driver_handle(VOS_HANDLE hMP3Main)
{
	hMP3 = hMP3Main;

	return;
}

void mp3_attach_SPI_master_driver_handle(VOS_HANDLE hSpiMasterMain)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_ATTACH;
	mp3Cb.spi_master_handle = hSpiMasterMain;
	// Internally, attach GPIO information of XRESET and DREQ as well
	mp3Cb.XRESET_GPIO_port = PORT_B; // GPIO port used for XRESET pin
	mp3Cb.XRESET_GPIO_pin = 5; // GPIO pin used for XRESET pin
	mp3Cb.DREQ_GPIO_port = PORT_B; // GPIO port used for DREQ pin
	mp3Cb.DREQ_GPIO_pin = 6; // GPIO pin used for DREQ pin
	mp3Cb.SDI_CS_identifier = SPI_CHIP_SELECT_1;
	mp3Cb.SCI_CS_identifier = SPI_CHIP_SELECT_0;	
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3Begin(void)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_SETUP;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3SetVolume(uint8 leftVolume, uint8 rightVolume)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_SET_VOLUME;
	mp3Cb.set.volume.left = leftVolume;
	mp3Cb.set.volume.right = rightVolume;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3SetBass(uint8 amplitude, uint8 freqLimit)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_SET_BASS;
	mp3Cb.set.bass.amplitude = amplitude;
	mp3Cb.set.bass.freqLimit = freqLimit;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3SetTreble(uint8 amplitude, uint8 freqLimit)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_SET_TREBLE;
	mp3Cb.set.treble.amplitude = amplitude;
	mp3Cb.set.treble.freqLimit = freqLimit;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

uint16 mp3Send(uint8 *buffer, uint16 numBytesToWrite)
{
	uint16 numBytesWritten;

	vos_dev_write(hMP3, buffer, numBytesToWrite, &numBytesWritten);

	return numBytesWritten;
}

void mp3Sent(void)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_FILE_SENT;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3Cancel(void)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_PLAYBACK_CANCELED;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3SoftReset(void)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_SOFT_RESET;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}

void mp3HardReset(void)
{
	mp3_VS1053_ioctl_cb mp3Cb;

	mp3Cb.ioctl_code = VOS_IOCTL_MP3_VS1053_HARD_RESET;
	vos_dev_ioctl(hMP3, &mp3Cb);

	return;
}
