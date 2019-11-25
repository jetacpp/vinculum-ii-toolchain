#ifndef _VINCO_H_
#define _VINCO_H_

#include "vos.h"

#include "configuration.h"

#ifdef DIGITAL_H
	#include "digital_IO.h"
#endif /* DIGITAL_H */

#ifdef ANALOG_H
	#include "ADC_MCP3008.h"
	#include "pwm.h"
	#include "SPIMaster.h"
	#include "analog_IO.h"
	extern void analog_init();
	extern void analog_attach_spi_master_handle(VOS_HANDLE spi_master_handle);
#endif /* ANALOG_H */

#ifdef INTERRUPT_H
	#include "GPIO.h"
	#include "interrupts.h"
	extern void intpt_init();
	extern void intpt_create_thread();
#endif /* INTERRUPT_H */

#ifdef TIME_H
	#include "Timers.h"
	#include "time.h"
	extern void time_init();
	extern void tmr_create_thread();
#endif /* TIME_H */

#ifdef SERIAL_H
	#include "UART.h"
	#include "serial.h"
	extern void serial_Init(stSerialFunctions_t *);
#endif /* SERIAL_H */

#ifdef USBHOST_H
	#include "USB.h"
	#include "USBHost.h"
	#include "GPIO.h"
	#include "Vinco_USBH.h"
#endif /* USBHOST_H */

#ifdef USBSLAVE_H
	#include "USB.h"
	#include "USBSlave.h"
	#include "Vinco_USBS.h"
#endif /* USBSLAVE_H */

#ifdef ETHERNET_H
	#include "SPIMaster.h"
	#include "Ethernet_W5100.h"
	#include "ethernet.h"
	#include "ethernet_server.h"
	#include "ethernet_client.h"
	#include "ethernet_udp.h"
	extern tcp_server Server;
	extern tcp_client Client;
	extern Ethernet_t Ethernet;
	extern Udp_t Udp;
#endif /* ETHERNET_H */

#ifdef MP3_H
	#include "SPIMaster.h"
	#include "MP3_VS1053.h"
	#include "vinco_mp3.h"
	extern mp3_st MP3;
#endif /* MP3_H */

#define VOS_DEV_UART	0
#define SPI_MASTER 		1
#define ADC_MCP3008 	2
#define PWM 			3
#define GPIO			4
#define TIMER0  		5
#define USBHOST 		6
#define USBSLAVE 		7
#define ETHERNET 		8
#define MP3_VS1053B		9

#ifndef NUM_ADDITIONAL_DEVICES
	#define NUM_ADDITIONAL_DEVICES 0
#endif

#undef NUMBER_OF_DEVICES
#define NUMBER_OF_DEVICES 10 + NUM_ADDITIONAL_DEVICES

#endif /* _VINCULO_H_ */
