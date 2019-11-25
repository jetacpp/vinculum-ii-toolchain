/*
** digital_macros.c
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
#include "IOMux.h"

/* Macro for shifting left the first bit in an 8-bit value */
#define BM(x) (1 << (x))

const uint8 Vinco_To_Vinculum_II[] =
{
	52,                                /* J3_1 ** pin 0 ** is pin 52 of Vinculum II */
	51,                                /* J3_2 ** pin 1 ** is pin 51 of Vinculum II */
	55,                                /* J3_3 ** pin 2 ** is pin 55 of Vinculum II */
	56,                                /* J3_4 ** pin 3 ** is pin 56 of Vinculum II */
	57,                                /* J3_5 ** pin 4 ** is pin 57 of Vinculum II */
	58,                                /* J3_6 ** pin 5 ** is pin 58 of Vinculum II */
	59,                                /* J3_7 ** pin 6 ** is pin 59 of Vinculum II */
	60,                                /* J3_8 ** pin 7 ** is pin 60 of Vinculum II */
	17,                                /* J4_1 ** pin 8 ** is pin 17 of Vinculum II */
	18,                                /* J4_2 ** pin 9 ** is pin 18 of Vinculum II */
	23,                                /* J4_3 ** pin 10 ** is pin 23 of Vinculum II */
	20,                                /* J4_4 ** pin 11 ** is pin 20 of Vinculum II */
	22,                                /* J4_5 ** pin 12 ** is pin 22 of Vinculum II */
	19,                                /* J4_6 ** pin 13 ** is pin 19 of Vinculum II */
	NOT_A_PIN,                         /* J4_7 ** pin 14 ** is GND and is not configurable */
	NOT_A_PIN,                         /* J4_8 ** pin 15 ** is AREF and is not configurable */
	62,                                /* J5_1 ** pin 16 ** is pin 62 of Vinculum II */
	63,                                /* J5_2 ** pin 17 ** is pin 63 of Vinculum II */
	64,                                /* J5_3 ** pin 18 ** is pin 64 of Vinculum II */
	12,                                /* J5_4 ** pin 19 ** is pin 12 of Vinculum II */
	13,                                /* J5_5 ** pin 20 ** is pin 13 of Vinculum II */
	14,                                /* J5_6 ** pin 21 ** is pin 14 of Vinculum II */
	15,                                /* J5_7 ** pin 22 ** is pin 15 of Vinculum II */
	16,                                /* J5_8 ** pin 23 ** is pin 16 of Vinculum II */
	24,                                /* J6_1 ** pin 24 ** is pin 24 of Vinculum II */
	25,                                /* J6_2 ** pin 25 ** is pin 25 of Vinculum II */
	26,                                /* J6_3 ** pin 26 ** is pin 26 of Vinculum II */
	27,                                /* J6_4 ** pin 27 ** is pin 27 of Vinculum II */
	28,                                /* J6_5 ** pin 28 ** is pin 28 of Vinculum II */
	29,                                /* J6_6 ** pin 29 ** is pin 29 of Vinculum II */
	31,                                /* J6_7 ** pin 30 ** is pin 31 of Vinculum II */
	32,                                /* J6_8 ** pin 31 ** is pin 32 of Vinculum II */
	39,                                /* LED1 ** pin 32 ** is pin 39 of Vinculum II */
	40                                 /* LED2 ** pin 33 ** is pin 40 of Vinculum II */
};

