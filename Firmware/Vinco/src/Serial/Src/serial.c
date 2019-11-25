/*
** serial.c
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

#include "serial.h"
#include "vos.h"
#include "UART.h"

// #define PRN_NUM_TYPE	(unsigned long)

// #define VOS_DEV_UART                                    0

/******************************************************************************/
/*								Local function declarations					  */
/******************************************************************************/
static void printNumber(PRN_NUM_TYPE n, unsigned char base);

/******************************************************************************/
/*								Global variables							  */
/******************************************************************************/

/*!
 * \brief Members of this structure are the functions that form the Serial API
 *
 * [detailed description]
 *
 * \sa Defination of stSerialFunctions_t
 * \note Addresses of functions fn_begin, fn_end, etc needs to be assigned to the members(function
 * pointers) of this structure before Serial.begin is called. This may be done in function main() as
 * Serial.begin = &fn_begin; Serial.end = &fn_end; etc
*/
extern stSerialFunctions_t Serial;

#ifdef UNITTEST
int currentDebugLevel = 7;
#endif

unsigned char devNum;

#ifndef UNITTEST
// UART context structure
uart_context_t uartCtx;

/* VOS handles for opened devices*/
VOS_HANDLE hUart;

// UART IOCTL request block */
common_ioctl_cb_t uart_iocb;

#endif

void serial_Init(unsigned char uartDevNum, stSerialFunctions_t *Serial)
{
	// Initializing serial library
	Serial->begin = &fn_begin;
	Serial->end = &fn_end;
	Serial->available = &fn_available;
	Serial->read = &fn_read;
	Serial->peek = &fn_peek;
	Serial->flush = &fn_flush;
	Serial->print = &fn_print;
	Serial->println = &fn_println;
	Serial->write = &fn_write;
	Serial->printstr = &fn_printstr;
	
	devNum = uartDevNum;
}

/******************************************************************************/
/*						Public Function ddefinations						  */
/******************************************************************************/

/*!
 * \brief Initializes the serial communication module
 *
 * Sets the data rate in bits per second (baud) for serial data transmission.
 * For communicating with the computer, use one of these rates: 300, 1200,
 * 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200.
 * However, other baud rates may be specified to communicate with components
 * that requires a particuler baude rate
 *
 * \param[in] speed Baud rate to be generated
 * \param[out] none
 * \return none
 * \sa
 * \note Maximum baud rate = CPU clock frequency / 3
 * \note This function is to be called before vos_start_scheduler() is called
 * \warning
 */
void fn_begin(long speed)
{
#ifndef UNITTEST
	vos_iomux_define_output(51, IOMUX_OUT_UART_TXD); // UART Tx
	vos_iomux_define_input(52, IOMUX_IN_UART_RXD);   //

//	devNum = VOS_DEV_UART;

	// uart init
	/* initialise device drivers */
	/* call initialisation routines for included device drivers */
	uartCtx.buffer_size = VOS_BUFFER_SIZE_128_BYTES;
	uart_init(devNum, &uartCtx);       /*to be called before vos_start_scheduler()*/

	/* find and open UART device */
	hUart = vos_dev_open(devNum);

	/* UART ioctl call to enable DMA and link to DMA driver */
	uart_iocb.ioctl_code = VOS_IOCTL_COMMON_ENABLE_DMA;
	uart_iocb.set.param = DMA_ACQUIRE_AS_REQUIRED;
	vos_dev_ioctl(hUart, &uart_iocb);

	/* UART setup */
	/* set baud rate */
	uart_iocb.ioctl_code = VOS_IOCTL_UART_SET_BAUD_RATE;
	uart_iocb.set.uart_baud_rate = speed;
	vos_dev_ioctl(hUart, &uart_iocb);
	/* set flow control */
	uart_iocb.ioctl_code = VOS_IOCTL_UART_SET_FLOW_CONTROL;
	uart_iocb.set.param = UART_FLOW_NONE;
	vos_dev_ioctl(hUart, &uart_iocb);
	/* set data bits */
	uart_iocb.ioctl_code = VOS_IOCTL_UART_SET_DATA_BITS;
	uart_iocb.set.param = UART_DATA_BITS_8;
	vos_dev_ioctl(hUart, &uart_iocb);
	/* set stop bits */
	uart_iocb.ioctl_code = VOS_IOCTL_UART_SET_STOP_BITS;
	uart_iocb.set.param = UART_STOP_BITS_1;
	vos_dev_ioctl(hUart, &uart_iocb);
	/* set parity */
	uart_iocb.ioctl_code = VOS_IOCTL_UART_SET_PARITY;
	uart_iocb.set.param = UART_PARITY_NONE;
	vos_dev_ioctl(hUart, &uart_iocb);
#endif
}

