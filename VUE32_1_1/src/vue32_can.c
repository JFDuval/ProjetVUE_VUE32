#include "vue32_can.h"
#include <string.h>

//This code is an adaptation of the file can_bridge.c by
//Dominic Letourneau, ing., M.Sc.A. - IntRoLab

//ToDo - Clean, CAN2
//Right now CAN1 is working. Tested on the 500kbits/s Steering wheel sensor.

#define CAN_BUS_SPEED 500000

//This is the timestamp timer...
#define CAN_TIMER_PRESCALER (SYS_XTAL_FREQ / 1000)


#define CAN_FIFO_SIZE 32
#define CAN_NB_CHANNELS 2

unsigned short steering_angle = 0;


/* isCAN1MsgReceived is true if CAN1 FIFO1 received
 * a message. This flag is updated in the CAN1 ISR. */
static volatile BOOL isCAN1MsgReceived = FALSE;

/* isCAN2MsgReceived is true if CAN2 FIFO1 received
 * a message. This flag is updated in the CAN2 ISR. */
static volatile BOOL isCAN2MsgReceived = FALSE;


BYTE CAN1MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];
BYTE CAN2MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];


static int overflow_CAN1 = 0;
static int overflow_CAN2 = 0;

//CAN1: vector(46), CAN2: vector(47)
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

void init_can1()
{

    CAN_BIT_CONFIG canBitConfig;

    /* This function will intialize
     * CAN1 module. */

    /* Step 1: Switch the CAN module
     * ON and switch it to Configuration
     * mode. Wait till the mode switch is
     * complete. */

    CANEnableModule(CAN1, TRUE);



    CANSetOperatingMode(CAN1, CAN_CONFIGURATION);
    while (CANGetOperatingMode(CAN1) != CAN_CONFIGURATION);


    //Enable time stamping...
    CANSetTimeStampValue(CAN1, 0x0);
    CANSetTimeStampPrescalar(CAN1, CAN_TIMER_PRESCALER);
    CANEnableFeature(CAN1, CAN_RX_TIMESTAMP, TRUE);


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

    CANSetSpeed(CAN1, &canBitConfig, SYS_XTAL_FREQ, CAN_BUS_SPEED);

    /* Step 3: Assign the buffer area to the
     * CAN module.
     */
    CANAssignMemoryBuffer(CAN1, CAN1MessageFifoArea, sizeof (CAN1MessageFifoArea));

    /* Step 4: Configure channel 0 for TX and size of
     * 8 message buffers with RTR disabled and low medium
     * priority. Configure channel 1 for RX and size
     * of 8 message buffers and receive the full message.
     */

    CANConfigureChannelForTx(CAN1, CAN_CHANNEL0, CAN_FIFO_SIZE, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
    CANConfigureChannelForRx(CAN1, CAN_CHANNEL1, CAN_FIFO_SIZE, CAN_RX_FULL_RECEIVE);

    /* Step 5: Configure filters and mask. Configure
     * filter 0 to accept EID messages with ID 0x8004001.
     * Configure filter mask 0 to compare all the ID
     * bits and to filter by the ID type specified in
     * the filter configuration.Messages accepted by
     * filter 0 should be stored in channel 1. */


    //Nothing filtered.
    CANConfigureFilter(CAN1, CAN_FILTER0, 0x00000000, CAN_EID);
    CANConfigureFilter(CAN1, CAN_FILTER1, 0x00000000, CAN_EID);

    CANConfigureFilterMask(CAN1, CAN_FILTER_MASK0, 0x00000000, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);

    //ToDo debug only
    C1RXM0 = 0x00000000;
    C1RXM1 = 0x00000000;
    C1RXM2 = 0x00000000;
    C1RXM3 = 0x00000000;

    CANLinkFilterToChannel(CAN1, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
    CANLinkFilterToChannel(CAN1, CAN_FILTER1, CAN_FILTER_MASK0, CAN_CHANNEL1);
    CANEnableFilter(CAN1, CAN_FILTER0, TRUE);
    CANEnableFilter(CAN1, CAN_FILTER1, TRUE);


    /* Step 6: Enable interrupt and events. Enable the receive
     * channel not empty  event (channel event) and the receive
     * channel event (module event).
     * The interrrupt peripheral library is used to enable
     * the CAN interrupt to the CPU. */

    CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
    CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);
    CANEnableModuleEvent(CAN1, CAN_RX_EVENT, TRUE);

    /* These functions are from interrupt peripheral
     * library. */

    INTSetVectorPriority(INT_CAN_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_CAN_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_CAN1, INT_ENABLED);

    /* Step 7: Switch the CAN mode
     * to normal mode. */

    CANSetOperatingMode(CAN1, CAN_NORMAL_OPERATION);
    while (CANGetOperatingMode(CAN1) != CAN_NORMAL_OPERATION);

}

CANRxMessageBuffer* can_recv_message()
{
    /* This function will check if a CAN
     * message is available in CAN1 channel 1.
     * If so , the message is read. Byte 0 of
     * the received message will indicate if
     * LED6 should be switched ON or OFF. */
    //CANRxMessageBuffer * message;

    if (isCAN1MsgReceived == FALSE) {
        /* CAN1 did not receive any message so
         * exit the function. Note that the
         * isCAN1MsgReceived flag is updated
         * by the CAN1 ISR. */
        return 0;
    }

    /* Message was received. Reset message received flag to catch
     * the next message and read the message. Note that
     * you could also check the CANGetRxMessage function
     * return value for null to check if a message has
     * been received. */

    isCAN1MsgReceived = FALSE;

    CANRxMessageBuffer *msgPtr = (CANRxMessageBuffer *) CANGetRxMessage(CAN1, CAN_CHANNEL1);

    if (msgPtr)
    {


        /* Call the CANUpdateChannel() function to let
         * CAN 1 module know that the message processing
         * is done. Enable the receive channel not empty event
         * so that the CAN module generates an interrupt when
         * the event occurs the next time.*/

	//Decode steering wheel angle:
	steering_angle = (msgPtr->data[0] + (msgPtr->data[1] << 8));

        CANUpdateChannel(CAN1, CAN_CHANNEL1);
        CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
        CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);

        return msgPtr;
    }

    return NULL;
}


