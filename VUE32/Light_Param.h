

#include "def.h"

    #define NB_INPUT 6
    #define DEF_LIGHT_OUTPUT 2

    //#if (NB_INPUT+NB_OUTPUT>8)
    //#error you can't use an digital port if you have more than the 8 bit
    //#endif

    #define DIGITAL_PORT_USED PORTE

    //Sortie du pic (toujours les premiers)
    #define SIGNAL_30       0
    #define SIGNAL_31       1
    //Entré du pic
    #define SIGNAL_56a      2
    #define SIGNAL_56b      3
    #define SIGNAL_58       4
    #define SIGNAL_83b      5
    #define SIGNAL_L        6
    #define SIGNAL_R        7



    #define PIN_30      (1<<SIGNAL_30)
    #define PIN_31     (1<<SIGNAL_31)
    #define PIN_L     (1<<SIGNAL_L)
    #define PIN_R     (1<<SIGNAL_R)
    #define PIN_56a      (1<<SIGNAL_56a)
    #define PIN_56b       (1<<SIGNAL_56b)
    #define PIN_58      (1<<SIGNAL_58)
    #define PIN_83b       (1<<SIGNAL_83b)



char Light_counter;
unsigned int Light_State[DEF_LIGHT_OUTPUT];
char Flag_Timer2;
unsigned char LIGHT_OUTPUT;

void Light_init(void);
void Light_Read(void);
void Light_Action(void);