/*!
 * \brief De-initializes the serial communication module
 *
 * Disables serial communication, allowing the RX and TX pins to be used
 * for general input and output. To re-enable serial communication, call
 *Serial.begin()
 *
 * \param[in] none
 * \param[out] none
 * \return none
 * \sa
 * \note This function frees any resources(h/w pins, memory, locks) that
 *was allocated to this module during initialization
 * \warning
 */
void fn_end(void)
{
	// TODO: Add code to unregister driver when that is supported by driver
#ifndef UNITTEST
	vos_dev_close(hUart);
#endif
}

/*!
 * \brief Returns the number of bytes read into internal buffer
 *
 * Get the number of bytes (characters) available for reading from the
 * serial port. This is data that's already arrived and stored in the serial
 * receive buffer (which holds 128 bytes)
 *
 * \param[in] none
 * \param[out] none
 * \return The number of bytes available to read
 * \sa
 * \note
 * \warning
 */
int fn_available(void)
{
	unsigned int avl = 0;

#ifndef UNITTEST
	uart_iocb.ioctl_code = VOS_IOCTL_COMMON_GET_RX_QUEUE_STATUS;
	vos_dev_ioctl(hUart, &uart_iocb);
	avl = uart_iocb.get.queue_stat;
#endif
	return avl;
}

/*!
 * \brief Reads incoming serial data
 *
 * Reads incoming serial data
 *
 * \param[in] none
 * \param[out] none
 * \return The first byte of incoming serial data available (or -1
 * if no data is available)
 * \sa
 * \note
 * \warning
 */
int fn_read(void)
{
	unsigned char val;
	unsigned short num_read;

	if (fn_available())
	{
		if (vos_dev_read(hUart, &val, (unsigned short) 1, &num_read) != UART_OK)
			return -1;
		else
			return (int) val;
	}
	else
		return -1;
}

/*!
 * \brief Reads without removing from buffer
 *
 * Returns the next byte (character) of incoming serial data without removing
 * it from the internal serial buffer. That is, successive calls to peek() will
 * return the same character, as will the next call to read()
 *
 * \param[in] none
 * \param[out] none
 * \return The first byte of incoming serial data available (or -1 if no data
 is available)
 * \sa
 * \note
 * \warning
 */
int fn_peek(void)
{
	int val;

	// No equivalent IOCTL supported by driver

	return val;
}

/*!
* \brief Flushes the internal buffer
*
* Flushes the buffer of incoming serial data. That is, any call to Serial.read()
* or Serial.available() will return only data received after all the most recent
* call to Serial.flush().
*
* \param[in] none
* \param[out] none
* \return none
* \sa
* \note
* \warning
*/
void fn_flush(void)
{
#if 1
	uint8 buf[10];
	int avl;
	unsigned short num_read = 0;
	avl = fn_available();

	if (avl > 0)
	{
		while (avl > 0)
		{
			vos_dev_read(hUart, buf, (unsigned short) (avl > 10?10:avl % 10), &num_read);
			avl = avl - num_read;
		}
	}

#else

	while (fn_available())
		fn_read();

#endif
}

#ifdef NO_FLOAT_SUPPORT

/*!
 * \brief Writes data in ASCII format to serial port
 *
 * Prints data to the serial port as human-readable ASCII text. This command
 * can take many forms. Numbers are printed using an ASCII character for each
 * digit. Floats are similarly printed as ASCII digits, defaulting to two
 * decimal places. Bytes are sent as a single character. The second parameter
 * specifies the base (format) to use; permitted values are BYTE, BIN (binary,
 * or base 2), OCT (octal, or base 8), DEC (decimal, or base 10), HEX
 * (hexadecimal, or base 16). For floating point numbers, this parameter
 * specifies the number of decimal places to use
 *
 * \param[in] val Address of the memory where the value is stored]
 * \param[in] format Format in which the value is to be printed]
  * \param[out] none
 * \return none
 * \sa typedef eFormat_t
 * \note If a val is a floating point number then valid values for format are 1 through 99
 * \warning
 */
