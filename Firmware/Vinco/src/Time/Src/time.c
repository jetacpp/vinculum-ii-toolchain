/*
** time.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Time Library for Vinco
**
** Author: FTDI
** Project: Vinco
** Module: Library Design
** Comments:
**
**
** History:
**  1 – initial version
*/

#include "time.h"
#include "vos.h"
#include "Timers.h"

#define SIZEOF_tIsr 512

vos_tcb_t *tcb2 = NULL;
uint32 milliSeconds = 0;
VOS_HANDLE hTimer0 = NULL;
uint8 timerStarted = 0;
tmr_ioctl_cb_t tmr_iocb;
tmr_context_t tmrCtx0;

uint32 us;

void time_init(uint8 timerDevNum)
{
	// Specify the timer that we wish to open, defined within the timer header file.
	tmrCtx0.timer_identifier = TIMER_0;
	// Initialize our device with the device manager.
	tmr_init(timerDevNum, &tmrCtx0);
	// Open the timer and get a handle
	hTimer0 = vos_dev_open(timerDevNum);
	// Set a tick size of 1us
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_SET_TICK_SIZE;
	tmr_iocb.param = TIMER_TICK_US;
	vos_dev_ioctl(hTimer0, &tmr_iocb);
	// Set timer to count up to 1000us
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_SET_DIRECTION;
	tmr_iocb.param = TIMER_COUNT_UP;
	vos_dev_ioctl(hTimer0, &tmr_iocb);
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_SET_COUNT;
	tmr_iocb.param = 1000;             // 1ms
	vos_dev_ioctl(hTimer0, &tmr_iocb);
	// Set continuous mode
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_SET_MODE;
	tmr_iocb.param = TIMER_MODE_CONTINUOUS;
	vos_dev_ioctl(hTimer0, &tmr_iocb);
}

/*
** millis
**
** Returns the number of milliseconds since starting an application
**
** Parameters:	None
** Returns:	Number of milliseconds since the program started (uint32)
** Comments: This function overflows (turns back to zero) after approximately 49.72 days
*/
uint32 millis()
{
	return milliSeconds;
}

/*
** micros
**
** Returns the number of microseconds since starting an application
**
** Parameters:	None
** Returns:	Number of microseconds since the program started (uint32)
** Comments: This function overflows (turns back to zero) after approximately 1.19 hours
*/
uint32 micros()
{
	uint32 microSeconds;
	tmr_ioctl_cb_t tmr_iocb;

	if (!timerStarted)
		return 0;

	/* The number of microseconds that have passed is equal to
	** (milliSeconds * 1000) + current timer count */
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_GET_CURRENT_COUNT;
	vos_dev_ioctl(hTimer0, &tmr_iocb);
	microSeconds = milliSeconds * 1000 + tmr_iocb.param;
	return microSeconds;
}

/*
** delay
**
** Pauses the program for the amount of time (in milliseconds) specified as parameter
**
** Parameters: number of milliseconds to pause
** Returns:	None
** Comments:
*/
void delay(uint16 ms)
{
	vos_delay_msecs(ms);
}

