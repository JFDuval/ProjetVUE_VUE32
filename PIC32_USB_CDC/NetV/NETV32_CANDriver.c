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
#include "NETV32_CANDriver.h"
#include "NETV32_Device.h"

#include "GenericTypeDefs.h"
#include <p32xxxx.h>
#include <sys/kmem.h>
#include "plib.h"


#define CAN_BUS_SPEED 1000000

//This is the timestamp timer...
#define CAN_TIMER_PRESCALER (SYS_XTAL_FREQ / 1000)


#define CAN_FIFO_SIZE 32
#define CAN_NB_CHANNELS 2

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

#if 0
	unsigned long caneid = 0;	
	unsigned char bufnum = 0;

	if (message) //pointer verification
	{			

		//Extract eid from message

		//priority
		caneid |= (((unsigned long)message->msg_priority << 26) & 0x1C000000);
		//type
		caneid  |= (((unsigned long)message->msg_type << 18) & 0x03FC0000);
		//boot
		caneid  |= (((unsigned long)(((message->msg_eeprom_ram & 0x01) << 1) | (message->msg_read_write & 0x01)) << 16) & 0x00030000);
		//cmd
		caneid  |= (((unsigned long) message->msg_cmd << 8) & 0x0000FF00);
		//dest
		caneid  |= (((unsigned long) message->msg_dest) & 0x000000FF);


		if (CAN1IsTXReady(0)) //Transmit buffer 0 ready?
		{
			bufnum = 0;
		}
		else if (CAN1IsTXReady(1)) //Transmit buffer 1 ready?
		{
			bufnum = 1;
		}
		else if (CAN1IsTXReady(2)) //Transmit buffer 2 ready?
		{
			bufnum = 2;
		}
		else //No transmit buffer available
		{
			//RETURN ERROR CODE
			return 1;
		}

		//TRANSMIT DATA
		if (message->msg_remote) //SENDING REMOTE FRAME
		{
			//force data length to zero
			CAN1SendMessage(CAN_TX_SID(caneid >> 18) & CAN_TX_EID_EN,
							(CAN_TX_EID(caneid)) & (CAN_REM_TX_REQ),
							message->msg_data, 0, bufnum);
		}
		else //SENDING NORMAL FRAME
		{
			CAN1SendMessage(CAN_TX_SID(caneid >> 18) & CAN_TX_EID_EN,
				(CAN_TX_EID(caneid)) & (CAN_NOR_TX_REQ),
				message->msg_data, message->msg_data_length, bufnum);
		}

		//RETURN SUCCESS CODE
		return 0;


	} //IF MESSAGE
#endif
	//SOMETHING IS WRONG
	//RETURN ERROR CODE
	return 1;
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
	unsigned char retval = 0;
