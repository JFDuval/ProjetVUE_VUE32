

#include "cn_vue32.h"
void __ISR(_CHANGE_NOTICE_VECTOR, ipl4) CNHandler(void)
{

    if (PORTCbits.RC14 =0)//CN0 down
    {
        speed[0]=CONV_SPEED(unTimer4Value[0]+TMR4);
        unTimer4Value[1]+=TMR4;
        unTimer4Value[0]=0;
    }
    if (PORTCbits.RC13 =0)//CN1 down
    {
        speed[1]=CONV_SPEED(unTimer4Value[1]+TMR4);
        unTimer4Value[0]+=TMR4;
        unTimer4Value[1]=0;
    }
    TMR4=0;
    IFS1CLR = _IFS1_CNIF_MASK;
}
void __ISR(_TIMER_4_VECTOR, ipl4) Timer4Handler(void)
{
    //Shouldn't happen, error
    TMR4=0;
    speed[0] =0 ;
    speed[0] = 0 ;
    IFS0CLR = _IFS0_T4IF_MASK;
}
void Input_Notification_Init(void)
{
    //Configure Timer 4
    T4CONbits.SIDL = 0 ;    //continue operation while CPU is IDLE
    T4CONbits.TCKPS = 7 ;    //prescaler value =2^(TCKPS+1)
    T4CONbits.TCS = 0 ;      //Internal clock (1= external clock)
    T4CONbits.T32 = 0 ;       // 16-bit Timer
    
    //enable individual input pin (CNx) with pull-up or pull down if desired
    CNPUE = 0x00000000; //pull-up not desired
    CNENbits.CNEN0 = 1 ;
    CNENbits.CNEN1 = 1 ;


    
    //clear the interrupt priority bit
    IFS1bits.CNIF = 0 ;
    IEC1bits.CNIE = 1 ;
    IPC6bits.CNIP = 4 ;
    
    //enable the CN module
    CNCONbits.ON = 1 ;
    //Configure the Input Capture
    T4CONbits.ON = 1 ;

    unTimer4Value[0] =0;
    unTimer4Value[1] =0;

}

