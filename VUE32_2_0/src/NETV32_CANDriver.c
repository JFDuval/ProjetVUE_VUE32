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
#include "VUE32_Impl.h"

#include "GenericTypeDefs.h"
#include "Board.h"
#include <p32xxxx.h>
#include <sys/kmem.h>
#include "plib.h"


#define CAN_BUS_SPEED 1000000
#define CAN_BUS_SPEED_STEERING 500000

//This is the timestamp timer...
#define CAN_TIMER_PRESCALER (SYS_XTAL_FREQ / 1000)


#define CAN_FIFO_SIZE 32
#define CAN_NB_CHANNELS 2

#define MINIMUM_MESSAGE_SIZE 8

//Steering wheel angle (CAN sensor)
unsigned short steering_angle = 0;

/* isCAN1MsgReceived is true if CAN1 FIFO1 received
 * a message. This flag is updated in the CAN1 ISR. */
volatile BOOL isCAN1MsgReceived = FALSE;

/* isCAN2MsgReceived is true if CAN2 FIFO1 received
 * a message. This flag is updated in the CAN2 ISR. */
volatile BOOL isCAN2MsgReceived = FALSE;


BYTE CAN1MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];
BYTE CAN2MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];


static int overflow_CAN1 = 0;
#ifdef _CAN2
static int overflow_CAN2 = 0;
#endif

void __attribute__((vector(46), interrupt(ipl4), nomips16)) CAN1InterruptHandler(void) {
    /* This is the CAN1 Interrupt Handler.
     * Note that there are many source events in the
     * CAN1 module for this interrupt. These
     * events are enabled by the  CANEnableModuleEvent()
     * function. In this example, only the RX_EVENT
     * is enabled. */


    /* Check if the source of the interrupt is
     * RX_EVENT. This is redundant since only this
     * event is enabled in this example but
     * this shows one scheme for handling events. */

    if ((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0) {

        /* Within this, you can check which channel caused the
         * event by using the CANGetModuleEvent() function
         * which returns a code representing the highest priority
         * pending event. */

        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL1_EVENT) {
            /* This means that channel 1 caused the event.
             * The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You
             * could either read the channel in the ISR
             * to clear the event condition or as done
             * here, disable the event source, and set
             * an application flag to indicate that a message
             * has been received. The event can be
             * enabled by the application when it has processed
             * one message.
             *
             * Note that leaving the event enabled would
             * cause the CPU to keep executing the ISR since
             * the CAN_RX_CHANNEL_NOT_EMPTY event is persistent (unless
             * the not empty condition is cleared.)
             * */

            //Test the channel events
            if (C1FIFOINT1bits.RXOVFLIF) {

                overflow_CAN1++;

                //OVERFLOW!!!
                CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, FALSE);

            } else {
                CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            }

            isCAN1MsgReceived = TRUE;
        }
    }

    /* The CAN1 Interrupt flag is  cleared at the end of the
     * interrupt routine. This is because the interrupt source
     * that could have caused this interrupt  to occur
     * (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to
     * clear the CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY
     * interrupt is enabled will not have any effect because the
     * base event is still present. */

    INTClearFlag(INT_CAN1);
   
}

#ifdef _CAN2
void __attribute__((vector(47), interrupt(ipl4), nomips16)) CAN2InterruptHandler(void) {
    /* This is the CAN2 Interrupt Handler.
     * Note that there are many source events in the
     * CAN2 module for this interrupt. These
     * events are enabled by the  CANEnableModuleEvent()
     * function. In this example, only the RX_EVENT
     * is enabled. */


    /* Check if the source of the interrupt is
     * RX_EVENT. This is redundant since only this
     * event is enabled in this example but
     * this shows one scheme for handling events. */

    if ((CANGetModuleEvent(CAN2) & CAN_RX_EVENT) != 0) {

        /* Within this, you can check which channel caused the
         * event by using the CANGetModuleEvent() function
         * which returns a code representing the highest priority
         * pending event. */

        if (CANGetPendingEventCode(CAN2) == CAN_CHANNEL1_EVENT) {
            /* This means that channel 1 caused the event.
             * The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You
             * could either read the channel in the ISR
             * to clear the event condition or as done
             * here, disable the event source, and set
             * an application flag to indicate that a message
             * has been received. The event can be
             * enabled by the application when it has processed
             * one message.
             *
             * Note that leaving the event enabled would
             * cause the CPU to keep executing the ISR since
             * the CAN_RX_CHANNEL_NOT_EMPTY event is persistent (unless
             * the not empty condition is cleared.)
             * */

            //Test the channel events
            if (C2FIFOINT1bits.RXOVFLIF) {

                overflow_CAN2++;

                //OVERFLOW!!!
                CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, FALSE);

            } else {
                CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            }

            isCAN2MsgReceived = TRUE;


        }
    }

    /* The CAN2 Interrupt flag is  cleared at the end of the
     * interrupt routine. This is because the interrupt source
     * that could have caused this interrupt  to occur
     * (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to
     * clear the CAN2 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY
     * interrupt is enabled will not have any effect because the
     * base event is still present. */

    INTClearFlag(INT_CAN2);
    LED1 ^= 1;  //Toggle LED 4Hz
}
#endif

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

