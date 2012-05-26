
#include "Wiper_Param.h"


void Wiper_init(void)
{
    WIPER_OUTPUT = DEF_WIPER_OUTPUT;
    TRISE = 0x00E0;
}
void Wiper_Read(void){


    if(Wiper_counter>=WIPER_OUTPUT)
    {
        Wiper_counter=0;
    }
    //Read digital value on port
        Wiper_State[Wiper_counter]= DIGITAL_PORT_USED;
    // output a channel
    DIGITAL_PORT_USED=1<<Wiper_counter;

    Wiper_counter++;
    Wiper_Action();
}
void Wiper_Action(void){
    if(Wiper_State[SIGNAL_15] & PIN_W)
    {
        //ACT2
        // Start fluid in front
    }
    if(Wiper_State[SIGNAL_31] & PIN_W)
    {
        //ACT1
        //Start fluid in back

    }
    if(Wiper_State[SIGNAL_15]&PIN_53b)
    {
        //E3

    }    
    if(Wiper_State[SIGNAL_15]&PIN_54)
    {
        //E2

    }
    if(Wiper_State[SIGNAL_31b] & PIN_54)
    {
        //E1
 
    }
    if(Wiper_State[SIGNAL_15] & PIN_I)
    {
        //E0

    }
    if(Wiper_State[SIGNAL_31] & PIN_53c)
    {
        //Repos 2

    }
    if(Wiper_State[SIGNAL_15] & PIN_53c)
    {
        //Repos1

    }
    

}
