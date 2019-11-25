/*
** ethernet_client.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the TCP Client.
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

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "vos.h"

#define DEFAULT_PORT 1024

typedef struct
{
	uint16 srcPort;
	uint8  sockId;
	uint8  *ip;
	uint16 sPort;
} clientInfo;

typedef int8 (*CLIENT_CLIENT_SOCK)(clientInfo *info, uint8 sockId);
typedef int8 (*CLIENT_CLIENT_IP)(clientInfo *info, uint8 *ip, uint16 sPort);
typedef uint8 (*CLIENT_STATUS)(clientInfo *info);
typedef int8 (*CLIENT_CONNECTED)(clientInfo *info);
typedef int8 (*CLIENT_CONNECT)(clientInfo *info);
typedef void (*CLIENT_WRITE_BYTE)(clientInfo *info, uint8 data);
typedef void (*CLIENT_WRITE_STR)(clientInfo *info, const char *data);
typedef void (*CLIENT_WRITE_BUF)(clientInfo *info, const uint8 *data, uint32 len);
typedef uint8 (*CLIENT_AVAILABLE)(clientInfo *info);
typedef int8 (*CLIENT_READ)(clientInfo *info);
typedef void (*CLIENT_FLUSH)(clientInfo *info);
typedef void (*CLIENT_STOP)(clientInfo *info);

typedef struct
{
	CLIENT_CLIENT_SOCK clientSock;
	CLIENT_CLIENT_IP   clientIp;
	CLIENT_STATUS	   status;
	CLIENT_CONNECTED   connected;
	CLIENT_CONNECT	   connect;
	CLIENT_WRITE_BYTE  writeByte;
	CLIENT_WRITE_STR   writeStr;
	CLIENT_WRITE_BUF   writeBuf;
	CLIENT_AVAILABLE   available;
	CLIENT_READ		   read;
	CLIENT_FLUSH	   flush;
	CLIENT_STOP		   stop;
} tcp_client;

void client_init(tcp_client *c);
void attach_ethernet_client(VOS_HANDLE mainEthernetHandle);
void client_attach_ethernet_structure_pointer(Ethernet_t *mainEthernet);

#endif                                 /*_CLIENT_H_*/