unsigned char can_netv_send_message(NETV_MESSAGE *message, CAN_MODULE CANx) {
    unsigned int i = 0;

    /* Get a pointer to the next buffer in the channel
     * check if the returned value is null. */
    CANTxMessageBuffer * msgPtr = NULL;

    if( !message || message->msg_data_length > MINIMUM_MESSAGE_SIZE )
    {
        // Invalid packet size
        // TODO: Count this error somewhere
        return 1;
    }

    //ACTIVE WAIT ON BUFFER
    /* TODO : Description:
    This routine returns a pointer to an empty TX buffer. The routine will return a
    null pointer if there aren't any empty TX buffers. In such a case, the application
    should flush the channel and wait until the TX channel has at least one empty
    buffer. In order to function correctly, it is essential that the CANUpdateChannel()
    function is called in the proper sequence for the CANGetTxMessageBuffer() function to
    return a pointer to an empty buffer. */
#ifndef TEST

#endif

    msgPtr = CANGetTxMessageBuffer(CANx, CAN_CHANNEL0);
    if (msgPtr == NULL)
    {
        // Todo: Flag this error somewhere
        return 1;
    }

    if (message && msgPtr) 
    {
        unsigned int ID = 0;

        //priority
        ID |= (((unsigned int) message->msg_priority << 28) & 0x10000000);

        //cmd
        ID |= (((unsigned int) message->msg_cmd << 20) & 0x0FF00000);

        //boot
        //ID |= ((unsigned int) message->msg_eeprom_ram << 17);
        //ID |= ((unsigned int) message->msg_read_write << 16);

        //type
        ID |= (((unsigned int) message->msg_type << 12) & 0x000FF000);

        //dest
        ID |= (((unsigned int) message->msg_dest << 6) & 0x00000FC0);

        //source
        ID |= (((unsigned int) message->msg_source) & 0x0000003F);

        msgPtr->msgSID.SID = (ID >> 18);
        msgPtr->msgEID.EID = (ID & 0x0003FFFF);

        //Set extended message
        msgPtr->msgEID.IDE = 1;

        //Those bits should always be cleared
        msgPtr->msgEID.SRR = 0;
        msgPtr->msgEID.RB0 = 0;
        msgPtr->msgEID.RB1 = 0;

        //Set RTR
        msgPtr->msgEID.RTR = message->msg_remote;

        //copy data length
        msgPtr->msgEID.DLC = message->msg_data_length;

        //copy data
        for (i = 0; i < MIN(8, message->msg_data_length); i++)
        {
            msgPtr->data[i] = message->msg_data[i];
        }

        /* This function lets the CAN module
         * know that the message processing is done
         * and message is ready to be processed. */

        CANUpdateChannel(CANx, CAN_CHANNEL0);

        /* Direct the CAN module to flush the
         * TX channel. This will send any pending
         * message in the TX channel. */

        CANFlushTxChannel(CANx, CAN_CHANNEL0);

        return 0;
    }

    return 1;
}

//////////////////////////////////////////////////////////////////////
//   can_netv_recv_message
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

