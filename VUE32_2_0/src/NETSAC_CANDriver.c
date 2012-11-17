#include "NETSAC_CANDriver.h"
#include "NETV32_Common.h"

/* isCAN1MsgReceived is true if CAN1 FIFO1 received
 * a message. This flag is updated in the CAN1 ISR. */
extern volatile BOOL isCAN1MsgReceived;

/* isCAN2MsgReceived is true if CAN2 FIFO1 received
 * a message. This flag is updated in the CAN2 ISR. */
extern volatile BOOL isCAN2MsgReceived;

unsigned char CanNETSACRxMessage(DRIVE_MSG *message, CAN_MODULE CANx)
{
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
        unsigned int SID = (msgPtr->messageWord[0]) & 0x000007FF;   //11 bits
        unsigned int EID = (msgPtr->messageWord[1] >> 10) & 0x0003FFFF; //18 bits
        unsigned int ID = (SID << 18) + EID;

        //Here convert the message buffer to a DRIVE_MESSAGE
        message->ucType = (unsigned char)(ID & 0x0F);
        message->address = ID & 0xFFFFFFF0;

       //copy data length
        message->dataLenght = msgPtr->msgEID.DLC;

        //copy data
        for (i = 0; i < MIN(8, msgPtr->msgEID.DLC); i++) {
            message->data[i] = msgPtr->data[i];
        }

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

unsigned char CanNETSACTxMessage(DRIVE_MSG *message, CAN_MODULE CANx) {

        NETV_MESSAGE messageUSB;
        messageUSB.msg_comm_iface = 0x04;
        messageUSB.msg_source = 0;
        messageUSB.msg_priority = 0;
        messageUSB.msg_data_length = 8;
        messageUSB.msg_dest = 1;
        messageUSB.msg_cmd = (unsigned char)message->address;
        messageUSB.msg_type = (unsigned char)message->ucType;
        messageUSB.msg_remote = 0;

        unsigned int i = 0;

        for(i = 0; i<8; i++)
        {
            messageUSB.msg_data[i] = message->data[i];
        }

        usb_netv_send_message(&messageUSB);
    //unsigned int i = 0;

    /* Get a pointer to the next buffer in the channel
     * check if the returned value is null. */
    CANTxMessageBuffer * msgPtr = 0;

    //ACTIVE WAIT ON BUFFER
    /* TODO : Description:
    This routine returns a pointer to an empty TX buffer. The routine will return a
    null pointer if there aren't any empty TX buffers. In such a case, the application
    should flush the channel and wait until the TX channel has at least one empty
    buffer. In order to function correctly, it is essential that the CANUpdateChannel()
    function is called in the proper sequence for the CANGetTxMessageBuffer() function to
    return a pointer to an empty buffer. */

    msgPtr = CANGetTxMessageBuffer(CANx, CAN_CHANNEL0);
    if (msgPtr == 0)
    {
        // Todo: Flag this error somewhere
        return 1;
    }

    if (message && msgPtr)
    {
        unsigned int ID = 0;

        //command type
        ID |= (((unsigned int) message->ucType) & 0x0000000F);

        //address
        ID |= (((unsigned int) message->address) & 0x1FFFFFF0);

        msgPtr->msgSID.SID = (ID >> 18);
        msgPtr->msgEID.EID = (ID & 0x0003FFFF);

        //Set extended message
        msgPtr->msgEID.IDE = 1;

        //Those bits should always be cleared
        msgPtr->msgEID.SRR = 0;
        msgPtr->msgEID.RB0 = 0;
        msgPtr->msgEID.RB1 = 0;

        //Set RTR
        msgPtr->msgEID.RTR = message->RTR;

        //copy data length
        msgPtr->msgEID.DLC = message->dataLenght;

        //copy data
        for (i = 0; i < MIN(8, message->dataLenght); i++)
        {
            msgPtr->data[i] = message->data[i];
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