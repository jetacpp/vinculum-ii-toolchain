/*
** interrupts.c
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

#include "interrupts.h"
#include "vos.h"
#include "digital_macros.h"
#include "IOMux.h"
#include "GPIO.h"

// extern fncptr thread_list[];
#define SIZEOF_iIsr 512

void interrupt_0(void);
void interrupt_1(void);
void interrupt_2(void);
void interrupt_3(void);
VOS_HANDLE hGpioB = NULL;
gpio_context_t gpioCtx;
gpio_ioctl_cb_t gpio_iocb;
fncptr thread_isr_0 = NULL;
fncptr thread_isr_1 = NULL;
fncptr thread_isr_2 = NULL;
fncptr thread_isr_3 = NULL;

const uint8 interrupt_num_pin[] =
{
	VOS_IOCTL_GPIO_SET_PROG_INT0_PIN,
	VOS_IOCTL_GPIO_SET_PROG_INT1_PIN,
	VOS_IOCTL_GPIO_SET_PROG_INT2_PIN,
	VOS_IOCTL_GPIO_SET_PROG_INT3_PIN
};

const uint8 port_b_pin[] =
{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3
};

const uint8 interrupt_num_mode[] =
{
	VOS_IOCTL_GPIO_SET_PROG_INT0_MODE,
	VOS_IOCTL_GPIO_SET_PROG_INT1_MODE,
	VOS_IOCTL_GPIO_SET_PROG_INT2_MODE,
	VOS_IOCTL_GPIO_SET_PROG_INT3_MODE
};

const int interrupt_gpio_port[] =
{
	IOMUX_IN_GPIO_PORT_B_0,
	IOMUX_IN_GPIO_PORT_B_1,
	IOMUX_IN_GPIO_PORT_B_2,
	IOMUX_IN_GPIO_PORT_B_3,
};

/* Interrupt Modes */
const uint8 interrupt_mode[] =
{
	GPIO_INT_ON_LOW_STATE,
	GPIO_INT_ON_ANY_EDGE,
	GPIO_INT_ON_POS_EDGE,
	GPIO_INT_ON_NEG_EDGE
};

/* Determines the mode for each interrupt */
uint8 mode_registry[] =
{
	GPIO_INT_ON_LOW_STATE,
	GPIO_INT_ON_LOW_STATE,
	GPIO_INT_ON_LOW_STATE,
	GPIO_INT_ON_LOW_STATE
};

uint8 interrupt_pin[] =
{
	57,                                // B_0 /* J3_5 ** pin 4 ** is pin 57 of Vinculum II */
	58,                                // B_1 /* J3_6 ** pin 5 ** is pin 58 of Vinculum II */
	55,                                // B_2 /* J3_3 ** pin 2 ** is pin 55 of Vinculum II */
	56                                 // B_3 /* J3_4 ** pin 3 ** is pin 56 of Vinculum II */
};

/*
** interrupts
**
** Enables interrupts.
**
** Parameters:	None
**
** Returns:	void
**
**
*/
void interrupts(void)
{
	/* Setting the mask for port b as input */
	asm {OUTPORT vII_gpio_cntrl_portb_1 0x00}
	/* After setting the mask, then enable the interrupt flags. */
	vos_enable_interrupts(VOS_GPIO_INT_IEN);
}

/*
** noInterrupts
**
** Disables interrupts.
**
** Parameters:	None
**
** Returns:	void
**
**
*/
void noInterrupts(void)
{
	/* Setting the mask for port b as output */
	asm {OUTPORT vII_gpio_cntrl_portb_1 0xff}
	/* Disable all interrupts */
	vos_disable_interrupts(VOS_GPIO_INT_IEN);
}

/*
** attachInterrupt
**
** Specifies an external function to call when an interrupt occur on the
** specified pin.
**
** Parameters:	intNum - interrupt number (0-3)
**              isr: interrupt service routine to call
**              mode: trigger mode of the interrupt
**                    Possible values: LOW, CHANGE, RISING, FALLING
**
** Returns:	INVALID_INT_NUM - invalid interrupt number
**			INVALID_MODE - unknown mode
**			SUCCESSFUL - on success
**
** Comments: Possible mode values
**
*/
int attachInterrupt(uint8 intNum, fncptr isr, uint8 mode)
{
	gpio_ioctl_cb_t gpio_iocb;

	if (invalidIntNumber(intNum))
		return INVALID_INT_NUM;

	if (invalidIntMode(mode))
		return INVALID_MODE;

	/* Configure GPIO */
	vos_iomux_define_input(interrupt_num_to_gpio_pin(intNum), pin_to_iomux_pin_config(intNum));

	/* Configuring interrupt pin */
	gpio_iocb.ioctl_code = pin_to_interrupt_num(intNum);
	gpio_iocb.value = pin_to_portb_pin(intNum);
	vos_dev_ioctl(hGpioB, &gpio_iocb);

	/* Configuring the interrupt mode */
	gpio_iocb.ioctl_code = pin_to_interrupt_mode_num(intNum);
	gpio_iocb.value = interrupt_mode[mode];
	vos_dev_ioctl(hGpioB, &gpio_iocb);

	mode_registry[intNum] = interrupt_mode[mode];

	/* Attaching of interrupts */
	// TODO: do manual for now while CMP bug is not yet fix
	// thread_list[intNum] = isr;
	if (intNum == INTERRUPT_0)
		thread_isr_0 = isr;
	else if (intNum == INTERRUPT_1)
		thread_isr_1 = isr;
	else if (intNum == INTERRUPT_2)
		thread_isr_2 = isr;
	else if (intNum == INTERRUPT_3)
		thread_isr_3 = isr;
	else
	{
	}

	return SUCCESSFUL;
}

