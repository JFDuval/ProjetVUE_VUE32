
#ifndef PWM_PARAM_H
#define PWM_PARAM_H


#include "def.h"
#include "VUE32def.h"

#define PWM_FREQUENCY 20000
#define T3CKPS 0
#define PERIOD_IN_BIT ((FPB/PWM_FREQUENCY) -1)     // 
#define PWM_MAX_RESOLUTION 12
#define MOTOR_A_ADC_CHANNEL 4
#define MOTOR_B_ADC_CHANNEL 5

#define COAST   0
#define CW      1
#define CCW     2
#define BRAKE   3

typedef struct
{
    unsigned int IN1;
    unsigned int IN2;
    volatile unsigned int *OCx1;
    volatile unsigned int *OCx2;    //Assign to Output compare Register for next length
    unsigned int max_current;
    volatile unsigned int *current;  //Assign to corresponding ADC value

} MOTOR;

#define CONV_SPEED(x) (x*PERIOD_IN_BIT/100)


 MOTOR MOTOR_A;
 MOTOR MOTOR_B;
         
 
//Lock Variable
unsigned char cLock;

void PWM_init(unsigned char ucMotor);
void motor_control(MOTOR *sel_motor,unsigned char dir, unsigned char speed);

void pwm_motor_A();
void pwm_motor_B();
void Lock_Init(void);
void Lock(void);

#endif

