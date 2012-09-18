#include "user_input.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned int VUE32_ID;       //main.c

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

    if(VUE32_ID == VUE32_4) //Wiper arm
    {
        if((action == WP_RLX1) || (action == WP_ACT1))
        {
            if(speed == WP_E0)
                power_out(POWER_OUT_WIPER, WP_SUPER_SLOW);
            else if(speed == WP_E1)
                power_out(POWER_OUT_WIPER, WP_SLOW);
            else if(speed == WP_E2)
                power_out(POWER_OUT_WIPER, WP_FAST);
            else if(speed == WP_E3)
                power_out(POWER_OUT_WIPER, WP_SUPER_FAST);
            else
                power_out(POWER_OUT_WIPER, 0);
        }
        else
            power_out(POWER_OUT_WIPER, 0);
    }

    if(VUE32_ID == VUE32_6) //Wiper fluid pump
    {
        if(action == WP_ACT1)
            power_out(POWER_OUT_WIPER, WP_PUMP_MAX);
        else
            power_out(POWER_OUT_WIPER, WP_PUMP_MIN);
    }
}

unsigned int read_accelerator(unsigned int adc_in)
{
    //If needed, do some computing here

    return(adc_in);
}

unsigned int read_brake(unsigned int adc_in)
{
    //ToDo

    return(0);
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

    //Are we braking?    
    if(read_brake(0))    //ToDo send proper ADC value!
        lt_status_3 = 0x80;

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
    return (lt_status_1 | lt_status_2 | lt_status_3);
}

unsigned int light_action(unsigned char light_input)
{
    unsigned char flashers = (light_input & 0xE0);
    unsigned char lights = (light_input & 0x0F);
    unsigned char brakes = (light_input & 0x80);

    if(VUE32_ID == VUE32_4) //Front Low/Night, Both flashers
    {
        //Front headlights - Low
        if(lights == LT_LOW)
             power_out(LT_PWR_FRONT_LOW, LT_MAX);
        else
            power_out(LT_PWR_FRONT_LOW, LT_MIN);

        //Left flashers
        if(flashers == LT_FLASHER_LEFT)
             power_out(LT_PWR_FLASH_LEFT, LT_MAX);
        else
            power_out(LT_PWR_FLASH_LEFT, LT_MIN);

        //Right flashers
        if(flashers == LT_FLASHER_RIGHT)
             power_out(LT_PWR_FLASH_RIGHT, LT_MAX);
        else
            power_out(LT_PWR_FLASH_RIGHT, LT_MIN);
    }

    if(VUE32_ID == VUE32_6) //High, Rear, Brakes
    {
        //Front headlights - High
        if(lights == LT_HIGH)
             power_out(LT_PWR_FRONT_HIGH, LT_MAX);
        else
            power_out(LT_PWR_FRONT_HIGH, LT_MIN);

        //Rear night lights
        if(lights == LT_LOW || lights == LT_HIGH)
             power_out(LT_PWR_REAR, LT_MAX);
        else
            power_out(LT_PWR_REAR, LT_MIN);

        //Rear brake lights //ToDo Proportionnal
        if(brakes == LT_BRAKE)
             power_out(LT_PWR_BRAKE, LT_MAX);
        else
            power_out(LT_PWR_BRAKE, LT_MIN);
    }
}
