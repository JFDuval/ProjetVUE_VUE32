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

// Library call
#include "NETV32_Shared.h"
#include "NETV32_Device.h"
#include "NETV32_Common.h"

#include "VUE32_Impl.h"

#include "Board.h"

#include <string.h>


// Prototypes
unsigned char netv_write_data_flow_table_v2(unsigned int offset, unsigned char mem_type, unsigned char *buffer, unsigned int size);
unsigned char netv_read_data_flow_table_v2(unsigned int offset, unsigned char mem_type, unsigned char *buffer, unsigned int size);

//GLOBAL BOOT CONFIGURATION USED FOR THIS DEVICE
BootConfig g_BootConfig;

//fit the size of the data flow table to the global variable structure
#define DATA_FLOW_TABLE_SIZE (sizeof(GlobalNETVVariables))

//Const pointer to changeable data
volatile unsigned char * const DATA_FLOW_TABLE = (unsigned char*) &g_globalNETVVariables;

/*******************************************************************
READ EEPROM
 *******************************************************************/
unsigned int netv_read_eeprom(unsigned int index) {
    //return ReadMem(index << 1);
    return 0;
}

/*******************************************************************
WRITE EEPROM
 *******************************************************************/
void netv_write_eeprom(unsigned int index, unsigned int data) {
    //WriteMem((index << 1), &data, 1);
}


/*******************************************************************
READ EEPROM
 *******************************************************************/
//unsigned char netv_read_eeprom(unsigned char addr) 
//{ 
//TODO
/*
volatile unsigned char eepTemp; 	
EEADR = addr; 
EECON1bits.EEPGD = 0; 
EECON1bits.CFGS = 0; 
EECON1bits.RD = 1; 
eepTemp = EEDATA; 
return eepTemp; 
 */
//} 

/*******************************************************************
WRITE EEPROM
 *******************************************************************/
//void netv_write_eeprom(unsigned char addr, unsigned char data) 
//{ 	
//TODO
/*    
__asm__ volatile ("disi #0x3FFF"); //disable interrupts	
EECON1bits.EEPGD = 0; //EEPROM ACCESS
EECON1bits.CFGS = 0;  //FLASH OR EEPROM
EECON1bits.WREN = 1;  //WRITE ENABLE
EEADR = addr; //SET ADDRESS
EEDATA = data; //SET DATA
EECON2 = 0x55;        
EECON2 = 0xaa;        
EECON1bits.WR=1; //WRITE
while (EECON1bits.WR == 1);
//enable interrupts
__asm__ volatile ("disi #0x000"); //Enable interrupts
 */
//} 


//////////////////////////////////////////////////////////////////////
//   netv_transceiver()
//////////////////////////////////////////////////////////////////////
//
//   Description: MCP2510 unsigned charerrupt sub-routine
//                Handles all MCP2510 unsigned charerruptions until none are left
//
//   Input: NONE
//   Output: NONE
//   Input/Output: NONE
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

char netv_transceiver(unsigned char netv_addr, NETV_MESSAGE *pMsgRecep) {
    NETV_MESSAGE g_rMessage;

    while (netv_recv_message(&g_rMessage)) {
        
        // The g_rMessage message wasn't intended for us, forward it
        if ( g_rMessage.msg_dest != netv_addr && GetBoardID() != 0 )
        {

            //Get the VUE32's routing Table
#ifndef __32MX575F512H__
            /*if(netv_get_path(gRoutingTable[GetBoardID()], gRoutingTableSize[GetBoardID()], &g_rMessage))
            {
                NETV_MESSAGE sendMsg;
                memcpy(&sendMsg, &g_rMessage, sizeof(NETV_MESSAGE));
                netv_send_message(&sendMsg);
            }*/
#endif

            // For now, we'll just broadcast it through our other interfaces
            NETV_MESSAGE sendMsg;
            memcpy(&sendMsg, &g_rMessage, sizeof(NETV_MESSAGE));
            
            sendMsg.msg_comm_iface = ~g_rMessage.msg_comm_iface; // Swap interfaces (avoid resending the message on the same iface it was received)            
            
            // Quick hack to prevent the BMSs from overflowing the CAN1 network
            //if ( sendMsg.msg_cmd >= E_ID_BMS_BOARD_TEMP && sendMsg.msg_cmd <= E_ID_BMS_STATE_READONLY )
            //    sendMsg.msg_comm_iface &= 0xFE;
            if ( (sendMsg.msg_dest < 0x11 || sendMsg.msg_dest > (0x11 + 24)) && !(sendMsg.msg_source == 0 && ((sendMsg.msg_cmd > 0x13 && sendMsg.msg_cmd < 0x17)|| sendMsg.msg_cmd==0x1e) ))
                sendMsg.msg_comm_iface &= 0xFD;
            
            netv_send_message(&sendMsg);
        }

        // If we are targeted by the message
        if ( g_rMessage.msg_dest == netv_addr || g_rMessage.msg_dest == NETV_ADDRESS_BROADCAST || GetBoardID() == 0 )
        {
            // This message is for us
            //TODO: Analyse for boot mode first

            // Automatically answer to the Alive requests
            if ( g_rMessage.msg_remote && g_rMessage.msg_type == NETV_TYPE_ALIVE )
            {
                netv_send_im_alive(&g_rMessage);
            }
            else if ( pMsgRecep )
            {
                // Send it to the application layer
                memcpy(pMsgRecep, &g_rMessage, sizeof(NETV_MESSAGE));
                return 1;
            }
        }

    }//while

    return 0;
}



