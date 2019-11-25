#ifndef _SERIAL_CORE_H
#define _SERIAL_CORE_H

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

#endif                                 /*_SERIAL_CORE_H*/
