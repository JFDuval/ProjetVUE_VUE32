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
#include "vue32_i2c.h"

#include "def.h"

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//interrupt.c
extern volatile unsigned char flag_adc_filter;

unsigned char wiper_control_state = 0, wiper_control_previous_state = 0;
unsigned char light_previous_state_vue32_6 = 0;

extern volatile unsigned int flag_1ms_a, flag_8ms;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_6_Ress[] =
{
    {E_ID_LATERALACCELERATIONSENSOR, sizeof(unsigned short), Sensor},
    {E_ID_YAWRATE, sizeof(unsigned short), Sensor},
    {E_ID_WIPERMODECONTROL, sizeof(unsigned char), Sensor},
    {E_ID_WIPERFLUIDPUMP, sizeof(unsigned char), Actuator},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},
    {E_ID_AUDIOAMPLIFIER, sizeof(unsigned char), Actuator},
    {E_ID_3AXES_ACCEL_X, sizeof(short), Sensor},
    {E_ID_3AXES_ACCEL_Y, sizeof(short), Sensor},
    {E_ID_3AXES_ACCEL_Z, sizeof(short), Sensor}
};

/*
 * Specific Initialization
 */
void InitVUE32_6(void)
{
    init_wiper_input();
    power_out(3, 0);
    light_previous_state_vue32_6 =0;

    // Setup I2C
    init_i2c();

    // Init 3-axis sensor
    init_adxl345();
}

/*
 * State Machine Processing
 */
void ImplVUE32_6(void)
{
    // Process the I2C sensor, result is put in the global variables (accel_x, accel_y and accel_z)
    EVERY_X_MS(1)
        read_adxl345();
        gResourceMemory[E_ID_3AXES_ACCEL_X] = (int)accel_x;
        gResourceMemory[E_ID_3AXES_ACCEL_Y] = (int)accel_y;
        gResourceMemory[E_ID_3AXES_ACCEL_Z] = (int)accel_z;
    END_OF_EVERY

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
        wiper_control_state = read_wiper_input();
        if(wiper_control_state != gResourceMemory[E_ID_WIPERMODECONTROL] && wiper_control_state == wiper_control_previous_state)
        {
            gResourceMemory[E_ID_WIPERMODECONTROL] = wiper_control_state;
            //Send the command
            EmitAnEvent(E_ID_WIPERBLADES, VUE32_4, 1, gResourceMemory[E_ID_WIPERMODECONTROL]);
            wiper_action((unsigned char)gResourceMemory[E_ID_WIPERMODECONTROL]);
        }
        wiper_control_previous_state = wiper_control_state;

        if(light_previous_state_vue32_6 != gResourceMemory[E_ID_SET_LIGTH_STATE])
        {
            light_previous_state_vue32_6 = (unsigned char)gResourceMemory[E_ID_SET_LIGTH_STATE];
            light_action(light_previous_state_vue32_6);
        }
    }

    if(flag_adc_filter)
    {
        flag_adc_filter = 0;
	filter_adc();
        gResourceMemory[E_ID_YAWRATE] = read_yaw(adc_mean[ADC_FILTERED_AN1]);
        gResourceMemory[E_ID_LATERALACCELERATIONSENSOR] = read_lateral(adc_mean[ADC_FILTERED_AN0]);
    }
}

/*
 * Message Processing
 */
void OnMsgVUE32_6(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_LATERALACCELERATIONSENSOR, unsigned short, gResourceMemory[E_ID_LATERALACCELERATIONSENSOR])
            ANSWER1(E_ID_YAWRATE, unsigned short, gResourceMemory[E_ID_YAWRATE])
            ANSWER1(E_ID_WIPERMODECONTROL, unsigned char, gResourceMemory[E_ID_WIPERMODECONTROL])
            ANSWER1(E_ID_WIPERFLUIDPUMP, unsigned char, gResourceMemory[E_ID_WIPERFLUIDPUMP])
            ANSWER1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE])
            ANSWER1(E_ID_AUDIOAMPLIFIER, unsigned char, gResourceMemory[E_ID_AUDIOAMPLIFIER])
            ANSWER1(E_ID_3AXES_ACCEL_X, short, gResourceMemory[E_ID_3AXES_ACCEL_X])
            ANSWER1(E_ID_3AXES_ACCEL_Y, short, gResourceMemory[E_ID_3AXES_ACCEL_Y])
            ANSWER1(E_ID_3AXES_ACCEL_Z, short, gResourceMemory[E_ID_3AXES_ACCEL_Z])
                com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION1(E_ID_WIPERFLUIDPUMP, unsigned char, gResourceMemory[E_ID_WIPERFLUIDPUMP]) END_OF_ACTION
        ACTION1(E_ID_AUDIOAMPLIFIER, unsigned char, gResourceMemory[E_ID_AUDIOAMPLIFIER]) END_OF_ACTION
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_WIPERFLUIDPUMP, unsigned char, gResourceMemory[E_ID_WIPERFLUIDPUMP]) END_OF_ACTION
        ACTION1(E_ID_AUDIOAMPLIFIER, unsigned char, gResourceMemory[E_ID_AUDIOAMPLIFIER]) END_OF_ACTION
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_6(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_6 = NULL;
