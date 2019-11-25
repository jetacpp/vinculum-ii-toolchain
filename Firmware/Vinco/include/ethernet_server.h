/*
** ethernet_server.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Header file containing definitions for the TCP Server.
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

#ifndef _SERVER_H_
#define _SERVER_H_

#include "vos.h"
#include "ethernet_client.h"

#define SUCCESS 0
#define FAILURE -1

#define TRUE	1
#define FALSE	0

typedef void (*SERVER_BEGIN)(uint16 sPort);
typedef uint8 (*SERVER_AVAILABLE)(uint16 sPort, clientInfo *ret);
typedef void (*SERVER_WRITE_BYTE)(uint8 b, uint16 sPort);
typedef void (*SERVER_WRITE_STR)(const char *str, uint16 sPort);
typedef void (*SERVER_WRITE_BUF)(const uint8 *buf, uint32 size, uint16 sPort);

typedef struct
{
	SERVER_BEGIN	  begin;
	SERVER_AVAILABLE  available;
	SERVER_WRITE_BYTE writeByte;
	SERVER_WRITE_STR  writeStr;
	SERVER_WRITE_BUF  writeBuf;
} tcp_server;

extern void server_init(tcp_server *s);
void attach_ethernet_server(VOS_HANDLE mainEthernetHandle);
void client_attach_structure_pointer(tcp_client *Client1);
void server_attach_ethernet_structure_pointer(Ethernet_t *mainEthernet);

#endif                                 /* _SERVER_H_ */

