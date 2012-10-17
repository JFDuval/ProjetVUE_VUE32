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
#include "VUE32_Impl.h"

#include "def.h"
#include "Board.h"

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//user_input.c
extern volatile unsigned char set_flashers;

unsigned char light_previous_state_vue32_7 = 0;
unsigned short wheel_spdo1_kph_VUE32_7 = 0;
extern unsigned short spdo1_mean;
extern volatile unsigned char spd1_moving;

extern volatile unsigned int flag_1ms_b, flag_8ms;
extern volatile unsigned int flag_flash;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_7_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_BL, 4, Sensor},
    {E_ID_LEFTFLASHER, 1, Actuator},
    {E_ID_REVERSELIGHT_BL, 1, Actuator},
    {E_ID_NIGHTLIGHT_BL, 1, Actuator},
    {E_ID_BRAKELIGHT_BL, 1, Actuator}
};

/*
 * Specific Initialization
 */
void InitVUE32_7(void)
{
    light_previous_state_vue32_7 =0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_7(void)
{
    static unsigned char flash = 0;

    if(flag_1ms_b)
    {
        flag_1ms_b = 0;
        //Filte the wheel speed
        //Disable interrupt during filtering
        //TODO Implement a memcpy between SPI data and temporary variable instead of filtering during the interrupts are disabled
        asm volatile ("di"); //Disable int
        filter_wheel();
        asm volatile ("ei"); //Enable int
        wheel_spdo1_kph_VUE32_7 = wheel_period_to_kph(spdo1_mean, spd1_moving);
    }


    //Left Lights
    if(flag_8ms)
    {
        flag_8ms = 0;
        //Actuator
        //Right Light Control
        if(light_previous_state_vue32_7 != gResourceMemory[E_ID_SET_LIGTH_STATE])
        {
            light_previous_state_vue32_7 = (unsigned char)gResourceMemory[E_ID_SET_LIGTH_STATE];
            light_action(light_previous_state_vue32_7);
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
    }
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

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_7(void)
{
    return;
}

ROUTING_TABLE gRoutingTableVUE32_7[24] =
{
    {NETV_COMM_IFACE_CAN2, BMS_1},
    {NETV_COMM_IFACE_CAN2, BMS_2},
    {NETV_COMM_IFACE_CAN2, BMS_3},
    {NETV_COMM_IFACE_CAN2, BMS_4},
    {NETV_COMM_IFACE_CAN2, BMS_5},
    {NETV_COMM_IFACE_CAN2, BMS_6},
    {NETV_COMM_IFACE_CAN2, BMS_7},
    {NETV_COMM_IFACE_CAN2, BMS_8},
    {NETV_COMM_IFACE_CAN2, BMS_9},
    {NETV_COMM_IFACE_CAN2, BMS_10},
    {NETV_COMM_IFACE_CAN2, BMS_11},
    {NETV_COMM_IFACE_CAN2, BMS_12},
    {NETV_COMM_IFACE_CAN2, BMS_13},
    {NETV_COMM_IFACE_CAN2, BMS_14},
    {NETV_COMM_IFACE_CAN2, BMS_15},
    {NETV_COMM_IFACE_CAN2, BMS_16},
    {NETV_COMM_IFACE_CAN2, BMS_17},
    {NETV_COMM_IFACE_CAN2, BMS_18},
    {NETV_COMM_IFACE_CAN2, BMS_19},
    {NETV_COMM_IFACE_CAN2, BMS_20},
    {NETV_COMM_IFACE_CAN2, BMS_21},
    {NETV_COMM_IFACE_CAN2, BMS_22},
    {NETV_COMM_IFACE_CAN2, BMS_23},
    {NETV_COMM_IFACE_CAN2, BMS_24}
};