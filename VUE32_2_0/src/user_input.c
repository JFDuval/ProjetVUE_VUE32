#include "user_input.h"
#include "def.h"
#include "Board.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

volatile unsigned char set_flashers = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void init_wiper_input(void)
{
    //Set GPIOs
    TRIS_DIO = 0b00000111;
}

unsigned char read_wiper_input(void)
{
    unsigned int wp_status_1 = 0;
    unsigned int wp_status_2 = 0;

    //Set one output, read the inputs:

    //Relax 1 or Relax 2?
    WP_OUT_53c = 1;
    ShortDelay(5*US_TO_CT_TICKS);
    if(WP_IN_31)
        wp_status_1 = WP_RLX2;
    else if(WP_IN_15)
        wp_status_1 = WP_RLX1;
    WP_OUT_53c = 0;

    //ACT1 or ACT2?
    WP_OUT_W = 1;
    ShortDelay(5*US_TO_CT_TICKS);
    if(WP_IN_31)
        wp_status_1 = WP_ACT1;
    else if(WP_IN_15)
        wp_status_1 = WP_ACT2;
    WP_OUT_W = 0;

    //E1 or E2?
    WP_OUT_54 = 1;
    ShortDelay(5*US_TO_CT_TICKS);
    if(WP_IN_31b)
        wp_status_2 = WP_E1;
    else if(WP_IN_15)
        wp_status_2 = WP_E2;
    WP_OUT_54 = 0;

    //E0?
    WP_OUT_I = 1;
    ShortDelay(5*US_TO_CT_TICKS);
    if(WP_IN_15)
        wp_status_2 = WP_E0;
    WP_OUT_I = 0;

    //E3?
    WP_OUT_53b = 1;
    ShortDelay(5*US_TO_CT_TICKS);
    if(WP_IN_15)
        wp_status_2 = WP_E3;
    WP_OUT_53b = 0;

    //Output position and speed in 1 byte:
    return (wp_status_1 | wp_status_2);
}

unsigned int wiper_action(unsigned char wiper_input)
{
    //Here's how it works:
    //E0 through E3 are the speed levels.
    //E0 = Super Slow, ..., E3 = Super Fast
    //Relax 2 (RLX2) = Do Nothing
    //Relax 1 (RLX1) or ACT1 = Move wipers at Ex speed
    //ACT1 = Activates pump
    //ACT2 = Unused for now

    unsigned char speed = (wiper_input & 0x0F);
    unsigned char action = (wiper_input & 0xF0);
    static unsigned char state = 0;

    if(GetBoardID() == VUE32_4) //Wiper arm
    {
        switch(state)
        {
            case 0:     //Initial - stopped
                if((action == WP_RLX1) || (action == WP_ACT1))
                    state = 1;
                else
                    state = 2;
                break;
            case 1:     //Active - moving
                power_out(WIPER_PWR_ARMS,1);    //Move arms
                if((action == WP_RLX1) || (action == WP_ACT1))
                    state = 1;
                else
                    state = 2;
                break;
            case 2:     //Go to rest position...
                if(!DIO_WIPER_SW)
                {
                    power_out(WIPER_PWR_ARMS,0);    //Stop arms
                    state = 0;
                }
                else
                    state = 2;  //Not there yet
                break;
        }
    }

    if(GetBoardID() == VUE32_6) //Wiper fluid pump
    {
        if(action == WP_ACT1)
            power_out(WIPER_PWR_PUMP, WP_PUMP_MAX);
        else
            power_out(WIPER_PWR_PUMP, WP_PUMP_MIN);
    }
}

//Accelerator pedal position.
//0 = Relaxed/Unactivated. ~500 is maximum acceleration (hold tight!)
//Linear from 0 to ~400, then it jumps to ~500
unsigned short read_accelerator(unsigned short adc_in1, unsigned short adc_in2)
{
    unsigned short mean = 0;

    //We have 2 pots in // in the pedal.
    if((adc_in1 > adc_in2 + 5) || (adc_in1 < adc_in2 - 5))
	return 0;   //Problem, we don't want to move!

    mean = (adc_in1 + adc_in2) >> 1;

    //The zero is 42 to 46. We add a small dead band.
    if(mean < DEADBAND)
	return 0;
    else
	return (mean - DEADBAND); 

    return 0;
}

unsigned short read_brake(unsigned short adc_in)
{
    unsigned short sw = DIO_BRAKE_SW;
    unsigned short intensity = 0;
    sw = (sw & 0x01) << 15;

    intensity = adc_in; //Todo Add processing here

    return(intensity | sw);
}

void init_light_input(void)
{
    //Set GPIOs
    TRIS_DIO = 0b01111111;
}

unsigned char read_light_input(void)
{
    unsigned int lt_status_1 = 0;
    unsigned int lt_status_2 = 0;
    unsigned int lt_status_3 = 0;
    unsigned int lt_status_4 = 0;

    //Are we braking?    
    if(read_brake(0))    //ToDo send proper ADC value!
        lt_status_3 = LT_BRAKE;

    //Are we in Reverse?
    if(read_dpr_key() & DPRK_DPR_REVERSE)
        lt_status_4 = LT_REVERSE;

    //Set the output, read the inputs:
    LT_OUT_31 = 1;
    ShortDelay(5*US_TO_CT_TICKS);

    //Flasher?
    if(LT_IN_L)
        lt_status_1 = LT_FLASHER_LEFT;
    else if(LT_IN_R)
        lt_status_1 = LT_FLASHER_RIGHT;

    LT_OUT_31 = 0;
    ShortDelay(5*US_TO_CT_TICKS);

    //Light level?
    lt_status_2 = LT_OFF;   //Default = Off
    if(LT_IN_58)
        lt_status_2 = LT_LOW;
    if(LT_IN_58 && LT_IN_56a)
        lt_status_2 = LT_HIGH;

    //Output flasher and intensity in 1 byte:
    return (lt_status_1 | lt_status_2 | lt_status_3 | lt_status_4);
}

