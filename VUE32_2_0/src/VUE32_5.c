/******************************************************************************
 * VUE32 #5 functions implementation
 *  - Accelerator pedal potentiometer
 *  - Brake pedal potentiometer
 *  - DPR switch
 *  - Ingnition Key
 *  - CAN2: Steering wheel angle
 *  - Audo Amp Enable
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

unsigned char user_input_VUE32_5 = 0;
unsigned char roof_light;
extern volatile unsigned int flag_1ms_a, flag_8ms;
extern volatile unsigned int flag_x100ms;

//interrupt.c
extern volatile unsigned int flag_1ms_a;
extern volatile unsigned char flag_adc_filter;

unsigned short previous_brake_state = 0, brake_state = 0, brake_selected_state = 0;
unsigned char dpr_switch_state = 0, previous_dpr_switch_state = 0;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];
extern unsigned short steering_angle;

unsigned char ucBrakeSwithRead = 0, ucPreviousBrakeSwithRead = 0, ucBrakeSwithState =0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_5_Ress[] =
{
    {E_ID_BRAKEPEDAL, sizeof(unsigned short), Sensor},
    {E_ID_ACCELERATOR, sizeof(unsigned short), Sensor},
    {E_ID_STEERINGANGLESENSOR, sizeof(unsigned int), Sensor},
    {E_ID_IGNITIONKEY, sizeof(unsigned char), Sensor},
    {E_ID_DPR, sizeof(unsigned char), Sensor},
    {E_ID_STATE_SWICHT_TRUNK, sizeof(unsigned char), Sensor},
    {E_ID_TRUNK_SIGNAL, sizeof(unsigned char), Actuator},
    {E_ID_SET_ROOF_LIGTH, sizeof(unsigned char), Actuator}
};

/*
 * Specific Initialization
 */
void InitVUE32_5(void)
{
    //Door sensors:
    TRIS_DOOR_TRUNK = 1;

    TRIS_DIO_DPR_SW1 = 1;
    TRIS_DIO_DPR_SW2 = 1;
    
    // Init
    gResourceMemory[E_ID_STEERINGANGLESENSOR] = 0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_5(void)
{    
    if(flag_adc_filter)
    {
        flag_adc_filter = 0;
	filter_adc();
        gResourceMemory[E_ID_ACCELERATOR] = read_accelerator(adc_mean[ADC_FILTERED_AN0], adc_mean[ADC_FILTERED_AN1]);
        gResourceMemory[E_ID_BRAKEPEDAL] = read_brake(adc_mean[ADC_FILTERED_AN2]);
    }

    gResourceMemory[E_ID_STEERINGANGLESENSOR] =(unsigned int) steering_angle;

    //Todo trunk switch

    EVERY_X_MS(100)
        //Send the accelerator position to the VUE32 #5
        EmitAnEvent(E_ID_ACCELERATOR, VUE32_3,  sizeof(unsigned short), gResourceMemory[E_ID_ACCELERATOR]);
        EmitAnEvent(E_ID_BRAKEPEDAL, VUE32_3,  sizeof(unsigned short), gResourceMemory[E_ID_BRAKEPEDAL]);

        brake_state = gResourceMemory[E_ID_BRAKEPEDAL] & 0xf0;

        if( brake_selected_state != brake_state && brake_state == previous_brake_state)
        {
            brake_selected_state = brake_state;
            EmitAnEvent(E_ID_SET_BRAKE_LIGTH_STATE, VUE32_2, 2, gResourceMemory[E_ID_BRAKEPEDAL]);
            EmitAnEvent(E_ID_SET_BRAKE_LIGTH_STATE, VUE32_7, 2, gResourceMemory[E_ID_BRAKEPEDAL]);
        }
        previous_brake_state = brake_state;


        dpr_switch_state = read_dpr_key();

        if(gResourceMemory[E_ID_DPR] !=dpr_switch_state && dpr_switch_state == previous_dpr_switch_state)
        {
            gResourceMemory[E_ID_DPR] = dpr_switch_state;
            EmitAnEvent(E_ID_DPR, VUE32_1, 1, gResourceMemory[E_ID_DPR]);
            EmitAnEvent(E_ID_DPR, VUE32_2, 1, gResourceMemory[E_ID_DPR]);
            EmitAnEvent(E_ID_DPR, VUE32_3, 1, gResourceMemory[E_ID_DPR]);
            EmitAnEvent(E_ID_DPR, VUE32_7, 1, gResourceMemory[E_ID_DPR]);
        }
        previous_dpr_switch_state = dpr_switch_state;

        roof_light = gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_RIGHT] | gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_LEFT] | gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_TRUNK];

        /*if(roof_light)
            pwr_roof_light(1);
        else
            pwr_roof_light(0);*/
        END_OF_EVERY
}

/*
 * Message Processing
 */
void OnMsgVUE32_5(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_BRAKEPEDAL, unsigned short, gResourceMemory[E_ID_BRAKEPEDAL])
                ANSWER1(E_ID_ACCELERATOR, unsigned short, gResourceMemory[E_ID_ACCELERATOR])
                ANSWER1(E_ID_STEERINGANGLESENSOR, unsigned int, gResourceMemory[E_ID_STEERINGANGLESENSOR])
                ANSWER1(E_ID_IGNITIONKEY, unsigned char, gResourceMemory[E_ID_IGNITIONKEY])
                ANSWER1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR])
                ANSWER1(E_ID_STATE_SWICHT_TRUNK, unsigned char, gResourceMemory[E_ID_STATE_SWICHT_TRUNK])
                ANSWER1(E_ID_TRUNK_SIGNAL, unsigned char, gResourceMemory[E_ID_TRUNK_SIGNAL])
                ANSWER1(E_ID_SET_ROOF_LIGTH, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH])
                ANSWER1(E_ID_PORT_E, unsigned short, DIO_PORT)
                ANSWER1(E_ID_TRIS_E, unsigned short, DIO_TRIS)
                com_led_toggle();
    END_OF_MSG_TYPE
            
    ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
                ANSWER1(E_ID_TRUNK_SIGNAL, unsigned char, gResourceMemory[E_ID_TRUNK_SIGNAL])
                ANSWER1(E_ID_SET_ROOF_LIGTH, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH])
                com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_ROOF_LIGTH_FROM_RIGHT, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_RIGHT]) END_OF_ACTION
        ACTION1(E_ID_SET_ROOF_LIGTH_FROM_LEFT, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_LEFT]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_5(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_5 = NULL;