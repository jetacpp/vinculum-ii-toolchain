/*
** ADC_MCP3008.h
**
** Copyright © 2010-2011 Future Technology Devices International Limited
**
** Header file for Vinculum II ADC_MCP3008 Driver
** Header File
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II Drivers
** Requires: VOS, SPI Master
** Comments: Compatible with the Microchip MCP3008 and MCP3004 analog/digital converters
**
** History:
**  1 – Initial version
**
*/

#ifndef _ADC_MCP3008_H_
#define _ADC_MCP3008_H_

#define ADC_MCP3008_VERSION_STRING "2.0.2"

// ADC_MCP3008 Initialisation Function
unsigned char adc_mcp3008_init(unsigned char devNum);

// ==============================================================================
//  ADC_MCP3008 Card IOCTLS
// ==============================================================================
#define     VOS_IOCTL_ADC_MCP3008_ATTACH	   0x01 // Attach SPI Master driver to ADC MCP3008 driver.
#define     VOS_IOCTL_ADC_MCP3008_DETACH	   0x02 // Detach SPI Master driver from ADC MCP3008 driver.
#define     VOS_IOCTL_ADC_MCP3008_READ_CHANNEL 0x03 // Read the specified ADC channel

// ADC Modes
#define     ADC_MCP3008_MODE_DIFFERENTIAL	   0x00
#define     ADC_MCP3008_MODE_SINGLE_ENDED	   0x80

// Chip select indentifiers for use in attch IOCTL
#define     ADC_MCP3008_CHIP_SELECT_0		   0x00 // ADC uses SPI Master slave select 0
#define     ADC_MCP3008_CHIP_SELECT_1		   0x01 // ADC uses SPI Master slave select 1

typedef struct _adc_mcp3008_ioctl_cb_attach_t
{
    VOS_HANDLE	  spi_master_handle;
    unsigned char chip_select_identifier;
} adc_mcp3008_ioctl_cb_attach_t;

typedef struct _adc_mcp3008_ioctl_cb_t
{
    unsigned char				  ioctl_code;
    adc_mcp3008_ioctl_cb_attach_t *attach_info;
    unsigned char				  channel;
    unsigned char				  mode;
    unsigned short				  value;
} adc_mcp3008_ioctl_cb_t;

// ==============================================================================
//  ADC_MCP3008 Return Codes
// ==============================================================================
enum ADC_MCP3008_STATUS {
    ADC_MCP3008_OK = 0x00,
    ADC_MCP3008_INVALID_PARAMETER,
    ADC_MCP3008_INVALID_IOCTL_CODE,
    ADC_MCP3008_ERROR,
    ADC_MCP3008_FATAL_ERROR = 0xFF
};

#endif                                 /*_ADC_MCP3008_H_*/
