
#include "periph.h"
#include "Timer_Param.h"
#include "ADC_Param.h"
#include "PWM_Param.h"
#include "Device_configuration.h"
/* VUE32 differents Module */
#include "VUE32def.h"
#include "Analogic_Module.h"
#include "Digital_Module.h"
#include "Power_Module.h"
#include "internalTemp.h"

char VUE32_ID;
unsigned int pb_clk_test;


void VUE32_init(void)
{
    unsigned char i;

    // For now, let's say we have the board #5a
    VUE32_ID = VUE32_5a;

    // Initialize the function array
    for(i =0 ; i<= MAX_FUNCTION ; i ++)
    {
        function_table[i] = 0;      //address for the reset, so if our pic doesn't stop resetting, we have an error somewhere because of that
        variable_array[i] = 0;      //Variable to send
    }
    ucFunctTableSize = 0;
    ucVariableArraySize = 0;
    
    // Initialise Pinout For every VUE32
    // with the exeption of the logical
    // Pin as the input/output can be different
    pinout_init();
    Timer1_init();  // Timer 1 serves as the main clock for the code. It's this timer that run the Global Timestamp
    AD1_init(VUE32_ADC_CHANNEL); // The ADC will be used for whatever VUE32 we are, we just don't need all the value he's going to get
    InternalTemp_init(); // Internal temperature is present on every VUE32
    
    
    // Depending of the board ID,
    // initialize the necessary modules and put
    // them in the function array
    if(VUE32_ID == VUE32_5a)
    {
        PWM_init(VUE32_5A_PWM_MOTOR);
        MOTOR_A.max_current = VUE32_5A_MOTOR_A_MAX_CURRENT; 
        MOTOR_B.max_current = VUE32_5A_MOTOR_B_MAX_CURRENT;
        Wiper_init();
    }
    if(VUE32_ID == VUE32_5b)
    {
        Light_init();       //initialise the wipers pin configuration
    }
    if(VUE32_ID == VUE32_6)
    {
        // Re-Transmit to OdB the Steering Wheels angle
    }
    if(VUE32_ID == VUE32_7)
    {
        Speed_Sensor_Left_Front_Init();
        Speed_Sensor_Right_Front_Init();
    }
    if(VUE32_ID == VUE32_8)
    {
        Speed_Sensor_Right_Rear_Init();
    }
    if(VUE32_ID == VUE32_9)
    {
        //to fill up
    }
    if(VUE32_ID == VUE32_10)
    {
        Speed_Sensor_Left_Rear_Init();
    }
}

int main(void){
    // Configure for SYSCLK (80MHz) and some config
    pb_clk_test=SYSTEMConfig(SYSCLK, SYS_CFG_PCACHE);

    // Enable multivectoring interruption system
    INTEnableSystemMultiVectoredInt();

    // Initialise peripheral depending on the VUE32's need
    VUE32_init();
    
    asm volatile ("ei"); //This routine enables the core to handle any pending interrupt requests

    unsigned char ucFuncTablePos = 0;

    while (1) //repeat continously
    {
            // Execute the current module
            function_table[ucFuncTablePos]();
            
            // Switch to the next one
            ucFuncTablePos += 1;
            // Turn over if touched the number of function
            if ( ucFuncTablePos == ucFunctTableSize )
            {
                ucFuncTablePos = 0;
            }


            if ( Flag_Timer1 )
            {
                mLED_1 ^= 1;   //alive led
                Flag_Timer1 = 0;
            }
    }
    return 0;
}






/*
void Timer1_ADC()
{
    if (flagAD1 == TRUE)
            {
                AD1_Mean();
                flagAD1 = FALSE;
            #if defined(DEBUG)
                count = ADC_DATA_FREQUENCY;
            #endif
            }

    if(Flag_Timer1==1)  //~100Hz
            {
                    Timer1_cnt++;
                    if(Timer1_cnt > 99)    //0.1Hz
                    {
                        Timer1_cnt = 0;
                        board_temp = CONV_TEMP((int)AD1_mean[6]);
                    }

                     Motor1_current = CONV_CURRENT(AD1_mean[4]);  //Motor 1
                     Motor2_current = CONV_CURRENT(AD1_mean[5]);  //Motor 2
                     Wiper_Read();//do a scan
                 Flag_Timer1 = 0;
            }
}

*/