/*
** delayMicroseconds
**
** Pauses the program for the amount of time (in microseconds) specified as parameter
**
** Parameters: number of microseconds to pause
** Returns:	None
** Comments: This function is working accurately for 48Mhz clock frequency. More testing
**           will be done for 24Mhz and 12Mhz.
*/
void delayMicroseconds48Mhz(uint32 duration)
{
	/* The following instructions cause the overhead for the function call:
	** 1 PUSH: 9 cycles (this function has only one parameter)
	** 1 CALL: 10 cycles
	** 3 SP_INC/SP_DEC (one from the caller, two inside the function): 18 cycles
	** 1 RTS: 7 cycles
	** Which takes a total of 44 clock cycles.
	** For clock frequency of 48Mhz, the overhead is 0.917us
	** For clock frequency of 24Mhz, the overhead is 1.833us
	** For clock frequency of 12Mhz, the overhead is 3.666us */

	us = duration;                     /* A global variable (us) is needed for inline assembly; this instruction takes
	                                    *33 cycles to complete thanks to pipelining */

	/* For delay <= 2us, simply return because all the overhead until return add up to 2.271us */
	if (us <= 2)                       /* 1 CMP and 1 JUMP, takes 19 cycles = 0.396us to complete thanks to pipelined
		                                *execution with the previous instruction */
		return;                        /* 1 SP_INC and 1 RTS, takes 13 cycles = 0.271us to complete */

	asm
	{
		/* Subtract the time taken in previous steps and the next few needed steps */
		SUB32 us $3                    /* 18 cycles = 0.375us; after this instruction the overhead is 2.375us */

		/* The next three instructions and CLRI cause an overhead of 0.562us; the total overhead is 2.937us,
		   that's why we subtract 3 from above */
		NOP
		NOP
		//			SETI	/* Enter critical section, 1 cycles = 0.021us due to parallel execution with SUB32 */
		CMP32 us $0                    /* 15 cycles = 0.312us */
		JZ @LoopEnd48                  /* 7 cycles = 0.146us */
		/* The following loop takes 48 clock cycles = 1us to complete each iteration, so perform it (us) times */
@LoopStart48:
		JUMP @TempDst148               /* 7 cycles */
@TempDst148:
		JUMP @TempDst248               /* 7 cycles */
@TempDst248:
		NOP
		NOP
		NOP
		NOP
		NOP
		DEC32 us $1                    /* 15 cycles */
		//			CMP32	us	$0			/* 12 cycles, parallel execution with DEC32 reduces 1 flash_access_time */
		JGT @LoopStart48               /* 7 cycles */
		JUMP @LoopEnd48                /* 7 cycles */
@LoopEnd48:
		//			CLRI	/* Exit critical section, 4 cycles = 0.083us */
	}

	/*
	** Note:
	** The maximum deviance and the minimum delay that can be generated for each clock frequency are:
	** 48Mhz:   Deviance: 0.06us,   Mimimum Delay: 2us
	** 24Mhz:   Deviance: 0.5us,    Minimum Delay: 5us
	** 12Mhz:   Deviance: 1.5us,    Minimum Delay: 11us
	*/
	return;
}

void delayMicroseconds24Mhz(uint32 duration)
{
	/* The following instructions cause the overhead for the function call:
	** 1 PUSH: 9 cycles (this function has only one parameter)
	** 1 CALL: 10 cycles
	** 3 SP_INC/SP_DEC (one from the caller, two inside the function): 18 cycles
	** 1 RTS: 7 cycles
	** Which takes a total of 44 clock cycles.
	** For clock frequency of 48Mhz, the overhead is 0.917us
	** For clock frequency of 24Mhz, the overhead is 1.833us
	** For clock frequency of 12Mhz, the overhead is 3.666us */

	us = duration;                     /* A global variable (us) is needed for inline assembly; this instruction takes
	                                    *33 cycles to complete thanks to pipelining */

	/* For delay <= 5us, simply return because all the overhead until return add up to 4.541us */
	if (us <= 5)                       /* 1 CMP and 1 JUMP, takes 19 cycles = 0.792us to complete thanks to pipelined
		                                *execution with the previous instruction */
		return;                        /* 1 SP_INC and 1 RTS, takes 13 cycles = 0.542us to complete */

	asm
	{
		/* Subtract the time taken in previous steps and the next few needed steps */
		SUB32 us $6                    /* 18 cycles = 0.75us; after this instruction the overhead is 4.75us */

		/* The next three instructions and CLRI cause an overhead of 1.125us; the total overhead until now is 5.875us,
		   that's why we subtract 6 from above. The 0.125us lacked will be accounted for later. */
		//			SETI	/* Enter critical section, 1 cycles = 0.042us due to parallel execution with SUB32 */
		CMP32 us $0                    /* 15 cycles = 0.625us */
		JZ @LoopEnd24                  /* 7 cycles = 0.292us */
		SHR32 us $1
		/* The following loop takes 48 clock cycles = 2us to complete each iteration, so perform it (us/2) times */
@LoopStart24:
		JUMP @TempDst124               /* 7 cycles */
@TempDst124:
		JUMP @TempDst224               /* 7 cycles */
@TempDst224:
		NOP
		NOP
		//			NOP
		//			NOP
		//			NOP
		DEC32 us $1                    /* 15 cycles */

		// DEC32	us	$2			/* 15 cycles */
		// CMP32	us	$1			/* 12 cycles, parallel execution with DEC32 reduces 1 flash_access_time */
		JGT @LoopStart24               /* 7 cycles */
		JUMP @LoopEnd24                /* 7 cycles */
@LoopEnd24:

		/* At this point, us is either 0 or 1. A delay of 0.5us is introduced so that it gives
		   a maximum deviance of approximately 0.5us, which is acceptable */
		//		    NOP		/* 3 cycles = 0.125us, compensation for the 0.125 lacked above */
		/* The next 4 NOPs give 0.5us delay */
		//			NOP
		//			NOP
		//			NOP
		//			NOP
		//			CLRI	/* Exit critical section, 4 cycles = 0.166us */
	}

	/*
	** Note:
	** The maximum deviance and the minimum delay that can be generated for each clock frequency are:
	** 48Mhz:   Deviance: 0.06us,   Mimimum Delay: 2us
	** 24Mhz:   Deviance: 0.5us,    Minimum Delay: 5us
	** 12Mhz:   Deviance: 1.5us,    Minimum Delay: 11us
	*/
	return;
}

