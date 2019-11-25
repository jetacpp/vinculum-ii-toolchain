/*
** Timers.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II user timers driver
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II Timers Driver
** Requires: vos.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __TIMERS_H__
#define __TIMERS_H__

#define TIMERS_VERSION_STRING "2.0.2"

// Timer IOCTL definitions
#define VOS_IOCTL_TIMER_SET_TICK_SIZE	  1 // set the base tick for the timer, 1us or 1ms
#define VOS_IOCTL_TIMER_SET_COUNT		  2 // set initial/final value of timer
#define VOS_IOCTL_TIMER_SET_DIRECTION	  3 // specify if timer counts up or down
#define VOS_IOCTL_TIMER_SET_MODE		  4 // specify single-shot or continuous
#define VOS_IOCTL_TIMER_START			  5 // start the timer
#define VOS_IOCTL_TIMER_GET_CURRENT_COUNT 6 // retrieve the current timer count
#define VOS_IOCTL_TIMER_STOP			  7 // stop the timer
#define VOS_IOCTL_TIMER_WAIT_ON_COMPLETE  8 // wait on the timer completing

// Timer identifiers
#define TIMER_0							  0
#define TIMER_1							  1
#define TIMER_2							  2

// Timer ticks
#define TIMER_TICK_US					  0
#define TIMER_TICK_MS					  1

// Timer direction
#define TIMER_COUNT_DOWN				  0
#define TIMER_COUNT_UP					  1

// Timer mode
#define TIMER_MODE_CONTINUOUS			  0
#define TIMER_MODE_SINGLE_SHOT			  1

enum TIMER_STATUS {
    TIMER_OK = 0,
    TIMER_INVALID_IDENTIFIER,
    TIMER_INVALID_PARAMETER,
    TIMER_ERROR,
    TIMER_FATAL_ERROR = 0xFF
};

// Timer context
typedef struct _tmr_context_t {
    unsigned char timer_identifier;
} tmr_context_t;

// Timer control block for use with Timers IOCTL function
typedef struct _tmr_ioctl_cb_t {
    unsigned char  ioctl_code;
    unsigned short param;
} tmr_ioctl_cb_t;

// Timer initialisation function
unsigned char tmr_init(
    unsigned char devNum,
    void *context
    );

#endif                                 /*__TIMERS_H__*/