#if 0
	if (message)
	{
		//Provided dsPIC library does not offer enough functionalities
		//for reading messages. Doing it by hand.
		if(C1RX0CONbits.RXFUL) //READ RX0 FRAME
		{

			//READING EID
			//PRIORITY
			message->msg_priority = (CAN1.cxrx0sid >> 10) & 0x0007;

			//TYPE
			message->msg_type = (CAN1.cxrx0sid >> 2) & 0x00FF;

			//BOOT
			message->msg_eeprom_ram = (CAN1.cxrx0eid >> 11) & 0x0001; 
			message->msg_read_write = (CAN1.cxrx0eid >> 10) & 0x0001;

			//CMD
			message->msg_cmd = (CAN1.cxrx0eid >> 2) & 0x00FF; 

			//DEST
			message->msg_dest = (((CAN1.cxrx0eid << 6) & 0x00C0) | ((CAN1.cxrx0dlc >> 10) & 0x003F ) )& 0x00FF;


			//MESSAGE REMOTE ?
			message->msg_remote = (CAN1.cxrx0dlc >> 9) & 0x0001;

			//READING DATA
			message->msg_data_length = CAN1.cxrx0dlc & 0x000F;
			message->msg_data[0] = CAN1.cxrx0b1;
			message->msg_data[1] = CAN1.cxrx0b1 >> 8;
			message->msg_data[2] = CAN1.cxrx0b2;
			message->msg_data[3] = CAN1.cxrx0b2 >> 8;
			message->msg_data[4] = CAN1.cxrx0b3;
			message->msg_data[5] = CAN1.cxrx0b3 >> 8;
			message->msg_data[6] = CAN1.cxrx0b4;
			message->msg_data[7] = CAN1.cxrx0b4 >> 8;
			
			//FILTER HIT
			//message->msg_filter_hit = CAN1.cxrx0con & 0x0001;
			
			//CLEAR OVERFLOW
			//message->msg_overflow = C1INTFbits.RX0OVR;
			C1INTFbits.RX0OVR = 0;

			//DONE WITH THIS FRAME
			C1RX0CONbits.RXFUL = 0;

			retval = 1;
		}
		else if (C1RX1CONbits.RXFUL) //READ RX1 FRAME
		{
			//READING EID
			//PRIORITY
			message->msg_priority = (CAN1.cxrx1sid >> 10) & 0x0007;

			//TYPE
			message->msg_type = (CAN1.cxrx1sid >> 2) & 0x00FF;

			//BOOT
			message->msg_eeprom_ram = (CAN1.cxrx1eid >> 11) & 0x0001; 
			message->msg_read_write = (CAN1.cxrx1eid >> 10) & 0x0001;

			//CMD
			message->msg_cmd = (CAN1.cxrx1eid >> 2) & 0x00FF; 

			//DEST
			message->msg_dest = (((CAN1.cxrx1eid << 6) & 0x00C0) | ((CAN1.cxrx1dlc >> 10) & 0x003F ) )& 0x00FF;


			//MESSAGE REMOTE ?
			message->msg_remote = (CAN1.cxrx1dlc >> 9) & 0x0001;

			//READING DATA
			message->msg_data_length = CAN1.cxrx1dlc & 0x000F;
			message->msg_data[0] = CAN1.cxrx1b1;
			message->msg_data[1] = CAN1.cxrx1b1 >> 8;
			message->msg_data[2] = CAN1.cxrx1b2;
			message->msg_data[3] = CAN1.cxrx1b2 >> 8;
			message->msg_data[4] = CAN1.cxrx1b3;
			message->msg_data[5] = CAN1.cxrx1b3 >> 8;
			message->msg_data[6] = CAN1.cxrx1b4;
			message->msg_data[7] = CAN1.cxrx1b4 >> 8;
			
			//FILTER HIT
			//message->msg_filter_hit = CAN1.cxrx1con & 0x0007;

			//CLEAR OVERFLOW
			//message->msg_overflow = C1INTFbits.RX1OVR;
			C1INTFbits.RX1OVR = 0;
			
			//DONE WITH THIS FRAME
			C1RX1CONbits.RXFUL = 0;

			retval = 1;
		}
	} //VALID MESSAGE PTR
	else
	{
		retval = 0;
	} //INVALID MESSAGE PTR
	
#endif
	return retval;
}

//////////////////////////////////////////////////////////////////////
//   netv_apply_accept_mask
//////////////////////////////////////////////////////////////////////
//
//   Description: Sets the MCP2510 in configuration mode
//                Updates the specified mask and configures it to its
//                previous mode
//
//   Input: object_id specifying the mask number
//   Output: NONE
//   Input/Output: mask
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////
void netv_apply_accept_mask(NETV_MASK *mask, unsigned char mask_id)
{
#if 0
  	unsigned long caneid = 0;

	if (mask && C1CTRLbits.REQOP == 0x04) //mask valid and configuration mode
	{
		//SETUP MASK
		if (mask_id < 2)
		{
			//priority
			caneid |= (((unsigned long)mask->mask_priority << 26) & 0x1C000000);
			//type
			caneid  |= (((unsigned long)mask->mask_type << 18) & 0x03FC0000);
			//cmd
			caneid  |= (((unsigned long) mask->mask_cmd << 8) & 0x0000FF00);
			//dest
			caneid  |= (((unsigned long) mask->mask_dest) & 0x000000FF);

			CAN1SetMask(mask_id, CAN_MASK_SID(caneid >> 18) & CAN_MATCH_FILTER_TYPE, CAN_MASK_EID(caneid));
		}
	}
#endif
}

