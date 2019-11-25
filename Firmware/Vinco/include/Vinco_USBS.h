/*
** Vinco_USBS.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing function pointers for the USB Slave library.
**
** Author: FTDI
** Project: Vinco
** Module: Vinco USB Slave Library
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#include "vos.h"
#include "USB.h"
#include "USBSlave.h"

#ifndef __USBSLAVE_LIB_H__
#define __USBSLAVE_LIB_H__

// endpoint type definitions
#define USBSLAVE_CONTROL_IN_ENDPOINT  1
#define USBSLAVE_CONTROL_OUT_ENDPOINT 2
#define USBSLAVE_BULK_IN_ENDPOINT	  3
#define USBSLAVE_BULK_OUT_ENDPOINT	  4
#define USBSLAVE_ISO_IN_ENDPOINT	  5
#define USBSLAVE_ISO_OUT_ENDPOINT	  6
#define USBSLAVE_INT_IN_ENDPOINT	  7
#define USBSLAVE_INT_OUT_ENDPOINT	  8

typedef uint8 (*INIT)(void);
typedef uint8 (*GET_STATE)(void);
typedef uint8 (*SET_CONFIG)(uint8);
typedef uint8 (*GET_CONFIG)(void);
typedef uint8 (*SET_ADDR)(uint8);
typedef uint8 (*SETUP_TRANSFER)(usbslave_ep_handle_t, uint8 *, int16, int16 *);
typedef uint8 (*WAIT_SETUP_RCVD)(uint8 *, int16, int16 *);
typedef uint8 (*INIT_EP)(uint8, usbslave_ep_handle_t *, uint8);
typedef uint8 (*SET_EP_MAX_PCKT_SIZE)(usbslave_ep_handle_t, uint32);
typedef uint8 (*TRANSFER)(usbslave_ep_handle_t, uint8 *, int16, int16 *);
typedef uint8 (*DISCONNECT)(void);
typedef uint8 (*STALL_EP)(uint8);
typedef uint8 (*CLEAR_EP)(uint8);
typedef int8 (*EP_STATE)(uint8);
typedef uint8 (*DISABLE_INTERRUPTS)(void);
typedef uint8 (*ENABLE_INTERRUPTS)(void);
typedef uint8 (*WAIT_ON_USB_SUSPEND)(void);
typedef uint8 (*WAIT_ON_USB_RESUME)(void);
typedef uint8 (*ISSUE_REMOTE_WAKEUP)(void);
typedef uint8 (*SET_LOW_SPEED)(void);

typedef struct _stUSBSlave_t
{
	INIT				 init;
	GET_STATE			 getState;
	SET_CONFIG			 setConfiguration;
	GET_CONFIG			 getConfiguration;
	SET_ADDR			 setAddress;
	SETUP_TRANSFER		 setupTransfer;
	WAIT_SETUP_RCVD		 waitSetupRcvd;
	INIT_EP				 initEp;
	SET_EP_MAX_PCKT_SIZE setEpMaxPcktSize;
	TRANSFER			 transfer;
	DISCONNECT			 disconnect;
	STALL_EP			 stallEp;
	CLEAR_EP			 clearEp;
	EP_STATE			 epState;
	DISABLE_INTERRUPTS	 disableInterrupts;
	ENABLE_INTERRUPTS	 enableInterrupts;
	WAIT_ON_USB_SUSPEND	 waitOnUSBSuspend;
	WAIT_ON_USB_RESUME	 waitOnUSBResume;
	ISSUE_REMOTE_WAKEUP	 issueRemoteWakeup;
	SET_LOW_SPEED		 setLowSpeed;
} stUSBSlave_t;

extern stUSBSlave_t USBSlave;

/******************************************************************************/
/*								   Functions							      */
/******************************************************************************/
/* This function has to be called in main.c before the USB Slave Library is used */
void usbslave_struct_init(stUSBSlave_t *);

#endif                                 /* __USBSLAVE_LIB_H__ */