const uint8 digital_pin_to_port[] =
{
	PA,                                /* J3_1 ** pin 0 ** is mapped to port A pin 1 */
	PA,                                /* J3_2 ** pin 1 ** is mapped to port A pin 0 */
	PA,                                /* J3_3 ** pin 2 ** is mapped to port A pin 2 */
	PA,                                /* J3_4 ** pin 3 ** is mapped to port A pin 3 */
	PA,                                /* J3_5 ** pin 4 ** is mapped to port A pin 4 */
	PA,                                /* J3_6 ** pin 5 ** is mapped to port A pin 5 */
	PA,                                /* J3_7 ** pin 6 ** is mapped to port A pin 6 */
	PA,                                /* J3_8 ** pin 7 ** is mapped to port A pin 7 */
	PE,                                /* J4_1 ** pin 8 ** is mapped to port E pin 2 */
	PE,                                /* J4_2 ** pin 9 ** is mapped to port E pin 3 */
	PE,                                /* J4_3 ** pin 10 ** is mapped to port E pin 7 */
	PE,                                /* J4_4 ** pin 11 ** is mapped to port E pin 5 */
	PE,                                /* J4_5 ** pin 12 ** is mapped to port E pin 6 */
	PE,                                /* J4_6 ** pin 13 ** is mapped to port E pin 4 */
	NOT_A_PORT,                        /* J4_7 ** pin 14 ** is GND and is not mapped to any port */
	NOT_A_PORT,                        /* J4_8 ** pin 15 ** is AREF and is not mapped to any port */
	PE,                                /* J5_1 ** pin 16 ** is mapped to port E pin 1 */
	PC,                                /* J5_2 ** pin 17 ** is mapped to port C pin 6 */
	PC,                                /* J5_3 ** pin 18 ** is mapped to port C pin 7 */
	PC,                                /* J5_4 ** pin 19 ** is mapped to port C pin 1 */
	PC,                                /* J5_5 ** pin 20 ** is mapped to port C pin 2 */
	PC,                                /* J5_6 ** pin 21 ** is mapped to port C pin 3 */
	PC,                                /* J5_7 ** pin 22 ** is mapped to port C pin 4 */
	PC,                                /* J5_8 ** pin 23 ** is mapped to port C pin 5 */
	PD,                                /* J6_1 ** pin 24 ** is mapped to port D pin 0 */
	PD,                                /* J6_2 ** pin 25 ** is mapped to port D pin 1 */
	PD,                                /* J6_3 ** pin 26 ** is mapped to port D pin 2 */
	PD,                                /* J6_4 ** pin 27 ** is mapped to port D pin 3 */
	PD,                                /* J6_5 ** pin 28 ** is mapped to port D pin 4 */
	PD,                                /* J6_6 ** pin 29 ** is mapped to port D pin 5 */
	PD,                                /* J6_7 ** pin 30 ** is mapped to port D pin 6 */
	PD,                                /* J6_8 ** pin 31 ** is mapped to port D pin 7 */
	PC,                                /* LED1 ** pin 32 ** is mapped to port C pin 0 */
	PB                                 /* LED2 ** pin 33 ** is mapped to port B pin 5 */
};

const uint8 digital_pin_to_bit_mask[] =
{
	BM(1),                             /* J3_1 ** pin 0 ** port A*/
	BM(0),
	BM(2),
	BM(3),
	BM(4),
	BM(5),
	BM(6),
	BM(7),
	BM(2),                             /* J4_1 ** pin 8 ** port E*/
	BM(3),
	BM(7),
	BM(5),
	BM(6),
	BM(4),
	0,                                 /* J4_7 ** pin 14 ** is not mapped to any port */
	0,                                 /* J4_8 ** pin 15 ** is not mapped to any port */
	BM(1),                             /* J5_1 ** pin 16 ** port E */
	BM(6),                             /* J5_2 ** pin 17 ** port C */
	BM(7),
	BM(1),
	BM(2),
	BM(3),
	BM(4),
	BM(5),
	BM(0),                             /* J6_1 ** pin 24 ** port D */
	BM(1),
	BM(2),
	BM(3),
	BM(4),
	BM(5),
	BM(6),
	BM(7),
	BM(0),                             /* LED1 ** pin 32 ** port C */
	BM(5)                              /* LED2 ** pin 33 ** port B */
};

