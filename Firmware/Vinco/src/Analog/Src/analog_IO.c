/*
** analog_IO.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Analog I/O Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 – initial version
*/

#include "analog_IO.h"
#include "vos.h"
#include "ADC_MCP3008.h"
#include "pwm.h"
#include "SPIMaster.h"

uint8 init = 0;
VOS_HANDLE hPwm = NULL;
VOS_HANDLE hSPIm = NULL;
VOS_HANDLE hAdc = NULL;
uint8 pwmDeviceNumber;
uint8 adcDeviceNumber;

void analog_init(uint8 pwmDevNum, uint8 adcDevNum)
{
	/* Set all pins that are connected to the ADC inputs as input pins */
	vos_iomux_define_input(43, IOMUX_IN_GPIO_PORT_B_4);
	vos_iomux_define_input(44, IOMUX_IN_UART_DSR_N);
	vos_iomux_define_input(45, IOMUX_IN_UART_DCD);
	vos_iomux_define_input(46, IOMUX_IN_UART_RI);
	vos_iomux_define_input(47, IOMUX_IN_GPIO_PORT_C_0);
	vos_iomux_define_input(48, IOMUX_IN_GPIO_PORT_B_5);
	vos_iomux_define_input(49, IOMUX_IN_GPIO_PORT_B_6);
	vos_iomux_define_input(50, IOMUX_IN_GPIO_PORT_B_7);
	pwmDeviceNumber = pwmDevNum;
	adcDeviceNumber = adcDevNum;
	pwm_init(pwmDeviceNumber);
	adc_mcp3008_init(adcDeviceNumber);
}

void analog_attach_spi_master_handle(VOS_HANDLE spi_master_handle)
{
	hSPIm = spi_master_handle;
}

/*
** analogRead
**
** Read the analog value coming into an analog pin
**
** Parameters:	pin: pin name/number (A0 to A7)
**
** Returns:	Analog value, between 0 and 1023
** Comments:
**
*/
uint16 analogRead(uint8 pin)
{
	adc_mcp3008_ioctl_cb_t adc_iocb;
	adc_mcp3008_ioctl_cb_attach_t adc_attach_info;
	common_ioctl_cb_t spim_iocb;
	uint16 ADC_Value;

	/* Set pins for SPI Master */
	vos_iomux_define_output(19, IOMUX_OUT_SPI_MASTER_CLK);
	vos_iomux_define_output(20, IOMUX_OUT_SPI_MASTER_MOSI);
	vos_iomux_define_input(22, IOMUX_IN_SPI_MASTER_MISO);
	vos_iomux_define_output(61, IOMUX_OUT_SPI_MASTER_CS_1);

	/* Open ADC driver */
	hAdc = vos_dev_open(adcDeviceNumber);

	/* Attach ADC driver to SPI master */
	adc_iocb.ioctl_code = VOS_IOCTL_ADC_MCP3008_ATTACH;
	adc_attach_info.spi_master_handle = hSPIm;
	adc_attach_info.chip_select_identifier = ADC_MCP3008_CHIP_SELECT_1;
	adc_iocb.attach_info = &adc_attach_info;
	vos_dev_ioctl(hAdc, &adc_iocb);

	/* Read channel 0 of the ADC in single-ended mode */
	adc_iocb.ioctl_code = VOS_IOCTL_ADC_MCP3008_READ_CHANNEL;
	adc_iocb.mode = ADC_MCP3008_MODE_SINGLE_ENDED;

	switch (pin)
	{
	case A0:
		adc_iocb.channel = 0;
		break;

	case A1:
		adc_iocb.channel = 1;
		break;

	case A2:
		adc_iocb.channel = 2;
		break;

	case A3:
		adc_iocb.channel = 3;
		break;

	case A4:
		adc_iocb.channel = 4;
		break;

	case A5:
		adc_iocb.channel = 5;
		break;

	case A6:
		adc_iocb.channel = 6;
		break;

	case A7:
		adc_iocb.channel = 7;
		break;

	default:
	}

	vos_dev_ioctl(hAdc, &adc_iocb);

	/* The 10-bit ADC value will be returned in the value member of the IOCTL control block */
	ADC_Value = adc_iocb.value;

	/* Detach ADC driver from SPI master */
	adc_iocb.ioctl_code = VOS_IOCTL_ADC_MCP3008_DETACH;
	vos_dev_ioctl(hAdc, &adc_iocb);

	vos_dev_close(hAdc);

	return ADC_Value;
}

