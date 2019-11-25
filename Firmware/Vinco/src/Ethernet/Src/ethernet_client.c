/*
** ethernet_client.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source file containing the definitions of the TCP Client APIs
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
#include "ethernet_client.h"
//#include "string.h"
// #include "stdlib.h"
// #include "Vinco.h"

VOS_HANDLE hEthernetClient;
Ethernet_t *EthernetClient;
uint8 c_available(clientInfo *info);

/*
** c_client_sock
**
** Creates a client which can connect to the socket number specified.
** Client information will be updated when the function exits.
**
** Parameters: info - client information
**			   sockId - socket number to create
**
**
** Returns: ETHERNET_LIB_SUCCESS, ETHERNET_LIB_FAILURE
** Requirements:
** Comments:
*/
int8 c_client_sock(clientInfo *info, uint8 sockId)
{
	uint8 status = ETHERNET_LIB_FAILURE;
	ethernet_ioctl_cb_t cb;

	if (NULL != info)
	{
		status = ETHERNET_LIB_SUCCESS;

		info->srcPort = DEFAULT_PORT;
		info->sockId = sockId;
		info->ip = NULL;
		info->sPort = 0;

		/*
		        cb.ioctl_code = VOS_IOCTL_ETHERNET_SOCKET;
		        cb.socket_number = info->sockId;
		        cb.protocol = TCP;
		        cb.eth_port = info->sport;
		        vos_dev_ioctl(hEthernetClient, &cb);
		*/
	}

	return status;
}

/*
** c_client_ip
**
** Creates a client which can connect to the specified ip address and port.
** Client information will be updated when the function exits.
**
** Parameters: info - client information
**			   ip - IP address
**			   sport - port number
**
**
** Returns: ETHERNET_LIB_SUCCESS, ETHERNET_LIB_FAILURE
** Requirements:
** Comments:
*/
int8 c_client_ip(clientInfo *info, uint8 *ip, uint16 sPort)
{
	uint8 status = ETHERNET_LIB_FAILURE;
	ethernet_ioctl_cb_t cb;

	if (NULL != info)
	{
		status = ETHERNET_LIB_SUCCESS;

		info->srcPort = DEFAULT_PORT;
		info->sockId = MAX_SOCK_NUM;
		info->ip = ip;
		info->sPort = sPort;

		/*
		        cb.ioctl_code = VOS_IOCTL_ETHERNET_SOCKET;
		        cb.socket_number = info->sockId;
		        cb.protocol = TCP;
		        cb.eth_port = info->sport;
		        vos_dev_ioctl(hEthernetClient, &cb);
		*/
	}

	return status;
}

/*
** c_status
**
** Check the status of the socket.
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: Socket status
** Requirements:
** Comments:
*/
uint8 c_status(clientInfo *info)
{
	uint8 status = SOCK_CLOSED;
	ethernet_ioctl_cb_t cb;

	if (NULL != info)
	{
		if (info->sockId == MAX_SOCK_NUM)
		{
			status = SOCK_CLOSED;
		}
		else
		{
			cb.ioctl_code = VOS_IOCTL_ETHERNET_GET_SOCK_STATUS;
			cb.socket_number = info->sockId;
			vos_dev_ioctl(hEthernetClient, &cb);
			status = cb.sock_status;
		}
	}

	return status;
}

/*
** c_connected
**
** Checks whether the client is connected or not. Note that a client is considered
** connected if the connection has been closed but there is still unread data.
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: ETHERNET_LIB_SUCCESS - connected, ETHERNET_LIB_FAILURE - unconnected
** Requirements:
** Comments:
*/
int8 c_connected(clientInfo *info)
{
	uint8 status = ETHERNET_LIB_SUCCESS;
	uint8 clientStatus = SOCK_CLOSED;

	if (NULL != info)
	{
		if (info->sockId == MAX_SOCK_NUM)
		{
			status = ETHERNET_LIB_FAILURE;
			return status;
		}

		clientStatus = c_status(info);

		if (clientStatus == SOCK_LISTEN || clientStatus == SOCK_CLOSED || clientStatus == SOCK_FIN_WAIT ||
			(clientStatus == SOCK_CLOSE_WAIT && !c_available(info)))
		{
			status = ETHERNET_LIB_FAILURE;
		}
	}

	return status;
}

