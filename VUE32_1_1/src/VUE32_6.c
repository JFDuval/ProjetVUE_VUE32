/******************************************************************************
 * VUE32 #6 functions implementation
 *  - Lateral accel. sensor
 *  - Yaw rate sensor
 *  - Wiper control
 *  - Windshield fluid pump
 *  - Lights (High)
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"

#include "def.h"

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_6_Ress[] =
{
    {E_ID_LATERALACCELERATIONSENSOR, 2, 0x00},
    {E_ID_YAWRATE, 2, 0x00},
    {E_ID_WIPERMODECONTROL, 2, 0x00},
};

/*
 * Specific Initialization
 */
void InitVUE32_6(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_6(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_6(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_LATERALACCELERATIONSENSOR, unsigned short, 6)
                ANSWER1(E_ID_YAWRATE, unsigned short, 6)
                ANSWER1(E_ID_WIPERMODECONTROL, unsigned short, 6)
                LED2 = ~LED2;
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_6(void)
{
    return;
}