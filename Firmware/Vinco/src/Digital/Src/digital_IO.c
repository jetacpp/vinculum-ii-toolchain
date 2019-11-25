/*
** digital_IO.c
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

#include "digital_macros.h"
#include "digital_IO.h"
#include "IOMux.h"

uint8 bitMask;
uint8 IOPort;
uint8 portValue;
uint8 pinValue;
uint8 temp;
uint8 VinculumIIPin;

/*
** pinMode
**
** Set the I/O mode for a pin
**
** Parameters:	pin: pin name/number (Jx_y or numeric value from 0 -> 31)
**				mode: either INPUT or OUTPUT
** Returns:	SUCCESSFUL, INVALID_PIN or INVALID_MODE
** Comments: pin J3_7 (14) and pin J3_8 (15) are GND and AREF respectively and cannot be used for I/O
**
*/
int8 pinMode(uint8 pin, uint8 mode)
{
	if (invalidPin(pin))
	{
		return INVALID_PIN;
	}

	if (invalidMode(mode))
	{
		return INVALID_MODE;
	}

	VinculumIIPin = VincoPinToVinculumIIPin(pin); /* Vinco pins need to be mapped to VNC2 pins before using IOMux */
	IOPort = digitalPinToPort(pin);               /* refer to digital_macros.c for the mapping of pins to VNC2 GPIO ports */
	bitMask = digitalPinToBitMask(pin);           /* the bit at the pin's position in a port will be set to 1, other bits are 0 */

	if (mode == INPUT)
	{
		ioMuxDefineInput(VinculumIIPin, pin);	/* configure IOMux for input signals */

		/*
		bitMask = ~bitMask;
		switch (IOPort)
		{
		    case PA:
		        vII_gpio_cntrl_porta_1 &= bitMask;
		        break;
		    case PB:
		        vII_gpio_cntrl_portb_1 &= bitMask;
		        break;
		    case PE:
		        vII_gpio_cntrl_porte_1 &= bitMask;
		        break;
		    case PC:
		        vII_gpio_cntrl_portc_1 &= bitMask;
		        break;
		    case PD:
		        vII_gpio_cntrl_portd_1 &= bitMask;
		        break;
		    default:
		        return INVALID_PIN;
		}
		*/
		switch (IOPort)                              /* Configure the direction register of each port for input/output pins: 1 for output, 0 for input */
		{
		case PA:
			vII_gpio_int_reg_en_1.BIT_INT_4_IEN = 0; /* Disable GPIO port interrupt */
			asm
			{
				INPORT vII_gpio_cntrl_porta_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_cntrl_porta_1 portValue
			}
			break;

		case PB:
			asm
			{
				INPORT vII_gpio_cntrl_portb_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portb_1 portValue
			}
			break;

		case PE:
			asm
			{
				INPORT vII_gpio_cntrl_porte_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_cntrl_porte_1 portValue
			}
			break;

		case PC:
			asm
			{
				INPORT vII_gpio_cntrl_portc_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portc_1 portValue
			}
			break;

		case PD:
			asm
			{
				INPORT vII_gpio_cntrl_portd_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portd_1 portValue
			}
			break;

		default:
			return INVALID_PIN;
		}
	}
	else                               /* mode == OUTPUT */
	{
		ioMuxDefineOutput(VinculumIIPin, pin);  /* configure IOMux for output signals */

		/*
		switch (IOPort)
		{
		    case PA:
		        vII_gpio_cntrl_porta_1 |= bitMask;
		        break;
		    case PB:
		        vII_gpio_cntrl_portb_1 |= bitMask;
		        break;
		    case PE:
		        vII_gpio_cntrl_porte_1 |= bitMask;
		        break;
		    case PC:
		        vII_gpio_cntrl_portc_1 |= bitMask;
		        break;
		    case PD:
		        vII_gpio_cntrl_portd_1 |= bitMask;
		        break;
		    default:
		        return INVALID_PIN;
		}
		*/
		switch (IOPort)                              /* Configure the direction register of each port for input/output pins: 1 for output, 0 for input */
		{
		case PA:
			vII_gpio_int_reg_en_1.BIT_INT_4_IEN = 0; /* Disable GPIO port interrupt */
			asm
			{
				INPORT vII_gpio_cntrl_porta_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_cntrl_porta_1 portValue
			}
			break;

		case PB:
			asm
			{
				INPORT vII_gpio_cntrl_portb_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portb_1 portValue
			}
			break;

		case PE:
			asm
			{
				INPORT vII_gpio_cntrl_porte_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_cntrl_porte_1 portValue
			}
			break;

		case PC:
			asm
			{
				INPORT vII_gpio_cntrl_portc_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portc_1 portValue
			}
			break;

		case PD:
			asm
			{
				INPORT vII_gpio_cntrl_portd_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_cntrl_portd_1 portValue
			}
			break;

		default:
			return INVALID_PIN;
		}
	}

	vII_gpio_sys_cntrl_1 = MASK_GPIO_EN;
	return SUCCESSFUL;
}

