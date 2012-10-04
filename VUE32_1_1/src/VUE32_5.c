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

#include "def.h"

/*
 * Specific Initialization
 */
void InitVUE32_5(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_5(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_5(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_BRAKEPEDALPOT, unsigned short, 5)
                ANSWER1(E_ID_BRAKEPEDALSWITCH, unsigned char, 5)
                ANSWER1(E_ID_ACCELERATORPOT1, unsigned short, 5)
                ANSWER1(E_ID_ACCELERATORPOT2, unsigned short, 5)
                ANSWER1(E_ID_STEERINGANGLESENSOR, unsigned int, 5)
                ANSWER1(E_ID_TRANSMISSIONCONTROL, unsigned short, 5)
                ANSWER1(E_ID_IGNITIONKEY, unsigned short, 5)
                LED2 = ~LED2;
    END_OF_MSG_TYPE

}

