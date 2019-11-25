/*
** ethernet_server.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source file containing the definitions of the TCP Server APIs
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

#include "ethernet_w5100.h"
#include "ethernet.h"
#include "ethernet_server.h"
#include "ethernet_client.h"
//#include "string.h"
// #include "stdlib.h"
// #include "Vinco.h"

VOS_HANDLE hEthernetServer;
Ethernet_t *EthernetServer;
tcp_client *ClientServer;

/*
** s_begin
**
** Create a socket for the server and listen for incoming connections.
**
** Parameters: sPort - port to listen to
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void s_begin(uint16 sPort)
{
	uint8 sockId = 0;
	clientInfo info;
	ethernet_ioctl_cb_t cb;

	for (sockId = 0; sockId < MAX_SOCK_NUM; sockId++)
	{
		/* Will open a socket*/
		ClientServer->clientSock(&info, sockId);

		/* Check for available socket id to use */
		if (ClientServer->status(&info) == SOCK_CLOSED)
		{
			/* If the socket is closed, then use it. */
			cb.ioctl_code = VOS_IOCTL_ETHERNET_SOCKET;
			cb.socket_number = sockId;
			cb.protocol = TCP;
			cb.eth_port = sPort;
			vos_dev_ioctl(hEthernetServer, &cb);

			cb.ioctl_code = VOS_IOCTL_ETHERNET_LISTEN;
			cb.socket_number = sockId;
			vos_dev_ioctl(hEthernetServer, &cb);

			EthernetServer->server_port[sockId] = sPort;
			break;
		}
	}
}

/*
** s_accept
**
** Accept incoming connection.
**
** Parameters: sPort - port to listen to
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void s_accept(uint16 sPort)
{
	uint8 sockId = 0;
	uint8 clientIsListening = 0;
	clientInfo info;
	uint8 clientStatus = 0;

	for (sockId = 0; sockId < MAX_SOCK_NUM; sockId++)
	{
		ClientServer->clientSock(&info, sockId);

		if (EthernetServer->server_port[sockId] == sPort)
		{
			clientStatus = ClientServer->status(&info);

			if (clientStatus == SOCK_LISTEN)
			{
				clientIsListening = 1;
			}
			/* If the socket is waiting for closure and no data is available */
			else if (clientStatus == SOCK_CLOSE_WAIT && !ClientServer->available(&info))
			{
				ClientServer->stop(&info);
			}
			else
			{
				/* Nothing to do here*/
			}
		}
	}

	/*If no client is listening, then create a socket for that.*/
	if (clientIsListening == 0)
	{
		s_begin(sPort);
	}
}

/*
** s_available
**
** Gets a client which is connected to the server and has data available for
** reading. Socket can be close by called s_cstop().
**
** Parameters: sPort - Server port
**			   ret - Information of the connected client
**
**
** Returns:	void
** Requirements:
** Comments:
*/
uint8 s_available(uint16 sPort, clientInfo *ret)
{
	uint8 sockId;
	uint8 clientStatus = 0;
	clientInfo info;

	if (NULL == ret)
	{
		return FALSE;
	}

	vos_memset(ret, 0, sizeof(clientInfo));

	//	s_accept(sPort);
	for (sockId = 0; sockId < MAX_SOCK_NUM; sockId++)
	{
		ClientServer->clientSock(&info, sockId);
		clientStatus = ClientServer->status(&info);

		if (EthernetServer->server_port[sockId] == sPort &&
			(clientStatus == SOCK_ESTABLISHED || clientStatus == SOCK_CLOSE_WAIT))
		{
			if (ClientServer->available(&info))
			{
				vos_memcpy(ret, &info, sizeof(clientInfo));
				return TRUE;
			}
		}
	}

	/* Ret will be modified here */
	ClientServer->clientSock(ret, MAX_SOCK_NUM);
	return FALSE;
}

/*
** s_write_buf
**
** Writes data to all clients connected to the server.
**
** Parameters: buf - Buffer of data
**             size - Size of the data in the buffer
**			   sPort - Server port
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void s_write_buf(const uint8 *buf, uint32 size, uint16 sPort)
{
	uint8 sockId;
	uint8 clientStatus = 0;
	clientInfo info;

	//	s_accept(sPort);

	/* Traverse the socket list */
	for (sockId = 0; sockId < MAX_SOCK_NUM; sockId++)
	{
		ClientServer->clientSock(&info, sockId);
		clientStatus = ClientServer->status(&info);

		if (EthernetServer->server_port[sockId] == sPort && clientStatus == SOCK_ESTABLISHED)
		{
			ClientServer->writeBuf(&info, buf, size);
		}
	}
}

/*
** s_write_str
**
** Writes an array of characters (NULL terminated)  to all the clients connected
** to the server.
**
** Parameters: str - String
**			   sPort - Server port
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void s_write_str(const char *str, uint16 sPort)
{
	s_write_buf(str, str_len(str), sPort);
}

/*
** s_write_byte
**
** Writes a byte to all the clients connected to the server.
**
** Parameters: b - byte of data
**			   sPort - Server port
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void s_write_byte(uint8 b, uint16 sPort)
{
	s_write_buf(&b, 1, sPort);
}

/*
** server_init
**
** Initialize the function pointers of tcp_server structure.
**
** Parameters: s - tcp_server instance
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void server_init(tcp_server *s)
{
	s->begin = &s_begin;
	s->available = &s_available;
	s->writeByte = &s_write_byte;
	s->writeStr = &s_write_str;
	s->writeBuf = &s_write_buf;
}

void client_attach_structure_pointer(tcp_client *Client1)
{
	ClientServer = vos_malloc(sizeof(tcp_client));
	ClientServer = Client1;
}

void attach_ethernet_server(VOS_HANDLE mainEthernetHandle)
{
	hEthernetServer = mainEthernetHandle;
}

void server_attach_ethernet_structure_pointer(Ethernet_t *mainEthernet)
{
	EthernetServer = vos_malloc(sizeof(Ethernet_t));
	EthernetServer = mainEthernet;
}

