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


// Mapping between pins and functionnalities
#define WHEELVELOCITYSSENSOR_FR SPDO1
#define WHEELVELOCITYSSENSOR_FR_TRIS SPDO1_TRIS
#define WHEELVELOCITYSSENSOR_FL SPDO2
#define WHEELVELOCITYSSENSOR_FL_TRIS SPDO2_TRIS

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
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FR, unsigned int, WHEELVELOCITYSSENSOR_FR)
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FL, unsigned int, WHEELVELOCITYSSENSOR_FL)
            LED2 = ~LED2;
        END_OF_MSG_TYPE
}