//#define CAN_BUS_SPEED 500000
//
////This is the timestamp timer...
//#define CAN_TIMER_PRESCALER (SYS_XTAL_FREQ / 1000)
//
//
//#define CAN_FIFO_SIZE 32
//#define CAN_NB_CHANNELS 2
//
//unsigned short steering_angle = 0;
//
//
///* isCAN1MsgReceived is true if CAN1 FIFO1 received
// * a message. This flag is updated in the CAN1 ISR. */
//static volatile BOOL isCAN1MsgReceived = FALSE;
//
///* isCAN2MsgReceived is true if CAN2 FIFO1 received
// * a message. This flag is updated in the CAN2 ISR. */
//static volatile BOOL isCAN2MsgReceived = FALSE;
//
//
//BYTE CAN1MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];
//BYTE CAN2MessageFifoArea[CAN_NB_CHANNELS * CAN_FIFO_SIZE * 16];
//
//
//static int overflow_CAN1 = 0;
//static int overflow_CAN2 = 0;
//
////CAN1: vector(46), CAN2: vector(47)
//void __attribute__((vector(47), interrupt(ipl4), nomips16)) CAN2InterruptHandler(void) {
//    /* This is the CAN2 Interrupt Handler.
//     * Note that there are many source events in the
//     * CAN2 module for this interrupt. These
//     * events are enabled by the  CANEnableModuleEvent()
//     * function. In this example, only the RX_EVENT
//     * is enabled. */
//
//
//    /* Check if the source of the interrupt is
//     * RX_EVENT. This is redundant since only this
//     * event is enabled in this example but
//     * this shows one scheme for handling events. */
//
//    if ((CANGetModuleEvent(CAN2) & CAN_RX_EVENT) != 0) {
//
//        /* Within this, you can check which channel caused the
//         * event by using the CANGetModuleEvent() function
//         * which returns a code representing the highest priority
//         * pending event. */
//
//        if (CANGetPendingEventCode(CAN2) == CAN_CHANNEL1_EVENT) {
//            /* This means that channel 1 caused the event.
//             * The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You
//             * could either read the channel in the ISR
//             * to clear the event condition or as done
//             * here, disable the event source, and set
//             * an application flag to indicate that a message
//             * has been received. The event can be
//             * enabled by the application when it has processed
//             * one message.
//             *
//             * Note that leaving the event enabled would
//             * cause the CPU to keep executing the ISR since
//             * the CAN_RX_CHANNEL_NOT_EMPTY event is persistent (unless
//             * the not empty condition is cleared.)
//             * */
//
//            //Test the channel events
//            if (C2FIFOINT1bits.RXOVFLIF) {
//
//                overflow_CAN2++;
//
//                //OVERFLOW!!!
//                CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, FALSE);
//
//            } else {
//                CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
//            }
//
//            isCAN2MsgReceived = TRUE;
//        }
//    }
//
//    /* The CAN2 Interrupt flag is  cleared at the end of the
//     * interrupt routine. This is because the interrupt source
//     * that could have caused this interrupt  to occur
//     * (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to
//     * clear the CAN2 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY
//     * interrupt is enabled will not have any effect because the
//     * base event is still present. */
//
//    INTClearFlag(INT_CAN2);
//
//
//}
//
//void init_can2()
//{
//
//    CAN_BIT_CONFIG canBitConfig;
//
//    /* This function will intialize
//     * CAN2 module. */
//
//    /* Step 1: Switch the CAN module
//     * ON and switch it to Configuration
//     * mode. Wait till the mode switch is
//     * complete. */
//
//    CANEnableModule(CAN2, TRUE);
//
//
//
//    CANSetOperatingMode(CAN2, CAN_CONFIGURATION);
//    while (CANGetOperatingMode(CAN2) != CAN_CONFIGURATION);
//
//
//    //Enable time stamping...
//    CANSetTimeStampValue(CAN2, 0x0);
//    CANSetTimeStampPrescalar(CAN2, CAN_TIMER_PRESCALER);
//    CANEnableFeature(CAN2, CAN_RX_TIMESTAMP, TRUE);
//
//
//    /* Step 2: Configure the Clock.The
//     * CAN_BIT_CONFIG data structure is used
//     * for this purpose. The propagation segment,
//     * phase segment 1 and phase segment 2
//     * are configured to have 3TQ. SYSTEM_FREQ
//     * and CAN_BUS_SPEED are defined in  */
//    canBitConfig.phaseSeg2Tq = CAN_BIT_3TQ;
//    canBitConfig.phaseSeg1Tq = CAN_BIT_5TQ;
//    canBitConfig.propagationSegTq = CAN_BIT_1TQ;
//    canBitConfig.phaseSeg2TimeSelect = TRUE;
//    canBitConfig.sample3Time = FALSE;
//    canBitConfig.syncJumpWidth = CAN_BIT_1TQ;
//
//    CANSetSpeed(CAN2, &canBitConfig, SYS_XTAL_FREQ, CAN_BUS_SPEED);
//
//    /* Step 3: Assign the buffer area to the
//     * CAN module.
//     */
//    CANAssignMemoryBuffer(CAN2, CAN2MessageFifoArea, sizeof (CAN2MessageFifoArea));
//
//    /* Step 4: Configure channel 0 for TX and size of
//     * 8 message buffers with RTR disabled and low medium
//     * priority. Configure channel 1 for RX and size
//     * of 8 message buffers and receive the full message.
//     */
//
//    CANConfigureChannelForTx(CAN2, CAN_CHANNEL0, CAN_FIFO_SIZE, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
//    CANConfigureChannelForRx(CAN2, CAN_CHANNEL1, CAN_FIFO_SIZE, CAN_RX_FULL_RECEIVE);
//
//    /* Step 5: Configure filters and mask. Configure
//     * filter 0 to accept EID messages with ID 0x8004001.
//     * Configure filter mask 0 to compare all the ID
//     * bits and to filter by the ID type specified in
//     * the filter configuration.Messages accepted by
//     * filter 0 should be stored in channel 1. */
//
//
//    //Nothing filtered.
//    CANConfigureFilter(CAN2, CAN_FILTER0, 0x00000000, CAN_EID);
//    CANConfigureFilter(CAN2, CAN_FILTER1, 0x00000000, CAN_EID);
//
//    CANConfigureFilterMask(CAN2, CAN_FILTER_MASK0, 0x00000000, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);
//
//    //ToDo debug only
//    C2RXM0 = 0x00000000;
//    C2RXM1 = 0x00000000;
//    C2RXM2 = 0x00000000;
//    C2RXM3 = 0x00000000;
//
//    CANLinkFilterToChannel(CAN2, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
//    CANLinkFilterToChannel(CAN2, CAN_FILTER1, CAN_FILTER_MASK0, CAN_CHANNEL1);
//    CANEnableFilter(CAN2, CAN_FILTER0, TRUE);
//    CANEnableFilter(CAN2, CAN_FILTER1, TRUE);
//
//
//    /* Step 6: Enable interrupt and events. Enable the receive
//     * channel not empty  event (channel event) and the receive
//     * channel event (module event).
//     * The interrrupt peripheral library is used to enable
//     * the CAN interrupt to the CPU. */
//
//    CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
//    CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);
//    CANEnableModuleEvent(CAN2, CAN_RX_EVENT, TRUE);
//
//    /* These functions are from interrupt peripheral
//     * library. */
//
//    INTSetVectorPriority(INT_CAN_2_VECTOR, INT_PRIORITY_LEVEL_4);
//    INTSetVectorSubPriority(INT_CAN_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
//    INTEnable(INT_CAN2, INT_ENABLED);
//
//    /* Step 7: Switch the CAN mode
//     * to normal mode. */
//
//    CANSetOperatingMode(CAN2, CAN_NORMAL_OPERATION);
//    while (CANGetOperatingMode(CAN2) != CAN_NORMAL_OPERATION);
//
//}
//
//CANRxMessageBuffer* can_recv_message()
//{
//    /* This function will check if a CAN
//     * message is available in CAN2 channel 1.
//     * If so , the message is read. Byte 0 of
//     * the received message will indicate if
//     * LED6 should be switched ON or OFF. */
//    //CANRxMessageBuffer * message;
//
//    if (isCAN2MsgReceived == FALSE) {
//        /* CAN2 did not receive any message so
//         * exit the function. Note that the
//         * isCAN2MsgReceived flag is updated
//         * by the CAN2 ISR. */
//        return 0;
//    }
//
//    /* Message was received. Reset message received flag to catch
//     * the next message and read the message. Note that
//     * you could also check the CANGetRxMessage function
//     * return value for null to check if a message has
//     * been received. */
//
//    isCAN2MsgReceived = FALSE;
//
//    CANRxMessageBuffer *msgPtr = (CANRxMessageBuffer *) CANGetRxMessage(CAN2, CAN_CHANNEL1);
//
//    if (msgPtr)
//    {
//
//
//        /* Call the CANUpdateChannel() function to let
//         * CAN 1 module know that the message processing
//         * is done. Enable the receive channel not empty event
//         * so that the CAN module generates an interrupt when
//         * the event occurs the next time.*/
//
//	//Decode steering wheel angle:
//	steering_angle = (msgPtr->data[0] + (msgPtr->data[1] << 8));
//
//        CANUpdateChannel(CAN2, CAN_CHANNEL2);
//        CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
//        CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_OVERFLOW, TRUE);
//
//        return msgPtr;
//    }
//
//    return NULL;
//}