//////////////////////////////////////////////////////////////////////
//   netv_send_im_alive
//////////////////////////////////////////////////////////////////////
//
//   Description: Send a I'M Alive can message
//
//   Input: netv_addr (Address read in the EEPROM at 0XFE)
//   Output: NONE
//   Input/Output: NONE
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////

void netv_send_im_alive(NETV_MESSAGE *msg_req) {
    NETV_MESSAGE msg;

    msg.msg_priority = 0x00;
    msg.msg_type = NETV_TYPE_ALIVE;
    msg.msg_cmd = NETV_EVENTS_CMD_ALIVE;
    msg.msg_dest = msg_req->msg_source;
    msg.msg_data_length = 8;
    msg.msg_comm_iface = msg_req->msg_comm_iface;
    msg.msg_source = GetBoardID();

    g_BootConfig.project_id = 103;

    //Copy boot config
    memcpy(msg.msg_data, (char*) netv_get_boot_config(), 8);

    //make sure we are returning the right netv_addr
    msg.msg_data[2] = GetMyAddr();
    msg.msg_remote = 0;

    netv_send_message(&msg);
}

//////////////////////////////////////////////////////////////////////
//   read_data_flow_table_v2
//////////////////////////////////////////////////////////////////////
//
//   Description: Read "size" byte(s) from DATA_FLOW_TABLE
//
//   Input: 
//			 offset  - table index
//			 mem_type - eeprom or ram
//			 buffer - buffer address whre to store the read data
//			 size - the size of the read
//   Output: read succesfull/not succesfull,If the reading is successfull "1" is returned else "0"
//
//////////////////////////////////////////////////////////////////////

unsigned char netv_read_data_flow_table_v2(unsigned int offset, unsigned char mem_type, unsigned char *buffer, unsigned int size) {
    unsigned int i = 0;
    unsigned char success = 1;

    switch (mem_type) {
        case NETV_REQUEST_RAM:
            if (offset + size <= DATA_FLOW_TABLE_SIZE) {
                asm volatile("di"); //disable interrupts
                for (i = offset; i < (offset + size); i++) {
                    buffer[i - offset] = DATA_FLOW_TABLE[i];
                }
                asm volatile("ei"); //Enable interrupts

                success = 1;
            } else {
                //memory out of bound
                success = 0;
            }
            break;

        case NETV_REQUEST_EEPROM:
            if (offset + size <= DATA_FLOW_TABLE_SIZE) {
                asm volatile("di"); //disable interrupts
                for (i = offset; i < (offset + size); i++) {
                    buffer[i - offset] = netv_read_eeprom(i);
                }
                asm volatile("ei"); //Enable interrupts

                success = 1;
            } else {
                //memory out of bound
                success = 0;
            }
            break;

        default:
            success = 0;
            break;
    }

    return success;
}