void delayMicroseconds12Mhz(uint32 duration)
{
	/* The following instructions cause the overhead for the function call:
	** 1 PUSH: 9 cycles (this function has only one parameter)
	** 1 CALL: 10 cycles
	** 3 SP_INC/SP_DEC (one from the caller, two inside the function): 18 cycles
	** 1 RTS: 7 cycles
	** Which takes a total of 44 clock cycles.
	** For clock frequency of 48Mhz, the overhead is 0.917us
	** For clock frequency of 24Mhz, the overhead is 1.833us
	** For clock frequency of 12Mhz, the overhead is 3.666us */

	us = duration;                     /* A global variable (us) is needed for inline assembly; this instruction takes
	                                    *33 cycles to complete thanks to pipelining */

	/* For delay <= 11us, simply return because all the overhead until return add up to 9.083us. 2us deviance can be
	 *accepted here. */
	if (us <= 11)                      /* 1 CMP and 1 JUMP, takes 19 cycles = 1.583us to complete thanks to pipelined
		                                *execution with the previous instruction */
		return;                        /* 1 SP_INC and 1 RTS, takes 13 cycles = 1.083us to complete */

	asm
	{
		/* Subtract the time taken in previous steps and the next few needed steps */
		SUB32 us $12                   /* 18 cycles = 1.5us; after this instruction the overhead is 9.5us */

		/* The next three instructions and CLRI cause an overhead of 2.25us; the total overhead until now is 11.75us,
		   that's why we subtract 12 from above. The 0.25us lacked will be accounted for later. */
		//			SETI	/* Enter critical section, 1 cycles = 0.083us due to parallel execution with SUB32 */
		CMP32 us $0                    /* 15 cycles = 1.25s */
		JZ @LoopEnd12                  /* 7 cycles = 0.584us */
		/* The following loop takes 48 clock cycles = 4us to complete each iteration, so perform it (us/4) times */
@LoopStart12:
		JUMP @TempDst112               /* 7 cycles */
@TempDst112:
		JUMP @TempDst212               /* 7 cycles */
@TempDst212:
		DEC32 us $4                    /* 15 cycles */
		//			CMP32	us	$3			/* 12 cycles, parallel execution with DEC32 reduces 1 flash_access_time */
		NOP
		NOP
		NOP
		NOP
		JGT @LoopStart12               /* 7 cycles */
		JUMP @LoopEnd12                /* 7 cycles */
@LoopEnd12:

		/* At this point, us is either 0, 1, 2 or 3. A delay of 1.5us is introduced so that it gives
		   a maximum deviance of approximately 1.5us, which is acceptable */
		//		    NOP		/* 3 cycles = 0.25us, compensation for the 0.25us lacked above */
		/* The next 6 NOPs give the delay of 1.5us */
		NOP                            /* 3 cycles = 0.25us */
		NOP                            /* 3 cycles = 0.25us */
		NOP                            /* 3 cycles = 0.25us */
		NOP                            /* 3 cycles = 0.25us */
		NOP                            /* 3 cycles = 0.25us */
		NOP                            /* 3 cycles = 0.25us */
		//			CLRI	/* Exit critical section, 4 cycles = 0.332us */
	}

	/*
	** Note:
	** The maximum deviance and the minimum delay that can be generated for each clock frequency are:
	** 48Mhz:   Deviance: 0.06us,   Mimimum Delay: 2us
	** 24Mhz:   Deviance: 0.5us,    Minimum Delay: 5us
	** 12Mhz:   Deviance: 1.5us,    Minimum Delay: 11us
	*/
	return;
}

void timerInterruptISR(void)
{
	tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_START;
	vos_dev_ioctl(hTimer0, &tmr_iocb);
	timerStarted = 1;

	while (1)
	{
		// Block until the timer cycle has completed
		tmr_iocb.ioctl_code = VOS_IOCTL_TIMER_WAIT_ON_COMPLETE;
		vos_dev_ioctl(hTimer0, &tmr_iocb);
		// When the interrupt is fired, 1ms has passed, so add 1 to milliSeconds
		milliSeconds += 1;
	}
}

void tmr_create_thread()
{
	tcb2 = vos_create_thread(31, SIZEOF_tIsr, &timerInterruptISR, 0);
}

