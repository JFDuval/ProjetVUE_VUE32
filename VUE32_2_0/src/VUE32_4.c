/******************************************************************************
 * VUE32 #4 functions implementation
 *  - Light Control
 *  - Wiper end-of-course switch
 *  - Flashers (Right and Left)
 *  - Wipers
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"


#include "def.h"

unsigned char user_input = 0;

extern volatile unsigned int flag_1ms_a;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_4_Ress[] =
{
    {E_ID_FRONTLIGHTCONTROL, 4, 0x00},
    {E_ID_WIPERSENDOFCOURSE, 1, 0x00},
};

/*
 * Specific Initialization
 */
void InitVUE32_4(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_4(void)
{
    if(flag_1ms_a)
    {
        flag_1ms_a = 0;

        user_input = read_light_input();
        light_action(user_input);
    }
}

/*
 * Message Processing
 */
void OnMsgVUE32_4(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_FRONTLIGHTCONTROL, unsigned short, 4)
            ANSWER1(E_ID_WIPERSENDOFCOURSE, unsigned char, 4)
            LED2 = ~LED2;
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_4(void)
{
    return;
}


ROUTING_TABLE *gRoutingTableVUE32_4 = NULL;