/*
** digitalRead
**
** Read the value of an input pin
**
** Parameters:	pin: pin name/number (Jx_y or numeric value from 0 -> 31)
** Returns:	either HIGH or LOW
** Comments: pin J3_7 (14) and pin J3_8 (15) are GND and AREF respectively and cannot be used for I/O
**
*/
uint8 digitalRead(uint8 pin)
{
	bitMask = digitalPinToBitMask(pin); /* the bit at the pin's position in a port will be set to 1, other bits are 0 */
	IOPort = digitalPinToPort(pin);     /* refer to digital_macros.c for the mapping of pins to VNC2 GPIO ports */

	/*
	switch (IOPort)
	{
	    case PA:
	        pinValue = vII_gpio_data_rx_pa_1;
	        break;
	    case PB:
	        pinValue = vII_gpio_data_rx_pb_1;
	        break;
	    case PE:
	        pinValue = vII_gpio_data_rx_pe_1;
	        break;
	    case PC:
	        pinValue = vII_gpio_data_rx_pc_1;
	        break;
	    case PD:
	        pinValue = vII_gpio_data_rx_pd_1;
	        break;
	    default:
	        return INVALID_PIN;
	}
	pinValue &= bitMask;
	if (pinValue != 0)
	    return 1;
	else
	    return 0;
	*/
	switch (IOPort)                     /* Get the value in the input data register of the port */
	{
	case PA:
		asm
		{
			INPORT vII_gpio_data_rx_pa_1 portValue
		}
		break;

	case PB:
		asm
		{
			INPORT vII_gpio_data_rx_pb_1 portValue
		}
		break;

	case PE:
		asm
		{
			INPORT vII_gpio_data_rx_pe_1 portValue
		}
		break;

	case PC:
		asm
		{
			INPORT vII_gpio_data_rx_pc_1 portValue
		}
		break;

	case PD:
		asm
		{
			INPORT vII_gpio_data_rx_pd_1 portValue
		}
		break;

	default:
	}

	asm                                /* Perform bit-wise AND between portValue and bitMask to get the value of the bit corresponding to the pin */
	{
		AND8 portValue bitMask
		CMP8 portValue $0x00
		JZ @ReturnLow
@ReturnHigh:
		LD8 pinValue $0x01
		JUMP @End
@ReturnLow:
		LD8 pinValue $0x00
@End:
	}
	return pinValue;
}

