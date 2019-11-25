/*
** PWM.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II pulse width modulators (PWMs)
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II PWM Driver
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __PWM_H__
#define __PWM_H__

#define PWM_VERSION_STRING "2.0.2"

// PWM IOCTL definitions
#define VOS_IOCTL_PWM_RESET						1  // reset all PWMs
#define VOS_IOCTL_PWM_ENABLE_OUTPUT				2  // enable PWM output
#define VOS_IOCTL_PWM_DISABLE_OUTPUT			3  // disable PWM output
#define VOS_IOCTL_PWM_SET_TRIGGER_MODE			4  // set trigger mode for all PWMs
#define VOS_IOCTL_PWM_ENABLE_INTERRUPT			5  // enable interrupt for all PWMs
#define VOS_IOCTL_PWM_DISABLE_INTERRUPT			6  // disable interrupt for all PWMs
#define VOS_IOCTL_PWM_SET_PRESCALER_VALUE		7  // set prescaler value for all PWMs
#define VOS_IOCTL_PWM_SET_COUNTER_VALUE			8  // maximum counter value, used for end of cycle
#define VOS_IOCTL_PWM_SET_COMPARATOR_VALUE		9  // set a comparator value
#define VOS_IOCTL_PWM_SET_OUTPUT_TOGGLE_ENABLES 10 // set which comparators the PWM output should toggle on
#define VOS_IOCTL_PWM_SET_INITIAL_STATE			11 // set the initial state of the PWMs hi (1) or low (0)
#define VOS_IOCTL_PWM_RESTORE_INITIAL_STATE		12 // restores the initial state of the PWM on completion of cycle
#define VOS_IOCTL_PWM_SET_NUMBER_OF_CYCLES		13 // set the number of times the PWM should repeat the output
#define VOS_IOCTL_PWM_WAIT_ON_COMPLETE			14 // wait on the specified number of PWM cycles completing

// PWM port definitions
#define PWM_0									0
#define PWM_1									1
#define PWM_2									2
#define PWM_3									3
#define PWM_4									4
#define PWM_5									5
#define PWM_6									6
#define PWM_7									7

// comparator definitions
#define COMPARATOR_0							0
#define COMPARATOR_1							1
#define COMPARATOR_2							2
#define COMPARATOR_3							3
#define COMPARATOR_4							4
#define COMPARATOR_5							5
#define COMPARATOR_6							6
#define COMPARATOR_7							7

// PWM mask definitions for use with restore initial state enable IOCTL
#define MASK_PWM_0								(1 << 0)
#define MASK_PWM_1								(1 << 1)
#define MASK_PWM_2								(1 << 2)
#define MASK_PWM_3								(1 << 3)
#define MASK_PWM_4								(1 << 4)
#define MASK_PWM_5								(1 << 5)
#define MASK_PWM_6								(1 << 6)
#define MASK_PWM_7								(1 << 7)

// comparator mask definitions for use with output toggle enable IOCTL
#define MASK_COMPARATOR_0						(1 << 0)
#define MASK_COMPARATOR_1						(1 << 1)
#define MASK_COMPARATOR_2						(1 << 2)
#define MASK_COMPARATOR_3						(1 << 3)
#define MASK_COMPARATOR_4						(1 << 4)
#define MASK_COMPARATOR_5						(1 << 5)
#define MASK_COMPARATOR_6						(1 << 6)
#define MASK_COMPARATOR_7						(1 << 7)

// PWM trigger modes
#define PWM_TRIGGER_MODE_DISABLED				0
#define PWM_TRIGGER_MODE_POSITIVE_EDGE			1
#define PWM_TRIGGER_MODE_NEGATIVE_EDGE			2
#define PWM_TRIGGER_MODE_ANY_EDGE				3

enum PWM_STATUS {
    PWM_OK = 0,
    PWM_INVALID_IOCTL_CODE,
    PWM_INVALID_COMPARATOR_NUMBER,
    PWM_INVALID_PWM_NUMBER,
    PWM_INTERRUPT_NOT_ENABLED,
    PWM_IN_CONTINUOUS_MODE,
    PWM_ERROR,
    PWM_FATAL_ERROR = 0xFF,
    PWM_IN_CONTINOUS_MODE = PWM_IN_CONTINUOUS_MODE, // deprecated spelling
};

// PWM control block for use with PWM IOCTL function
typedef struct _pwm_ioctl_cb_t {
    unsigned char ioctl_code;
    union
    {
        unsigned char pwm_number;
        unsigned char comparator_number;
    } identifier;
    union
    {
        unsigned char  prescaler;
        unsigned short value;
    } count;
    union
    {
        unsigned short value;
    } comparator;
    union
    {
        unsigned char enable_mask;
        unsigned char mode;
        unsigned char init_state_mask;
        unsigned char trigger_mode;
        unsigned char restore_state_mask;
    } output;
} pwm_ioctl_cb_t;

// PWM initialisation function
unsigned char pwm_init(
    unsigned char devNum
    );

#endif                                 /*__PWM_H__*/