const uint8 digital_pin_to_input_signal[] =
{
	IOMUX_IN_GPIO_PORT_A_1,            /* J3_1 ** pin 0 ** is mapped to port A pin 1 */
	IOMUX_IN_GPIO_PORT_A_0,            /* J3_2 ** pin 1 ** is mapped to port A pin 0 */
	IOMUX_IN_GPIO_PORT_A_2,            /* J3_3 ** pin 2 ** is mapped to port A pin 2 */
	IOMUX_IN_GPIO_PORT_A_3,            /* J3_4 ** pin 3 ** is mapped to port A pin 3 */
	IOMUX_IN_GPIO_PORT_A_4,            /* J3_5 ** pin 4 ** is mapped to port A pin 4 */
	IOMUX_IN_GPIO_PORT_A_5,            /* J3_6 ** pin 5 ** is mapped to port A pin 5 */
	IOMUX_IN_GPIO_PORT_A_6,            /* J3_7 ** pin 6 ** is mapped to port A pin 6 */
	IOMUX_IN_GPIO_PORT_A_7,            /* J3_8 ** pin 7 ** is mapped to port A pin 7 */
	IOMUX_IN_GPIO_PORT_E_2,            /* J4_1 ** pin 8 ** is mapped to port E pin 2 */
	IOMUX_IN_GPIO_PORT_E_3,            /* J4_2 ** pin 9 ** is mapped to port E pin 3 */
	IOMUX_IN_GPIO_PORT_E_7,            /* J4_3 ** pin 10 ** is mapped to port E pin 7 */
	IOMUX_IN_GPIO_PORT_E_5,            /* J4_4 ** pin 11 ** is mapped to port E pin 5 */
	IOMUX_IN_GPIO_PORT_E_6,            /* J4_5 ** pin 12 ** is mapped to port E pin 6 */
	IOMUX_IN_GPIO_PORT_E_4,            /* J4_6 ** pin 13 ** is mapped to port E pin 4 */
	NOT_A_SIGNAL,                      /* J4_7 ** pin 14 ** is not mapped to any signal */
	NOT_A_SIGNAL,                      /* J4_8 ** pin 15 ** is not mapped to any signal */
	IOMUX_IN_GPIO_PORT_E_1,            /* J5_1 ** pin 16 ** is mapped to port E pin 1 */
	IOMUX_IN_GPIO_PORT_C_6,            /* J5_2 ** pin 17 ** is mapped to port C pin 6 */
	IOMUX_IN_GPIO_PORT_C_7,            /* J5_3 ** pin 18 ** is mapped to port C pin 7 */
	IOMUX_IN_GPIO_PORT_C_1,            /* J5_4 ** pin 19 ** is mapped to port C pin 1 */
	IOMUX_IN_GPIO_PORT_C_2,            /* J5_5 ** pin 20 ** is mapped to port C pin 2 */
	IOMUX_IN_GPIO_PORT_C_3,            /* J5_6 ** pin 21 ** is mapped to port C pin 3 */
	IOMUX_IN_GPIO_PORT_C_4,            /* J5_7 ** pin 22 ** is mapped to port C pin 4 */
	IOMUX_IN_GPIO_PORT_C_5,            /* J5_8 ** pin 23 ** is mapped to port C pin 5 */
	IOMUX_IN_GPIO_PORT_D_0,            /* J6_1 ** pin 24 ** is mapped to port D pin 0 */
	IOMUX_IN_GPIO_PORT_D_1,            /* J6_2 ** pin 25 ** is mapped to port D pin 1 */
	IOMUX_IN_GPIO_PORT_D_2,            /* J6_3 ** pin 26 ** is mapped to port D pin 2 */
	IOMUX_IN_GPIO_PORT_D_3,            /* J6_4 ** pin 27 ** is mapped to port D pin 3 */
	IOMUX_IN_GPIO_PORT_D_4,            /* J6_5 ** pin 28 ** is mapped to port D pin 4 */
	IOMUX_IN_GPIO_PORT_D_5,            /* J6_6 ** pin 29 ** is mapped to port D pin 5 */
	IOMUX_IN_GPIO_PORT_D_6,            /* J6_7 ** pin 30 ** is mapped to port D pin 6 */
	IOMUX_IN_GPIO_PORT_D_7,            /* J6_8 ** pin 31 ** is mapped to port D pin 7 */
	IOMUX_IN_GPIO_PORT_C_0,            /* LED1 ** pin 32 ** is mapped to port C pin 0 */
	IOMUX_IN_GPIO_PORT_B_5             /* LED2 ** pin 33 ** is mapped to port B pin 5 */
};

