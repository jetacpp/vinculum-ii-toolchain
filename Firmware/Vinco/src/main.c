#include "Vinco.h"

#if defined ANALOG_H || defined ETHERNET_H
#include "SPIMaster.h"
#endif

extern void setup();
extern void loop();
extern void setupInterrupts();

void SPI_Master_Init();

#define SIZEOF_tcb 4000

vos_tcb_t *tcb1;
vos_driver_t drvInit;

void threadFunction(void);

#if defined ANALOG_H || defined ETHERNET_H || defined MP3_H
	VOS_HANDLE hSPIm;
#endif

#ifdef SERIAL_H
	stSerialFunctions_t Serial;
#endif /*SERIAL_H*/

#ifdef USBHOST_H
	VOS_HANDLE hGpio = NULL;
	USBHost_t USBHost;
#endif /* USBHOST_H*/

#ifdef USBSLAVE_H
	stUSBSlave_t USBSlave;
#endif /*USBSLAVE_H*/

#ifdef ETHERNET_H
	VOS_HANDLE hEthernet;
	Udp_t Udp;
	tcp_server Server;
	tcp_client Client;
	Ethernet_t Ethernet;
#endif /* ETHERNET_H */

#ifdef MP3_H
	VOS_HANDLE hMP3Main;
	mp3_st MP3;
#endif

/*
** Function: SPI_Master_Init()
** Description: Initializes the SPI Master
** Parameters: None
** Returns:	None
** Requirements: This function must only be called after the scheduler starts
** Comments: This function is only included in the code if ANALOG_H or ETHERNET_H is defined
*/
#if defined ANALOG_H || defined ETHERNET_H || defined MP3_H
void SPI_Master_Init()
{
	common_ioctl_cb_t spim_iocb;

	// Setup SPI Master
	// open SPI Master and get a handle
	hSPIm = vos_dev_open(SPI_MASTER);

	// enable DMA
	spim_iocb.ioctl_code = VOS_IOCTL_COMMON_ENABLE_DMA;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set clock phase
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SCK_CPHA;
	spim_iocb.set.param = SPI_MASTER_SCK_CPHA_0;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set clock polarity
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SCK_CPOL;
	spim_iocb.set.param = SPI_MASTER_SCK_CPOL_0;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set data order
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_DATA_ORDER;
	spim_iocb.set.param = SPI_MASTER_DATA_ORDER_MSB; // MSB first
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set clock rate
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SET_SCK_FREQUENCY;
	spim_iocb.set.spi_master_sck_freq = 1000000;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// Set data delay
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SET_DATA_DELAY;
	spim_iocb.set.param = 0;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set initial state of chip select 0 pin
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SS_0;
	spim_iocb.set.param = SPI_MASTER_SS_DISABLE;
	vos_dev_ioctl(hSPIm, &spim_iocb);

	// set initial state of chip select 1 pin
	spim_iocb.ioctl_code = VOS_IOCTL_SPI_MASTER_SS_1;
	spim_iocb.set.param = SPI_MASTER_SS_DISABLE;
	vos_dev_ioctl(hSPIm, &spim_iocb);
}
#endif

void main(void)
{
	#if defined ANALOG_H || defined ETHERNET_H || defined MP3_H
		spimaster_context_t spimaster_ctx;
	#endif

	/* Initialise RTOS */
    vos_init(VOS_QUANTUM, VOS_TICK_INTERVAL, NUMBER_OF_DEVICES);

    /* Set the CPU frequency of the connected device. */
    vos_set_clock_frequency(VOS_48MHZ_CLOCK_FREQUENCY);

	vos_dev_init(VOS_DEV_UART, &drvInit, NULL);
	vos_dev_init(SPI_MASTER, &drvInit, NULL);
	vos_dev_init(ADC_MCP3008, &drvInit, NULL);
	vos_dev_init(PWM, &drvInit, NULL);
	vos_dev_init(GPIO, &drvInit, NULL);
	vos_dev_init(TIMER0, &drvInit, NULL);
	vos_dev_init(USBHOST, &drvInit, NULL);
	vos_dev_init(USBSLAVE, &drvInit, NULL);
	vos_dev_init(ETHERNET, &drvInit, NULL);

	#if defined ANALOG_H || defined ETHERNET_H || defined MP3_H
		spimaster_ctx.buffer_size = 255;
		spimaster_init(SPI_MASTER, &spimaster_ctx);
	#endif

	#ifdef TIME_H
		/*Initialize timer for time library*/
		time_init();
	#endif /*TIME_H*/

	#ifdef INTERRUPT_H
		/* Initialize the gpio ports before configuring interrupt pins.*/
		intpt_init();
		 /* Enable the interrupts. In Arduino, interrupts are enabled by default */
		interrupts();
	#endif /*INTERRUPT_H*/

	#ifdef SERIAL_H
		 serial_Init(&Serial);
	#endif *SERIAL_H*/

	#ifdef ANALOG_H
		analog_init();
	#endif /*ANALOG_H*/

	#ifdef USBHOST_H
		usbh_init_fnptrs(&USBHost);
	#endif /* USBHOST_H*/

	#ifdef USBSLAVE_H
		usbslave_struct_init(&USBSlave);
	#endif/* USBSLAVE_H*/

	#ifdef ETHERNET_H
		ethernet_init(ETHERNET);
		ethernetlib_init(&Ethernet);
		udp_init(&Udp);
		server_init(&Server);
		client_init(&Client);
	#endif /* ETHERNET_H */

	#ifdef MP3_H
		mp3_VS1053_init(MP3_VS1053B, NULL);
		mp3_init_func_ptrs(&MP3);
	#endif /* MP3_H */

	setupInterrupts();

	// Main thread, contains setup() and loop()
	tcb1 = vos_create_thread_ex(30, SIZEOF_tcb, &threadFunction, "Loop", 0);

	#ifdef TIME_H
		// Create Timer interrupt thead
		tmr_create_thread();
	#endif /* TIME_H */

	#ifdef INTERRUPT_H
		// Create GPIO interrupt threads
		intpt_create_thread();
	#endif /* INTERRUPT_H */

	// Start Scheduler kicks off the created threads.
    vos_start_scheduler();

main_loop:
	goto main_loop;
}

void threadFunction(void)
{
	#if defined ANALOG_H || defined ETHERNET_H || defined MP3_H
		SPI_Master_Init();
	#endif
	#ifdef ANALOG_H
		analog_attach_spi_master_handle(hSPIm);
	#endif
	#ifdef ETHERNET_H
		hEthernet = vos_dev_open(ETHERNET);

		attach_ethernet_core(hEthernet);
		ethernet_attach_spim_handle(hSPIm);

		attach_ethernet_client(hEthernet);
		client_attach_ethernet_structure_pointer(&Ethernet);

		attach_ethernet_server(hEthernet);
		client_attach_structure_pointer(&Client);
		server_attach_ethernet_structure_pointer(&Ethernet);

		attach_ethernet_udp(hEthernet);
	#endif
	#ifdef MP3_H
		hMP3Main = vos_dev_open(MP3_VS1053B);
		mp3_attach_MP3_VS1053b_driver_handle(hMP3Main);
		mp3_attach_SPI_master_driver_handle(hSPIm);
	#endif

	setup();
    while(1)
    {
		loop();
    }
}
