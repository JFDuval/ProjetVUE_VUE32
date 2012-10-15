/******************************************************************************
 * VUE32 #2 functions implementation
 *  - Battery current sensing
 *  - Ground Fault
 *  - Speed sensor, Rear Right
 *  - Lights: Rear Right
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"



#include "def.h"
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];

unsigned char gfi_freq = 0;

unsigned short wheel_spdo1_kph = 0;
extern unsigned short spdo1_mean;
extern volatile unsigned char spd1_moving;

extern volatile unsigned int flag_1ms_a, flag_1ms_b;


//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_2_Ress[] = 
{
    {E_ID_BATTERYCURRENT, 2, 0x00},
    {E_ID_GROUNDFAULT_FREQ, 1, 0x00},
    {E_ID_WHEELVELOCITYSSENSOR_BR, 4, 0x00},
};


//TODO remove these define and use the interface provided by HDW_MAPPING
//Mapping between pins and functionnalities
#define GNDFAULT_FREQ DIO0
#define GNDFAULT_STATE DIO1
#define BATTERYCURRENT TRIS_AN0
#define WHEELVELOCITYSSENSOR_BR SPDO1
#define WHEELVELOCITYSSENSOR_BR_TRIS SPDO1_TRIS
#define GNDFAULT_FREQ_TRIS DIO0_TRIS
#define GNDFAULT_STATE_TRIS DIO1_TRIS

// Local variables
unsigned int m_prev_gndfaultstate = 0;


/*
 * Specific Initialization
 */
void InitVUE32_2(void)
{
    // Set the ground fault pins as input
    GNDFAULT_FREQ_TRIS = 1;
    GNDFAULT_STATE_TRIS = 1;
    WHEELVELOCITYSSENSOR_BR_TRIS = 1;
    m_prev_gndfaultstate = GNDFAULT_STATE;

    // Set the LED2 as output (test)
    LED2_TRIS = 0;
    

}

/*
 * State Machine Processing
 */
void ImplVUE32_2(void)
{
    // Check if a ground fault change is detected
    if (GNDFAULT_STATE != m_prev_gndfaultstate)
    {
        m_prev_gndfaultstate = GNDFAULT_STATE;
        // TODO: Send a message or do something
    }

    //TODO forward data to software interface
    if(flag_1ms_a)
    {
        flag_1ms_a = 0;
        //GFI Frequency
        gfi_freq = gfi_freq_sensor();

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
        wheel_spdo1_kph = wheel_period_to_kph(spdo1_mean, spd1_moving);
    }
    
}

/*
 * Message Processing
 */
void OnMsgVUE32_2(NETV_MESSAGE *msg)
{
    unsigned char test;
    unsigned short test2;
    unsigned short test3;

    // Deal with GETVALUE requests
    ON_MSG_TYPE_RTR( VUE32_TYPE_GETVALUE )
        ANSWER1(E_ID_BATTERYCURRENT, unsigned short, 2)
        ANSWER1(E_ID_GROUNDFAULT_FREQ, unsigned char, 0xFF ? 0xFF : 0)
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BR, unsigned int, 2)
        LED2 = ~LED2;
    END_OF_MSG_TYPE
            

    // Deal with SETVALUE requests
    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION3(E_ID_LOWBEAM, unsigned char, test, unsigned char, test, unsigned short, test2)
            LED2 = ~LED2;
            ANSWER3(E_ID_LOWBEAM, unsigned char, test, unsigned char, test, unsigned short, test2)
        END_OF_ACTION
    END_OF_MSG_TYPE


}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_2(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_2 = NULL;