/*
** digitalWrite
**
** Write the specified value to an output pin
**
** Parameters:	pin: pin name/number (Jx_y or numeric value from 0 -> 31)
**				value: either HIGH or LOW
** Returns:	SUCCESSFUL, INVALID_PIN or INVALID_MODE
** Comments: pin J3_7 (14) and pin J3_8 (15) are GND and AREF respectively and cannot be used for I/O
**
*/
int8 digitalWrite(uint8 pin, uint8 value)
{
	if (invalidPin(pin))
	{
		return INVALID_PIN;
	}

	if (invalidValue(value))
	{
		return INVALID_VALUE;
	}

	bitMask = digitalPinToBitMask(pin); /* the bit at the pin's position in a port will be set to 1, other bits are 0 */
	IOPort = digitalPinToPort(pin);     /* refer to digital_macros.c for the mapping of pins to VNC2 GPIO ports */

	if (value == HIGH)
	{
		/*
		switch (IOPort)
		{
		    case PA:
		        vII_gpio_data_tx_pa_1 |= bitMask;
		        break;
		    case PB:
		        vII_gpio_data_tx_pb_1 |= bitMask;
		        break;
		    case PE:
		        vII_gpio_data_tx_pe_1 |= bitMask;
		        break;
		    case PC:
		        vII_gpio_data_tx_pc_1 |= bitMask;
		        break;
		    case PD:
		        vII_gpio_data_tx_pd_1 |= bitMask;
		        break;
		    default:
		        return INVALID_PIN;
		}
		*/
		switch (IOPort)                /* Write 1 to the bit corresponding to the pin by OR-ing bitMask with the output data register */
		{
		case PA:
			asm
			{
				INPORT vII_gpio_data_tx_pa_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pa_1 portValue
			}
			break;

		case PB:
			asm
			{
				INPORT vII_gpio_data_tx_pb_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pb_1 portValue
			}
			break;

		case PE:
			asm
			{
				INPORT vII_gpio_data_tx_pe_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pe_1 portValue
			}
			break;

		case PC:
			asm
			{
				INPORT vII_gpio_data_tx_pc_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pc_1 portValue
			}
			break;

		case PD:
			asm
			{
				INPORT vII_gpio_data_tx_pd_1 portValue
				OR8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pd_1 portValue
			}
			break;

		default:
			return INVALID_PIN;
		}
	}
	else                               /* value == LOW */
	{
		/*
		bitMask = ~bitMask;
		switch (IOPort)
		{
		    case PA:
		        vII_gpio_data_tx_pa_1 &= bitMask;
		        break;
		    case PB:
		        vII_gpio_data_tx_pb_1 &= bitMask;
		        break;
		    case PE:
		        vII_gpio_data_tx_pe_1 &= bitMask;
		        break;
		    case PC:
		        vII_gpio_data_tx_pc_1 &= bitMask;
		        break;
		    case PD:
		        vII_gpio_data_tx_pd_1 &= bitMask;
		        break;
		    default:
		        return INVALID_PIN;
		}
		*/
		switch (IOPort) /* Write 1 to the bit corresponding to the pin by AND-ing (~bitMask) with the output data register */
		{
		case PA:
			asm
			{
				INPORT vII_gpio_data_tx_pa_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pa_1 portValue
			}
			break;

		case PB:
			asm
			{
				INPORT vII_gpio_data_tx_pb_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pb_1 portValue
			}
			break;

		case PE:
			asm
			{
				INPORT vII_gpio_data_tx_pe_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pe_1 portValue
			}
			break;

		case PC:
			asm
			{
				INPORT vII_gpio_data_tx_pc_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pc_1 portValue
			}
			break;

		case PD:
			asm
			{
				INPORT vII_gpio_data_tx_pd_1 portValue
				INV8 temp bitMask
				CPY8 bitMask temp
				AND8 portValue bitMask
				OUTPORT vII_gpio_data_tx_pd_1 portValue
			}
			break;

		default:
			return INVALID_PIN;
		}
	}

	return SUCCESSFUL;
}

