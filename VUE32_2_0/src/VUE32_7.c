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

#define RIGHT_TEMP_MOTOR_OFFSET 26
#define LEFT_TEMP_MOTOR_OFFSET 28

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//user_input.c
extern volatile unsigned char set_flashers;

unsigned char light_previous_state_vue32_7 = 0;
extern unsigned short spdo1_mean;
extern volatile unsigned char spd1_moving;

extern volatile unsigned int flag_1ms_b, flag_8ms;
extern volatile unsigned int flag_flash;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];
extern volatile unsigned char flag_adc_filter;

/*Hardware resources manage localy by this VUE32
 * The HDW_MAPPING size has to be set in VUE32_Impl.c
 * gHardwareSize contents size of every gVUE32_X_Ress
 * Note this array is used by long pooling functionnality
 */
HDW_MAPPING gVUE32_7_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_BL, sizeof(unsigned int), Sensor},
    {E_ID_LEFT_MOTOR_TEMP_ADC, sizeof(unsigned short), Sensor},
    {E_ID_RIGHT_MOTOR_TEMP_ADC, sizeof(unsigned short), Sensor},
    {E_ID_NUM_BMS_CONNECTED, sizeof(unsigned short), Sensor},
    {E_ID_BMS_GLOBAL_STATE, sizeof(unsigned short), Sensor},
    {E_ID_BMS_MINMAX_TENSION, sizeof(unsigned int), Sensor},
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
    gResourceMemory[E_ID_NUM_BMS_CONNECTED] = 0;
    gResourceMemory[E_ID_BMS_GLOBAL_STATE] = 0;

    // Init speed sensors
    init_change_notification();
}

/*
 * State Machine Processing
 */
void ImplVUE32_7(void)
{
    static unsigned char flash = 1;

    if(flag_1ms_b)
    {
        flag_1ms_b = 0;
        //Filte the wheel speed
        //Disable interrupt during filtering
        //TODO Implement a memcpy between SPI data and temporary variable instead of filtering during the interrupts are disabled
        asm volatile ("di"); //Disable int
        filter_wheel();
        asm volatile ("ei"); //Enable int
        gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BL] = wheel_period_to_kph(spdo1_mean, spd1_moving);
    }

    if(flag_adc_filter)
    {   flag_adc_filter = 0;
        filter_adc();
        gResourceMemory[E_ID_LEFT_MOTOR_TEMP_ADC] = read_motor_temp(adc_mean[ADC_FILTERED_AN0])+LEFT_TEMP_MOTOR_OFFSET;
        gResourceMemory[E_ID_RIGHT_MOTOR_TEMP_ADC] = read_motor_temp(adc_mean[ADC_FILTERED_AN1])+RIGHT_TEMP_MOTOR_OFFSET;
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

    EVERY_X_MS(250)
        EmitAnEvent(E_ID_LEFT_MOTOR_TEMP_ADC, VUE32_3, sizeof(unsigned short), gResourceMemory[E_ID_LEFT_MOTOR_TEMP_ADC]);
        EmitAnEvent(E_ID_RIGHT_MOTOR_TEMP_ADC, VUE32_3, sizeof(unsigned short), gResourceMemory[E_ID_RIGHT_MOTOR_TEMP_ADC]);
    END_OF_EVERY

    // Run the battery pack state machine
    //RunBatteryPack();
    gResourceMemory[E_ID_NUM_BMS_CONNECTED] = GetNumConnectedBMS();
    gResourceMemory[E_ID_BMS_GLOBAL_STATE] = GetBmsGlobalState();
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
        ANSWER1(E_ID_LEFT_MOTOR_TEMP, unsigned short, 7)
        ANSWER1(E_ID_RIGHT_MOTOR_TEMP, unsigned short, 7)
        ANSWER1(E_ID_NUM_BMS_CONNECTED, unsigned short, gResourceMemory[E_ID_NUM_BMS_CONNECTED])
        ANSWER1(E_ID_BMS_GLOBAL_STATE, unsigned short, gResourceMemory[E_ID_BMS_GLOBAL_STATE])
        ANSWER1(E_ID_BMS_MINMAX_TENSION, unsigned int, gResourceMemory[E_ID_BMS_MINMAX_TENSION])
        ANSWER1(E_ID_PORT_E, unsigned char, DIO_PORT)
        ANSWER1(E_ID_TRIS_E, unsigned char, DIO_TRIS)
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE(VUE32_TYPE_SETVALUE)
        unsigned int eStateCmd;
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_BMS_GLOBAL_STATE, unsigned short, eStateCmd )
            SetState(eStateCmd);
            gResourceMemory[E_ID_BMS_GLOBAL_STATE] = eStateCmd;
        END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE_RTR(NETV_TYPE_SYNCHRONIZE)
        SYNC1(E_ID_WHEELVELOCITYSSENSOR_BL, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BL])
    END_OF_MSG_TYPE
}

/* Put emergency instructions here
 * Every device manage by this VUE32 and has to be
 * manage differently in emergency mode
 * must be manage in this function
 */
void OnEmergencyMsgVUE32_7(void)
{
    return;
}

/*
 * Not used
 * Do a static routing between to different network
 * without an network address translation
 */
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
