#include "Power_Module.h"


void Fct_Low_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Low_Light;
}
void Fct_Low_Light(void)
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

void Fct_Left_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Left_Light;
    cLeftLight =0;
}
void Fct_Left_Light(void)
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

void Fct_Right_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Right_Light;
}
void Fct_Right_Light(void)
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

void Fct_High_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_High_Light;
}
void Fct_High_Light(void)
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

void Fct_Brake_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Brake_Light;
}
void Fct_Brake_Light(void)
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

void Fct_Night_Light_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Night_Light;
}
void Fct_Night_Light(void)
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

void Fct_Cooling_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Cooling_Pump;
    cCoolingPump =1;// need to be changed along with the function
}
void Fct_Cooling_Pump(void)
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
void Fct_Wiper_Front_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Wiper_Front_Pump;
    cWiperFrontPump =0;// need to be changed along with the function
}
void Fct_Wiper_Front_Pump(void)
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
void Fct_Wiper_Back_Pump_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Wiper_Back_Pump;
    cWiperBackPump =0;// need to be changed along with the function
}
void Fct_Wiper_Back_Pump(void)
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


