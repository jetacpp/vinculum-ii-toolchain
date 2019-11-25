/*
** ethernet.c
**
** Copyright © 2011 Future Technology Devices International Limited
**
** Source file containing the definitions of the Ethernet Library functions.
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
#include "ethernet.h"
#include "vos.h"
// #include "stdlib.h"

#define BUF_SIZE 4

VOS_HANDLE hEthernetCore;
VOS_HANDLE hSPIMasterCore;

/*
** e_begin_mac_ip_gw_sn
**
** Initialize the Ethernet Library given the mac address, ip address, gateway
** and subnet.
**
** Parameters: mac - MAC (Media Access Control) address (6 bytes), Ethernet
**			         hardware address of the shield
**			   ip - IP address (4 bytes)
**			   gateway - IP address of the network gateway (4 bytes).
**			   subnet - subnet mask of the network (4 bytes)
**
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void e_begin_mac_ip_gw_sn(uint8 *mac, uint8 *ip, uint8 *gateway, uint8 *subnet)
{
	ethernet_ioctl_cb_t cb;

	//	hEthernet = vos_dev_open(ETHERNET);

	/* Attach the SPI Master handle to the Ethernet driver */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_ATTACH_SPI_M_HANDLE;
	cb.spi_master_handle = hSPIMasterCore;
	cb.chip_select_identifier = ETHERNET_CHIP_SELECT_1;
	vos_dev_ioctl(hEthernetCore, &cb);

	/* Initialize the w5100 chip */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_W5100_INIT;
	vos_dev_ioctl(hEthernetCore, &cb);

	/* Set the mac address */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_SET_MAC_ADDRESS;
	cb.mac_addr = mac;
	vos_dev_ioctl(hEthernetCore, &cb);

	/* Set the IP address */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_SET_IP_ADDRESS;
	cb.ip_addr = ip;
	vos_dev_ioctl(hEthernetCore, &cb);

	/* Set the gateway address */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_SET_GATEWAY_IP;
	cb.gtw_addr = gateway;
	vos_dev_ioctl(hEthernetCore, &cb);

	/* Set the subnet mask */
	cb.ioctl_code = VOS_IOCTL_ETHERNET_SET_SUBNET_MASK;
	cb.sub_mask = subnet;
	vos_dev_ioctl(hEthernetCore, &cb);
}

/*
** e_begin_mac_ip_gw
**
** Initialize the Ethernet Library given the mac address, ip address and gateway.
** The subnet mask is set to 255.255.255.0.
**
** Parameters: mac - MAC (Media Access Control) address (6 bytes), Ethernet
**			         hardware address of the shield
**			   ip - IP address (4 bytes)
**			   gateway - IP address of the network gateway (4 bytes)
**
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void e_begin_mac_ip_gw(uint8 *mac, uint8 *ip, uint8 *gateway)
{
	/* Default subnet */
	uint8 subnet[BUF_SIZE] = {255, 255, 255, 0};

	e_begin_mac_ip_gw_sn(mac, ip, gateway, subnet);
}

/*
** e_begin_mac_ip
**
** Initialize the Ethernet Library given the mac address and ip address.
** The subnet mask is set to 255.255.255.0 while the gateway is set to the
** value of the IP address with the last octet set to 1.
**
** Parameters: mac - MAC (Media Access Control) address (6 bytes), Ethernet
**			         hardware address of the shield
**			   ip - IP address (4 bytes)
**
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void e_begin_mac_ip(uint8 *mac, uint8 *ip)
{
	uint8 gateway[BUF_SIZE];

	/* Use the ip as the gateway */
	gateway[0] = ip[0];
	gateway[1] = ip[1];
	gateway[2] = ip[2];
	gateway[3] = 1;

	e_begin_mac_ip_gw(mac, ip, gateway);
}

void e_setInterruptMask(uint8 mask)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_SET_INTERRUPT_MASK;
	cb.interrupt_mask = mask;
	vos_dev_ioctl(hEthernetCore, &cb);

	return;
}

uint8 e_getInterruptType(void)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_GET_INTERRUPT_TYPE;
	vos_dev_ioctl(hEthernetCore, &cb);

	return cb.interrupt_type;
}

void e_clearInterruptFlag(uint8 interruptFlag)
{
	ethernet_ioctl_cb_t cb;

	cb.ioctl_code = VOS_IOCTL_ETHERNET_CLEAR_INTERRUPT_REG;
	cb.interrupt_type = interruptFlag;
	vos_dev_ioctl(hEthernetCore, &cb);

	return;
}

/*
** ethernetlib_init
**
** Initialize the function pointers of the Ethernet structure.
**
** Parameters: e - Ethernet structure instance
**
**
** Returns:	void
** Requirements:
** Comments:
*/
void ethernetlib_init(Ethernet_t *e)
{
	uint8 i;

	e->beginMacIp = &e_begin_mac_ip;
	e->beginMacIpGw = &e_begin_mac_ip_gw;
	e->beginMacIpGwSn = &e_begin_mac_ip_gw_sn;
	e->setInterruptMask = &e_setInterruptMask;
	e->getInterruptType = &e_getInterruptType;
	e->clearInterruptFlag = &e_clearInterruptFlag;
	vos_memset(e->server_port, 0, MAX_SOCK_NUM);
	// memset(e->state, 0, MAX_SOCK_NUM);

	vos_iomux_define_output(19, IOMUX_OUT_SPI_MASTER_CLK);
	vos_iomux_define_output(20, IOMUX_OUT_SPI_MASTER_MOSI);
	vos_iomux_define_input(22, IOMUX_IN_SPI_MASTER_MISO);
	vos_iomux_define_output(28, IOMUX_OUT_SPI_MASTER_CS_1);
}

void attach_ethernet_core(VOS_HANDLE mainEthernetHandle)
{
	hEthernetCore = mainEthernetHandle;
}

void ethernet_attach_spim_handle(VOS_HANDLE mainSpiMasterHandle)
{
	hSPIMasterCore = mainSpiMasterHandle;
}

uint16 str_len(const char *str)
{
	char *p;
	uint16 len = 0;

	p = str;

	while (*p++)
	{
		len++;
	}

	return len;
}