unsigned int light_action(unsigned char light_input)
{
    unsigned char flashers = (light_input & 0x30);
    unsigned char lights = (light_input & 0x0F);
    unsigned char brakes = (light_input & 0x80);
    unsigned char reverse = (light_input & 0x40);

    if((GetBoardID() == VUE32_2) || (GetBoardID() == VUE32_7)) //Right lights: Reverse, Night, Brake
    {
        //Night lights
        if((lights == LT_LOW) || (lights == LT_HIGH))
             power_out(LT_PWR_REAR, 1);
        else
            power_out(LT_PWR_REAR, 0);

        //Brake
        if(brakes == LT_BRAKE)
             power_out(LT_PWR_BRAKE, 1);
        else
            power_out(LT_PWR_BRAKE, 0);

        //Reverse
        if(reverse == LT_REVERSE)
             power_out(LT_PWR_REVERSE, 1);
        else
            power_out(LT_PWR_REVERSE, 0);

	//Flashers
	if(GetBoardID() == VUE32_2)
	{
	    if(flashers == LT_FLASHER_RIGHT)
		//power_out(LT_PWR_FLASH_REAR_RIGHT, 1);
                set_flashers = 1;
	    else
		//power_out(LT_PWR_FLASH_REAR_RIGHT, 0);
                set_flashers = 0;
	}
	if(GetBoardID() == VUE32_7)
	{
	    if(flashers == LT_FLASHER_LEFT)
		//power_out(LT_PWR_FLASH_REAR_LEFT, 1);
                set_flashers = 1;
	    else
		//power_out(LT_PWR_FLASH_REAR_LEFT, 0);
                set_flashers = 0;
	}
    }

    if(GetBoardID() == VUE32_4) //Flashers and low beams
    {
        //Flashers
        if(flashers == LT_FLASHER_LEFT || flashers == LT_FLASHER_RIGHT)
            //power_out(LT_PWR_FLASH_FRONT_LEFT, 1);
            set_flashers = 1;
        else
            //power_out(LT_PWR_FLASH_FRONT_LEFT, 0);
            set_flashers = 0;

        //Low Beams
        if((lights & LT_LOW) == LT_LOW)
             power_out(LT_PWR_FRONT_LOW, 1);
        else
            power_out(LT_PWR_FRONT_LOW, 0);
    }

    if(GetBoardID() == VUE32_6) //High beams
    {
        //Front headlights - High
        if(lights == LT_HIGH)
             power_out(LT_PWR_FRONT_HIGH, 1);
        else
            power_out(LT_PWR_FRONT_HIGH, 0);
    }
}

void light_flashers(unsigned char light_input, unsigned char flash_state)
{
    unsigned char flashers = (light_input & 0x30);

    if((GetBoardID() == VUE32_2) || (GetBoardID() == VUE32_7))
    {
	//Flashers
	if(GetBoardID() == VUE32_2)
	{
	    if(flashers == LT_FLASHER_RIGHT)
		power_out(LT_PWR_FLASH_REAR_RIGHT, flash_state);
	    else
		power_out(LT_PWR_FLASH_REAR_RIGHT, 0);
	}
	if(GetBoardID() == VUE32_7)
	{
	    if(flashers == LT_FLASHER_LEFT)
		power_out(LT_PWR_FLASH_REAR_LEFT, flash_state);
	    else
		power_out(LT_PWR_FLASH_REAR_LEFT, 0);
	}
    }

    if(GetBoardID() == VUE32_4)
    {
        //Left flashers
        if(flashers == LT_FLASHER_LEFT)
            power_out(LT_PWR_FLASH_FRONT_LEFT, flash_state);
        else
            power_out(LT_PWR_FLASH_FRONT_LEFT, 0);

	//Right flashers
        if(flashers == LT_FLASHER_RIGHT)
            power_out(LT_PWR_FLASH_FRONT_RIGHT, flash_state);
        else
            power_out(LT_PWR_FLASH_FRONT_RIGHT, 0);
    }
}

void init_dpr_key(void)
{
    //Configure pins as inputs:
    TRIS_DIO_DPR_SW1 = 1;
    TRIS_DIO_DPR_SW2 = 1;
}

unsigned char read_dpr_key(void)
{
    unsigned char out = 0;

    if(!DIO_DPR_SW2 && DIO_DPR_SW1)
        out = DRIVE;
    else if(!DIO_DPR_SW1 && DIO_DPR_SW2)
        out = REVERSE;
    else
        out = PARK;

    return out;
}

//For trunk, use pin_state = DOOR_TRUNK
//For right door, use pin_state = DOOR_RIGHT
unsigned char read_door(unsigned char pin_state)
{
    if(pin_state)
        return OPENED;
    else
        return CLOSED;

    return;
}