/*
** detachInterrupt
**
** Removing the interrupt routine attached on a specified pin.
**
** Parameters:	intNum - interrupt number (0-3)
**
** Returns:	INVALID_INT_NUM - invalid interrupt number
**			SUCCESSFUL - on success
**
** Comments: Possible mode values
**
*/
int detachInterrupt(uint8 intNum)
{
	if (invalidIntNumber(intNum))
		return INVALID_INT_NUM;

	/* Detaching of interrupts */
	// TODO: to uncomment later if array of function pointers bug is solved
	// thread_list[intNum] = NULL;
	if (intNum == INTERRUPT_0)
		thread_isr_0 = (fncptr) NULL;
	else if (intNum == INTERRUPT_1)
		thread_isr_1 = (fncptr) NULL;
	else if (intNum == INTERRUPT_2)
		thread_isr_2 = (fncptr) NULL;
	else if (intNum == INTERRUPT_3)
		thread_isr_3 = (fncptr) NULL;
	else
	{
	}

	return SUCCESSFUL;
}

void intpt_init(uint8 gpioDevNum)
{
	gpioCtx.port_identifier = GPIO_PORT_B;
	gpio_init(gpioDevNum, &gpioCtx);
	hGpioB = vos_dev_open(gpioDevNum);
}

void intpt_create_thread()
{
	vos_create_thread(31, SIZEOF_iIsr, &interrupt_0, 0);
	vos_create_thread(31, SIZEOF_iIsr, &interrupt_1, 0);
	vos_create_thread(31, SIZEOF_iIsr, &interrupt_2, 0);
	vos_create_thread(31, SIZEOF_iIsr, &interrupt_3, 0);
}

void interrupt_0()
{
	gpio_ioctl_cb_t gpio_iocb;

	if (NULL == thread_isr_0)
		return;

	while (1)
	{
		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_SET_PROG_INT0_MODE;
		gpio_iocb.value = mode_registry[0];
		vos_dev_ioctl(hGpioB, &gpio_iocb);

		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_WAIT_ON_INT0;
		vos_dev_ioctl(hGpioB, &gpio_iocb);
		//		    thread_list[0]();
		thread_isr_0();
	}
}

void interrupt_1()
{
	gpio_ioctl_cb_t gpio_iocb;

	if (NULL == thread_isr_1)
		return;

	while (1)
	{
		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_SET_PROG_INT1_MODE;
		gpio_iocb.value = mode_registry[1];
		vos_dev_ioctl(hGpioB, &gpio_iocb);

		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_WAIT_ON_INT1;
		vos_dev_ioctl(hGpioB, &gpio_iocb);
		//		    thread_list[1]();
		thread_isr_1();
	}
}

void interrupt_2()
{
	gpio_ioctl_cb_t gpio_iocb;

	if (NULL == thread_isr_2)
		return;

	while (1)
	{
		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_SET_PROG_INT2_MODE;
		gpio_iocb.value = mode_registry[2];
		vos_dev_ioctl(hGpioB, &gpio_iocb);

		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_WAIT_ON_INT2;
		vos_dev_ioctl(hGpioB, &gpio_iocb);
		//		thread_list[2]();
		thread_isr_2();
	}
}

void interrupt_3()
{
	gpio_ioctl_cb_t gpio_iocb;

	if (NULL == thread_isr_3)
		return;

	while (1)
	{
		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_SET_PROG_INT3_MODE;
		gpio_iocb.value = mode_registry[3];
		vos_dev_ioctl(hGpioB, &gpio_iocb);

		gpio_iocb.ioctl_code = VOS_IOCTL_GPIO_WAIT_ON_INT3;
		vos_dev_ioctl(hGpioB, &gpio_iocb);
		//		thread_list[3]();
		thread_isr_3();
	}
}

