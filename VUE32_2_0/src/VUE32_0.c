/******************************************************************************
 * VUE32 #0 functions implementation
 * THIS VERSION IS USED AS A COMPLETE SIMULATOR FOR TESTING PURPOSE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"

#include "Board.h"

#include "def.h"
#include <stdlib.h>
#include <math.h>

// This VUE32 card has to ability to simulate any other card
extern unsigned char m_ucAddrCAN;

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

// Local variables
short sRandomTemp, m_state, sRandomVoltage;

/*Hardware resources manage localy by this VUE32
 * The HDW_MAPPING size has to be set in VUE32_Impl.c 
 * gHardwareSize contents size of every gVUE32_X_Ress 
 * Note this array is used by long pooling functionnality
 */
HDW_MAPPING gVUE32_0_Ress[] =
{
    {E_ID_LEFT_DOOR_STATE, sizeof(unsigned char), Sensor},
    {E_ID_RIGHT_DOOR_STATE, sizeof(unsigned char), Sensor},
    {E_ID_BATTERYCURRENT, 2, Sensor},
    {E_ID_GROUNDFAULT_FREQ, 1, Sensor},
    {E_ID_WHEELVELOCITYSSENSOR_BR, 4, Sensor},
    {E_ID_SET_LIGTH_STATE, 1, Actuator},
    {E_ID_SET_BRAKE_LIGTH_STATE, 2, Actuator},
    {E_ID_WHEELVELOCITYSSENSOR_FR, 4, Sensor},
    {E_ID_WHEELVELOCITYSSENSOR_FL, 4, Sensor},
    {E_ID_BRAKEPEDAL, sizeof(unsigned short), Sensor},      //TO REMOVE
    {E_ID_ACCELERATOR, sizeof(unsigned short), Sensor},     //TO REMOVE
    {E_ID_DPR, sizeof(unsigned char), Sensor},              //TO REMOVE
    {E_ID_COOLINGPUMP, 1, Actuator},
    {E_ID_MAIN_CONTACTOR, 1, Actuator},
    {E_ID_FRONTLIGHTCONTROL, sizeof(unsigned char), Sensor},
    {E_ID_WIPERSENDOFCOURSE, sizeof(unsigned char), Sensor},
    {E_ID_WIPERBLADES, sizeof(unsigned char), Actuator},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},
    {E_ID_BRAKEPEDAL, sizeof(unsigned short), Sensor},
    {E_ID_ACCELERATOR, sizeof(unsigned short), Sensor},
    {E_ID_STEERINGANGLESENSOR, sizeof(unsigned int), Sensor},
    {E_ID_IGNITIONKEY, sizeof(unsigned char), Sensor},
    {E_ID_DPR, sizeof(unsigned char), Sensor},
    {E_ID_STATE_SWICHT_TRUNK, sizeof(unsigned char), Sensor},
    {E_ID_TRUNK_SIGNAL, sizeof(unsigned char), Actuator},
    {E_ID_SET_ROOF_LIGTH, sizeof(unsigned char), Actuator},
    {E_ID_LATERALACCELERATIONSENSOR, sizeof(unsigned short), Sensor},
    {E_ID_YAWRATE, sizeof(unsigned short), Sensor},
    {E_ID_WIPERMODECONTROL, sizeof(unsigned char), Sensor},
    {E_ID_WIPERFLUIDPUMP, sizeof(unsigned char), Actuator},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},
    {E_ID_AUDIOAMPLIFIER, sizeof(unsigned char), Actuator},
    {E_ID_WHEELVELOCITYSSENSOR_BL, sizeof(unsigned int), Sensor},
    {E_ID_LEFT_MOTOR_TEMP, sizeof(unsigned short), Sensor},
    {E_ID_RIGHT_MOTOR_TEMP, sizeof(unsigned short), Sensor},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator},
    {E_ID_SET_BRAKE_LIGTH_STATE,sizeof(unsigned short), Actuator}
};

// Some macro to make the code more clear
#define RANDOM(var, min, max, freq_ms) \
EVERY_X_MS(freq_ms + __LINE__) \
var = (rand() % (max-min)) + min; \
END_OF_EVERY