/*
** c_connect
**
** Connects to the server based on the IP address and port in the client
** information
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: ETHERNET_LIB_SUCCESS, ETHERNET_LIB_FAILURE
** Requirements:
** Comments:
*/
int8 c_connect(clientInfo *info)
{
	uint8 sockId;
	uint8 ret = ETHERNET_LIB_FAILURE;
	uint8 clientStatus = 0;
	ethernet_ioctl_cb_t cb;

	if (NULL == info)
	{
		return ETHERNET_LIB_FAILURE;
	}

	if (info->sockId != MAX_SOCK_NUM)
	{
		return ETHERNET_LIB_FAILURE;
	}

	for (sockId = 0; sockId < MAX_SOCK_NUM; sockId++)
	{
		cb.ioctl_code = VOS_IOCTL_ETHERNET_GET_SOCK_STATUS;
		cb.socket_number = sockId;
		vos_dev_ioctl(hEthernetClient, &cb);
		ret = cb.sock_status;

		if (ret == SOCK_CLOSED || ret == SOCK_FIN_WAIT)
		{
			info->sockId = sockId;
			break;
		}
	}

	info->srcPort++;

	if (info->srcPort == 0)
	{
		info->srcPort = DEFAULT_PORT;
	}

	/* Create socket */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_SOCKET;
	cb.socket_number = info->sockId;
	cb.protocol = TCP;
	cb.eth_port = info->sPort;
	vos_dev_ioctl(hEthernetClient, &cb);

	/* Connect */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_CONNECT;
	cb.socket_number = info->sockId;
	cb.remote_dev_ip_addr = info->ip;
	cb.remote_dev_port = &(info->sPort);
	vos_dev_ioctl(hEthernetClient, &cb);

	clientStatus = c_status(info);

	while (clientStatus != SOCK_ESTABLISHED)
	{
		vos_delay_msecs(1);
		clientStatus = c_status(info);

		if (clientStatus == SOCK_CLOSED)
		{
			return ETHERNET_LIB_FAILURE;
		}

		clientStatus = c_status(info);
	}

	return ETHERNET_LIB_SUCCESS;
}

/*
** c_available
**
** Returns the number of bytes available for reading.
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: Number of bytes available for the client
** Requirements:
** Comments:
*/
uint8 c_available(clientInfo *info)
{
	uint8 status = 0;
	ethernet_ioctl_cb_t cb;

	if (NULL != info)
	{
		if (info->sockId != MAX_SOCK_NUM)
		{
			cb.ioctl_code = VOS_IOCTL_ETHERNET_GET_RX_RCVD_SIZE;
			cb.socket_number = info->sockId;
			vos_dev_ioctl(hEthernetClient, &cb);
			status = cb.rxRcvdSize;
		}
	}

	return status;
}

/*
** c_read
**
** Read the next byte received from the server.
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: Data (byte)
** Requirements:
** Comments:
*/
int8 c_read(clientInfo *info)
{
	uint32 readByte = 0;
	// uint16 rcvdSize;
	ethernet_ioctl_cb_t cb;

	if (NULL != info)
	{
		if (ETHERNET_LIB_FAILURE == c_available(info))
		{
			return readByte;
		}

		cb.ioctl_code = VOS_IOCTL_ETHERNET_RECV;
		cb.socket_number = info->sockId;
		cb.read_buffer = &readByte;
		cb.read_buf_len = 1;
		vos_dev_ioctl(hEthernetClient, &cb);
	}

	return readByte;
}

