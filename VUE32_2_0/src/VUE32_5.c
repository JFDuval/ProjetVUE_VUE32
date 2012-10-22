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

//interrupt.c
extern volatile unsigned int flag_1ms_a;
extern volatile unsigned char flag_adc_filter;

unsigned short previous_brake_state = 0, brake_state = 0, brake_selected_state = 0;
unsigned char dpr_switch_state = 0, previous_dpr_switch_state = 0;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];

unsigned char ucBrakeSwithRead = 0, ucPreviousBrakeSwithRead = 0, ucBrakeSwithState =0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_5_Ress[] =
{
    {E_ID_BRAKEPEDAL, 2, 0x00},
    {E_ID_ACCELERATOR, 2, 0x00},
    {E_ID_STEERINGANGLESENSOR, 4, 0x00},
    {E_ID_IGNITIONKEY, 2, 0x00},
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
        //gResourceMemory[E_ID_BRAKEPEDAL] = read_brake(adc_mean[ADC_FILTERED_AN2]);
        gResourceMemory[E_ID_BRAKEPEDAL] = read_brake(0);
    }

    //Todo trunk switch

    if(flag_8ms)
    {
        flag_8ms = 0;

        brake_state = gResourceMemory[E_ID_BRAKEPEDAL];

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
            EmitAnEvent(E_ID_DPR, VUE32_7, 1, gResourceMemory[E_ID_DPR]);
        }
        previous_dpr_switch_state = dpr_switch_state;

        roof_light = gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_RIGHT] | gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_LEFT] | gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_TRUNK];

        if(roof_light)
            pwr_roof_light(1);
        else
            pwr_roof_light(0);
    }
}

/*
 * Message Processing
 */
void OnMsgVUE32_5(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_BRAKEPEDAL, unsigned short, 5)
                ANSWER1(E_ID_ACCELERATOR, unsigned short, 5)
                ANSWER1(E_ID_STEERINGANGLESENSOR, unsigned int, 5)
                ANSWER1(E_ID_IGNITIONKEY, unsigned short, 5)
                LED2 = ~LED2;
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_ROOF_LIGTH_FROM_RIGHT, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_RIGHT]) END_OF_ACTION
        ACTION1(E_ID_SET_ROOF_LIGTH_FROM_LEFT, unsigned char, gResourceMemory[E_ID_SET_ROOF_LIGTH_FROM_LEFT]) END_OF_ACTION
        LED2 = ~LED2;
    END_OF_MSG_TYPE

}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_5(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_5 = NULL;