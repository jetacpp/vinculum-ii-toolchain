/*
** digital_macros.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Digital I/O Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 – initial version
*/

#ifndef _DIGITAL_MACROS_H_
#define _DIGITAL_MACROS_H_

#include "vos.h"

/* Control */
#define BIT_GPIO_EN	   1
#define MASK_GPIO_EN   (1 << 1)
#define BIT_INT_4_IEN  4               /* Interrupt enable bit for int_4 */
#define MASK_INT_4_IEN (1 << 4)        /* Interrupt enable bit for int_4 */

/* Vinculum II port names */
#define PA			   1
#define PB			   2
#define PC			   3
#define PD			   4
#define PE			   5

/* Definitions for invalid usage of pins */
#define NOT_A_PORT	   0
#define NOT_A_PIN	   0
#define NOT_A_SIGNAL   127

extern const uint8 Vinco_To_Vinculum_II[];
extern const uint8 digital_pin_to_bit_mask[];
extern const uint8 digital_pin_to_port[];
extern const uint8 digital_pin_to_input_signal[];
extern const uint8 digital_pin_to_output_signal[];

/* Macro for validating pins, modes and values */
#define invalidPin(pin)			   (((pin) < (0)) || ((pin) == (14)) || ((pin) == (15)) || ((pin) > (33)))
#define invalidMode(mode)		   (((mode) != (INPUT)) && ((mode) != (OUTPUT)))
#define invalidValue(value)		   (((value) != (HIGH)) && ((value) != (LOW)))

/* Macros for mapping a pin number to a port, getting the corresponding bit mask and
** getting registers which are associated to that port */
#define VincoPinToVinculumIIPin(P) Vinco_To_Vinculum_II[P]
#define digitalPinToBitMask(P)	   digital_pin_to_bit_mask[P]
#define ioMuxDefineInput(P, S)	   vos_iomux_define_input(P, digital_pin_to_input_signal[S])
#define ioMuxDefineOutput(P, S)	   vos_iomux_define_output(P, digital_pin_to_output_signal[S])
#define digitalPinToPort(P)		   digital_pin_to_port[P]

/* Port registers */
#define VII_GPIO_SYS_CNTRL_1   0x180   /* GPIO Control Register */
#define VII_GPIO_CNTRL_PORTA_1 0x181
#define VII_GPIO_CNTRL_PORTB_1 0x182
#define VII_GPIO_CNTRL_PORTC_1 0x183
#define VII_GPIO_CNTRL_PORTD_1 0x184
#define VII_GPIO_CNTRL_PORTE_1 0x185
#define VII_GPIO_DATA_TX_PA_1  0x186
#define VII_GPIO_DATA_TX_PB_1  0x187
#define VII_GPIO_DATA_TX_PC_1  0x188
#define VII_GPIO_DATA_TX_PD_1  0x189
#define VII_GPIO_DATA_TX_PE_1  0x18a
#define VII_GPIO_DATA_RX_PA_1  0x18b
#define VII_GPIO_DATA_RX_PB_1  0x18c
#define VII_GPIO_DATA_RX_PC_1  0x18d
#define VII_GPIO_DATA_RX_PD_1  0x18e
#define VII_GPIO_DATA_RX_PE_1  0x18f
#define VII_GPIO_INT_REG_EN_1  0x19a   /* GPIO Interrupt Register */

port vII_gpio_sys_cntrl_1 @ VII_GPIO_SYS_CNTRL_1;
port vII_gpio_cntrl_porta_1 @ VII_GPIO_CNTRL_PORTA_1;
port vII_gpio_cntrl_portb_1 @ VII_GPIO_CNTRL_PORTB_1;
port vII_gpio_cntrl_portc_1 @ VII_GPIO_CNTRL_PORTC_1;
port vII_gpio_cntrl_portd_1 @ VII_GPIO_CNTRL_PORTD_1;
port vII_gpio_cntrl_porte_1 @ VII_GPIO_CNTRL_PORTE_1;
port vII_gpio_data_tx_pa_1 @ VII_GPIO_DATA_TX_PA_1;
port vII_gpio_data_tx_pb_1 @ VII_GPIO_DATA_TX_PB_1;
port vII_gpio_data_tx_pc_1 @ VII_GPIO_DATA_TX_PC_1;
port vII_gpio_data_tx_pd_1 @ VII_GPIO_DATA_TX_PD_1;
port vII_gpio_data_tx_pe_1 @ VII_GPIO_DATA_TX_PE_1;
port vII_gpio_data_rx_pa_1 @ VII_GPIO_DATA_RX_PA_1;
port vII_gpio_data_rx_pb_1 @ VII_GPIO_DATA_RX_PB_1;
port vII_gpio_data_rx_pc_1 @ VII_GPIO_DATA_RX_PC_1;
port vII_gpio_data_rx_pd_1 @ VII_GPIO_DATA_RX_PD_1;
port vII_gpio_data_rx_pe_1 @ VII_GPIO_DATA_RX_PE_1;
port vII_gpio_int_reg_en_1 @ VII_GPIO_INT_REG_EN_1;

#endif                                 /* _DIGITAL_MACROS_H_ */
