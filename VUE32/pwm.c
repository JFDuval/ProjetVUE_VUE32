
#include "PWM_Param.h"
#include "VUE32def.h"
unsigned char cPreviousLock;
unsigned char unStartLockTimestamp;

void __ISR(_TIMER_3_VECTOR, ipl3) T3_IntHandler (void)//20kHz
{

    *MOTOR_A.OCx1 = MOTOR_A.IN1;
    *MOTOR_A.OCx2 = MOTOR_A.IN2;
    *MOTOR_B.OCx1 = MOTOR_B.IN1;
    *MOTOR_B.OCx2 = MOTOR_B.IN2;
    
    TMR3=0;
    IFS0bits.T3IF = 0;           // Clearing Timer2 interrupt flag
}

void PWM_init(unsigned char ucMotor)
{
    //configure the timer that is going to be used by the OC
    T3CONbits.ON =0;
    T3CONbits.SIDL = 0 ;                //continue operation while CPU is IDLE
    T3CONbits.TCKPS = T3CKPS;           //prescaler value =2^(TCKPS)
    T3CONbits.TCS = 0;                  //Internal clock (1= external clock)
    IFS0bits.T3IF = 0;                  // clear interrupt flag
    IPC3bits.T3IP = 3;                  // Set T3 interrupt priority to 7
    IEC0bits.T3IE = 1;                  // enable interrupt
    PR3=PERIOD_IN_BIT;                  //PWM_frequency compared to time base
    

    //configure Output compare 1 through 4
    if (ucMotor & 1)
    {
        OC1CONbits.ON = 0;              //close OCx
        OC3CONbits.ON = 0;              //close OCx
        OC1CONbits.OCTSEL = 1;          //Select Timer 3 as time base
        OC3CONbits.OCTSEL = 1;          //Select Timer 3 as time base
        OC1CONbits.OC32 = 0 ;           //Compare only the 16-bit of OCxR
        OC3CONbits.OC32 = 0 ;           //Compare only the 16-bit of OCxR
        OC1CONbits.SIDL = 0 ;           //Continue operation while idle
        OC3CONbits.SIDL = 0 ;           //Continue operation while idle
        OC1CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled
        OC3CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

        OC1R = 0x0000;                  // Initialize primary Compare register
        OC1RS = 0x0000;                 //Initialize second compare register (next value)
        OC3R = 0x0000;                  // Initialize primary Compare register
        OC3RS = 0x0000;                 //Initialize second compare register (next value)

        OC1CONbits.ON = 1;             // Enable OC1
        OC3CONbits.ON = 1;             // Enable OC3


        //configuring the motor
        MOTOR_A.OCx1 = &OC1RS;
        MOTOR_A.OCx2 = &OC3RS;
        MOTOR_A.current = &AD1_mean[MOTOR_A_ADC_CHANNEL];
        function_table[ucFunctTableSize++] = &pwm_motor_A;

    }
     if(ucMotor & 2)
    {

        OC2CONbits.ON = 0;              //close OCx
        OC4CONbits.ON = 0;              //close OCx
        OC2CONbits.OCTSEL = 1;          //Select Timer 3 as time base
        OC4CONbits.OCTSEL = 1;          //Select Timer 3 as time base
        OC2CONbits.OC32 = 0 ;           //Compare only the 16-bit of OCxR
        OC4CONbits.OC32 = 0 ;           //Compare only the 16-bit of OCxR
        OC2CONbits.SIDL = 0 ;           //Continue operation while idle
        OC4CONbits.SIDL = 0 ;           //Continue operation while idle
        OC2CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled
        OC4CONbits.OCM = 0b110;         // Configure for PWM mode without Fault pin enabled

        OC2R = 0x0000;                  // Initialize primary Compare register
        OC2RS = 0x0000;                 //Initialize second compare register (next value)

        OC4R = 0x0000;                  // Initialize primary Compare register
        OC4RS = 0x0000;                 //Initialize second compare register (next value)

        OC2CONbits.ON = 1;             // Enable OC2
        OC4CONbits.ON = 1;             // Enable OC4

        //configuring the motor
        MOTOR_B.OCx1 = &OC2RS;
        MOTOR_B.OCx2 = &OC4RS;
        MOTOR_B.current = &AD1_mean[MOTOR_B_ADC_CHANNEL];
        function_table[ucFunctTableSize++] = &pwm_motor_B;
    }
    T3CONbits.ON =1;               //Activate Timer3
}

void pwm_motor_A()
{
    // do something with motor A
    // think about current in the motor depending on the motor type

}
void pwm_motor_B()
{
    // do something with motor B
}


void motor_control( MOTOR *sel_motor,unsigned char dir, unsigned char speed)
{
    (*sel_motor).IN1 = 0;
    (*sel_motor).IN2 = 0;

    /*Select output*/
    switch(dir)
    {
        case CW:
            //forward
            if (speed < 95 && speed > 5 )
            {
            //sel_motor.IN1 = CONV_SPEED(speed);
                (*sel_motor).IN1 = CONV_SPEED(speed) ;
                (*sel_motor).IN2 = 0;
            }
            break;
        case CCW:
            //Reverse
            if (speed < 95 && speed > 5 )
            {
            (*sel_motor).IN1 = 0;
            (*sel_motor).IN2 = CONV_SPEED(speed);
            }
            break;
        case BRAKE:
            //Brake
            (*sel_motor).IN1 = PERIOD_IN_BIT;
            (*sel_motor).IN2 = PERIOD_IN_BIT;
            break;
        default:
            //Coast
            break;
    }

}

void Lock_Init(void)    //Must be called after defining the lock state
{
    function_table[ucFunctTableSize++] = &Lock;
    cPreviousLock = LOCK_UNKNOWN;
}
void Lock(void)
{
    if (cPreviousLock = LOCK_UNKNOWN)
    {
        cPreviousLock = cLock;
    }
    if(power_module == 1)
    {

        if(cLock ==LOCK_LOCKED && cPreviousLock != LOCK_UNLOCKED)
        {
            //Push current on CW
            unStartLockTimestamp = unGlobalTimestamp;
            cPreviousLock = LOCK_LOCKED;
        }
        else if(cLock ==LOCK_UNLOCKED && cPreviousLock != LOCK_LOCKED)
        {
            //Push current on CCW
            unStartLockTimestamp = unGlobalTimestamp;
            cPreviousLock = LOCK_UNLOCKED;
        }
        if(unStartLockTimestamp + 75 > unGlobalTimestamp)
        {
            //Stop pushing current
        }
    }
}
