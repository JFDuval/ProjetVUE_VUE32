

#include "def.h"

    #define DEF_WIPER_OUTPUT 3
    #define NB_INPUT 5
    

    //#if (NB_INPUT+NB_OUTPUT>8)
    //#error you can't use an digital port if you have more than the 8 bit
    //#endif

    #define DIGITAL_PORT_USED PORTE

    #define SIGNAL_53b  7
    #define SIGNAL_53c  6
    #define SIGNAL_54   5
    #define SIGNAL_W    4
    #define SIGNAL_I    3
    #define SIGNAL_15   2
    #define SIGNAL_31   1
    #define SIGNAL_31b  0

    //sortie
    #define PIN_53b     (1<<SIGNAL_53b)
    #define PIN_53c     (1<<SIGNAL_53c)
    #define PIN_54      (1<<SIGNAL_54)
    #define PIN_W       (1<<SIGNAL_W)
    #define PIN_I       (1<<SIGNAL_I)
    //Entré
    #define PIN_15      (1<<SIGNAL_15)
    #define PIN_31      (1<<SIGNAL_31)
    #define PIN_31b     (1<<SIGNAL_31b)


unsigned char WIPER_OUTPUT;
unsigned char Wiper_counter;
unsigned int Wiper_State[DEF_WIPER_OUTPUT];


void Wiper_init(void);
void Wiper_Read(void);
void Wiper_Action(void);
