/******************************************************************************
 * VUE32 #3 functions implementation
 *  - CAN2: Drives
 *  - Speed sensor, front right
 *  - Speed sensor, front left
 *  - Main contactor
 *  - Cooling pump
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"

#include "def.h"

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_3_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_FR, 4, 0x00},
    {E_ID_WHEELVELOCITYSSENSOR_FL, 4, 0x00},
};

// Mapping between pins and functionnalities
#define WHEELVELOCITYSSENSOR_FR SPDO1
#define WHEELVELOCITYSSENSOR_FR_TRIS SPDO1_TRIS
#define WHEELVELOCITYSSENSOR_FL SPDO2
#define WHEELVELOCITYSSENSOR_FL_TRIS SPDO2_TRIS

unsigned int tm_unRandom = 65000;

/*
 * Specific Initialization
 */
void InitVUE32_3(void)
{
     // Set the ground fault pins as input
     WHEELVELOCITYSSENSOR_FL_TRIS = 1;
     WHEELVELOCITYSSENSOR_FR_TRIS = 1;

     // Set the LED2 as output (test)
     LED2_TRIS = 0;

     srand( TMR3 );
}

/*
 * State Machine Processing
 */
void ImplVUE32_3(void)
{
}

/*
 * Message Processing
 */
void OnMsgVUE32_3(NETV_MESSAGE *msg)
{
        // Deal with GETVALUE requests
        ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FR, unsigned int, 3)
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FL, unsigned int, 3)
            LED2 = ~LED2;
        END_OF_MSG_TYPE
}

