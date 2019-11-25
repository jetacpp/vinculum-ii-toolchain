/*
** ethernet_w5100.h
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Company Confidential
**
** h Header file for Vinculum II Ethernet driver
** Main module
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II Ethernet Driver
** Requires: VOS
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __ETHERNETW5100_H__
#define __ETHERNETW5100_H__

#include "vos.h"
#define ETHERNET_W5100_VERSION_STRING "2.0.2"

typedef unsigned char SOCKET;

// Ethernet IOCTL definitions
#define VOS_IOCTL_ETHERNET_W5100_INIT				1
#define VOS_IOCTL_ETHERNET_SET_GATEWAY_IP			2
#define VOS_IOCTL_ETHERNET_GET_GATEWAY_IP			3
#define VOS_IOCTL_ETHERNET_SET_SUBNET_MASK			4
#define VOS_IOCTL_ETHERNET_GET_SUBNET_MASK			5
#define VOS_IOCTL_ETHERNET_SET_MAC_ADDRESS			6
#define VOS_IOCTL_ETHERNET_GET_MAC_ADDRESS			7
#define VOS_IOCTL_ETHERNET_SET_IP_ADDRESS			8
#define VOS_IOCTL_ETHERNET_GET_IP_ADDRESS			9
#define VOS_IOCTL_ETHERNET_SET_RETRANSMISSION_TIME	10
#define VOS_IOCTL_ETHERNET_SET_RETRANSMISSION_COUNT 11
#define VOS_IOCTL_ETHERNET_SOCKET					12
#define VOS_IOCTL_ETHERNET_CLOSE					13
#define VOS_IOCTL_ETHERNET_LISTEN					14
#define VOS_IOCTL_ETHERNET_CONNECT					15
#define VOS_IOCTL_ETHERNET_DISCONNECT				16
#define VOS_IOCTL_ETHERNET_SEND						17
#define VOS_IOCTL_ETHERNET_RECV						18
#define VOS_IOCTL_ETHERNET_SENDTO					19
#define VOS_IOCTL_ETHERNET_RECVFROM					20
#define VOS_IOCTL_ETHERNET_GET_SOCK_STATUS			21
#define VOS_IOCTL_ETHERNET_GET_TX_FREE_SIZE			22
#define VOS_IOCTL_ETHERNET_GET_RX_RCVD_SIZE			23
#define VOS_IOCTL_ETHERNET_SET_INTERRUPT_MASK		24
#define VOS_IOCTL_ETHERNET_GET_INTERRUPT_TYPE		25
#define VOS_IOCTL_ETHERNET_CLEAR_INTERRUPT_REG		26
#define VOS_IOCTL_ETHERNET_ATTACH_SPI_M_HANDLE		27
#define VOS_IOCTL_ETHERNET_DETACH_SPI_M_HANDLE		28

// Ethernet socket definitions
#define ETHERNET_SOCKET_0							0
#define ETHERNET_SOCKET_1							1
#define ETHERNET_SOCKET_2							2
#define ETHERNET_SOCKET_3							3

#define MAX_SOCK_NUM								4

#define TCP_PORT									80   // TCP/IP Port

// Sn_MR (Socket n Mode Register) values (n is socket number: 0, 1, 2, 3).
#define CLOSE										0x00 // Unused socket
#define TCP											0x01 // TCP
#define UDP											0x02 // UDP
#define IPRAW										0x03 // IP LAYER RAW SOCK
#define MACRAW										0x04 // MAC LAYER RAW SOCK
#define PPPOE										0x05 // PPPoE
#define ND											0x20 // No Delayed Ack(TCP) flag
#define MULTI										0x80 // Support multicating

// Sn_SR (Socket n Status Register) values (n is socket number: 0, 1, 2, 3)
#define SOCK_CLOSED									0x00 // Closed
#define SOCK_INIT									0x13 // Init state
#define SOCK_LISTEN									0x14 // Listen state
#define SOCK_SYNSENT								0x15 // Connection state
#define SOCK_SYNRECV								0x16 // Connection state
#define SOCK_ESTABLISHED							0x17 // Success to connect
#define SOCK_FIN_WAIT								0x18 // Closing state
#define SOCK_CLOSING								0x1A // Closing state
#define SOCK_TIME_WAIT								0x1B // Closing state
#define SOCK_CLOSE_WAIT								0x1C // Closing state
#define SOCK_LAST_ACK								0x1D // Closing state
#define SOCK_UDP									0x22 // UDP socket
#define SOCK_IPRAW									0x32 // IP raw mode socket
#define SOCK_MACRAW									0x42 // MAC raw mode socket
#define SOCK_PPPOE									0x5F // PPPOE socket

// IR (Interrupt Register) values
#define IR_CONFLICT									0x80 // IP Conflict
#define IR_UNREACH									0x40 // Destination unreachable
#define IR_PPPOE									0x20 // PPPoE Connection Close
#define IR_S3_INT									0x08 // Occurrence of Socket 3 Interrupt
#define IR_S2_INT									0x04 // Occurrence of Socket 2 Interrupt
#define IR_S1_INT									0x02 // Occurrence of Socket 1 Interrupt
#define IR_S0_INT									0x01 // Occurrence of Socket 0 Interrupt
#define IR_SOCKS									0x0F // Enable all socket interrupts

// Sn_IR (Socket n Interrupt Register) values
#define IR_SEND_OK									0x10 // Send operation is completed
#define IR_TIMEOUT									0x08 // Timeout occurs during connection establishment / termination
	                                                     // / data transmission
#define IR_RECV										0x04 // W5100 receives data / received data remains after CMD_RECV
	                                                     // command
#define IR_DISCON									0x02 // Connection termination is requested or finished
#define IR_CON										0x01 // Connection is established

// Chip select indentifiers for use in attch IOCTL
#define     ETHERNET_CHIP_SELECT_0					0x00 // Use SPI Master slave select 0
#define     ETHERNET_CHIP_SELECT_1					0x01 // Use SPI Master slave select 1

enum ETHERNET_STATUS
{
	ETHERNET_STATUS_OK = 0x00,
	ETHERNET_STATUS_SOCKET_CREATION_FAILED,
	ETHERNET_STATUS_LISTEN_FAILED,
	ETHERNET_STATUS_INVALID_SERVER_ADDRESS,
	ETHERNET_STATUS_SENDING_FAILED,
	ETHERNET_STATUS_RECEIVING_FAILED,
	ETHERNET_STATUS_INVALID_IOCTL_CODE,
	ETHERNET_STATUS_INVALID_PARAMETER,
	ETHERNET_STATUS_FATAL_ERROR = 0xFF
};

// Ethernet device
typedef struct _ethernet_device_t
{
	unsigned char pnum;
	unsigned char addr;
} ethernet_device_t;

// IOCTL control block
typedef struct _ethernet_ioctl_cb_t
{
	unsigned char			  ioctl_code;
	ethernet_device_t 		  handle;
	SOCKET			  		  socket_number;

	unsigned char			  interrupt_type;
	unsigned char			  interrupt_mask;

	unsigned char			  *mac_addr;       // local device mac address
	unsigned char			  *gtw_addr;       // local device gateway address
	unsigned char			  *sub_mask;       // local device subnet mask
	unsigned char			  *ip_addr;        // local device ip address
	unsigned short			  eth_port;        // local device ethernet port number

	unsigned char			  protocol;
	unsigned char			  retry;
	unsigned short			  timeout;
	unsigned short			  rcvd_bytes;

	unsigned char			  *read_buffer;
	unsigned short			  read_buf_len;        // local device data buffer length

	unsigned char			  *write_buffer;
	unsigned short			  write_buf_len;       // local device data buffer length

	unsigned char			  *remote_dev_ip_addr; // remote device ip address
	unsigned short			  *remote_dev_port;    // remote device port

	unsigned char			  sock_status;         // socket status, check status definitions above

	unsigned short			  txFreeSize;
	unsigned short			  rxRcvdSize;

	VOS_HANDLE		  		  spi_master_handle;
	unsigned char			  chip_select_identifier;
} ethernet_ioctl_cb_t;

/******************************************************************************/
/*								Global variables							  */
/******************************************************************************/

/******************************************************************************/
/*								   Functions							      */
/******************************************************************************/
/* This function has to be called in main.c before the Ethernet Library is used */
unsigned char ethernet_init(unsigned char devNum);

#endif                                 /* __ETHERNETW5100_H__ */
