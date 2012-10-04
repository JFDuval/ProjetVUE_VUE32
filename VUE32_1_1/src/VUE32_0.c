/******************************************************************************
 * VUE32 #0 functions implementation
 * THIS VERSION IS USED AS A COMPLETE SIMULATOR FOR TESTING PURPOSE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "Board.h"

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

    if ( msg->msg_dest == VUE32_3)
        OnMsgVUE32_3(msg);
    if ( msg->msg_dest == VUE32_4)
        OnMsgVUE32_4(msg);
    if ( msg->msg_dest == VUE32_5)
        OnMsgVUE32_5(msg);
    if ( msg->msg_dest == VUE32_6)
        OnMsgVUE32_6(msg);
    if ( msg->msg_dest == VUE32_7)
        OnMsgVUE32_7(msg);

    // On every message received, toggle the LED2
    LED2 = ~LED2;

    // Deal with SETVALUE requests
    ON_MSG_TYPE( VUE32_TYPE_SETVALUE )
        ACTION3(E_ID_LOWBEAM, unsigned char, ucTest, unsigned char, ucTest, unsigned short, usTest)
            unTest = ((unsigned int)ucTest << 16) + usTest;
            ANSWER3(E_ID_LOWBEAM, unsigned int, unTest, unsigned short, usTest, unsigned char, ucTest)
        END_OF_ACTION
    END_OF_MSG_TYPE
}
