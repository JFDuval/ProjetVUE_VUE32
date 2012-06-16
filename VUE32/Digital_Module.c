
#include "digital_module.h"
#include "pwm_vue32.h"

unsigned int unStarterKeyTimestamp;
unsigned int unChargerTimestamp;
unsigned int unWindowsButtonTimestamp;
unsigned char cWindowDown;
unsigned char cWindowUp;

#if defined(DEBUG)
    unsigned int dummy_var;
#endif

void Fct_Light_init(void)
{
    LIGHT_OUTPUT == 2;
    DIGITAL_TRIS_USED = 0x00FC;
}
void Fct_Light_Read(void){


        if(Light_counter>=LIGHT_OUTPUT)
        {
            Light_counter=0;
        }
        //Read digital value on port
        Light_State[Light_counter++]= DIGITAL_PORT_USED;
  
      // output a channel
      DIGITAL_PORT_USED=1<<Light_counter;
      Fct_Light_Action();
}

void Fct_Light_Action(void){
    cLeftLight =0;
    cRightLight =0;
    cLowLight =0;
    cHighLight =0;
    cNightLight=0;
    switch(Light_State[LIGHT_SIGNAL_31])
    {
        case LIGHT_PIN_L:
            //Left Light Flash
            cLeftLight =1;
            break;
        case LIGHT_PIN_R:
            //Right Light Flash
            cRightLight =1;
            break;
        default:
            //do nothing
            break;
    }
    if(Light_State[LIGHT_SIGNAL_30] & LIGHT_PIN_83b)    // if we see 83b, that means we are at L3
    {
        //Brume (Night ???)
        //cNightLight =1;   // Not activated in our system, replaced with cLowLight
        cLowLight= 1;

    }
    else if(Light_State[LIGHT_SIGNAL_30] &LIGHT_PIN_56b) // 83 is not there but 56b is, L2
    {
        //Normal light 
        cHighLight = 1;
    }
    else if (Light_State[LIGHT_SIGNAL_30] &LIGHT_PIN_58)
    {
        // Low light
        cLowLight = 1;
    }

    if(Light_State[LIGHT_SIGNAL_30] &LIGHT_PIN_56a)
    {
        //Flash des fortes
        cHighLight =1;
    }

}

void Fct_Wiper_init(void)
{
    WIPER_OUTPUT = DEF_WIPER_OUTPUT;
    DIGITAL_TRIS_USED = 0x00E0;
}
void Fct_Wiper_Read(void){

    if(Wiper_counter>=WIPER_OUTPUT)
    {
        Wiper_counter=0;
    }
    //Read digital value on port
        Wiper_State[Wiper_counter++]= DIGITAL_PORT_USED;
    // output a channel
    DIGITAL_PORT_USED=1<<Wiper_counter;
    Fct_Wiper_Action();
}
void Fct_Wiper_Action(void){

    if(Wiper_State[WIPER_SIGNAL_15] & WIPER_PIN_W)
    {
        //ACT2
        // Start fluid in front
        cWiperFrontPump =1;
    }
    else
    {
        cWiperFrontPump =0;
    }
    if(Wiper_State[WIPER_SIGNAL_31] & WIPER_PIN_W)
    {
        //ACT1
        //Start fluid in back
        cWiperBackPump =1;
    }
    else
    {
        cWiperBackPump =0;
    }
    if(Wiper_State[WIPER_SIGNAL_15]&WIPER_PIN_53b)
    {
        //E3

    }
    if(Wiper_State[WIPER_SIGNAL_15]&WIPER_PIN_54)
    {
        //E2

    }
    if(Wiper_State[WIPER_SIGNAL_31b] & WIPER_PIN_54)
    {
        //E1

    }
    if(Wiper_State[WIPER_SIGNAL_15] & WIPER_PIN_I)
    {
        //E0

    }
    if(Wiper_State[WIPER_SIGNAL_31] & WIPER_PIN_53c)
    {
        //Repos 2
        
    }
    if(Wiper_State[WIPER_SIGNAL_15] & WIPER_PIN_53c)
    {
        //Repos1

    }
}

void Fct_Starter_Key_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Starter_Key;
}
void Fct_Starter_Key(void)
{

}

void Fct_Charger_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_Charger;
    DIGITAL_TRIS_USED = DIGITAL_TRIS_USED | CHARGER_INDICATOR_PIN;
}
void Fct_Charger(void)
{
    if(DIGITAL_PORT_USED & CHARGER_INDICATOR_PIN)
    {
        cCharger = 1;
    }
    else
    {
        cCharger = 0;
    }
}

void Fct_End_Wiper_Course_Init(void)
{
    function_table[ucFunctTableSize++] = &Fct_End_Wiper_Course;
    DIGITAL_TRIS_USED = DIGITAL_TRIS_USED | WIPER_END_COURSE_PIN;
}
void Fct_End_Wiper_Course(void)
{
    //how is it generated?
}

void Fct_Window_Button_Init(void)
{
    DIGITAL_PORT_USED = DIGITAL_PORT_USED | WINDOW_BUTTON_OUTPUT_PIN;
    function_table[ucFunctTableSize++] = &Fct_Window_Button;

}
void Fct_Window_Button(void)
{
    if(DIGITAL_PORT_USED & WINDOW_BUTTON_INPUT_DOWN_PIN )
    {
        if((WINDOW_MOTOR.max_current > *(WINDOW_MOTOR.current) )&& cWindowDown == FALSE) // Send windows down
        {
            //go down
            cWindowUp = FALSE;
        }
        if(WINDOW_MOTOR.max_current <= *(WINDOW_MOTOR.current)) // Send windows down
        {
            //Stop!!!
            cWindowDown = TRUE;
        }
    }
    if(DIGITAL_PORT_USED & WINDOW_BUTTON_INPUT_UP_PIN )
    {
        if(WINDOW_MOTOR.max_current > *(WINDOW_MOTOR.current) && cWindowUp == FALSE) // Send windows down
        {
            //go down
            cWindowDown = FALSE;
        }
        if(WINDOW_MOTOR.max_current <= *(WINDOW_MOTOR.current)) // Send windows down
        {
            //Stop!!!
            cWindowUp = TRUE;
        }
    }
}