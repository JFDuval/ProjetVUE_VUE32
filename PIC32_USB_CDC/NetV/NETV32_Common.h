/*
The OpenEcoSys project / NETVProtocolStack
Copyright (C) 2011  IntRoLab - Universite de Sherbrooke

Author(s)

Dominic Letourneau, ing., M.Sc.A.

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

#ifndef _NETV32_COMMON_H_
#define _NETV32_COMMON_H_

/*
MESSAGE PRIORITY DEFINITIONS
*/
#define NETV_PRIORITY_HIGHEST     0
#define NETV_PRIORITY_HIGH        1
#define NETV_PRIORITY_MEDIUM_HIGH 2
#define NETV_PRIORITY_MEDIUM      3
#define NETV_PRIORITY_MEDIUM_LOW  4
#define NETV_PRIORITY_LOW         5
#define NETV_PRIORITY_LOWEST      6
#define NETV_PRIORITY_EVENTS      7

/*
MESSAGE TYPE DEFINITIONS
*/
#define NETV_TYPE_EMERGENCY                0x01
#define NETV_TYPE_ACTUATOR_HIGH_PRIORITY   0x02
#define NETV_TYPE_SENSOR_HIGH_PRIORITY     0x04
#define NETV_TYPE_ACTUATOR_LOW_PRIORITY    0x08
#define NETV_TYPE_SENSOR_LOW_PRIORITY      0x10
#define NETV_TYPE_REQUEST_DATA             0x20
#define NETV_TYPE_USER2                    0x40
#define NETV_TYPE_EVENTS                   0x80

/*
EMERGENCY MESSAGE COMMANDS (TYPE_EMERGENCY)
*/
#define NETV_EMERGENCY_CMD_RESET        0x00
#define NETV_EMERGENCY_CMD_STOP         0x01
#define NETV_EMERGENCY_CMD_DISCONNECT   0x02
#define NETV_EMERGENCY_CMD_RECONNECT    0x03
#define NETV_EMERGENCY_CMD_PROGRAM      0x04

//BOOT-MEMORY FLAGS
#define NETV_REQUEST_READ                0x01
#define NETV_REQUEST_WRITE               0x00
#define NETV_REQUEST_EEPROM              0x01
#define NETV_REQUEST_RAM                 0x00

/*
EVENTS MESSAGE COMMANDS (TYPE EVENTS)
*/
#define NETV_EVENTS_CMD_ALIVE           0x00
#define NETV_EVENTS_CMD_REGISTER        0x01  

/*
CAN ADDRESS DEFINITIONS
*/
#define NETV_ADDRESS_BROADCAST 0xFF

/*
STRUCTURES
*/

typedef struct _message{
   unsigned char msg_priority;
   unsigned char msg_type;
   unsigned char msg_cmd;
   unsigned char msg_dest;
   unsigned char msg_read_write;
   unsigned char msg_eeprom_ram;
   unsigned char msg_data_length;
   unsigned char msg_data[8];
   unsigned char msg_remote;
} NETV_MESSAGE;



typedef struct _BootConfig
{
	//WILL BE WRITTEN TO EEPROM
	unsigned char module_state;
	unsigned char project_id;
	unsigned char module_id;
	unsigned char code_version;
	unsigned char table_version;
	unsigned char boot_delay;

	//READ ONLY DEVICE ID
	unsigned char devid_low;
	unsigned char devid_high;		
} BootConfig;


//MODULE STATES
enum {BOOT_IDLE=0x0A, BOOT_PROGRAM_FLASH=0x01, BOOT_PROGRAM_EEPROM=0x02, BOOT_NORMAL=0x05};


//Function prototypes
unsigned char netv_send_message(NETV_MESSAGE *message);
unsigned char netv_recv_message(NETV_MESSAGE *message);



void netv_send_im_alive(unsigned char netv_addr);
void netv_transceiver(unsigned char netv_addr);
void netv_write_eeprom(unsigned int addr, unsigned int data);
unsigned int netv_read_eeprom(unsigned int addr);

//This function needs to be defined in your code to handle custom messages
extern void netv_proc_message(NETV_MESSAGE *message);

//Boot configuration
BootConfig* netv_get_boot_config(void);
void netv_read_boot_config(BootConfig *config);
void netv_write_boot_config(BootConfig *config);

#endif
