/******************************************************************************
 * VUE32 #0 functions implementation
 * THIS VERSION IS USED AS A COMPLETE SIMULATOR FOR TESTING PURPOSE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"

#include "def.h"
#include <stdlib.h>

// Mapping between pins and functionnalities
#define GNDFAULT_FREQ DIO0
#define GNDFAULT_STATE DIO1
#define GNDFAULT_FREQ_TRIS DIO0_TRIS
#define GNDFAULT_STATE_TRIS DIO1_TRIS

// Local variables
unsigned int m_unRandom = 65000;
unsigned short m_usRandom = 32000;
unsigned char m_ucRandom = 128;
int m_nRandom = 0;
short m_sRandom = 0;
char m_cRandom = 0;

/*
 * Specific Initialization
 */
void InitVUE32_0(void)
{
    // Initialize random seed
    srand( TMR3 );
}

/*
 * State Machine Processing
 */
void ImplVUE32_0(void)
{
    // Randomize the test variables
    m_unRandom += (rand() % 11) - 5;
    m_usRandom += (rand() % 11) - 5;
    m_ucRandom += (rand() % 11) - 5;
    m_nRandom += (rand() % 11) - 5;
    m_sRandom += (rand() % 11) - 5;
    m_cRandom += (rand() % 11) - 5;
}

/*
 * Message Processing
 */
void OnMsgVUE32_0(NETV_MESSAGE *msg)
{
    unsigned char ucTest;
    unsigned short usTest;
    unsigned int unTest;

    // On every message received, toggle the LED2
    LED2 = ~LED2;

    // Deal with GETVALUE requests
    ON_MSG_TYPE_RTR( VUE32_TYPE_GETVALUE )
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FL, unsigned int, m_unRandom)
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FR, unsigned int, m_unRandom)
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BL, unsigned int, m_unRandom)
        ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BR, unsigned int, m_unRandom)
        ANSWER1(E_ID_BATTERYCURRENT, unsigned short, m_usRandom)
        ANSWER1(E_ID_GROUNDFAULT, unsigned char, m_usRandom & 1 ? 0xFF : 0)
        ANSWER1(E_ID_FRONTLIGHTCONTROL, unsigned short, m_usRandom)
        ANSWER1(E_ID_BRAKEPEDALPOT, unsigned short, m_usRandom)
        ANSWER1(E_ID_BRAKEPEDALSWITCH, unsigned char, m_usRandom & 1? 0xFF : 0)

        ANSWER2(E_ID_BMS_BOARD_TEMP, unsigned short, 0xEFBE, unsigned char, 0xAB)
    END_OF_MSG_TYPE

    // Deal with SETVALUE requests
    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION3(E_ID_LOWBEAM, unsigned char, ucTest, unsigned char, ucTest, unsigned short, usTest)
            unTest = ((unsigned int)ucTest << 16) + usTest;
            ANSWER3(E_ID_LOWBEAM, unsigned int, unTest, unsigned short, usTest, unsigned char, ucTest)
        END_OF_ACTION
    END_OF_MSG_TYPE
}
