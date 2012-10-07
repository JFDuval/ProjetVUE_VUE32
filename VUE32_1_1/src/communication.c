
// TODO: Create file header for this file

#include "communication.h"
#include "NETV32_Common.h"
#include "NETV32_USB-CDCDriver.h"
#include "NETV32_CANDriver.h"
#include "Board.h"
#include "VUE32_Impl.h"

// Send the message through the selected interfaces
unsigned char netv_send_message (NETV_MESSAGE *message)
{
    // CAN1
    if ( message->msg_comm_iface & NETV_COMM_IFACE_CAN1 )
        can_netv_send_message(message, CAN1);

    // CAN2
#ifdef _CAN2
    if ( message->msg_comm_iface & NETV_COMM_IFACE_CAN2 )
        can_netv_send_message(message, CAN2);
#endif

    // USB
#ifndef __32MX575F512H__
    if ( message->msg_comm_iface & NETV_COMM_IFACE_USB )
        usb_netv_send_message(message);
#endif

    return 1;
}

// Receive a message from any interface (and set the corresponding flag)
unsigned char netv_recv_message (NETV_MESSAGE *message)
{
    // CAN1
    if ( can_netv_recv_message(message, CAN1) )
    {
        message->msg_comm_iface = NETV_COMM_IFACE_CAN1;
        return 1;
    }

    // CAN2
#ifdef _CAN2
    if ( can_netv_recv_message(message, CAN2) )
    {
        message->msg_comm_iface = NETV_COMM_IFACE_CAN2;
        return 1;
    }
#endif

    // USB
#ifndef __32MX575F512H__
    if ( usb_netv_recv_message(message) )
    {
        message->msg_comm_iface = NETV_COMM_IFACE_USB;
        return 1;
    }
#endif
}

/*
 * We received a message, check if a generic action can be done or else forward
 * it to the right implementation
 */
void OnMsgVUE32(NETV_MESSAGE *pMsg)
{
    if ( pMsg->msg_remote && pMsg->msg_type == VUE32_TYPE_GETVALUE )
    {
        // If it's a request, let's see if we can answer it
        switch( pMsg->msg_cmd )
        {
            case E_ID_VERSION:
                pMsg->msg_dest = pMsg->msg_source;
                pMsg->msg_remote = 0;
                pMsg->msg_data_length = 2;
                pMsg->msg_source = GetMyAddr();
                pMsg->msg_data[0] = (unsigned char)(GetFirmVersion() >> 8);
                pMsg->msg_data[1] = (unsigned char)(GetFirmVersion() & 0x00FF);
                netv_send_message(pMsg);
                return;
                break;
            case E_ID_ADDRESS:
                pMsg->msg_dest = pMsg->msg_source;
                pMsg->msg_remote = 0;
                pMsg->msg_data_length = 1;
                pMsg->msg_source = GetMyAddr();
                pMsg->msg_data[0] = GetMyAddr();
                netv_send_message(pMsg);
                return;
                break;
            default:

                break;
        }
    }

#ifndef __32MX575F512H__
    // Call the ID specific message parser
    gOnMsgFunc[GetBoardID()](pMsg);
#else
    // Call the BMS message parser
    OnMsgBMS(pMsg);
#endif
}