unsigned char can_netv_recv_message(NETV_MESSAGE *message, CAN_MODULE CANx) {
    unsigned int i = 0;

    /* This function will check if a CAN
     * message is available in CAN1 channel 1.
     * If so , the message is read. Byte 0 of
     * the received message will indicate if
     * LED6 should be switched ON or OFF. */
    //CANRxMessageBuffer * message;

    if (CANx == CAN1 && isCAN1MsgReceived == FALSE) {
        /* CAN1 did not receive any message so
         * exit the function. Note that the
         * isCAN1MsgReceived flag is updated
         * by the CAN1 ISR. */
        return 0;
    }
#ifdef _CAN2
    else if (CANx == CAN2 && isCAN2MsgReceived == FALSE) {
        /* CAN1 did not receive any message so
         * exit the function. Note that the
         * isCAN1MsgReceived flag is updated
         * by the CAN1 ISR. */
        return 0;
    }
#endif

    /* Message was received. Reset message received flag to catch
     * the next message and read the message. Note that
     * you could also check the CANGetRxMessage function
     * return value for null to check if a message has
     * been received. */

    if(CANx == CAN1) isCAN1MsgReceived = FALSE;
#ifdef _CAN2
    if(CANx == CAN2) isCAN2MsgReceived = FALSE;
#endif

    CANRxMessageBuffer *msgPtr = (CANRxMessageBuffer *) CANGetRxMessage(CANx, CAN_CHANNEL1);

    if (msgPtr && message) {

        /* Check byte 0 of the data payload.
         * If it is 0 then switch off LED6 else
         * switch it on. */

        //Copy message...
        unsigned int SID = (msgPtr->messageWord[0]) & 0x000007FF;
        unsigned int EID = (msgPtr->messageWord[1] >> 10) & 0x0003FFFF;

        //Here convert the message buffer to a NETV_CAN message
        message->msg_priority = (SID >> 10) & 0x01;
        message->msg_cmd = ((SID) >> 2) & 0x0FF;
        //message->msg_eeprom_ram = (EID >> 17) & 0x01;
        //message->msg_read_write = (EID >> 16) & 0x01;
        message->msg_type = ((SID & 0x0003) << 6) | ((EID >> 12) & 0x3F);
        message->msg_dest = (EID & 0x00FC0) >> 6;
        message->msg_source = (EID) & 0x3F;
        message->msg_data_length = msgPtr->msgEID.DLC;

        //copy data
        for (i = 0; i < MIN(8, msgPtr->msgEID.DLC); i++) {
            message->msg_data[i] = msgPtr->data[i];
        }

        message->msg_remote = msgPtr->msgEID.RTR;
	//Decode steering wheel angle:
#ifdef _CAN2
	if((GetBoardID() == VUE32_5) && (CANx == CAN2))
	{
	    steering_angle = (msgPtr->data[0] + (msgPtr->data[1] << 8));
	}
#endif

        /* Call the CANUpdateChannel() function to let
         * CAN 1 module know that the message processing
         * is done. Enable the receive channale not empty event
         * so that the CAN module generates an interrupt when
         * the event occurs the next time.*/


        CANUpdateChannel(CANx, CAN_CHANNEL1);
        CANEnableChannelEvent(CANx, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        CANEnableChannelEvent(CANx, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);

        return 1;
    }

    return 0;
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

void netv_apply_accept_mask(NETV_MASK *mask, unsigned char mask_id) {
#if 0
    unsigned long caneid = 0;

    if (mask && C1CTRLbits.REQOP == 0x04) //mask valid and configuration mode
    {
        //SETUP MASK
        if (mask_id < 2) {
            //priority
            caneid |= (((unsigned long) mask->mask_priority << 26) & 0x1C000000);
            //type
            caneid |= (((unsigned long) mask->mask_type << 18) & 0x03FC0000);
            //cmd
            caneid |= (((unsigned long) mask->mask_cmd << 8) & 0x0000FF00);
            //dest
            caneid |= (((unsigned long) mask->mask_dest) & 0x000000FF);

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

void netv_apply_filter(NETV_FILTER *filter, unsigned char filter_id) {
#if 0
    unsigned long caneid = 0;

    //Filter must be valid and we need to be in configuration mode
    if (filter && C1CTRLbits.REQOP == 0x04) {
        //SETUP FILTER
        if (filter_id < 6) {
            //priority
            caneid |= (((unsigned long) filter->filter_priority << 26) & 0x1C000000);
            //type
            caneid |= (((unsigned long) filter->filter_type << 18) & 0x03FC0000);
            //cmd
            caneid |= (((unsigned long) filter->filter_cmd << 8) & 0x0000FF00);
            //dest
            caneid |= (((unsigned long) filter->filter_dest) & 0x000000FF);

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

void netv_init_can_driver(unsigned char canAddr, CAN_MODULE CANx) {

    CAN_BIT_CONFIG canBitConfig;

    /* This function will intialize
     * CAN1 module. */

    /* Step 1: Switch the CAN module
     * ON and switch it to Configuration
     * mode. Wait till the mode switch is
     * complete. */

    CANEnableModule(CANx, TRUE);



    CANSetOperatingMode(CANx, CAN_CONFIGURATION);
    while (CANGetOperatingMode(CANx) != CAN_CONFIGURATION);


    //Enable time stamping...
    CANSetTimeStampValue(CANx, 0x0);
    CANSetTimeStampPrescalar(CANx, CAN_TIMER_PRESCALER);
    CANEnableFeature(CANx, CAN_RX_TIMESTAMP, TRUE);


    /* Step 2: Configure the Clock.The
     * CAN_BIT_CONFIG data structure is used
     * for this purpose. The propagation segment,
     * phase segment 1 and phase segment 2
     * are configured to have 3TQ. SYSTEM_FREQ
     * and CAN_BUS_SPEED are defined in  */
    canBitConfig.phaseSeg2Tq = CAN_BIT_3TQ;
    canBitConfig.phaseSeg1Tq = CAN_BIT_5TQ;
    canBitConfig.propagationSegTq = CAN_BIT_1TQ;
    canBitConfig.phaseSeg2TimeSelect = TRUE;
    canBitConfig.sample3Time = FALSE;
    canBitConfig.syncJumpWidth = CAN_BIT_1TQ;

    //On #5, CAN2 is used for the steering wheel sensor
#ifdef _CAN2
    if((GetBoardID() == VUE32_5) && (CANx == CAN2))
	CANSetSpeed(CANx, &canBitConfig, SYS_XTAL_FREQ, CAN_BUS_SPEED_STEERING);
    else
#endif
	CANSetSpeed(CANx, &canBitConfig, SYS_XTAL_FREQ, CAN_BUS_SPEED);


    /* Step 3: Assign the buffer area to the
     * CAN module.
     */
    if (CANx == CAN1)
    {
        CANAssignMemoryBuffer(CANx, CAN1MessageFifoArea, sizeof (CAN1MessageFifoArea));
    }
#ifdef _CAN2
    else if(CANx == CAN2)
    {
        CANAssignMemoryBuffer(CANx, CAN2MessageFifoArea, sizeof (CAN2MessageFifoArea));
    }
#endif

    /* Step 4: Configure channel 0 for TX and size of
     * 8 message buffers with RTR disabled and low medium
     * priority. Configure channel 1 for RX and size
     * of 8 message buffers and receive the full message.
     */

    CANConfigureChannelForTx(CANx, CAN_CHANNEL0, CAN_FIFO_SIZE, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
    CANConfigureChannelForRx(CANx, CAN_CHANNEL1, CAN_FIFO_SIZE, CAN_RX_FULL_RECEIVE);

    /* Step 5: Configure filters and mask. Configure
     * filter 0 to accept EID messages with ID 0x8004001.
     * Configure filter mask 0 to compare all the ID
     * bits and to filter by the ID type specified in
     * the filter configuration.Messages accepted by
     * filter 0 should be stored in channel 1. */

    //Todo: Nothing filtered.
    //CANConfigureFilter(CANx, CAN_FILTER0, 0x00000000, CAN_EID);
    //CANConfigureFilter(CANx, CAN_FILTER1, 0x00000000, CAN_EID);

    //CANConfigureFilter(CANx, CAN_FILTER0, (unsigned long) canAddr, CAN_EID); //local node
    //CANConfigureFilter(CANx, CAN_FILTER1, 0x000000FF, CAN_EID); //broadcast
#ifdef NETV_MASTER_NODE
    CANConfigureFilterMask(CANx, CAN_FILTER_MASK0, 0x00000000, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);
#else
    CANConfigureFilterMask(CANx, CAN_FILTER_MASK0, 0x000000FF, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);
#endif
    CANLinkFilterToChannel(CANx, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
    CANLinkFilterToChannel(CANx, CAN_FILTER1, CAN_FILTER_MASK0, CAN_CHANNEL1);
    CANEnableFilter(CANx, CAN_FILTER0, TRUE);
    CANEnableFilter(CANx, CAN_FILTER1, TRUE);

        //ToDo debug only
    C1RXM0 = 0x00000000;
    C1RXM1 = 0x00000000;
    C1RXM2 = 0x00000000;
    C1RXM3 = 0x00000000;
#ifdef _CAN2
    C2RXM0 = 0x00000000;
    C2RXM1 = 0x00000000;
    C2RXM2 = 0x00000000;
    C2RXM3 = 0x00000000;
#endif

    /* Step 6: Enable interrupt and events. Enable the receive
     * channel not empty  event (channel event) and the receive
     * channel event (module event).
     * The interrrupt peripheral library is used to enable
     * the CAN interrupt to the CPU. */

    CANEnableChannelEvent(CANx, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
    CANEnableChannelEvent(CANx, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);
    CANEnableModuleEvent(CANx, CAN_RX_EVENT, TRUE);

    /* These functions are from interrupt peripheral
     * library. */

    if(CANx==CAN1)
    {
        INTSetVectorPriority(INT_CAN_1_VECTOR, INT_PRIORITY_LEVEL_4);
        //INTSetVectorSubPriority(INT_CAN_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
        INTEnable(INT_CAN1, INT_ENABLED);
    }
#ifdef _CAN2
    else
    {
        INTSetVectorPriority(INT_CAN_2_VECTOR, INT_PRIORITY_LEVEL_4);
        INTSetVectorSubPriority(INT_CAN_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
        INTEnable(INT_CAN2, INT_ENABLED);
    }
#endif

    /* Step 7: Switch the CAN mode
     * to normal mode. */

    //CANSetOperatingMode(CANx, CAN_NORMAL_OPERATION CAN_LOOPBACK);
    CANSetOperatingMode(CANx, CAN_NORMAL_OPERATION);

    while (CANGetOperatingMode(CANx) != CAN_NORMAL_OPERATION);

}

