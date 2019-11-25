/*
** RTC.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file for Vinculum II RTC Driver (PCF2123)
** Header File
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II Applications
** Requires: None
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __RTC_H__
#define __RTC_H__

#define RTC_VERSION_STRING "2.0.2"

#include "SPIMaster.h"
#include "GPIO.h"

typedef struct _rtc_ioctl_cb_attach_t
{
    VOS_HANDLE	  spi_master_handle;   // Handle to the SPI Master Driver.
    unsigned char spi_master_dma_mode; // DMA mode used by the SPI Master Driver.
    unsigned char spi_ss;              // SPI Slave Select line.
    VOS_HANDLE	  gpio_int_handle;     // Handle to GPIO Port B.
    unsigned char gpio_int_pin;        // Pin connected to the INT# signal on the RTC.
} rtc_ioctl_cb_attach_t;

typedef struct _rtc_ioctl_cb_t {
    unsigned char ioctl_code;
    unsigned char *get;
    unsigned char *set;
} rtc_ioctl_cb_t;

unsigned char rtc_init(unsigned char devnum);

// ==============================================================================
//  RTC Date/Time Defines
// ==============================================================================
#define MODE_24HOUR (0 << 2)
#define MODE_12HOUR (1 << 2)
#define AM			0
#define PM			1

typedef struct _rtc_time {
    char second;
    char minute;
    char hour;
    char am_pm;                        // If the clock is in 12hr mode use this bit to specify am or pm.  Otherwise 0.
    char day;
    char weekday;
    char month;
    char year;
} rtc_time;

enum WEEKDAYS {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
}

enum MONTHS {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}

// ==============================================================================
//  RTC IOCtl Codes
// ==============================================================================
#define RTC_IOCTL_ATTACH			  0x00 // Attach SPI Master driver to the RTC
#define RTC_IOCTL_DETACH			  0x01 // Detach the SPI Master driver from the RTC
#define RTC_IOCTL_RESET				  0x02 // Reset the chip
#define RTC_IOCTL_SET_TIME			  0x03 // Set the time
#define RTC_IOCTL_GET_TIME			  0x04 // Get the time
#define RTC_IOCTL_GET_TIME_MODE		  0x05 // Check whether the clk is 24hr or 12hr mode
#define RTC_IOCTL_SET_TIME_MODE		  0x06 // Set 24hr or 12hr mode
#define RTC_IOCTL_CHECK_CLK_RUNNING	  0x07
#define RTC_IOCTL_SET_ALARM			  0x08 // Set and wait on alarm interrupt
#define RTC_IOCTL_GET_ALARM			  0x09 // Get the alarm time
#define RTC_IOCTL_CANCEL_ALARM		  0x0A // Cancel alarm
#define RTC_IOCTL_START_COUNTDOWN	  0x0B // Start a countdown timer
#define RTC_IOCTL_CANCEL_COUNTDOWN	  0x0C // Cancel the countdown timer
#define RTC_IOCTL_START_MIN_INTERRUPT 0x0D // Start the minute interrupt
#define RTC_IOCTL_STOP_MIN_INTERRUPT  0x0E // Cancel minute interrupt
#define RTC_IOCTL_START_SEC_INTERRUPT 0x0F // Start second interrupt
#define RTC_IOCTL_STOP_SEC_INTERRUPT  0x10 // Cancel second interrupt

// ==============================================================================
//  RTC Return Codes
// ==============================================================================
enum RTC_STATUS {
    RTC_OK,                            // Successful return code
    RTC_INVALID_PARAMETER,             // Invalid parameter to an IOCtl call
    RTC_CLK_STOPPED,                   // The RTC is stopped
    RTC_OSC_STOPPED,                   // The onboard oscillator has stopped
    RTC_RESET_FAILED,                  // Failed to reset the device and get a valid response

    RTC_FATAL_ERROR = 0xFF             // Fatal error, e.g. failed to malloc memory
};

#endif /* __RTC_H__ */