//////////////////////////////////////////////////////////////////////
//   write_data_flow_table
//////////////////////////////////////////////////////////////////////
//
//   Description: Write "size" byte(s) to DATA_FLOW_TABLE
//
//   Input: 
//			 offset  - table index
//			 mem_type - eeprom or ram
//			 buffer - buffer address where to get the data
//			 size - the size of the write
//   Output: read succesfull/not succesfull,If the reading is successfull "1" is returned else "0"
//
//////////////////////////////////////////////////////////////////////

unsigned char netv_write_data_flow_table_v2(unsigned int offset, unsigned char mem_type, unsigned char *buffer, unsigned int size) {

    unsigned int i = 0;
    unsigned char success = 1;

    switch (mem_type) {
        case NETV_REQUEST_RAM:
            if (offset + size <= DATA_FLOW_TABLE_SIZE) {
                asm volatile("di"); //disable interrupts
                for (i = offset; i < (offset + size); i++) {
                    DATA_FLOW_TABLE[i] = buffer[i - offset];
                }
                asm volatile("ei"); //Enable interrupts

                success = 1;
            } else {
                //memory out of bound
                success = 0;
            }
            break;


        case NETV_REQUEST_EEPROM:
            //must protect firt 8 bytes.
            if ((offset + size <= DATA_FLOW_TABLE_SIZE) && (offset >= 8)) {
                asm volatile("di"); //disable interrupts
                for (i = offset; i < (offset + size); i++) {
                    netv_write_eeprom(i, buffer[i - offset]);
                }
                asm volatile("ei"); //Enable interrupts

                success = 1;
            } else {
                //memory out of bound
                success = 0;
            }
            break;

        default:
            success = 0;
            break;
    }

    return success;
}


//unsigned char table_read(void)
//{
//     _asm
//         TBLRDPOSTINC
//     _endasm
//     return TABLAT;
//}

void netv_read_boot_config(BootConfig *config) {
#if 0
    unsigned int devid = 0;

    if (config) {
        config->module_state = (unsigned char) ReadMem(0);
        config->project_id = (unsigned char) ReadMem(2);
        config->module_id = (unsigned char) ReadMem(4);
        config->code_version = (unsigned char) ReadMem(6);
        config->table_version = (unsigned char) ReadMem(8);
        config->boot_delay = (unsigned char) ReadMem(10);

        //read devid
        TBLPAG = 0xFF;
        devid = __builtin_tblrdl(0x0000);
        config->devid_low = devid;
        config->devid_high = devid >> 8;

    }

#endif
    config->module_state = 0;
    config->project_id = 0;
    config->module_id = 0;
    config->code_version = 0;
    config->table_version = 0;
    config->boot_delay = 0;
    config->devid_low = 0;
    config->devid_high = 0;

}

void netv_write_boot_config(BootConfig *config) {

#if 0
    if (config) {

        unsigned int data[sizeof (BootConfig)]; //first page of data
        data[0] = config->module_state;
        data[1] = config->project_id;
        data[2] = config->module_id;
        data[3] = config->code_version;
        data[4] = config->table_version;
        data[5] = config->boot_delay;

        //Writing DEVID is not mandatory, it will be read from DEVID registers, not EEPROM
        data[6] = config->devid_high;
        data[7] = config->devid_low;

        //WRITING BACK PAGE
        WriteMem(0, data, sizeof (BootConfig));

    }
#endif



}

BootConfig* netv_get_boot_config() {
    return &g_BootConfig;
}


unsigned char netv_get_path(ROUTING_TABLE *pRoutingTable, unsigned char ucRoutingTableSize, NETV_MESSAGE *msg)
{
    unsigned  int i= 0;

    if (msg->msg_comm_iface == NETV_COMM_IFACE_USB)
    {
        msg->msg_comm_iface = NETV_COMM_IFACE_CAN1;
        return 1;
    }

    if (msg->msg_comm_iface == NETV_COMM_IFACE_CAN2)
    {
        msg->msg_comm_iface = NETV_COMM_IFACE_CAN1;
        return 1;
    }

    if(msg->msg_comm_iface == NETV_COMM_IFACE_CAN1)
    {
        if(ucRoutingTableSize == 0)
            return 0;

        for(i = 0; i<ucRoutingTableSize; i++)
        {
            if(pRoutingTable[i].ucAddress == msg->msg_dest)
            {
                msg->msg_comm_iface = pRoutingTable[i].ucComm_iface;
                return 1;
            }
        }
    }

    return 0;
}
