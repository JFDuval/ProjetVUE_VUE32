/******************************************************************************
 * VUE32 #4 functions implementation
 *  - Light Control
 *  - Wiper end-of-course switch
 *  - Flashers (Right and Left)
 *  - Wipers
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"

#include "def.h"

/*
 * Specific Initialization
 */
void InitVUE32_4(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_4(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_4(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_FRONTLIGHTCONTROL, unsigned short, 4)
            ANSWER1(E_ID_WIPERSENDOFCOURSE, unsigned char, 4)
            LED2 = ~LED2;
    END_OF_MSG_TYPE
}

