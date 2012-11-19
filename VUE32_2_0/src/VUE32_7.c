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
#include "../VUE32_2_0.X/BatteryPack.h"

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

//interupt.c
extern volatile unsigned int flag_1ms_b, flag_8ms;
extern volatile unsigned int flag_x100ms;
extern volatile unsigned int flag_flash;
extern volatile unsigned char flag_adc_filter;

//VUE32_adc.h
extern unsigned short adc_mean[ADC_CH];

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_7_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_BL, sizeof(unsigned int), Sensor},
    {E_ID_MOTOR_TEMP1, sizeof(unsigned short), Sensor},
    {E_ID_MOTOR_TEMP2, sizeof(unsigned short), Sensor},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},
    {E_ID_SET_BRAKE_LIGTH_STATE,sizeof(unsigned short), Actuator}
};

/*
 * Specific Initialization
 */
void InitVUE32_7(void)
{
    light_previous_state_vue32_7 =0;
    InitBatteryPack();
}

/*
 * State Machine Processing
 */
void ImplVUE32_7(void)
{
    static unsigned char flash = 1;

    if(flag_adc_filter)
    {
        flag_adc_filter = 0;
        filter_adc();
        // left side motor (driver-side)
        gResourceMemory[E_ID_MOTOR_TEMP1]= adc_mean[ADC_FILTERED_AN0];
        // rigth side motor (passenger-side)
        gResourceMemory[E_ID_MOTOR_TEMP2]= adc_mean[ADC_FILTERED_AN1];


    }

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
        //Mask with the brake ligth state
        gResourceMemory[E_ID_SET_LIGTH_STATE] &= 0x3F;
        gResourceMemory[E_ID_SET_LIGTH_STATE] = gResourceMemory[E_ID_SET_LIGTH_STATE] | (unsigned char)(gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE] >> 8 & 0x80);
        if(gResourceMemory[E_ID_DPR] == REVERSE)
            gResourceMemory[E_ID_SET_LIGTH_STATE] |= LT_REVERSE;
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
            light_flashers(gResourceMemory[E_ID_SET_LIGTH_STATE], flash);
        }
        else
        {
            light_flashers(gResourceMemory[E_ID_SET_LIGTH_STATE], 0);
        }
    }

    if(flag_x100ms)
    {
        flag_x100ms = 0;

        EmitAnEvent(E_ID_MOTOR_TEMP1, VUE32_3, sizeof(unsigned short), gResourceMemory[E_ID_MOTOR_TEMP1]);
        EmitAnEvent(E_ID_MOTOR_TEMP2, VUE32_3, sizeof(unsigned short), gResourceMemory[E_ID_MOTOR_TEMP2]);
    }

    // Run the battery pack state machine
    RunBatteryPack();
    gResourceMemory[E_ID_BMS_GLOBAL_STATE] = (unsigned int) GetBmsGlobalState();
    gResourceMemory[E_ID_BMS_MINMAX_TENSION] = GetBmsMinMaxTension();
}

/*
 * Message Processing
 */
void OnMsgVUE32_7(NETV_MESSAGE *msg)
{
    // Most of the message received are for the battery pack
    OnBatteryMsg(msg);

    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BL, unsigned int, 7)
        ANSWER1(E_ID_MOTOR_TEMP1, unsigned short, 7)
        ANSWER1(E_ID_MOTOR_TEMP2, unsigned short, 7)
        ANSWER1(E_ID_NUM_BMS_CONNECTED, unsigned short, E_ID_NUM_BMS_CONNECTED)
        ANSWER1(E_ID_BMS_GLOBAL_STATE, unsigned int, gResourceMemory[E_ID_BMS_GLOBAL_STATE])
        ANSWER1(E_ID_BMS_MINMAX_TENSION, unsigned int, gResourceMemory[E_ID_BMS_MINMAX_TENSION])
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE(VUE32_TYPE_SETVALUE)
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_BMS_GLOBAL_STATE, unsigned int, gResourceMemory[E_ID_BMS_GLOBAL_STATE] )
            //SetState(eStateCmd);
        END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
        com_led_toggle();
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
