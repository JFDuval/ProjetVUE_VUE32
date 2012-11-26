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
#include "VUE32_Impl.h"
#include "Board.h"
#include "vue32_i2c.h"


#include "def.h"


//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//user_input.c
extern volatile unsigned char set_flashers;

//Interrupt.h
extern volatile unsigned int flag_1ms_a, flag_8ms;
extern volatile unsigned int flag_flash;

unsigned char light_previous_state_vue32_4 = 0;
unsigned char light_state_vue32_4 = 0;
unsigned char wiper_control_previous_state_vue32_4 = 0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_4_Ress[] =
{
    {E_ID_FRONTLIGHTCONTROL, sizeof(unsigned char), Sensor},
    {E_ID_WIPERSENDOFCOURSE, sizeof(unsigned char), Sensor},
    {E_ID_3AXES_ACCEL_X, sizeof(short), Sensor},
    {E_ID_3AXES_ACCEL_Y, sizeof(short), Sensor},
    {E_ID_3AXES_ACCEL_Z, sizeof(short), Sensor},    
    {E_ID_WIPERBLADES, sizeof(unsigned char), Actuator},
    {E_ID_SET_LIGTH_STATE, sizeof(unsigned char), Actuator}    
};

/*
 * Specific Initialization
 */
void InitVUE32_4(void)
{
    //Light lever
    init_light_input();

    // Setup I2C
    init_i2c();

    // Init 3-axis sensor
    init_adxl345();
}

/*
 * State Machine Processing
 */
void ImplVUE32_4(void)
{
    static unsigned char flash = 1, dummy = 0;

    // Process the I2C sensor, result is put in the global variables (accel_x, accel_y and accel_z)
    EVERY_X_MS(1)
        read_adxl345();
        gResourceMemory[E_ID_3AXES_ACCEL_X] = (int)accel_x;
        gResourceMemory[E_ID_3AXES_ACCEL_Y] = (int)accel_y;
        gResourceMemory[E_ID_3AXES_ACCEL_Z] = (int)accel_z;
    END_OF_EVERY

    if(flag_8ms)
    {
        flag_8ms = 0;

        //Light
        //TODO When FRONTLIGTHCONTROL changing, copy the value in (E_ID_SET_LIGTH_STATE. After read the configuration directly in E_ID_SET_LIGTH_STATE
        light_state_vue32_4 = read_light_input();
        if(gResourceMemory[E_ID_FRONTLIGHTCONTROL] != light_state_vue32_4 && light_state_vue32_4 == light_previous_state_vue32_4)
        {
            gResourceMemory[E_ID_FRONTLIGHTCONTROL] = (unsigned int)light_state_vue32_4;
            EmitAnEvent(E_ID_FRONTLIGHTCONTROL, VUE32_1, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_2, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_6, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
            EmitAnEvent(E_ID_SET_LIGTH_STATE, VUE32_7, 1, gResourceMemory[E_ID_FRONTLIGHTCONTROL]);

            light_action((unsigned char)gResourceMemory[E_ID_FRONTLIGHTCONTROL]);
        }
        light_previous_state_vue32_4 = light_state_vue32_4;
    }

    if(flag_1ms_a)
    {
        flag_1ms_a = 0;
        //Wiper state machine:
        wiper_action((unsigned char)gResourceMemory[E_ID_WIPERBLADES]);
    }

    //Flashers
    if(flag_flash)
    {
        flag_flash = 0;

        flash ^= 1;

        if(set_flashers)
        {
            light_flashers(gResourceMemory[E_ID_FRONTLIGHTCONTROL], flash);
        }
        else
        {
            light_flashers(gResourceMemory[E_ID_FRONTLIGHTCONTROL], 0);
        }
    }
}

/*
 * Message Processing
 */
void OnMsgVUE32_4(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_FRONTLIGHTCONTROL, unsigned char, gResourceMemory[E_ID_FRONTLIGHTCONTROL])
            ANSWER1(E_ID_WIPERSENDOFCOURSE, unsigned char, gResourceMemory[E_ID_WIPERSENDOFCOURSE])
            ANSWER1(E_ID_WIPERBLADES, unsigned char, gResourceMemory[E_ID_WIPERBLADES])
            ANSWER1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE])
            ANSWER1(E_ID_3AXES_ACCEL_X, short, gResourceMemory[E_ID_3AXES_ACCEL_X])
            ANSWER1(E_ID_3AXES_ACCEL_Y, short, gResourceMemory[E_ID_3AXES_ACCEL_Y])
            ANSWER1(E_ID_3AXES_ACCEL_Z, short, gResourceMemory[E_ID_3AXES_ACCEL_Z])
            ANSWER1(E_ID_PORT_E, unsigned char, DIO_PORT)
            ANSWER1(E_ID_TRIS_E, unsigned char, DIO_TRIS)
            com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
            ACTION1(E_ID_WIPERBLADES, unsigned char, gResourceMemory[E_ID_WIPERBLADES]) END_OF_ACTION
            ACTION1(E_ID_SET_LIGTH_STATE, unsigned char, gResourceMemory[E_ID_SET_LIGTH_STATE]) END_OF_ACTION
            com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE( NETV_TYPE_EVENT )
        ACTION1(E_ID_WIPERBLADES, unsigned char, gResourceMemory[E_ID_WIPERBLADES]) END_OF_ACTION
        com_led_toggle();
    END_OF_MSG_TYPE

    ON_MSG_TYPE_RTR(NETV_TYPE_SYNCHRONIZE)
        SYNC1(E_ID_3AXES_ACCEL_X, short, gResourceMemory[E_ID_3AXES_ACCEL_X])
        SYNC1(E_ID_3AXES_ACCEL_Y, short, gResourceMemory[E_ID_3AXES_ACCEL_Y])
        SYNC1(E_ID_3AXES_ACCEL_Z, short, gResourceMemory[E_ID_3AXES_ACCEL_Z])
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_4(void)
{
    return;
}


ROUTING_TABLE *gRoutingTableVUE32_4 = NULL;
