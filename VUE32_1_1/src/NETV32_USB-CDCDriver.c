/*
The OpenEcoSys project / NETVProtocolStack
Copyright (C) 2011  IntRoLab - Universite de Sherbrooke

Author(s)

Dominic Letourneau, ing., M.Sc.A.
Jean-Francois Duval

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "NETV32_USB-CDCDriver.h"
#include "NETV32_Device.h"
#include "NETV32_Shared.h"
#include "NETV32_Utils.h"

//USB Buffers:
extern char USB_In_Buffer[64];
extern char USB_Out_Buffer[64];

//memory buffer
unsigned char g_recvDataBytes[RX_BUFFER_SIZE];

unsigned int g_availableBytes = 0;
unsigned int g_readIndex = 0;
unsigned int g_writeIndex = 0;
unsigned int netv_send_usb_flag = 0;

void netv32_usb_task()
{
    BYTE numBytesRead;
    unsigned int i = 0;

    // If character received:
    if(mUSBUSARTIsTxTrfReady())
    {
        BYTE i;

        numBytesRead = getsUSBUSART(USB_In_Buffer,64);

        //store the data
        for(i = 0; i < numBytesRead; i++)
        {
            g_recvDataBytes[g_writeIndex++] = USB_In_Buffer[i];

            //circular buffer
            if (g_writeIndex >= RX_BUFFER_SIZE)
            {
                    g_writeIndex = 0;
            }

            //One more byte available
            g_availableBytes++;
        }
    }

    //Ready to transmit?
    if(netv_send_usb_flag)
    {
        if(USBUSARTIsTxTrfReady())
        {
            putUSBUSART(USB_Out_Buffer, sizeof(NETVSerialMessage));
            netv_send_usb_flag = 0;
        }
    }

}

//TODO This should be moved somewhere else.
unsigned char serial_calculate_checksum(const NETVSerialMessage *message)
{
	unsigned char checksum = 0;
	int i = 0;

	//simple accumulation of bytes from start until checksum (excluded)
	for (i = 0; i < (sizeof(NETVSerialMessage) - 1); i++)
	{
		checksum += message->messageBytes[i];
	}

	return checksum;

}

unsigned int serial_bytes_available(void)
{
	unsigned int available = 0;
	asm volatile("di"); //disable interrupts
	available = g_availableBytes;
	asm volatile("ei"); //Enable interrupts
	return available;
}

//////////////////////////////////////////////////////////////////////
//   netv_send_message
//////////////////////////////////////////////////////////////////////
//
//   Description: Fills a TX buffer with a modified message and sends
//                a Request To Send.
//
//   Input: object_id specifying the TX buffer to use
//   Output: NONE
//   Input/Output: message
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////

unsigned char netv_send_message(NETV_MESSAGE *message)
{
    unsigned char i=0;

    //Need to transform a TxMessageBuffer into a NETV_MESSAGE
    NETVSerialMessage buf;

/*
		unsigned char start_byte;
		unsigned char pri_boot_rtr;
		unsigned char type;
		unsigned char cmd;
		unsigned char dest;
		unsigned char data_length_iface;
		unsigned char data[8];
		unsigned char checksum;
*/

    //Set fields
    buf.start_byte = START_BYTE;
    buf.pri_boot_rtr = (message->msg_priority << 5) | (message->msg_read_write << 3) | (message->msg_eeprom_ram << 4) | (message->msg_remote);
    buf.type = message->msg_type;
    buf.cmd = message->msg_cmd;
    buf.dest = message->msg_dest;
    buf.data_length_iface = (message->msg_data_length << 4);

    //copy data
    for (i = 0 ; i < 8; i++)
    {
        buf.data[i] = message->msg_data[i];
    }

    //calculate checksum
    buf.checksum = serial_calculate_checksum(&buf);


    //Place data in USB output buffer
    //TODO Optimize
    USB_Out_Buffer[0] = buf.start_byte;
    USB_Out_Buffer[1] = buf.pri_boot_rtr;
    USB_Out_Buffer[2] = buf.type;
    USB_Out_Buffer[3] = buf.cmd;
    USB_Out_Buffer[4] = buf.dest;
    USB_Out_Buffer[5] = buf.data_length_iface;
    for (i = 0 ; i < 8; i++)
    {
        USB_Out_Buffer[6+i] = buf.data[i];
    }
    USB_Out_Buffer[14] = buf.checksum;

    //Ready to send
    netv_send_usb_flag = 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////
//   netv_recv_message
//////////////////////////////////////////////////////////////////////
//
//   Description: Extract RX buffer message and put it in a message
//                structure.
//
//   Input: object_id specifying the TX buffer to use
//   Output: NONE
//   Input/Output: message
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////

unsigned char netv_recv_message(NETV_MESSAGE *message)
{
    unsigned char i = 0;
    NETVSerialMessage buf;

	if(serial_bytes_available() >= sizeof(NETVSerialMessage))
	{
		//Fill NETVSerialMessage with available bytes
		//TODO Memory boundaries verification?
		//Here we assume that we have enough buffer to avoid corruption

		//DEBUG: 1Hz

		if (g_recvDataBytes[g_readIndex] == START_BYTE)		{

			for (i = 0; i < sizeof(NETVSerialMessage); i++)
			{
				//Copy byte
				buf.messageBytes[i] = g_recvDataBytes[g_readIndex];

				//Increment read index
				g_readIndex = (g_readIndex + 1) % RX_BUFFER_SIZE;
			}


			//One less message available
			asm volatile("di"); //disable interrupts
			g_availableBytes -= sizeof(NETVSerialMessage);
			asm volatile("ei"); //Enable interrupts


			//Verify checksum
			if (buf.checksum == serial_calculate_checksum(&buf))
			{
				/**
					unsigned char start_byte;
					unsigned char pri_boot_rtr;
					unsigned char type;
					unsigned char cmd;
					unsigned char dest;
					unsigned char data_length_iface;
					unsigned char data[8];
					unsigned char checksum;
				*/

				//Convert data structures
				message->msg_priority = (buf.pri_boot_rtr >> 5) & 0x07;
				message->msg_type = buf.type;
				message->msg_eeprom_ram = (buf.pri_boot_rtr >> 4) & 0x01;
				message->msg_read_write = (buf.pri_boot_rtr >> 3) & 0x01;
				message->msg_cmd = buf.cmd;
				message->msg_dest = buf.dest;
				message->msg_remote = (buf.pri_boot_rtr & 0x01);
				message->msg_data_length = ((buf.data_length_iface >> 4) & 0x0F);

				//copy data
				for(i = 0; i < 8; i++)
				{
				   message->msg_data[i] = buf.data[i];
				}

				//Toggle LED2
				com_led_toggle();

				//message valid
				return 1;
			}
			else //CHECKSUM ERROR
			{
				return 0;
			}
		}
		else //not START_BYTE
		{
			//Will try next byte next time...
			g_readIndex = (g_readIndex + 1) % RX_BUFFER_SIZE;

			//One less byte available
			asm volatile("di"); //disable interrupts
			g_availableBytes--;
			asm volatile("ei"); //Enable interrupts

			return 0;
		}
	}//enough byte available

	return 0;
}
