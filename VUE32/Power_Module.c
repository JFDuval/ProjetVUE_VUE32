#include "Power_Module.h"


void Low_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Low_Light;
}
void Low_Light(void)
{
    if(power_module == 1)
    {
        if(cLowLight ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_LOW_LIGHT+3));
        }
        if(cLowLight ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_LOW_LIGHT+3));
        }
    }
    if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_LOW_LIGHT+3));
    }
}

void Left_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Left_Light;
    cLeftLight =0;
}
void Left_Light(void)
{
    TIMESTAMP_SECURITY(unLastLeftLightTimestamp,100);
    if(COMPARE_TIMESTAMP(unLastLeftLightTimestamp,100))
    {
        if(cLeftLight == 1)
        {
            if(LeftLighToggle)
            {
                PORTD = PORTD | (1<<(PWR_PIN_POSITION_LEFT_LIGHT+3));
                LeftLighToggle = 0;
            }
            else
            {
                PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_LEFT_LIGHT+3));
                LeftLighToggle = 1;
            }

        }
        else
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_LEFT_LIGHT+3));
            LeftLighToggle = 1;
        }
        unLastLeftLightTimestamp = unGlobalTimestamp;
    }
}

void Right_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Right_Light;
}
void Right_Light(void)
{
    TIMESTAMP_SECURITY(unLastRightLightTimestamp,100);
    if(COMPARE_TIMESTAMP(unLastRightLightTimestamp,100))
    {
        if(cRightLight == 1)
        {
            if(RightLighToggle)
            {
                PORTD = PORTD | (1<<(PWR_PIN_POSITION_RIGHT_LIGHT+3));
                RightLighToggle = 0;
            }
            else
            {
                PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_RIGHT_LIGHT+3));
                RightLighToggle = 1;
            }

        }
        else
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_RIGHT_LIGHT+3));
            RightLighToggle = 1;
        }
        unLastRightLightTimestamp = unGlobalTimestamp;
    }
}

void High_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &High_Light;
}
void High_Light(void)
{
    if(power_module == 1)
    {
        if(cHighLight ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_HIGH_LIGHT+3));
        }
        if(cHighLight ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_HIGH_LIGHT+3));
        }
    }
    if(power_module == 0)
    {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_HIGH_LIGHT+3));
    }
}

void Brake_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Brake_Light;
}
void Brake_Light(void)
{
    if(power_module == 1)
    {
        if(cBrakeLight ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_BRAKE_LIGHT+3));
        }
        if(cBrakeLight ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_BRAKE_LIGHT+3));
        }
    }
    if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_BRAKE_LIGHT+3));
    }
}

void Night_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Night_Light;
}
void Night_Light(void)
{
    if(power_module == 1)
    {
        if(cNightLight ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_NIGHT_LIGHT+3));
        }
        if(cNightLight ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_NIGHT_LIGHT+3));
        }
    }
     if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_NIGHT_LIGHT+3));
    }
}

void Cooling_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Cooling_Pump;
    cCoolingPump =1;// need to be changed along with the function
}
void Cooling_Pump(void)
{
    if(power_module == 1)
    {
        if(cCoolingPump ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_COOLING_PUMP+3));
        }
        if(cCoolingPump ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_COOLING_PUMP+3));
        }
    }
    if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_COOLING_PUMP+3));
    }
}
void Wiper_Front_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Wiper_Front_Pump;
    cWiperFrontPump =0;// need to be changed along with the function
}
void Wiper_Front_Pump(void)
{
    if(power_module == 1)
    {
        if(cWiperFrontPump ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_WIPER_FRONT_PUMP+3));
        }
        if(cWiperFrontPump ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_WIPER_FRONT_PUMP+3));
        }
    }
    if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_WIPER_FRONT_PUMP+3));
    }
}
void Wiper_Back_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Wiper_Back_Pump;
    cWiperBackPump =0;// need to be changed along with the function
}
void Wiper_Back_Pump(void)
{
    if(power_module == 1)
    {
        if(cWiperBackPump ==1)
        {
            PORTD = PORTD | (1<<(PWR_PIN_POSITION_WIPER_BACK_PUMP+3));
        }
        if(cWiperBackPump ==0)
        {
            PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_WIPER_BACK_PUMP+3));
        }
    }
    if(power_module ==0)
    {
        PORTD = PORTD & ~(1<<(PWR_PIN_POSITION_WIPER_BACK_PUMP+3));
    }
}


