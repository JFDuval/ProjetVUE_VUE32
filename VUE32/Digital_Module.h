

#ifndef DIGITAL_MODULE_H
#define DIGITAL_MODULE_H
#include "VUE32def.h"
#include "def.h"

/* ***LIGHT**** */
    //Sortie du pic (toujours les premiers)
    #define LIGHT_SIGNAL_30       0
    #define LIGHT_SIGNAL_31       1
    //Entré du pic
    #define LIGHT_SIGNAL_56a      2
    #define LIGHT_SIGNAL_56b      3
    #define LIGHT_SIGNAL_58       4
    #define LIGHT_SIGNAL_83b      5
    #define LIGHT_SIGNAL_L        6
    #define LIGHT_SIGNAL_R        7



    #define LIGHT_PIN_30        (1<<LIGHT_SIGNAL_30)
    #define LIGHT_PIN_31        (1<<LIGHT_SIGNAL_31)
    #define LIGHT_PIN_L         (1<<LIGHT_SIGNAL_L)
    #define LIGHT_PIN_R         (1<<LIGHT_SIGNAL_R)
    #define LIGHT_PIN_56a       (1<<LIGHT_SIGNAL_56a)
    #define LIGHT_PIN_56b       (1<<LIGHT_SIGNAL_56b)
    #define LIGHT_PIN_58        (1<<LIGHT_SIGNAL_58)
    #define LIGHT_PIN_83b       (1<<LIGHT_SIGNAL_83b)

/* ***WIPER**** */
    #define WIPER_SIGNAL_53b  7
    #define WIPER_SIGNAL_53c  6
    #define WIPER_SIGNAL_54   5
    #define WIPER_SIGNAL_W    4
    #define WIPER_SIGNAL_I    3
    #define WIPER_SIGNAL_15   2
    #define WIPER_SIGNAL_31   1
    #define WIPER_SIGNAL_31b  0

    #define WIPER_END_COURSE_SIGNAL 1

    //sortie
    #define WIPER_PIN_53b     (1<<WIPER_SIGNAL_53b)
    #define WIPER_PIN_53c     (1<<WIPER_SIGNAL_53c)
    #define WIPER_PIN_54      (1<<WIPER_SIGNAL_54)
    #define WIPER_PIN_W       (1<<WIPER_SIGNAL_W)
    #define WIPER_PIN_I       (1<<WIPER_SIGNAL_I)
    //Entré
    #define WIPER_PIN_15      (1<<WIPER_SIGNAL_15)
    #define WIPER_PIN_31      (1<<WIPER_SIGNAL_31)
    #define WIPER_PIN_31b     (1<<WIPER_SIGNAL_31b)
    
    #define WIPER_END_COURSE_PIN (1<<WIPER_END_COURSE_SIGNAL)
    
/* ****Windows**** */
    #define WINDOW_BUTTON_OUTPUT_SIGNAL 0
    #define WINDOW_BUTTON_OUTPUT_PIN (1<<WINDOW_BUTTON_OUTPUT_SIGNAL)
    #define WINDOW_BUTTON_INPUT_DOWN_SIGNAL 1
    #define WINDOW_BUTTON_INPUT_DOWN_PIN (1<<WINDOW_BUTTON_INPUT_DOWN_SIGNAL)
    #define WINDOW_BUTTON_INPUT_UP_SIGNAL 2
    #define WINDOW_BUTTON_INPUT_UP_PIN (1<<WINDOW_BUTTON_INPUT_UP_SIGNAL)
    #define WINDOW_MOTOR MOTOR_A

    #define CHARGER_INDICATOR_SIGNAL 0
    #define CHARGER_INDICATOR_PIN (1<<CHARGER_INDICATOR_SIGNAL)

    


    #define DIGITAL_PORT_USED PORTE
    #define DIGITAL_TRIS_USED TRISE
    #define DEF_LIGHT_OUTPUT 2
    #define DEF_WIPER_OUTPUT 3




char Light_counter;
unsigned int Light_State[DEF_LIGHT_OUTPUT];
char Flag_Timer2;
unsigned char LIGHT_OUTPUT;


unsigned char WIPER_OUTPUT;
unsigned char Wiper_counter;
unsigned int Wiper_State[DEF_WIPER_OUTPUT];


void Wiper_init(void);
void Wiper_Read(void);
void Wiper_Action(void);


void Light_init(void);
void Light_Read(void);
void Light_Action(void);

void Starter_Key_Init(void);
void Starter_Key(void);

void Charger_Init(void);
void Charger(void);

void End_Wiper_Course_Init(void);
void End_Wiper_Course(void);

void Window_Button_Init(void);
void Window_Button(void);


#endif