/*
** portMode
**
** Select the mode for any of the four ports on Vinco (J3, J4, J5, J6)
**
** Parameters:	portName: J3, J4, J5 or J6
**				mode: either INPUT or OUTPUT
** Returns:	SUCCESSFUL, INVALID_PIN or INVALID_MODE
** Comments: pin J3_7 (14) and pin J3_8 (15) are GND and AREF respectively and cannot be used for I/O
**
*/
int8 portMode(uint8 portName, uint8 mode)
{
	if ((portName != J3) && (portName != J4) && (portName != J5) && (portName != J6))
	{
		return INVALID_PORT;
	}

	if (invalidMode(mode))
	{
		return INVALID_MODE;
	}

	if (mode == INPUT)
	{
		switch (portName)
		{
		case J3:
			pinMode(J3_1, INPUT);
			pinMode(J3_2, INPUT);
			pinMode(J3_3, INPUT);
			pinMode(J3_4, INPUT);
			pinMode(J3_5, INPUT);
			pinMode(J3_6, INPUT);
			pinMode(J3_7, INPUT);
			pinMode(J3_8, INPUT);
			break;

		case J4:
			pinMode(J4_1, INPUT);
			pinMode(J4_2, INPUT);
			pinMode(J4_3, INPUT);
			pinMode(J4_4, INPUT);
			pinMode(J4_5, INPUT);
			pinMode(J4_6, INPUT);
			break;

		case J5:
			pinMode(J5_1, INPUT);
			pinMode(J5_2, INPUT);
			pinMode(J5_3, INPUT);
			pinMode(J5_4, INPUT);
			pinMode(J5_5, INPUT);
			pinMode(J5_6, INPUT);
			pinMode(J5_7, INPUT);
			pinMode(J5_8, INPUT);
			break;

		case J6:
			pinMode(J6_1, INPUT);
			pinMode(J6_2, INPUT);
			pinMode(J6_3, INPUT);
			pinMode(J6_4, INPUT);
			pinMode(J6_5, INPUT);
			pinMode(J6_6, INPUT);
			pinMode(J6_7, INPUT);
			pinMode(J6_8, INPUT);
			break;

		default:
			return INVALID_PORT;
		}
	}
	else                               /* mode == OUTPUT */
	{
		switch (portName)
		{
		case J3:
			pinMode(J3_1, OUTPUT);
			pinMode(J3_2, OUTPUT);
			pinMode(J3_3, OUTPUT);
			pinMode(J3_4, OUTPUT);
			pinMode(J3_5, OUTPUT);
			pinMode(J3_6, OUTPUT);
			pinMode(J3_7, OUTPUT);
			pinMode(J3_8, OUTPUT);
			break;

		case J4:
			pinMode(J4_1, OUTPUT);
			pinMode(J4_2, OUTPUT);
			pinMode(J4_3, OUTPUT);
			pinMode(J4_4, OUTPUT);
			pinMode(J4_5, OUTPUT);
			pinMode(J4_6, OUTPUT);
			break;

		case J5:
			pinMode(J5_1, OUTPUT);
			pinMode(J5_2, OUTPUT);
			pinMode(J5_3, OUTPUT);
			pinMode(J5_4, OUTPUT);
			pinMode(J5_5, OUTPUT);
			pinMode(J5_6, OUTPUT);
			pinMode(J5_7, OUTPUT);
			pinMode(J5_8, OUTPUT);
			break;

		case J6:
			pinMode(J6_1, OUTPUT);
			pinMode(J6_2, OUTPUT);
			pinMode(J6_3, OUTPUT);
			pinMode(J6_4, OUTPUT);
			pinMode(J6_5, OUTPUT);
			pinMode(J6_6, OUTPUT);
			pinMode(J6_7, OUTPUT);
			pinMode(J6_8, OUTPUT);
			break;

		default:
			return INVALID_PORT;
		}
	}

	return SUCCESSFUL;
}

/*
** portRead
**
** Read the value of a whole port on Vinco (J3, J4, J5 or J6)
**
** Parameters:	portName: J3, J4, J5 or J6
** Returns:	port value (8-bit value). The left most bit corresponds to the first pin (Jx_1) and the right most bit
**          corresponds the the last pin (Jx_8) of the port
** Comments: Port J4 has only 6 usable pins (J4_1 -> J4_6), so the last two bits of the returned value will always be 0
**			 and should be ommited in user's applications
*/
uint8 portRead(uint8 portName)
{
	uint8 value = 0x00;
	uint8 tempVal;

	switch (portName)
	{
	case J3:
		tempVal = digitalRead(J3_8);
		value = value | (tempVal << 0);
		tempVal = digitalRead(J3_7);
		value = value | (tempVal << 1);
		tempVal = digitalRead(J3_6);
		value = value | (tempVal << 2);
		tempVal = digitalRead(J3_5);
		value = value | (tempVal << 3);
		tempVal = digitalRead(J3_4);
		value = value | (tempVal << 4);
		tempVal = digitalRead(J3_3);
		value = value | (tempVal << 5);
		tempVal = digitalRead(J3_2);
		value = value | (tempVal << 6);
		tempVal = digitalRead(J3_1);
		value = value | (tempVal << 7);
		break;

	case J4:
		tempVal = digitalRead(J4_6);
		value = value | (tempVal << 2);
		tempVal = digitalRead(J4_5);
		value = value | (tempVal << 3);
		tempVal = digitalRead(J4_4);
		value = value | (tempVal << 4);
		tempVal = digitalRead(J4_3);
		value = value | (tempVal << 5);
		tempVal = digitalRead(J4_2);
		value = value | (tempVal << 6);
		tempVal = digitalRead(J4_1);
		value = value | (tempVal << 7);
		break;

	case J5:
		tempVal = digitalRead(J5_8);
		value = value | (tempVal << 0);
		tempVal = digitalRead(J5_7);
		value = value | (tempVal << 1);
		tempVal = digitalRead(J5_6);
		value = value | (tempVal << 2);
		tempVal = digitalRead(J5_5);
		value = value | (tempVal << 3);
		tempVal = digitalRead(J5_4);
		value = value | (tempVal << 4);
		tempVal = digitalRead(J5_3);
		value = value | (tempVal << 5);
		tempVal = digitalRead(J5_2);
		value = value | (tempVal << 6);
		tempVal = digitalRead(J5_1);
		value = value | (tempVal << 7);
		break;

	case J6:
		tempVal = digitalRead(J6_8);
		value = value | (tempVal << 0);
		tempVal = digitalRead(J6_7);
		value = value | (tempVal << 1);
		tempVal = digitalRead(J6_6);
		value = value | (tempVal << 2);
		tempVal = digitalRead(J6_5);
		value = value | (tempVal << 3);
		tempVal = digitalRead(J6_4);
		value = value | (tempVal << 4);
		tempVal = digitalRead(J6_3);
		value = value | (tempVal << 5);
		tempVal = digitalRead(J6_2);
		value = value | (tempVal << 6);
		tempVal = digitalRead(J6_1);
		value = value | (tempVal << 7);
		break;

	default:
	}

	return value;
}

