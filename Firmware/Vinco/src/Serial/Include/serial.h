/*
** serial.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Serial Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
** History:
**  1 - initial version
*/

#ifndef __SERIAL_H
#define __SERIAL_H

/******************************************************************************/
/*								Macro defines								  */
/******************************************************************************/
#include "vos.h"

#define NO_FLOAT_SUPPORT

/*! \typedef eFormat_t
 *	brief enum to specify print format
 *
 * Enumerated data type that specifies in which format will the first argument
 * to functions print and println be printed
 *
 *	\note Serial.println(1.23456, 0) gives "1"
 *	\note Serial.println(1.23456, 2) gives "1.23"
 *	\note Serial.println(1.23456, 4) gives "1.2346"
*/
typedef enum valueFormat
{BYTE = 100,                           /**< Serial.print(78, BYTE) gives "N"        */
 BIN,                                  /**< Serial.print(78, BIN) gives "1001110"	*/
 OCT,                                  /**< Serial.print(78, OCT) gives "116"		*/
 DEC,                                  /**< Serial.print(78, DEC) gives "78"		*/
 HEX                                   /**< Serial.print(78, HEX) gives "4E"		*/
} eFormat_t;

typedef void (*BEGIN)(long);
typedef void (*END)(void);
typedef int (*AVAILABLE)(void);
typedef int (*READ)(void);
typedef int (*PEEK)(void);
typedef void (*FLUSH)(void);

#ifdef NO_FLOAT_SUPPORT
typedef void (*PRINT)(int, eFormat_t);
typedef void (*PRINTLN)(int, eFormat_t);
#else
typedef void (*PRINT)(double, eFormat_t);
typedef void (*PRINTLN)(double, eFormat_t);
#endif
typedef void (*PRINTSTR)(char *);
typedef void (*WRITE)(char *, int);

/*! \typedef stSerialFunctions_t
 *    brief Collection of functions for serial communication
 *
 *	Member of this typedefed structure form the collection of functions that are
 *	provided to the user applications for serial communication on vinco
 *	platform
*/
typedef struct
{
	BEGIN	  begin;
	END		  end;
	AVAILABLE available;
	READ	  read;
	PEEK	  peek;
	FLUSH	  flush;
	PRINT	  print;
	PRINTLN	  println;
	PRINTSTR  printstr;
	WRITE	  write;
} stSerialFunctions_t;

/*!
 * \brief The variable gFtVcloLibSerDbg defines the debug level
 *
 * 0 - Emergency (emerg)
 * 1 - Alerts (alert)
 * 2 - Critical (crit)
 * 3 - Errors (err)
 * 4 - Warnings (warn)
 * 5 - Notification (notice)
 * 6 - Information (info)
 * 7 - Debug (debug)
*/
#ifdef UNITTEST
extern int currentDebugLevel;

	#define DBG(level, ...)	\
	do \
	{ \
		if (level <= currentDebugLevel)	\
			printf("\n%s:%d:%s():", __FILE__, __LINE__, __func__); \
		printf(__VA_ARGS__); \
	} \
	while (0)

#else
	#define DBG(level, fmt, ...) ;

#endif

/******************************************************************************/
/*								External variables							  */
/******************************************************************************/
extern stSerialFunctions_t Serial;

#define MAX_DIGITS_IN_NUMBER 32
#define MAX_STRING_LEN		 255
#define PRN_NUM_TYPE		 long
/******************************************************************************/
/*								Type defines								  */
/******************************************************************************/

/******************************************************************************/
/*								Function declarations						  */
/******************************************************************************/
void fn_begin(long speed);
void fn_end(void);
int fn_available(void);
int fn_read(void);
int fn_peek(void);
void fn_flush(void);
#ifdef NO_FLOAT_SUPPORT
void fn_print(int val, eFormat_t format);
void fn_println(int val, eFormat_t format);
#else
void fn_print(double val, eFormat_t format);
void fn_println(double val, eFormat_t format);
#endif
void fn_printstr(char *);
void fn_write(char *buf, int len);

void serial_Init(unsigned char uartDevNum, stSerialFunctions_t *);
/******************************************************************************/

#endif                                 /*__SERIAL_H*/
