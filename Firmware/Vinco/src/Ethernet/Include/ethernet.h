/*
** ethernet.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the Ethernet Library.
**
** Author: FTDI
** Project: Vinco
** Module: Vinco
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef _CORE_H_
#define _CORE_H_

#include "vos.h"
#include "Ethernet_W5100.h"

#define ETHERNET_LIB_SUCCESS 0
#define ETHERNET_LIB_FAILURE -1

typedef void (*CORE_BEGIN1)(uint8 *mac, uint8 *ip);
typedef void (*CORE_BEGIN2)(uint8 *mac, uint8 *ip, uint8 *gateway);
typedef void (*CORE_BEGIN3)(uint8 *mac, uint8 *ip, uint8 *gateway, uint8 *subnet);

/* Support for Ethernet Interrupt */
typedef void (*SET_INTERRUPT_MASK)(uint8 mask);
typedef uint8 (*GET_INTERRUPT_TYPE)(void);
typedef void (*CLEAR_INTERRUPT_FLAG)(uint8 interruptFlag);

typedef struct
{
	CORE_BEGIN1			 beginMacIp;
	CORE_BEGIN2			 beginMacIpGw;
	CORE_BEGIN3			 beginMacIpGwSn;
	/* It's this module who will handle the list of the ports */
	uint16				 server_port[MAX_SOCK_NUM];
	// uint16 state[MAX_SOCK_NUM];

	/* Support for Ethernet Interrupt */
	SET_INTERRUPT_MASK	 setInterruptMask;
	GET_INTERRUPT_TYPE	 getInterruptType;
	CLEAR_INTERRUPT_FLAG clearInterruptFlag;
} Ethernet_t;

void ethernetlib_init(Ethernet_t *e);
void attach_ethernet_core(VOS_HANDLE mainEthernetHandle);
void ethernet_attach_spim_handle(VOS_HANDLE mainSpiMasterHandle);
uint16 str_len(const char *str);

#endif                                 /* _CORE_H_ */