//////////////////////////////////////////////////////////////////////
//   netv_apply_filter
//////////////////////////////////////////////////////////////////////
//
//   Description: Sets the MCP2510 in configuration mode
//                Updates the specified filter and configures it to its
//                previous mode
//
//   Input: object_id specifying the filter number
//   Output: NONE
//   Input/Output: filter
//   Returned value: NONE
//
//////////////////////////////////////////////////////////////////////
void netv_apply_filter(NETV_FILTER *filter, unsigned char filter_id)
{
#if 0
	unsigned long caneid = 0;

	//Filter must be valid and we need to be in configuration mode
	if (filter && C1CTRLbits.REQOP == 0x04) 
	{
		//SETUP FILTER
		if (filter_id < 6)
		{
			//priority
			caneid |= (((unsigned long)filter->filter_priority << 26) & 0x1C000000);
			//type
			caneid  |= (((unsigned long)filter->filter_type << 18) & 0x03FC0000);
			//cmd
			caneid  |= (((unsigned long) filter->filter_cmd << 8) & 0x0000FF00);
			//dest
			caneid  |= (((unsigned long) filter->filter_dest) & 0x000000FF);

			CAN1SetFilter(filter_id, CAN_FILTER_SID(caneid >> 18) & CAN_RX_EID_EN, CAN_FILTER_EID(caneid));
		}
	}
#endif
}

////////////////////////////////////////////////////////////////////////
//
// netv_init_can_driver()
//
// Initializes PIC18xxx8 CAN peripheral.  Sets the RX filter and masks so the
// CAN peripheral will receive all incoming IDs.  Configures both RX buffers
// to only accept valid valid messages (as opposed to all messages, or all
// extended message, or all standard messages).  Also sets the tri-state
// setting of B2 to output, and B3 to input (apparently the CAN peripheral
// doesn't keep track of this)
//
// The constants (CAN_USE_RX_DOUBLE_BUFFER, CAN_ENABLE_DRIVE_HIGH,
// CAN_ENABLE_CAN_CAPTURE) are given a default define in the can-18xxx8.h file.
// These default values can be overwritten in the main code, but most
// applications will be fine with these defaults.
//
//////////////////////////////////////////////////////////////////////////////
void netv_init_can_driver (NETV_FILTER *filter, NETV_MASK *mask) 
{

#if 0
	unsigned char i = 0;

	// Setup input and output pins
	TRISFbits.TRISF0 = 1; //CAN RX
	TRISFbits.TRISF1 = 0; //CAN TX

	// Set request for configuration mode
	// FCAN = FCY
	CAN1SetOperationMode(CAN_IDLE_CON &
	CAN_MASTERCLOCK_1 &
	CAN_REQ_OPERMODE_CONFIG &
	CAN_CAPTURE_DIS);

	// Wait until we are in the config mode
	while(C1CTRLbits.OPMODE != C1CTRLbits.REQOP);

	// Load configuration register
	CAN1Initialize(CAN_SYNC_JUMP_WIDTH1 &
		CAN_BAUD_PRE_SCALE(1),
		CAN_WAKEUP_BY_FILTER_DIS &
		CAN_PHASE_SEG2_TQ(3) &
		CAN_PHASE_SEG1_TQ(5) &
		CAN_PROPAGATIONTIME_SEG_TQ(1) &
		CAN_SEG2_FREE_PROG &
		CAN_SAMPLE1TIME);
	
   	//make sure that mask[1].dest = at least 0xFF
   	mask[1].mask_dest = 0xFF;

   	//Set MASK
   	for(i=0;i<2;i++){
      	netv_apply_accept_mask(&mask[i],i);
   	}

	//Setup filters
 	//make sure to possess a filter with dest = 0xFF
   	filter[2].filter_dest = 0xFF;

   	//Set Filter
   	for(i=0;i<6;i++){
      	netv_apply_filter(&filter[i],i);
   	}


	//Transmit buffer configuration
	for (i = 0; i < 3; i++)
	{
		CAN1SetTXMode(i,
			CAN_TX_STOP_REQ &
			CAN_TX_PRIORITY_HIGH );
	}

	//Receive buffer configuration
	for (i = 0; i < 2; i++)
	{
		CAN1SetRXMode(i,
			CAN_RXFUL_CLEAR &
			CAN_BUF0_DBLBUFFER_EN);
	}

	/* Set request for Normal mode */
	CAN1SetOperationMode(CAN_IDLE_CON & CAN_CAPTURE_DIS &
	CAN_MASTERCLOCK_1 &
	CAN_REQ_OPERMODE_NOR);

	//WAIT until we are in normal mode
	while(C1CTRLbits.OPMODE != C1CTRLbits.REQOP);
#endif
	
 
}