void fn_print(int val, eFormat_t format)
{
	char output[MAX_DIGITS_IN_NUMBER];
	int outDataLen;                    /*Length of data in bytes*/

	switch (format)
	{
	case BYTE:
		outDataLen = 1;
		output[0] = (unsigned char) val;
		fn_write(output, outDataLen);
		break;

	case BIN:
		printNumber((PRN_NUM_TYPE) val, 2);
		break;

	case OCT:
		printNumber((PRN_NUM_TYPE) val, 8);
		break;

	case DEC:

		if (val < 0)
		{
			output[0] = '-';
			fn_write(output, 1);
			printNumber((PRN_NUM_TYPE) -val, 10);
		}
		else
			printNumber((PRN_NUM_TYPE) val, 10);

		break;

	case HEX:
		printNumber((PRN_NUM_TYPE) val, 16);
		break;

	default:

		if ((format >= 0) & (format < 100)) /*val is a floting point number*/
		{       // DBG(7,"Floating point support is disabled");
		}
		else /*Control shouldn't reach here*/
		{
#ifdef UNIT_TEST
			/*Not checking for negative cases to reduce footprint on embedded platform*/
			DBG(0, "fatal runtime exception catch: control should'nt reach here\n");
			exit(0);
#endif
		}

		break;
	}
}

#else

/*!
 * \brief Writes data in ASCII format to serial port
 *
 * Prints data to the serial port as human-readable ASCII text. This command
 * can take many forms. Numbers are printed using an ASCII character for each
 * digit. Floats are similarly printed as ASCII digits, defaulting to two
 * decimal places. Bytes are sent as a single character. The second parameter
 * specifies the base (format) to use; permitted values are BYTE, BIN (binary,
 * or base 2), OCT (octal, or base 8), DEC (decimal, or base 10), HEX
 * (hexadecimal, or base 16). For floating point numbers, this parameter
 * specifies the number of decimal places to use
 *
 * \param[in] val Address of the memory where the value is stored]
 * \param[in] format Format in which the value is to be printed]
  * \param[out] none
 * \return none
 * \sa typedef eFormat_t
 * \note If a val is a floating point number then valid values for format are 1 through 99
 * \warning
 */
// void fn_print(long val,eFormat_t format)
void fn_print(double val, eFormat_t format)
{
	unsigned char output[MAX_DIGITS_IN_NUMBER];
	int outDataLen;                    /*Length of data in bytes*/

	switch (format)
	{
	case BYTE:
		outDataLen = 1;
		output[0] = (unsigned char) val;
		fn_write(output, outDataLen);
		break;

	case BIN:
		printNumber(val, 2);
		break;

	case OCT:
		printNumber(val, 8);
		break;

	case DEC:

		if (val < 0)
		{
			output[0] = '-';
			fn_write(output, 1);
			printNumber(-val, 10);
		}
		else
			printNumber(val, 10);

		break;

	case HEX:
		printNumber(val, 16);
		break;

	default:

		if (format >= 0 & format < 100) /*val is a floting point number*/
		{
			int mul = 10;
			float fInput;
			long lWhole = 0;
			unsigned long ulPart = 0;
			int i;

			if (val > 0)
			{
				fInput = val;
			}
			else
			{
				fInput = -val;
				output[0] = '-';
				fn_write(output, 1);
			}

			for (i = 0; i < (int) format - 1; i++)
				mul = mul * 10;

			// Convert number from float to fixed point for display.
			// The number is converted to two parts.
			lWhole = (long) ((float) fInput);
			ulPart = (long) ((float) fInput * mul) - lWhole * mul;

			printNumber((unsigned long) lWhole, 10);

			if (format > 0)            /*print decimal part only if requested for*/
			{
				// TODO: add code to print successive zeros immediately after decimal point
				//		i.e if we support floating point numbers later
				printNumber((unsigned long) ulPart, 10);
			}
		}
		else /*Control shouldn't reach here*/
		{
#ifdef UNIT_TEST
			/*Not checking for negative cases to reduce footprint on embedded platform*/
			DBG(0, "fatal runtime exception catch: control shouldn't reach here\n");
			exit(0);
#endif
		}

		break;
	}
}

#endif

#ifdef NO_FLOAT_SUPPORT

