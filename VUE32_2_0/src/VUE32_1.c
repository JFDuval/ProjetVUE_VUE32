/******************************************************************************
 * VUE32 #1 functions implementation
 *  - Bridge
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"
#include "Board.h"
#include "def.h"

void refresh_display(void);

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//Interrupt.h
extern volatile unsigned int flag_8ms;

//Debouncing variables
unsigned char previous_door_right_state = 0 , door_right_state = 0;
unsigned char previous_door_left_state = 0 , door_left_state = 0;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_1_Ress[] =
{
    {E_ID_LEFT_DOOR_STATE, sizeof(unsigned char), Sensor},
    {E_ID_RIGHT_DOOR_STATE, sizeof(unsigned char), Sensor},
    {E_ID_GLOBAL_CAR_SPEED, sizeof(unsigned short), Sensor},
    {E_ID_ODOMETER, sizeof(unsigned short), Sensor}
};

//memory_map.h
extern unsigned int gResourceMemory[256];

/*
 * Specific Initialization
 */
void InitVUE32_1(void)
{
    // Set the LED2 as output (test)
    LED2_TRIS = 0;

    //Door sensors:
    TRIS_DOOR_RIGHT = 1;
    TRIS_DOOR_LEFT = 1;

    //Display
    TRIS_DIO_DISP_CLK = 0;
    TRIS_DIO_DISP_DATA = 0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_1(void)
{
    if(flag_8ms)
    {
        door_right_state = read_door(DOOR_RIGHT) == OPENED ? RIGHT_DOOR_OPENED : CLOSED;
        door_left_state =  read_door(DOOR_LEFT) == OPENED ? LEFT_DOOR_OPENED : CLOSED;
    
        
        //Deboucing RIGHT DOOR
        if(gResourceMemory[E_ID_RIGHT_DOOR_STATE] != door_right_state && door_right_state == previous_door_right_state)
        {
            gResourceMemory[E_ID_RIGHT_DOOR_STATE] = door_right_state;
            EmitAnEvent(E_ID_SET_ROOF_LIGTH_FROM_RIGHT, VUE32_5, 1, gResourceMemory[E_ID_RIGHT_DOOR_STATE]);
        }
        previous_door_right_state = door_right_state;

        //Deboucing LEFT DOOR
        if(gResourceMemory[E_ID_LEFT_DOOR_STATE] != door_left_state && door_left_state == previous_door_left_state)
        {
            gResourceMemory[E_ID_LEFT_DOOR_STATE] = door_left_state;
            EmitAnEvent(E_ID_SET_ROOF_LIGTH_FROM_LEFT, VUE32_5, 1, gResourceMemory[E_ID_LEFT_DOOR_STATE]);
        }
        previous_door_left_state = door_left_state;
    }

    if(gResourceMemory[E_ID_FRONTLIGHTCONTROL] != 0 )
        Nop();
    
    EVERY_X_MS(10)
        refresh_display();
    END_OF_EVERY
}

/*
 * Message Processing
 */
void OnMsgVUE32_1(NETV_MESSAGE *msg)
{
        ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_LEFT_DOOR_STATE, unsigned char, gResourceMemory[E_ID_LEFT_DOOR_STATE])
                ANSWER1(E_ID_RIGHT_DOOR_STATE, unsigned char, gResourceMemory[E_ID_RIGHT_DOOR_STATE])
                ANSWER1(E_ID_GLOBAL_CAR_SPEED, unsigned short, gResourceMemory[E_ID_GLOBAL_CAR_SPEED])
                ANSWER1(E_ID_ODOMETER, unsigned short, gResourceMemory[E_ID_ODOMETER])
                ANSWER1(E_ID_PORT_E, unsigned char, DIO_PORT)
                ANSWER1(E_ID_TRIS_E, unsigned char, DIO_TRIS)
                com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE(VUE32_TYPE_SETVALUE)
            //ACTION1(E_ID_GLOBAL_CAR_SPEED, unsigned short, gResourceMemory[E_ID_GLOBAL_CAR_SPEED]) END_OF_ACTION
            com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE( NETV_TYPE_EVENT )
            ACTION1(E_ID_FRONTLIGHTCONTROL, unsigned char, gResourceMemory[E_ID_FRONTLIGHTCONTROL]) END_OF_ACTION
            ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
        END_OF_MSG_TYPE



}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_1(void)
{
    return;
}

ROUTING_TABLE gRoutingTableVUE32_1[24] =
{
    {NETV_COMM_IFACE_USB, ODB}
};

//Display functions:

//Returns the average of the 4 speed sensors, in kph
unsigned char vehicle_spd(void)
{
    unsigned int temp = 0;

    temp =  gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL];
    temp >>= 2;

    return (temp/10);
}

void delay_clk_a(void)
{
    unsigned int i = 0;

    for(i = 0; i < 13; i++)
        Nop();
}

void delay_clk_b(void)
{
    unsigned int i = 0;

    for(i = 0; i < 10; i++)
        Nop();
}

void serial_out(unsigned short word)
{
    unsigned short mask = 0x8000;
    unsigned char i = 0;

    DIO_DISP_CLK = 0;
    for(i = 0; i < 16; i++)
    {
        DIO_DISP_DATA = ((word & mask) >> (15 - i));
        Nop(); Nop(); Nop();
        DIO_DISP_CLK = 1;
        delay_clk_a();
        DIO_DISP_CLK = 0;
        delay_clk_b();
        mask = mask >> 1;
    }
    delay_clk_b();
    DIO_DISP_DATA = 0;
    DIO_DISP_CLK = 0;
}

void refresh_display(void)
{
    unsigned short word1 = 0x6000;
    unsigned short word2 = 0x8000;
    unsigned short word3 = 0xC000;
    unsigned short tmp1 = 0;

    //Test mode:
/*  unsigned short speed = (uiTimeStamp >> 5) % 120;
    word1 = 0b0110000000101010 | (speed << 6); //100kph, Left, High, Drive
    word2 = 0b1001100101001011; //50%, 25C
    word3 = 0b1100010100111001; //1337km*/

    //Real one:
    //Word 1 construction:
    gResourceMemory[E_ID_GLOBAL_CAR_SPEED] = vehicle_spd();
    word1 |= ((gResourceMemory[E_ID_GLOBAL_CAR_SPEED] & 0x7F) << 6);     //Speed
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & LT_FLASHER_LEFT) << 1);  //Left
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & LT_FLASHER_RIGHT) >> 1); //Right
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00000011));      //Beams
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00010000) >> 1);               //Drive
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00100000) >> 3);               //Reverse

    //Word 2 construction:
    tmp1 = ((gResourceMemory[E_ID_LEFT_MOTOR_TEMP] + gResourceMemory[E_ID_LEFT_MOTOR_TEMP]) >> 1);
    word2 |= (tmp1 & 0x7F);                                                 //Temp
    word2 |= ((E_ID_BATT_LEVEL & 0x7F) << 7);

    //Word 3 construction:
    word3 |= (gResourceMemory[E_ID_ODOMETER] & 0xFFFF);

    //Clock data out
    serial_out(word1);
    serial_out(word2);
    serial_out(word3);
}
