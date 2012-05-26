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
#include "NETV32_Memory.h"



// Prototypes
unsigned char netv_write_data_flow_table_v2(unsigned int offset,unsigned char mem_type, unsigned char *buffer, unsigned int size);
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
unsigned int netv_read_eeprom(unsigned int index) 
{ 
	return  ReadMem(index << 1);
} 

/*******************************************************************
WRITE EEPROM
 *******************************************************************/
void netv_write_eeprom(unsigned int index, unsigned int data) 
{ 	
	WriteMem((index << 1),&data,1);
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
void netv_transceiver(unsigned char netv_addr)
{
   NETV_MESSAGE g_rMessage;
//   unsigned char buffer_size = 0;
   unsigned int offset = 0;
  

   while(netv_recv_message(&g_rMessage)) {

      //Analyse for boot mode and I'm alive signal
      switch(g_rMessage.msg_type){
      case NETV_TYPE_EMERGENCY:

         switch(g_rMessage.msg_cmd){
            case NETV_EMERGENCY_CMD_PROGRAM:
				//indicate to the bootloader that we are gonna program				

				//TODO Update Boot Config
				//netv_write_eeprom(0xFF,NETV_BOOT_MODE_ID);
				
				
				//TODO FIX THIS
				//software reset, from reset documentation!
                                //mSYSTEMUnlock();

                                //Set arm reset
                                RSWRSTSET = 1;

                                //Read register to trigger reset
                                volatile int *p = &RSWRST;

                                //Wait until the reset happens
                                while(1);

                                Reset();
               break;
         }//end switch msg_cmd

         break;

      case NETV_TYPE_EVENTS:
         switch(g_rMessage.msg_cmd){
            case NETV_EVENTS_CMD_ALIVE:
               //Send i'm alive
               netv_send_im_alive(netv_addr);
               break;
         }//end switch msg_cmd
         break;

      case NETV_TYPE_REQUEST_DATA:

		 //get the memory offset
		 offset = g_rMessage.msg_cmd; 

         switch(g_rMessage.msg_read_write){
            case NETV_REQUEST_READ:

				   //WE MUST RECEIVE A REMOTE REQUEST...
				   if (g_rMessage.msg_remote == 1)
				   {
		               netv_read_data_flow_table_v2(offset, 
											   g_rMessage.msg_eeprom_ram,
											   &g_rMessage.msg_data[0],
											   MIN(g_rMessage.msg_data_length,8));
	
		               g_rMessage.msg_remote = 0;
	
		               while(netv_send_message(&g_rMessage)){;}

				   }

               break;

            case NETV_REQUEST_WRITE:
	               // We don't want to overwrite EEPROM table information
				   // The message must not be a remote request
	               if(g_rMessage.msg_remote == 0)
				   {
						   netv_write_data_flow_table_v2(offset, 
						   g_rMessage.msg_eeprom_ram,
						   &g_rMessage.msg_data[0],
						   MIN(g_rMessage.msg_data_length,8));
                   }
               break;

         }//end sub-switch read_write
         break;
      }
      // processe the received message
      netv_proc_message(&g_rMessage);
   }
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
void netv_send_im_alive(unsigned char netv_addr)
{		
   NETV_MESSAGE msg;
   int i = 0;
   
   msg.msg_priority = 0x00;
   msg.msg_type = NETV_TYPE_EVENTS;
   msg.msg_cmd = NETV_EVENTS_CMD_ALIVE;
   msg.msg_dest = netv_addr;
   msg.msg_eeprom_ram = NETV_REQUEST_EEPROM;
   msg.msg_read_write = NETV_REQUEST_READ;
   msg.msg_data_length = 8;

   //Protocol version 2
   for (i = 0; i < 8; i++)
   {
   		msg.msg_data[i] = netv_read_eeprom(i);
   }

   //make sure we are returning the right netv_addr
   msg.msg_data[2] = netv_addr;

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
unsigned char netv_read_data_flow_table_v2(unsigned int offset, unsigned char mem_type, unsigned char *buffer, unsigned int size)
{	
   	unsigned int i = 0;
   	unsigned char success = 1;

	switch(mem_type)
	{
		case NETV_REQUEST_RAM:
			if (offset + size <= DATA_FLOW_TABLE_SIZE)
			{
				asm volatile("di"); //disable interrupts
				for (i = offset; i < (offset + size); i++)
				{
					buffer[i - offset] = DATA_FLOW_TABLE[i];
				}
				asm volatile("ei"); //Enable interrupts
	
				success = 1;
			}
			else
			{
				//memory out of bound
				success = 0;
			}
	 	break;

	    case NETV_REQUEST_EEPROM:
			if (offset + size <= DATA_FLOW_TABLE_SIZE)
			{
				asm volatile("di"); //disable interrupts
				for (i = offset; i < (offset + size); i++)
				{
					buffer[i - offset] = netv_read_eeprom(i);
				}
				asm volatile("ei"); //Enable interrupts
	
				success = 1;
			}
			else
			{
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
unsigned char netv_write_data_flow_table_v2(unsigned int offset,unsigned char mem_type, unsigned char *buffer, unsigned int size)
{

	unsigned int i = 0;
	unsigned char success = 1;
	
	switch(mem_type)
	{
		case NETV_REQUEST_RAM:
			if (offset + size <= DATA_FLOW_TABLE_SIZE)
			{
				asm volatile("di"); //disable interrupts
				for (i = offset; i < (offset + size); i++)
				{
					DATA_FLOW_TABLE[i] = buffer[i - offset];
				}
				asm volatile("ei"); //Enable interrupts
	
				success = 1;
			}
			else
			{
				//memory out of bound
				success = 0;
			}
		break;
	
	
	  	case NETV_REQUEST_EEPROM:
			//must protect firt 8 bytes.
			if ((offset + size <= DATA_FLOW_TABLE_SIZE) && (offset >= 8))
			{
				asm volatile("di"); //disable interrupts
				for (i = offset; i < (offset + size); i++)
				{
					netv_write_eeprom(i,buffer[i - offset]);
				}
				asm volatile("ei"); //Enable interrupts
	
				success = 1;
			}
			else
			{
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

void netv_read_boot_config(BootConfig *config)
{
#if 0
	unsigned int devid = 0;

	if (config)
	{
		config->module_state  = (unsigned char) ReadMem(0);
		config->project_id  = (unsigned char) ReadMem(2);
		config->module_id  = (unsigned char) ReadMem(4);
		config->code_version  = (unsigned char) ReadMem(6);
		config->table_version = (unsigned char) ReadMem(8);
		config->boot_delay  = (unsigned char) ReadMem(10);

		//read devid
        TBLPAG = 0xFF;
        devid = __builtin_tblrdl (0x0000);	
		config->devid_low = devid;
		config->devid_high = devid >> 8;

	}

#endif
     		config->module_state  = 0;
		config->project_id  = 0;
		config->module_id  = 0;
		config->code_version  = 0;
		config->table_version = 0;
		config->boot_delay  = 0;
                config->devid_low = 0;
		config->devid_high = 0;

}

void netv_write_boot_config(BootConfig *config)
{

#if 0
	if (config)
	{

		unsigned int data[sizeof(BootConfig)]; //first page of data
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
		WriteMem(0,data,sizeof(BootConfig));

	}
#endif



}

BootConfig* netv_get_boot_config()
{
	return &g_BootConfig;
}