/*
** c_read
**
** Discard the bytes of data that have been written to the client.
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: void
** Requirements:
** Comments:
*/
void c_flush(clientInfo *info)
{
	while (ETHERNET_LIB_SUCCESS == c_available(info))
	{
		c_read(info);
	}
}

/*
** c_stop
**
** Disconnect the client from the server
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**
**
** Returns: void
** Requirements:
** Comments:
*/
void c_stop(clientInfo *info)
{
	ethernet_ioctl_cb_t cb;
	uint32 timer;

	if (info->sockId == MAX_SOCK_NUM)
	{
		return;
	}

	cb.ioctl_code = VOS_IOCTL_ETHERNET_DISCONNECT;
	cb.socket_number = info->sockId;
	vos_dev_ioctl(hEthernetClient, &cb);

	// Not sure if this is really needed. Comment it temporarily.

	/*
	timer = millis();
	while((c_status(info) != SOCK_CLOSED) && millis() - timer < 1000)
	{
	    delay(1);
	}
	*/

	if (c_status(info) != SOCK_CLOSED)
	{
		cb.ioctl_code = VOS_IOCTL_ETHERNET_CLOSE;
		cb.socket_number = info->sockId;
		vos_dev_ioctl(hEthernetClient, &cb);
	}

	/* Update the list of ports in the Ethernet core */
	EthernetClient->server_port[info->sockId] = 0;
	info->sockId = MAX_SOCK_NUM;
}

/*
** c_write_buf
**
** Write a buffer of data to the server
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**			   data - data buffer
**			   len - size of data
**
**
** Returns: void
** Requirements:
** Comments:
*/
void c_write_buf(clientInfo *info, const uint8 *data, uint32 len)
{
	ethernet_ioctl_cb_t cb;

	if ((MAX_SOCK_NUM != info->sockId) && (NULL != info) && (NULL != data))
	{
		cb.ioctl_code = VOS_IOCTL_ETHERNET_SEND;
		cb.socket_number = info->sockId;
		cb.write_buffer = data;
		cb.write_buf_len = len;
		vos_dev_ioctl(hEthernetClient, &cb);
	}
}

/*
** c_write_byte
**
** Write a byte of data to the server
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**			   data - byte
**
**
** Returns: void
** Requirements:
** Comments:
*/
void c_write_byte(clientInfo *info, uint8 data)
{
	if (NULL != info)
	{
		c_write_buf(info, &data, 1);
	}
}

/*
** c_write_str
**
** Write a string (NULL terminated)  to the server
**
** Parameters: info - client information (which is returned from c_client_sock()
**				      or c_client_ip())
**			   data - string
**
** Returns: void
** Requirements:
** Comments:
*/
void c_write_str(clientInfo *info, const char *data)
{
	if ((NULL != info) && (NULL != data))
	{
		c_write_buf(info, data, str_len(data));
	}
}

/*
** client_init
**
** Initialize the function pointers of tcp_client structure.
**
** Parameters: c - tcp_client instance
**
** Returns: void
** Requirements:
** Comments:
*/
void client_init(tcp_client *c)
{
	c->clientSock = &c_client_sock;
	c->clientIp = &c_client_ip;
	c->status = &c_status;
	c->connected = &c_connected;
	c->connect = &c_connect;
	c->writeByte = &c_write_byte;
	c->writeStr = &c_write_str;
	c->writeBuf = &c_write_buf;
	c->available = &c_available;
	c->read = &c_read;
	c->flush = &c_flush;
	c->stop = &c_stop;
}

void attach_ethernet_client(VOS_HANDLE mainEthernetHandle)
{
	hEthernetClient = mainEthernetHandle;
}

void client_attach_ethernet_structure_pointer(Ethernet_t *mainEthernet)
{
	EthernetClient = vos_malloc(sizeof(Ethernet_t));
	EthernetClient = mainEthernet;
}

