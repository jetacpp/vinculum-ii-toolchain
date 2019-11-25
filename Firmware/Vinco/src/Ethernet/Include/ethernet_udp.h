/*
** ethernet_udp.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for UDP.
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

#ifndef _UDP_H_
#define _UDP_H_

#include "vos.h"

#define HEADER_LEN 8

typedef void (*UDP_BEGIN)(uint16 sPort);
typedef uint32 (*UDP_AVAILABLE)(void);
typedef uint16 (*UDP_SEND)(uint8 *buf, uint16 len, uint8 *ip, uint16 sPort);
typedef uint16 (*UDP_SEND_STRING)(const char *str, uint8 *ip, uint16 sPort);
typedef uint32 (*UDP_READ)(uint8 *buf, uint16 len, uint8 *ip, uint16 *sPort);
// typedef uint32 (*UDP_READPACKET2)(uint8* buf, uint16 len);
// typedef uint32 (*UDP_READPACKET3)(char *buf, uint16 len, uint8 *ip, uint16 *sport);

typedef struct
{
	UDP_BEGIN		begin;
	UDP_AVAILABLE	available;
	UDP_SEND		send;
	UDP_SEND_STRING sendString;
	UDP_READ		read;
	//	UDP_READPACKET2 readPacket2;
	//	UDP_READPACKET3 readPacket3;
} Udp_t;

extern void udp_init(Udp_t *u);

void attach_ethernet_udp(VOS_HANDLE mainEthernetHandle);
#endif                                 /* _UDP_H_ */