const uint8 digital_pin_to_output_signal[] =
{
	IOMUX_OUT_GPIO_PORT_A_1,           /* J3_1 ** pin 0 ** is mapped to port A pin 1 */
	IOMUX_OUT_GPIO_PORT_A_0,           /* J3_2 ** pin 1 ** is mapped to port A pin 0 */
	IOMUX_OUT_GPIO_PORT_A_2,           /* J3_3 ** pin 2 ** is mapped to port A pin 2 */
	IOMUX_OUT_GPIO_PORT_A_3,           /* J3_4 ** pin 3 ** is mapped to port A pin 3 */
	IOMUX_OUT_GPIO_PORT_A_4,           /* J3_5 ** pin 4 ** is mapped to port A pin 4 */
	IOMUX_OUT_GPIO_PORT_A_5,           /* J3_6 ** pin 5 ** is mapped to port A pin 5 */
	IOMUX_OUT_GPIO_PORT_A_6,           /* J3_7 ** pin 6 ** is mapped to port A pin 6 */
	IOMUX_OUT_GPIO_PORT_A_7,           /* J3_8 ** pin 7 ** is mapped to port A pin 7 */
	IOMUX_OUT_GPIO_PORT_E_2,           /* J4_1 ** pin 8 ** is mapped to port E pin 2 */
	IOMUX_OUT_GPIO_PORT_E_3,           /* J4_2 ** pin 9 ** is mapped to port E pin 3 */
	IOMUX_OUT_GPIO_PORT_E_7,           /* J4_3 ** pin 10 ** is mapped to port E pin 7 */
	IOMUX_OUT_GPIO_PORT_E_5,           /* J4_4 ** pin 11 ** is mapped to port E pin 5 */
	IOMUX_OUT_GPIO_PORT_E_6,           /* J4_5 ** pin 12 ** is mapped to port E pin 6 */
	IOMUX_OUT_GPIO_PORT_E_4,           /* J4_6 ** pin 13 ** is mapped to port E pin 4 */
	NOT_A_SIGNAL,                      /* J4_7 ** pin 14 ** is not mapped to any signal */
	NOT_A_SIGNAL,                      /* J4_8 ** pin 15 ** is not mapped to any signal */
	IOMUX_OUT_GPIO_PORT_E_1,           /* J5_1 ** pin 16 ** is mapped to port E pin 1 */
	IOMUX_OUT_GPIO_PORT_C_6,           /* J5_2 ** pin 17 ** is mapped to port C pin 6 */
	IOMUX_OUT_GPIO_PORT_C_7,           /* J5_3 ** pin 18 ** is mapped to port C pin 7 */
	IOMUX_OUT_GPIO_PORT_C_1,           /* J5_4 ** pin 19 ** is mapped to port C pin 1 */
	IOMUX_OUT_GPIO_PORT_C_2,           /* J5_5 ** pin 20 ** is mapped to port C pin 2 */
	IOMUX_OUT_GPIO_PORT_C_3,           /* J5_6 ** pin 21 ** is mapped to port C pin 3 */
	IOMUX_OUT_GPIO_PORT_C_4,           /* J5_7 ** pin 22 ** is mapped to port C pin 4 */
	IOMUX_OUT_GPIO_PORT_C_5,           /* J5_8 ** pin 23 ** is mapped to port C pin 5 */
	IOMUX_OUT_GPIO_PORT_D_0,           /* J6_1 ** pin 24 ** is mapped to port D pin 0 */
	IOMUX_OUT_GPIO_PORT_D_1,           /* J6_2 ** pin 25 ** is mapped to port D pin 1 */
	IOMUX_OUT_GPIO_PORT_D_2,           /* J6_3 ** pin 26 ** is mapped to port D pin 2 */
	IOMUX_OUT_GPIO_PORT_D_3,           /* J6_4 ** pin 27 ** is mapped to port D pin 3 */
	IOMUX_OUT_GPIO_PORT_D_4,           /* J6_5 ** pin 28 ** is mapped to port D pin 4 */
	IOMUX_OUT_GPIO_PORT_D_5,           /* J6_6 ** pin 29 ** is mapped to port D pin 5 */
	IOMUX_OUT_GPIO_PORT_D_6,           /* J6_7 ** pin 30 ** is mapped to port D pin 6 */
	IOMUX_OUT_GPIO_PORT_D_7,           /* J6_8 ** pin 31 ** is mapped to port D pin 7 */
	IOMUX_OUT_GPIO_PORT_C_0,           /* LED1 ** pin 32 ** is mapped to port C pin 0 */
	IOMUX_OUT_GPIO_PORT_B_5            /* LED2 ** pin 33 ** is mapped to port B pin 5 */
};

void dummy(void)
{
}

