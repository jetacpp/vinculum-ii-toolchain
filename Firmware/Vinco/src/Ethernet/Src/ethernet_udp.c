/*
** ethernet_udp.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source file containing the definitions of the UDP functions
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

//#include "string.h"
#include "ethernet_udp.h"
#include "ethernet.h"
// #include "Vinco.h"

VOS_HANDLE hEthernetUdp;
uint8 gSockId = 0;

/*
** u_begin
**
** Create a udp socket.
**
** Parameters: sPort - UDP port
**			   s - socket number
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void u_begin(uint16 sPort, uint8 s)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_SOCKET;
	gSockId = s;
	cb.socket_number = gSockId;
	cb.protocol = UDP;
	cb.eth_port = sPort;
	vos_dev_ioctl(hEthernetUdp, &cb);
}

/*
** u_available
**
** Check the number of bytes available for this socket.
**
** Parameters: None
**
**
** Returns:	Number of bytes
** Requirements:
** Comments:
*/
uint32 u_available(void)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_GET_RX_RCVD_SIZE;
	cb.socket_number = gSockId;
	vos_dev_ioctl(hEthernetUdp, &cb);
	return cb.rxRcvdSize;
}

/*
** u_sendPacket1
**
** Sends a buffer of data to the specified IP address and port
**
** Parameters: buf - buffer of data
**			   len - size of the data in the buffer
**			   ip - IP address
**			   sPort - port
**
**
** Returns:	Number of bytes
** Requirements:
** Comments:
*/
uint16 u_send(uint8 *buf, uint16 len, uint8 *ip, uint16 sPort)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_SENDTO;
	cb.socket_number = gSockId;
	cb.write_buffer = buf;
	cb.write_buf_len = len;
	cb.remote_dev_ip_addr = ip;
	cb.remote_dev_port = &sPort;

	return vos_dev_ioctl(hEthernetUdp, &cb);
}

/*
** u_sendPacket2
**
** Sends a string to the specified IP address and port
**
** Parameters: str - string
**			   ip - IP address
**			   sPort - port
**
**
** Returns:	Number of bytes
** Requirements:
** Comments:
*/
uint16 u_sendString(const char *str, uint8 *ip, uint16 sPort)
{
	uint16 sentBytes = 0;
	uint16 strLen = 0;

	if (0 != str)
	{
		strLen = str_len(str);
		sentBytes = u_send((uint8 *) str, strLen, ip, sPort);
	}

	return sentBytes;
}

uint32 u_read(uint8 *buf, uint16 len, uint8 *ip, uint16 *sPort)
{
	ethernet_ioctl_cb_t cb;
	uint16 readBytes = 0;

	do
	{
		if (len < 0)
		{
			readBytes = 0;
			break;
		}

		cb.ioctl_code = VOS_IOCTL_ETHERNET_RECVFROM;
		cb.socket_number = gSockId;
		cb.read_buffer = buf;
		cb.read_buf_len = len;
		cb.remote_dev_ip_addr = ip;
		cb.remote_dev_port = sPort;
		vos_dev_ioctl(hEthernetUdp, &cb);
		readBytes = cb.rcvd_bytes;
	}
	while (0);

	return readBytes;
}

/*
uint32 u_readPacket2(uint8* buf, uint16 len)
{
    uint8 ip[4];
    uint16 sPort;

    return u_readPacket1(buf, len, ip, &sport);
}

uint32 u_readPacket3(char *buf, uint16 len, uint8 *ip, uint16 *sport)
{
    return u_readPacket1((uint8*)buf, len, ip, sPort);
}
*/

void udp_init(Udp_t *u)
{
	u->begin = &u_begin;
	u->available = &u_available;
	u->send = &u_send;
	u->sendString = &u_sendString;
	u->read = &u_read;
	//	u->readPacket2	= &u_readPacket2;
	//	u->readPacket3	= &u_readPacket3;
}

void attach_ethernet_udp(VOS_HANDLE mainEthernetHandle)
{
	hEthernetUdp = mainEthernetHandle;
}

