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

//Hardware resources manage localy by this VUE32
HDW_MAPPING *gVUE32_1_Ress = NULL;

//memory_map.h
extern unsigned int gResourceMemory[256];

/*
 * Specific Initialization
 */
void InitVUE32_1(void)
{
    // Set the LED2 as output (test)
    LED2_TRIS = 0;
}

/*
 * State Machine Processing
 */
void ImplVUE32_1(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_1(NETV_MESSAGE *msg)
{
    LED2 = ~LED2;

    // Deal with GETVALUE requests ***** TEST *******
    if ( msg->msg_remote == 1 && msg->msg_type == VUE32_TYPE_GETVALUE )
    {
        if ( msg->msg_cmd == E_ID_BATTERYCURRENT ) // E_ID_BATTERYCURRENT
        {
            msg->msg_remote = 0;
            msg->msg_dest = msg->msg_source;
            msg->msg_source = GetMyAddr();
            msg->msg_data_length = 2;
            ((unsigned short*)msg->msg_data)[0] = 0xBEEF;
            netv_send_message(msg);
        }
    }

    /*if ( g_unVUE3FinDelais <= gTimeStamp)
    {
        g_unVUE3FinDelais = gTimeStamp + duree;

        // Faire ce qu'il y a à faire
    }*/
}
//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_1(void)
{
    return;
}

ROUTING_TABLE *gRoutingTableVUE32_1 = NULL;

//Display functions:

//Returns the average of the 4 speed sensors, in kph
unsigned char vehicle_spd(void)
{
    unsigned int temp = 0;

    temp =  gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL];
    temp >>= 4;

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
    unsigned short word1 = 0xA000;
    unsigned short word2 = 0x8000;
    unsigned short word3 = 0x8000;
    unsigned short tmp1 = 0;

    //Test mode:
    word1 = 0b1011100100101010; //100kph, Left, High, Drive
    word2 = 0b1001100101001011; //50%, 25C
    word3 = 0b0000010100111001; //1337km

    //Real one:

    //Word 1 construction:
    word1 |= ((vehicle_spd() & 0x7F) << 6);     //Speed
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00010000) << 1); //Left
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00100000) >> 1); //Right
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00000011));      //Beams
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00010000) >> 1);               //Drive
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00100000) >> 3);               //Reverse

    //Word 2 construction:
    tmp1 = ((gResourceMemory[E_ID_MOTOR_TEMP1] + gResourceMemory[E_ID_MOTOR_TEMP1]) >> 1);
    word2 |= (tmp1 & 0x7F);                                                 //Temp
    word2 |= ((E_ID_BATT_LEVEL & 0x7F) << 7);

    //Word 3 construction:
    word3 |= (gResourceMemory[E_ID_ODOMETER] & 0xFFFF);

    //Clock data out
    serial_out(word1);
    serial_out(word2);
    serial_out(word3);
}