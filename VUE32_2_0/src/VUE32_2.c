/******************************************************************************
 * VUE32 #2 functions implementation
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"
#include "VUE32_adc.h"



#include "def.h"

//user_input.c
extern volatile unsigned char set_flashers;

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//wheel_sensor.c
extern unsigned short spdo1_mean;
extern volatile unsigned char spd1_moving;

//interrupt.c
extern volatile unsigned int flag_1ms_a, flag_1ms_b, flag_8ms;
extern volatile unsigned char flag_adc_filter;
extern volatile unsigned int flag_flash;

//VUE32_adc.h
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];
extern unsigned short adc_mean[ADC_CH];

unsigned char light_previous_state_vue32_2 = 0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_2_Ress[] = 
{
    {E_ID_BATTERYCURRENT, 2, Sensor},
    {E_ID_GROUNDFAULT_FREQ, 1, Sensor},
    {E_ID_GROUNDFAULT_STATE, 1, Sensor},
    {E_ID_WHEELVELOCITYSSENSOR_BR, 4, Sensor},
    {E_ID_BATT_12V, sizeof(unsigned short), Sensor},
    {E_ID_SET_LIGTH_STATE, 1, Actuator},
    {E_ID_SET_BRAKE_LIGTH_STATE, 2, Actuator},
};


//TODO remove these define and use the interface provided by HDW_MAPPING
//Mapping between pins and functionnalities
#define GNDFAULT_FREQ DIO0
#define GNDFAULT_STATE DIO2
#define BATTERYCURRENT TRIS_AN0
#define WHEELVELOCITYSSENSOR_BR SPDO1
#define WHEELVELOCITYSSENSOR_BR_TRIS SPDO1_TRIS
#define GNDFAULT_FREQ_TRIS DIO0_TRIS
#define GNDFAULT_STATE_TRIS DIO2_TRIS

// Local variables
unsigned int m_prev_gndfaultstate = 1;


/*
 * Specific Initialization
 */
void InitVUE32_2(void)
{
    light_previous_state_vue32_2 =0;
    // Set the ground fault pins as input
    //GNDFAULT_FREQ_TRIS = 1;
    GNDFAULT_STATE_TRIS = 1;
    m_prev_gndfaultstate = GNDFAULT_STATE;
    gResourceMemory[E_ID_GROUNDFAULT_FREQ] = 0x80;
    /*WHEELVELOCITYSSENSOR_BR_TRIS = 1;
    */
}

/*
 * State Machine Processing
 */
void ImplVUE32_2(void)
{
    static unsigned char flash = 1;
    
    // GROUND FAULT DETECTION
    if ( GNDFAULT_STATE == 0 )
    {
        m_prev_gndfaultstate = GNDFAULT_STATE;
    }

    //TODO forward data to software interface
    EVERY_X_MS(250)
        flag_1ms_a = 0;
        //GFI Frequency
         gResourceMemory[E_ID_GROUNDFAULT_FREQ] = (unsigned int)gfi_freq_sensor();
         gResourceMemory[E_ID_GROUNDFAULT_STATE] = GNDFAULT_STATE;
    END_OF_EVERY

    if(flag_1ms_b)
    {
        flag_1ms_b = 0;
        //Filte the wheel speed
        //Disable interrupt during filtering
        //TODO Implement a memcpy between SPI data and temporary variable instead of filtering during the interrupts are disabled
        asm volatile ("di"); //Disable int
        filter_wheel();
        asm volatile ("ei"); //Enable int
        gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BR] = (unsigned int)wheel_period_to_kph(spdo1_mean, spd1_moving);
    }

    if(flag_adc_filter)
    {
        flag_adc_filter = 0;
	filter_adc();
        gResourceMemory[E_ID_BATTERYCURRENT] = read_current(adc_mean[ADC_FILTERED_AN0], adc_mean[ADC_FILTERED_VOLT]);
        gResourceMemory[E_ID_BATT_12V] = (unsigned short)read_vbat(adc_mean[ADC_FILTERED_VOLT]);
    }

    if(flag_8ms)
    {
        flag_8ms = 0;
        unsigned int dummy;
        //Actuator
        //Right Light Control
        //Mask with the brake ligth state

        gResourceMemory[E_ID_SET_LIGTH_STATE] &= 0x3F;
        gResourceMemory[E_ID_SET_LIGTH_STATE] = gResourceMemory[E_ID_SET_LIGTH_STATE] | (unsigned char)(gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE] >> 8 & 0x80);
        if(gResourceMemory[E_ID_DPR] == REVERSE)
            gResourceMemory[E_ID_SET_LIGTH_STATE] |= LT_REVERSE;
        if(light_previous_state_vue32_2 != gResourceMemory[E_ID_SET_LIGTH_STATE])
        {
            light_previous_state_vue32_2 = (unsigned char)gResourceMemory[E_ID_SET_LIGTH_STATE];
            light_action(light_previous_state_vue32_2);
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

    //Todo Door switch
}

/*
 * Message Processing
 */
void OnMsgVUE32_2(NETV_MESSAGE *msg)
{
    // Deal with GETVALUE requests
    ON_MSG_TYPE_RTR( VUE32_TYPE_GETVALUE )
        ANSWER1(E_ID_BATTERYCURRENT, unsigned short, gResourceMemory[E_ID_BATTERYCURRENT])
        ANSWER1(E_ID_GROUNDFAULT_FREQ, unsigned char, gResourceMemory[E_ID_GROUNDFAULT_FREQ])
        ANSWER1(E_ID_GROUNDFAULT_STATE, unsigned char, gResourceMemory[E_ID_GROUNDFAULT_STATE])
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BR, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BR])
        ANSWER1(E_ID_BATT_12V, unsigned short, gResourceMemory[E_ID_BATT_12V])
        ANSWER1(E_ID_PORT_E, unsigned char, DIO_PORT)
        ANSWER1(E_ID_TRIS_E, unsigned char, DIO_TRIS)
        com_led_toggle();
    END_OF_MSG_TYPE
            
    // Deal with SETVALUE requests TODO merge light resource Id in group
    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
        ACTION1(E_ID_SET_BRAKE_LIGTH_STATE, unsigned short, gResourceMemory[E_ID_SET_BRAKE_LIGTH_STATE]) END_OF_ACTION
        //Variable updated on event by a distant sensor
        ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE_RTR(NETV_TYPE_SYNCHRONIZE)
        SYNC1(E_ID_WHEELVELOCITYSSENSOR_BR, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BR])
    END_OF_MSG_TYPE

}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_2(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_2 = NULL;