#define RANDOMSINUS(var, min, max, freq_ms) \
EVERY_X_MS(freq_ms + __LINE__) \
var = (sin((uiTimeStamp/freq_ms) * 0.01) * ((max-min)/2)) + ((max-min)/2) + min; \
END_OF_EVERY

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

    // *** VUE #1 ***
    // E_ID_LEFT_DOOR_STATE, E_ID_RIGHT_DOOR_STATE and E_ID_TRUNK_DOOR_STATE
    RANDOM(gResourceMemory[E_ID_LEFT_DOOR_STATE], 0, 7, 4000);

    // *** VUE #2 ***
    RANDOM(gResourceMemory[E_ID_BATTERYCURRENT], 0, 10, 250);
    RANDOM(gResourceMemory[E_ID_GROUNDFAULT_FREQ], 0, 1, 10000);
    RANDOMSINUS(gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BR], -1000, 1100, 30); // 1 = 0.1 km/h

    // *** VUE #3 ***
    RANDOMSINUS(gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FR], 0, 1100, 40); // 1 = 0.1 km/h
    RANDOMSINUS(gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL], 0, 1100, 30); // 1 = 0.1 km/h
    RANDOM(gResourceMemory[E_ID_COOLINGPUMP], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_MAIN_CONTACTOR], 0, 1, 13300);

    // *** VUE #4 ***
    RANDOM(gResourceMemory[E_ID_FRONTLIGHTCONTROL], 0, 0xFF, 2600)
    RANDOM(gResourceMemory[E_ID_WIPERSENDOFCOURSE], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_WIPERBLADES], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_SET_LIGTH_STATE], 0, 0xFF, 2600)

    // *** VUE #5 ***
    RANDOM(gResourceMemory[E_ID_BRAKEPEDAL], 0, 0xFFFF, 2600)
    RANDOM(gResourceMemory[E_ID_ACCELERATOR], 0, 0xFFFF, 2800)
    RANDOM(gResourceMemory[E_ID_STEERINGANGLESENSOR], 0, 0xFFFF, 1800)
    RANDOM(gResourceMemory[E_ID_IGNITIONKEY], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_DPR], 0, 3, 5100)
    RANDOM(gResourceMemory[E_ID_STATE_SWICHT_TRUNK], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_TRUNK_SIGNAL], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_SET_ROOF_LIGTH], 0, 1, 10000);

    // *** VUE #6 ***
    RANDOMSINUS(gResourceMemory[E_ID_LATERALACCELERATIONSENSOR], 0, 0xFFFF, 14)
    RANDOMSINUS(gResourceMemory[E_ID_YAWRATE], 0, 0xFF, 26)
    RANDOM(gResourceMemory[E_ID_WIPERMODECONTROL], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_WIPERFLUIDPUMP], 0, 1, 10000);
    RANDOM(gResourceMemory[E_ID_SET_LIGTH_STATE], 0, 7, 10000);
    //RANDOM(gResourceMemory[E_ID_AUDIOAMPLIFIER], 1, 10000);

    // *** VUE #7 ***
    RANDOMSINUS(gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_BL], -1000, 1100, 36); // 1 = 0.1 km/h
    RANDOMSINUS(gResourceMemory[E_ID_LEFT_MOTOR_TEMP], 300, 1000, 102)
    RANDOMSINUS(gResourceMemory[E_ID_RIGHT_MOTOR_TEMP], 350, 1000, 103)

    // *** BMSs ***
    RANDOMSINUS(sRandomTemp, 20, 110, 1000)
    RANDOM(m_state, 2, 5, 900)
    RANDOMSINUS(sRandomVoltage, 2100, 3700, 350)
}

/*
 * Message Processing
 */
void OnMsgVUE32_0(NETV_MESSAGE *msg)
{
    // Try to simulate all other cards, excepted for broadcasted messages
    if ( msg->msg_dest >= NETV_ADDRESS_BROADCAST )
        m_ucAddrCAN = 0;
    else
        m_ucAddrCAN = msg->msg_dest;

    switch( msg->msg_dest )
    {
        case VUE32_1:
            OnMsgVUE32_1(msg);
            break;
        case VUE32_2:
            OnMsgVUE32_2(msg);
            break;
        case VUE32_3:
            OnMsgVUE32_3(msg);
            break;
        case VUE32_4:
            OnMsgVUE32_4(msg);
            break;
        case VUE32_5:
            OnMsgVUE32_5(msg);
            break;
        case VUE32_6:
            OnMsgVUE32_6(msg);
            break;
        case VUE32_7:
            OnMsgVUE32_7(msg);
            break;
        default:
            if ( msg->msg_dest > 0x10 && msg->msg_dest < 0x29 )
            {
            ON_MSG_TYPE(VUE32_TYPE_GETVALUE)

                // Maximum Temperature in the resistor array
                ANSWER1(E_ID_BMS_BOARD_TEMP, short, sRandomTemp)

                // temp
                if (m_state == 3)
                {
                    ANSWER3(E_ID_BMS_STATE_READONLY, short, (short)m_state, short, (short)1, unsigned short, 3600 )
                }
                else
                {
                    ANSWER1(E_ID_BMS_STATE_READONLY, short, (short)m_state)
                }

                if ( msg->msg_cmd == E_ID_BMS_CELL_GROUP1)
                {
                    NETV_MESSAGE oCopy = *msg;
                    ANSWER4(E_ID_BMS_CELL_GROUP1, short, (short)0,
                            short, (short)(sRandomVoltage+1),
                            short, (short)(sRandomVoltage+100),
                            short, sRandomTemp)

                    *msg = oCopy; // Reset the msg structure to allow proper interpretation
                    ANSWER3(E_ID_BMS_CELL_GROUP1, short, (short)1,
                            short, (short)(sRandomVoltage-50),
                            short, (short)(sRandomVoltage-100))
                }

                if ( msg->msg_cmd == E_ID_BMS_CELL_GROUP2)
                {
                    NETV_MESSAGE oCopy = *msg;
                    ANSWER4(E_ID_BMS_CELL_GROUP2, short, (short)0,
                            short, (short)(sRandomVoltage),
                            short, (short)(sRandomVoltage+20),
                            short, sRandomTemp)

                    *msg = oCopy; // Reset the msg structure to allow proper interpretation
                    ANSWER3(E_ID_BMS_CELL_GROUP2, short, (short)1,
                            short, (short)(sRandomVoltage-20),
                            short, (short)(sRandomVoltage-5))
                }
            END_OF_MSG_TYPE
            }
            break;
    }
}

/* Put emergency instructions here
 * Every device manage by this VUE32 and has to be
 * manage differently in emergency mode
 * must be manage in this function
 */
void OnEmergencyMsgVUE32_0(void)
{
    return;
}

/*
 * Not used
 * Do a static routing between to different network
 * without an network address translation
 */
ROUTING_TABLE *gRoutingTableVUE32_0 = NULL;
