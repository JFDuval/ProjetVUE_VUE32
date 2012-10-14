/******************************************************************************
 * VUE32 #1 functions implementation
 *  - Bridge
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "def.h"

//Hardware resources manage localy by this VUE32
HDW_MAPPING *gVUE32_1_Ress = NULL;

/*
 * Specific Initialization
 */
void InitVUE32_1(void)
{
    // Set the LED2 as output (test)
    LED2_TRIS = 0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_1(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_1(NETV_MESSAGE *msg)
{
    LED2 = ~LED2;

    // Deal with GETVALUE requests ***** TEST *******
    if ( msg->msg_remote == 1 && msg->msg_type == VUE32_TYPE_GETVALUE )
    {
        if ( msg->msg_cmd == E_ID_BATTERYCURRENT ) // E_ID_BATTERYCURRENT
        {
            msg->msg_remote = 0;
            msg->msg_dest = msg->msg_source;
            msg->msg_source = GetMyAddr();
            msg->msg_data_length = 2;
            ((unsigned short*)msg->msg_data)[0] = 0xBEEF;
            netv_send_message(msg);
        }
    }

    /*if ( g_unVUE3FinDelais <= gTimeStamp)
    {
        g_unVUE3FinDelais = gTimeStamp + duree;

        // Faire ce qu'il y a à faire
    }*/
}
//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_1(void)
{
    return;
}