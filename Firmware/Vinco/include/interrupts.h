/*
** interrupts.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Interrupts Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 - initial version
*/

#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "vos.h"

#define NO_INTERRUPT		 -1
#define MAX_INTERRUPT_NUMBER 3
#define ALL_INTERRUPTS_FLAG	 VOS_UART_INT_IEN | VOS_USB_0_DEV_INT_IEN | VOS_USB_1_DEV_INT_IEN \
	| VOS_USB_0_HC_INT_IEN | VOS_USB_1_HC_INT_IEN | VOS_GPIO_INT_IEN \
	| VOS_SPI_MASTER_INT_IEN | VOS_SPI_0_SLAVE_INT_IEN | VOS_SPI_1_SLAVE_INT_IEN \
	| VOS_PWM_TOP_INT_IEN | VOS_FIFO_245_INT_IEN

/* Return values */
#define SUCCESSFUL			 0
#define INVALID_INT_NUM		 -1
#define INVALID_MODE		 -2

#define INTERRUPT_0			 0
#define INTERRUPT_1			 1
#define INTERRUPT_2			 2
#define INTERRUPT_3			 3

/* Possible mode values */
// To avoid conflict in digital IO LOW value
#ifndef LOW
	#define LOW 0                      /* to trigger the interrupt whenever the pin is low */
#endif
#define CHANGE	1                      /* to trigger the interrupt whenever the pin changes value */
#define RISING	2                      /* to trigger when the pin goes from low to high */
#define FALLING 3                      /* for when the pin goes from high to low */

/* Macros */
#define invalidIntMode(mode)		   ((mode != LOW) && (mode != CHANGE) && (mode != RISING) && (mode != FALLING))
#define invalidIntNumber(num)		   (num > 3 || num < 0)
#define pin_to_interrupt_num(num)	   interrupt_num_pin[num]
#define pin_to_portb_pin(num)		   port_b_pin[num]
#define pin_to_interrupt_mode_num(num) interrupt_num_mode[num]
#define pin_to_iomux_pin_config(num)   interrupt_gpio_port[num]
#define interrupt_num_to_gpio_pin(num) interrupt_pin[num]

typedef void (*fncptr)(void);

/* Status of the pin */
typedef enum
{
	STATE_GPIO,
	STATE_GPIO_INTERRUPT
} pin_state_t;

/* Interrupts APIs */
void interrupts(void);
void noInterrupts(void);
int attachInterrupt(uint8 intNum, fncptr isr, uint8 mode);
int detachInterrupt(uint8 intNum);

#endif                                 /* _INTERRUPT_H */

