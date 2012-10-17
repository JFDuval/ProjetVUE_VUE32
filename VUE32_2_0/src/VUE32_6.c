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
#include "VUE32_Impl.h"
#include "Board.h"


#include "def.h"

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

unsigned char wiper_control_previous_state_vue32_6 = 0;
unsigned char light_previous_state_vue32_6 = 0;

extern volatile unsigned int flag_1ms_a, flag_8ms;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_6_Ress[] =
{
    {E_ID_LATERALACCELERATIONSENSOR, 2, Sensor},
    {E_ID_YAWRATE, 2, Sensor},
    {E_ID_WIPERMODECONTROL, 2, Sensor},
    {E_ID_HIGHBEAM, 1, Actuator},
    {E_ID_WIPERFLUIDPUMP, 1, Actuator}
};

/*
 * Specific Initialization
 */
void InitVUE32_6(void)
{
    init_wiper_input();
    power_out(3, 0);
    wiper_action((unsigned char)0);
    light_previous_state_vue32_6 =0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_6(void)
{
    if(flag_1ms_a)
    {
        flag_1ms_a = 0;

        

        #ifdef USE_I2C
        read_adxl345(0x32);	    //I2C Polling
        #endif
    }


    if(flag_8ms)
    {
        flag_8ms = 0;

        //Wiper
        //TODO Implement a general event handler
        gResourceMemory[E_ID_WIPERMODECONTROL] = read_wiper_input();
        if(wiper_control_previous_state_vue32_6 != gResourceMemory[E_ID_WIPERMODECONTROL])
        {
            wiper_control_previous_state_vue32_6 = gResourceMemory[E_ID_WIPERMODECONTROL];

            EmitAnEvent(E_ID_WIPERMODECONTROL, VUE32_4, 1, gResourceMemory[E_ID_SET_WIPER_STATE]);

            wiper_action((unsigned char)gResourceMemory[E_ID_WIPERMODECONTROL]);
        }

        if(light_previous_state_vue32_6 != gResourceMemory[E_ID_SET_LIGTH_STATE])
        {
            light_previous_state_vue32_6 = (unsigned char)gResourceMemory[E_ID_SET_LIGTH_STATE];
            light_action(light_previous_state_vue32_6);
        }
    }
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

    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_AUDIOAMPLIFIER, unsigned char, gResourceMemory[E_ID_AUDIOAMPLIFIER])
            power_out(3, (unsigned int)msg->msg_data);
        END_OF_ACTION
        LED2 = ~LED2;
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        LED2 = ~LED2;
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_6(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_6 = NULL;