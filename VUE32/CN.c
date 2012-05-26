

#include "CN_param.h"
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{

    if (PORTCbits.RC14 =0)//CN0 down
    {
        speed[0]=conv_speed(timer_value[0]+TMR2);
        timer_value[1]+=TMR2;
        timer_value[0]=0;
    }
    if (PORTCbits.RC13 =0)//CN1 down
    {
        speed[1]=conv_speed(timer_value[1]+TMR2);
        timer_value[0]+=TMR2;
        timer_value[1]=0;
    }
    TMR2=0;
    IFS1CLR = _IFS1_CNIF_MASK;
}
void __ISR(_TIMER_2_VECTOR, ipl4) Timer2Handler(void)
{
    //Shouldn't happen, error
    TMR2=0;
    speed[0]=0;
    speed[1]=0;
    IFS0CLR = _IFS0_T2IF_MASK;
}
void Input_Notification_Init(void)
{
    //Configure Timer 2
    T2CONbits.SIDL = 0 ;    //continue operation while CPU is IDLE
    T2CONbits.TCKPS = 0;    //prescaler value =2^(TCKPS)
    T2CONbits.TCS = 0;      //Internal clock (1= external clock)
    T2CONbits.T32 =0;       // 16-bit Timer
    
    //enable individual input pin (CNx) with pull-up or pull down if desired
    CNPUE = 0x00000000; //pull-up not desired
    CNENbits.CNEN0 =1;
    CNENbits.CNEN1 =1;


    
    //clear the interrupt priority bit
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    IPC6bits.CNIP = 4;
    
    //enable the CN module
    CNCONbits.ON = 1;
    //Configure the Input Capture
    T2CONbits.ON = 1;

}

