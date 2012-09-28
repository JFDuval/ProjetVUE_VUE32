#ifndef _NETV32_SERIAL_DRIVER_H_
#define _NETV32_SERIAL_DRIVER_H_

#include "NETV32_Common.h"

#define START_BYTE 0xF2

typedef union  
{
	struct {	
		unsigned char start_byte;
		unsigned char pri_boot_rtr;
		unsigned char type;
		unsigned char cmd;
		unsigned char dest;
                unsigned char source;
		unsigned char data_length_iface;
		unsigned char data[8];
		unsigned char checksum;
	};
	
	unsigned char messageBytes[16];
} NETVSerialMessage;


#define RX_BUFFER_SIZE (10 * sizeof(NETVSerialMessage))

void serial_usart_interrupt_handler(void);
unsigned char serial_calculate_checksum(const NETVSerialMessage *message);


#endif


