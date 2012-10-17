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
#include "Board.h"


#include "def.h"


//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//user_input.c
extern volatile unsigned char set_flashers;

//Interrupt.h
extern volatile unsigned int flag_1ms_a, flag_8ms;
extern volatile unsigned int flag_flash;

unsigned char light_previous_state_vue32_4 = 0;
unsigned char wiper_control_previous_state_vue32_4 = 0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_4_Ress[] =
{
    {E_ID_FRONTLIGHTCONTROL, 1, Sensor},
    {E_ID_WIPERSENDOFCOURSE, 1, Sensor},
    {E_ID_RIGHTFLASHER, 1, Actuator},
    {E_ID_LEFTFLASHER, 1, Actuator},
    {E_ID_LOWBEAM, 1, Actuator},
    {E_ID_WIPERBLADES,1, Actuator}
};

/*
 * Specific Initialization
 */
void InitVUE32_4(void)
{
    //Light lever
    init_light_input();
}

/*
 * State Machine Processing
 */
void ImplVUE32_4(void)
{
    static unsigned char flash = 0;

    if(flag_8ms)
    {
        flag_8ms = 0;

        //Light
        light_previous_state_vue32_4 = gResourceMemory[E_ID_FRONTLIGHTCONTROL];
        gResourceMemory[E_ID_FRONTLIGHTCONTROL] = read_light_input();

        //TODO Implement a general event handler
        if(light_previous_state_vue32_4 != gResourceMemory[E_ID_FRONTLIGHTCONTROL])
        {
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_2, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_6, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_7, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);

            light_action((unsigned char)gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
        }

        //Wiper
        if(wiper_control_previous_state_vue32_4  != gResourceMemory[E_ID_SET_WIPER_STATE])
        {
            wiper_control_previous_state_vue32_4  = gResourceMemory[E_ID_SET_WIPER_STATE];
            wiper_action((unsigned char)gResourceMemory[E_ID_SET_WIPER_STATE]);
        }

    }

    //Flashers
    if(flag_flash)
    {
        flag_flash = 0;

        flash ^= 1;

        if(set_flashers)
        {
            light_flashers(gResourceMemory[E_ID_FRONTLIGHTCONTROL], flash);
        }
        else
        {
            light_flashers(gResourceMemory[E_ID_FRONTLIGHTCONTROL], 0);
        }
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

    ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
            ACTION1(E_ID_SET_WIPER_STATE, unsigned char, gResourceMemory[E_ID_SET_WIPER_STATE]) END_OF_ACTION
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_4(void)
{
    return;
}


ROUTING_TABLE *gRoutingTableVUE32_4 = NULL;
