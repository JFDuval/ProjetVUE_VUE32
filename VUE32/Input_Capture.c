
#include "Input_Capture_Param.h"

void __ISR(_INPUT_CAPTURE_2_VECTOR, ipl3) InputCaptureHandler(void)
{
    for( IC_Counter =0; IC_Counter <= (ICI_CONST); IC_Counter++)
    {
        Input_Timer_read = IC1BUF;
    }
    IFS0CLR = _IFS0_IC1IF_MASK;

}
void __ISR(_TIMER_2_VECTOR, ipl4) Timer2Handler(void)
{
    //Shouldn't happen, error
    TMR2=0;
    IFS0CLR = _IFS0_T2IF_MASK;
}
void Input_Capture_Init(void)
{
    //Possible to need to uncomment the following line:
    //TRISD = TRISD | (1<<(ICx + 7));
    //Configure Timer 2
    //T2CONbits.FRZ = 0 ;     //continue operation while CPU is stop in Debug
    T2CONbits.SIDL = 0 ;    //continue operation while CPU is IDLE
    T2CONbits.TCKPS = 0;    //prescaler value =2^(TCKPS)
    T2CONbits.TCS = 0;      //Internal clock (1= external clock)
    T2CONbits.T32 =0;       // 16-bit Timer


    //Configure the Input Capture
    IC2CONbits.ICM = 0b010 ;    // Capture mode (010 = falling edge, single capture)
    IC2CONbits.SIDL = 0 ;       //Do not sleep when CPU is idle
    IC2CONbits.C32 = 0 ;        //16-bit Timer (1 = 32-bit timer selected)
    IC2CONbits.ICTMR = 1 ;      //Timer 2 (0= timer3)
    IC2CONbits.ICI = (ICI_CONST) ;     //interruptions on every 0b11+1 captures

    //IC2CONbits.FRZ = 0 ;        //Do not freeze on CPU Debug


    // interruption Enabler
    IFS0bits.T2IF = 0;              // clear interrupt flag
    IPC2bits.T2IP = 4;              // interrupt priority
    IEC0bits.T2IE = 1;              // enable interrupt
    IFS0bits.IC2IF =0;
    IPC2bits.IC2IP =1;
    IEC0bits.IC2IE =1;

    T2CONbits.ON = 1;
    IC2CONbits.ON = 1 ;         //Turn Input Capture On

}