/*!
 * \brief Writes data in ASCII format followed by carriage return and new line
 * character
 *
 * Prints data to the serial port as human-readable ASCII text followed by a
 * carriage return character (ASCII 13, or '\\r') and a newline character (ASCII
 * 10, or '\\n'). This command takes the same forms as Serial.print()
 *
 * \param[in] *val address of the memory where the value is stored
 * \param[in] format format in which the value is to be printed
 * \param[out] none
 * \return none
 * \sa typedef eFormat_t
 * \note If a val is a floating point number then valid values for format are 1
 * through 99
 * \warning
 */
void fn_println(int val, eFormat_t format)
{
	fn_print(val, format);
	fn_print('\r', BYTE);
	fn_print('\n', BYTE);
}

#else

/*!
 * \brief Writes data in ASCII format followed by carriage return and new line
 * character
 *
 * Prints data to the serial port as human-readable ASCII text followed by a
 * carriage return character (ASCII 13, or '\\r') and a newline character (ASCII
 * 10, or '\\n'). This command takes the same forms as Serial.print()
 *
 * \param[in] *val address of the memory where the value is stored
 * \param[in] format format in which the value is to be printed
 * \param[out] none
 * \return none
 * \sa typedef eFormat_t
 * \note If a val is a floating point number then valid values for format are 1
 * through 99
 * \warning
 */
void fn_println(double val, eFormat_t format)
{
	fn_print(val, format);
	fn_print('\r', BYTE);
	fn_print('\n', BYTE);
}

#endif

/*!
 * \brief Prints an array of string
 *
 * Prints an ASCII string to serial port
 *
 * \param[in] *str address of the starting character of the string
 * \param[out] none
 * \return none
 * \sa
 * \note
 * \warning The string must be NULL terminated
 */
void fn_printstr(char *str)
{
	int i = 0;
	char *tmp = str;

	while ((tmp[i] != '\0') && (i < MAX_STRING_LEN))
		i++;                           /*calculate string length*/

	fn_write(str, i);
}

/*!
 * \brief Writes binary data to serial port
 *
 * Writes binary data to the serial port. This data is sent as a byte or series
 * of bytes; to send the characters representing the digits of a number use the
 * print() function instead.
 *
 * \param[in] *buf Address of the first location in memory where the data is
 * stored
 * \param[out] len Length of data
 * \return none
 * \sa
 * \note
 * \warning This is a blocking function. Writing large amounts of data using a
 * single function call may make the application unresponsive
 */
void fn_write(char *buf, int len)
{
	uint16 written = 0;

#ifdef UNITTEST
	int i;
	DBG(7, "Sending %d byte(s) to UART: ", len);

	for (i = 0; i < len; i++)
		printf("%c", *(buf + i));

#else
	#if 0
	{
		unsigned char c;
		int i;

		for (i = 0; i < len; i++)
		{
			c = buf[i];
			vos_dev_write(hUart, &c, (uint16) 1, &written);
		}
	}
	#else
	vos_dev_write(hUart, (uint8 *) buf, (uint16) len, &written);
	#endif
#endif
}

/******************************************************************************/
/*						Local function definations						  */
/******************************************************************************/

/*!
 * \brief Converts to baseN and prints
 *
 * This function converts a decimal number to binary, octal or hexadecimal format and
 * then prints it by calling the function fn_write internally
 *
 * \param[in] n The value that is to be converted and printed
 * \param[in] base The base(i.e. 2,8,16) to which the given number is to be converted
 * \return none
 * \sa
 * \note
 * \warning
 */
static void printNumber(PRN_NUM_TYPE n, unsigned char base)
{
	unsigned char buf[MAX_DIGITS_IN_NUMBER]; // Assumes 8-bit chars.
	// unsigned long i = 0;
	unsigned char i = 0;
	char out[MAX_DIGITS_IN_NUMBER];
	int j = 0;

	// DBG(7,"Enter");
	if (n == 0)
	{
		out[0] = '0';
		fn_write(out, 1);
		return;
	}

	while (n > 0)
	{
#ifdef UNIT_TEST
		/*Not checking for negative cases to reduce footprint on embedded platform*/
		DBG(7, "n=%d  base=%d  i=%d", n, base, i);

		if (base == 0)
		{
			DBG(0, "fatal runtime exception catch: divide by 0\n");
			exit(0);
		}

#endif
		buf[i++] = (unsigned char) (n % base);
		n /= base;
	}

	for ( ; i > 0; i--)
	{
		out[j++] = (char) (buf[i - 1] < 10?'0' + buf[i - 1]:'A' + buf[i - 1] - 10);
	}

	fn_write(out, j);
	// DBG(7,"Exit");
}

