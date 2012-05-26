

#include "Light_Param.h"

#if defined(DEBUG)
    unsigned int dummy_var;
#endif
 
void Light_init(void)
{
    LIGHT_OUTPUT == 2;
    TRISE = 0x00FC;
}
/*void Light_Read(void){


    for(Light_counter=0;Light_counter<NB_OUTPUT;Light_counter++){
        // output a channel
        DIGITAL_PORT_USED=1<<Light_counter;
        //delay?
        //Read digital value on port
        Light_State[Light_counter]= DIGITAL_PORT_USED;
    }
    Light_Action();
}*/
void Light_Read(void){


    if(Light_counter>=LIGHT_OUTPUT)
    {
        Light_counter=0;
    }
    //Read digital value on port
        Light_State[Light_counter]= DIGITAL_PORT_USED;
    // output a channel
    DIGITAL_PORT_USED=1<<Light_counter;

  Light_counter++;
  Light_Action();
}

void Light_Action(void){
    switch(Light_State[SIGNAL_31])
    {
        case PIN_L:
            //Left Light Flash
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        case PIN_R:
            //Right Light Flash
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        default:
            //do nothing
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
    }
    switch(Light_State[SIGNAL_30])
    {
        case PIN_83b:
            //???
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        case PIN_56a:
            //???
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        case PIN_56b:
            //???
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        case PIN_58:
            //???
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
        default:
            //error, shouldn't happen
            #if defined(DEBUG)
                dummy_var++;
            #endif
            break;
    }

}
