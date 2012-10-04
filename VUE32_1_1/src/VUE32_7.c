/******************************************************************************
 * VUE32 #7 functions implementation
 *  - CAN2: BMS
 *  - Speed sensor, Rear Left
 *  - Lights: Rear Left
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"

#include "def.h"

/*
 * Specific Initialization
 */
void InitVUE32_7(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_7(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_7(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BL, unsigned int, 7)
                LED2 = ~LED2;
    END_OF_MSG_TYPE
}

