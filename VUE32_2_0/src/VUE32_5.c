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

//interrupt.c
extern volatile unsigned int flag_1ms_a;
extern volatile unsigned char flag_adc_filter;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];

unsigned char ucBrakeSwithRead = 0, ucPreviousBrakeSwithRead = 0, ucBrakeSwithState =0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_5_Ress[] =
{
    {E_ID_BRAKEPEDAL, sizeof(unsigned short), Sensor},
    {E_ID_ACCELERATOR, sizeof(unsigned short), Sensor},
    {E_ID_STEERINGANGLESENSOR, sizeof(unsigned int), Sensor},
    {E_ID_DPR_FORWARD, sizeof(unsigned char), Sensor},
    {E_ID_DPR_REVERSE, sizeof(unsigned char), Sensor},
    {E_ID_STATE_SWICHT_TRUNK, sizeof(unsigned char), Sensor},
    {E_ID_TRUNK_SIGNAL, sizeof(unsigned char), Actuator},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},        //Roof ligth
};

/*
 * Specific Initialization
 */
void InitVUE32_5(void)
{
    //Door sensors:
    TRIS_DOOR_TRUNK = 1;

    //CopyValueOn(VUE32_1, E_ID_ACCELERATOR, 2000);
}

/*
 * State Machine Processing
 */
void ImplVUE32_5(void)
{
    if(flag_1ms_a)
    {
        flag_1ms_a = 0;

        user_input_VUE32_5 = read_dpr_key();
    }
    
    if(flag_adc_filter)
    {
        flag_adc_filter = 0;
	filter_adc();
        gResourceMemory[E_ID_ACCELERATOR] = 10; //read_accelerator(adc_mean[ADC_FILTERED_AN0], adc_mean[ADC_FILTERED_AN1]);
        gResourceMemory[E_ID_BRAKEPEDAL] = read_brake(adc_mean[ADC_FILTERED_AN2]);
    }

    //Deboucing Brake Swith
    ucBrakeSwithRead = (unsigned char)gResourceMemory[E_ID_BRAKEPEDAL] >> 8;
    if(ucBrakeSwithRead == ucPreviousBrakeSwithRead && ucBrakeSwithState !=ucBrakeSwithRead)
    {
        ucBrakeSwithState = ucBrakeSwithRead;
        EmitAnEvent(E_ID_SET_BRAKE_LIGTH_STATE, VUE32_2, 1, (unsigned char)(gResourceMemory[E_ID_BRAKEPEDAL] >> 8));
        EmitAnEvent(E_ID_SET_BRAKE_LIGTH_STATE, VUE32_7, 1, (unsigned char)(gResourceMemory[E_ID_BRAKEPEDAL] >> 8));
    }
    ucPreviousBrakeSwithRead = ucBrakeSwithRead;


    //Todo trunk switch
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
                ANSWER1(E_ID_DPR_FORWARD, unsigned char, 5)
                ANSWER1(E_ID_DPR_REVERSE, unsigned char, 5)
                LED2 = ~LED2;
    END_OF_MSG_TYPE

    ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
            ACTION1(E_ID_TRUNK_SIGNAL, unsigned char, gResourceMemory[E_ID_TRUNK_SIGNAL]) END_OF_ACTION
            ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
            LED2 = ~LED2;
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_TRUNK_SIGNAL, unsigned char, gResourceMemory[E_ID_TRUNK_SIGNAL]) END_OF_ACTION
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        LED2 = ~LED2;
    END_OF_MSG_TYPE

}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_5(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_5 = NULL;