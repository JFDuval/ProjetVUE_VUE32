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

#include "def.h"
extern unsigned short adc_raw[ADC_CH][ADC_FILTER];

// Mapping between pins and functionnalities
#define GNDFAULT_FREQ DIO0
#define GNDFAULT_STATE DIO1
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
        ANSWER1(E_ID_BATTERYCURRENT, unsigned short, adc_raw[0][0])
        ANSWER1(E_ID_GROUNDFAULT, unsigned char, GNDFAULT_STATE ? 0xFF : 0)
    END_OF_MSG_TYPE

    // Deal with SETVALUE requests
    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION3(E_ID_LOWBEAM, unsigned char, test, unsigned char, test, unsigned short, test2)
            LED2 = ~LED2;
            ANSWER3(E_ID_LOWBEAM, unsigned char, test, unsigned char, test, unsigned short, test2)
        END_OF_ACTION
    END_OF_MSG_TYPE
}