/*
** analogWrite
**
** Write an analog value into an analog pin
**
** Parameters:	pin: pin name/number (A0 to A7)
**				value: between 0 and 255
** Returns:	None
** Comments: Only pins 4, 5, 6, 9, 10, 11, 12, 13 can be used for PWM output
**
*/
void analogWrite(uint8 pin, uint8 value)
{
	pwm_ioctl_cb_t pwm_iocb;

	if (!init)
	{
		init = 1;

		hPwm = vos_dev_open(pwmDeviceNumber);

		/* Set counter prescaler value */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_PRESCALER_VALUE;
		pwm_iocb.count.prescaler = 192;
		vos_dev_ioctl(hPwm, &pwm_iocb);

		/* Set counter value - cycle complete when internal counter reaches this value */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COUNTER_VALUE;
		pwm_iocb.count.value = 255;
		vos_dev_ioctl(hPwm, &pwm_iocb);

		/* Set mode to continuous */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_NUMBER_OF_CYCLES;
		pwm_iocb.output.mode = 0;
		vos_dev_ioctl(hPwm, &pwm_iocb);

		/* Set initial state - all PWM outputs will be low (0) initially */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_INITIAL_STATE;
		pwm_iocb.output.init_state_mask = 0;
		vos_dev_ioctl(hPwm, &pwm_iocb);

		/* Disable interrupt */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_DISABLE_INTERRUPT;
		vos_dev_ioctl(hPwm, &pwm_iocb);

		/* Enable output */
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_ENABLE_OUTPUT;
		vos_dev_ioctl(hPwm, &pwm_iocb);
	}

	/* Configure IOMux to map the pins to signals */
	switch (pin)
	{
	case 4:
		vos_iomux_define_output(57, IOMUX_OUT_PWM_0);
		break;

	case 5:
		vos_iomux_define_output(58, IOMUX_OUT_PWM_1);
		break;

	case 6:
		vos_iomux_define_output(59, IOMUX_OUT_PWM_2);
		break;

	case 9:
		vos_iomux_define_output(18, IOMUX_OUT_PWM_3);
		break;

	case 10:
		vos_iomux_define_output(23, IOMUX_OUT_PWM_7);
		break;

	case 11:
		vos_iomux_define_output(20, IOMUX_OUT_PWM_5);
		break;

	case 12:
		vos_iomux_define_output(22, IOMUX_OUT_PWM_6);
		break;

	case 13:
		vos_iomux_define_output(19, IOMUX_OUT_PWM_4);
		break;

	default:
	}

	/* Set comparator 0 value - toggle output at "value" */

	switch (pin)
	{
	case 4:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_0;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 5:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_1;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 6:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_2;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 9:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_3;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 10:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_4;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 11:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_5;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 12:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_6;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 13:
		pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_COMPARATOR_VALUE;
		pwm_iocb.identifier.comparator_number = COMPARATOR_7;
		pwm_iocb.comparator.value = 255 - value;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;
	}

	/* Enable comparators 0 and 1 */
	/* This will cause PWM output to toggle on comparators 0 and 1 */
	pwm_iocb.ioctl_code = VOS_IOCTL_PWM_SET_OUTPUT_TOGGLE_ENABLES;

	switch (pin)
	{
	case 4:
		pwm_iocb.identifier.pwm_number = PWM_0;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_0;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 5:
		pwm_iocb.identifier.pwm_number = PWM_1;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_1;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 6:
		pwm_iocb.identifier.pwm_number = PWM_2;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_2;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 9:
		pwm_iocb.identifier.pwm_number = PWM_3;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_3;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 10:
		pwm_iocb.identifier.pwm_number = PWM_7;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_4;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 11:
		pwm_iocb.identifier.pwm_number = PWM_5;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_5;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 12:
		pwm_iocb.identifier.pwm_number = PWM_6;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_6;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	case 13:
		pwm_iocb.identifier.pwm_number = PWM_4;
		pwm_iocb.output.enable_mask = MASK_COMPARATOR_7;
		vos_dev_ioctl(hPwm, &pwm_iocb);
		break;

	default:
	}

	pwm_iocb.ioctl_code = VOS_IOCTL_PWM_RESTORE_INITIAL_STATE;
	pwm_iocb.output.restore_state_mask = (MASK_PWM_0 | MASK_PWM_1 | MASK_PWM_2 |
										  MASK_PWM_3 | MASK_PWM_4 | MASK_PWM_5 |
										  MASK_PWM_6 | MASK_PWM_7);
	vos_dev_ioctl(hPwm, &pwm_iocb);
	return;
}