/*
** portWrite
**
** Write a value to a whole port on Vinco (J3, J4, J5 or J6)
**
** Parameters:	portName: J3, J4, J5 or J6
**				value: 8-bit value. The left most bit corresponds to the first pin (Jx_1) and the right most bit
**                  corresponds the the last pin (Jx_8) of the port
** Returns:	SUCCESSFUL or INVALID_PORT
** Comments: Port J4 has only 6 usable pins (J4_1 -> J4_6), so the last two bits of the written value will be omitted by the API
*/
int8 portWrite(uint8 portName, uint8 value)
{
	if ((portName != J3) && (portName != J4) && (portName != J5) && (portName != J6))
	{
		return INVALID_PORT;
	}

	switch (portName)
	{
	case J3:
		digitalWrite(J3_8, (value & 0x01) >> 0);
		digitalWrite(J3_7, (value & 0x02) >> 1);
		digitalWrite(J3_6, (value & 0x04) >> 2);
		digitalWrite(J3_5, (value & 0x08) >> 3);
		digitalWrite(J3_4, (value & 0x10) >> 4);
		digitalWrite(J3_3, (value & 0x20) >> 5);
		digitalWrite(J3_2, (value & 0x40) >> 6);
		digitalWrite(J3_1, (value & 0x80) >> 7);
		break;

	case J4:
		digitalWrite(J4_6, (value & 0x04) >> 2);
		digitalWrite(J4_5, (value & 0x08) >> 3);
		digitalWrite(J4_4, (value & 0x10) >> 4);
		digitalWrite(J4_3, (value & 0x20) >> 5);
		digitalWrite(J4_2, (value & 0x40) >> 6);
		digitalWrite(J4_1, (value & 0x80) >> 7);
		break;

	case J5:
		digitalWrite(J5_8, (value & 0x01) >> 0);
		digitalWrite(J5_7, (value & 0x02) >> 1);
		digitalWrite(J5_6, (value & 0x04) >> 2);
		digitalWrite(J5_5, (value & 0x08) >> 3);
		digitalWrite(J5_4, (value & 0x10) >> 4);
		digitalWrite(J5_3, (value & 0x20) >> 5);
		digitalWrite(J5_2, (value & 0x40) >> 6);
		digitalWrite(J5_1, (value & 0x80) >> 7);
		break;

	case J6:
		digitalWrite(J6_8, (value & 0x01) >> 0);
		digitalWrite(J6_7, (value & 0x02) >> 1);
		digitalWrite(J6_6, (value & 0x04) >> 2);
		digitalWrite(J6_5, (value & 0x08) >> 3);
		digitalWrite(J6_4, (value & 0x10) >> 4);
		digitalWrite(J6_3, (value & 0x20) >> 5);
		digitalWrite(J6_2, (value & 0x40) >> 6);
		digitalWrite(J6_1, (value & 0x80) >> 7);
		break;

	default:
		return INVALID_PORT;
	}

	return SUCCESSFUL;
}

