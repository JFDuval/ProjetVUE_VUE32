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
#define NETV_TYPE_ALIVE                    0x80
#define NETV_TYPE_EVENT                    0x88
/** Added for Projet VUE **/
#define VUE32_TYPE_GETVALUE                0x30
#define VUE32_TYPE_SETVALUE                0x32
#define VUE32_TYPE_STARTEMETTING           0x34
#define VUE32_TYPE_STOPEMETTING            0x36
#define VUE32_TYPE_KEEPALIVE               0x38

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

// VUE32 RESSOURCE IDs (command field)
enum CANResourceId {

            // Access in Read mode
            E_ID_VERSION = 0x00,
            E_ID_ADDRESS = 0x01,
            E_ID_WHEELVELOCITYSSENSOR_FL = 0x02,
            E_ID_WHEELVELOCITYSSENSOR_FR = 0x03,
            E_ID_WHEELVELOCITYSSENSOR_BL = 0x04,
            E_ID_WHEELVELOCITYSSENSOR_BR = 0x05,
            E_ID_BATTERYCURRENT = 0x06,
            E_ID_GROUNDFAULT_FREQ = 0x07,
            E_ID_GROUNDFAULT_STATE = 0x08,
            E_ID_FRONTLIGHTCONTROL = 0x09,
            E_ID_BRAKEPEDAL = 0x0a,
            E_ID_ACCELERATOR = 0x0b,
            E_ID_STEERINGANGLESENSOR = 0x0c,
            E_ID_DPR = 0x0d,
            E_ID_STATE_SWICHT_TRUNK = 0x0e,
            E_ID_IGNITIONKEY = 0x0f,
            E_ID_LATERALACCELERATIONSENSOR = 0x10,
            E_ID_YAWRATE = 0x11,
            E_ID_WIPERSENDOFCOURSE = 0x12,
            E_ID_WIPERMODECONTROL = 0x13,
            E_ID_BMS_BOARD_TEMP = 0x14,
            E_ID_BMS_CELL_GROUP1 = 0x15,
            E_ID_BMS_CELL_GROUP2 = 0x16,
            E_ID_BMS_STATE_READONLY = 0x17,
            E_ID_LEFT_DOOR_STATE = 0x18,
            E_ID_RIGHT_DOOR_STATE = 0x19,
            E_ID_MOTOR_TEMP1 = 0x1a,
            E_ID_MOTOR_TEMP2 = 0x1b,
            E_ID_BATT_LEVEL = 0x1c,
            E_ID_ODOMETER = 0x1d,
            E_ID_BATT_12V = 0x1e,
            E_ID_NUM_BMS_CONNECTED = 0x1F,
            E_ID_BMS_MINMAX_TENSION = 0x20,

            // Access in Read/Write mode  (actuator)
            E_ID_DRIVE_L = 0xEA,
            E_ID_DRIVE_R = 0xEB,
            E_ID_COOLINGPUMP = 0xEC,
            E_ID_WIPERFLUIDPUMP = 0xED,
            E_ID_WIPERBLADES = 0xEE,
            E_ID_BMS_STATE_ERROR = 0xEF,
            E_ID_BMS_STATE_BALANCING = 0xF0,
            E_ID_AUDIOAMPLIFIER = 0xF1,
            E_ID_SET_LIGTH_STATE = 0xF2,
            E_ID_SET_BRAKE_LIGTH_STATE = 0xF3,
            E_ID_TRUNK_SIGNAL = 0xF4,
            E_ID_BMS_TENSIONS = 0xF5,
            E_ID_BMS_TEMPERATURES = 0xF6,
            E_ID_SET_WIPER_STATE = 0xF7,
            E_ID_SET_ROOF_LIGTH = 0xF8,
            E_ID_SET_ROOF_LIGTH_FROM_RIGHT = 0xF9,
            E_ID_SET_ROOF_LIGTH_FROM_LEFT = 0xFA,
            E_ID_SET_ROOF_LIGTH_FROM_TRUNK = 0xFB,
            E_ID_SET_REVERSE_LIGTH_STATE = 0xFC,
            E_ID_MAIN_CONTACTOR = 0xFD,
            E_ID_BMS_GLOBAL_STATE = 0xFE,
            E_ID_RESERVED_MAX = 0xFF // Dernier actuateur
} CANResourceId;

/*
EVENTS MESSAGE COMMANDS (TYPE EVENTS)
*/
#define NETV_EVENTS_CMD_ALIVE           0x00
#define NETV_EVENTS_CMD_REGISTER        0x01  

/*
CAN ADDRESS DEFINITIONS
*/
#define NETV_ADDRESS_BROADCAST 0x3F

/*
COMMUNCATION INTERFACES (flags)
*/
#define NETV_COMM_IFACE_CAN1 0x01
#define NETV_COMM_IFACE_CAN2 0x02
#define NETV_COMM_IFACE_USB  0x04
#define NETV_COMM_IFACE_UART 0x08
#define NETV_COMM_IFAVE_ALL  0x0F
/*
STRUCTURES
*/

/* ************* CHANGES FROM ORIGINAL VERSION OF THE PROTOCOL ************
 - Added a field for the communication interface (CAN1, CAN2, USB, etc)
 - The addresses are coded on 6 bits, and a source field was added
 - The Boot field was removed, and priority field is now a single bit
 - The old command field is now used as source address
 - The first byte of the payload is now used to identify the data type and format
 * ************************************************************************
*/
typedef union _message{
    struct {
   unsigned char msg_priority;      // 1 bit
   unsigned char msg_type;          // 8 bits
   unsigned char msg_cmd;           // 8 bits
   unsigned char msg_dest;          // 6 bits
   unsigned char msg_source;        // 6 bits
   unsigned char msg_data_length;
   unsigned char msg_remote;
   unsigned char msg_comm_iface;   
   unsigned char msg_data[8];
   };
   unsigned int raw[4];
} NETV_MESSAGE;

typedef struct{
    unsigned char ucComm_iface;
    unsigned char ucAddress;
}ROUTING_TABLE;


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
extern unsigned char netv_send_message (NETV_MESSAGE *message);
extern unsigned char netv_recv_message (NETV_MESSAGE *message);



void netv_send_im_alive(NETV_MESSAGE *message);
char netv_transceiver(unsigned char netv_addr, NETV_MESSAGE *pMsgRecep);
void netv_write_eeprom(unsigned int addr, unsigned int data);
unsigned int netv_read_eeprom(unsigned int addr);

//This function needs to be defined in your code to handle custom messages
extern void netv_proc_message(NETV_MESSAGE *message);

//Boot configuration
BootConfig* netv_get_boot_config(void);
void netv_read_boot_config(BootConfig *config);
void netv_write_boot_config(BootConfig *config);

//Routing function
unsigned char netv_get_path(ROUTING_TABLE *pRoutingTable, unsigned char ucRoutingTableSize, NETV_MESSAGE *msg);

#endif
