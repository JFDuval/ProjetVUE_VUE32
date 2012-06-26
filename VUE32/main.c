/* VUE32 differents Module */
#include "VUE32def.h"
#include "analogic_module.h"
#include "digital_module.h"
#include "power_module.h"
#include "timer_vue32.h"
#include "adc_vue32.h"
#include "pwm_vue32.h"
#include "periph.h"
#include "Device_configuration.h"

//  The VUE 32 has two motor (MOTOR_A and MOTOR_B) which you just neet to configure the time and current
//  Also, the VUE 32 has multiple analog input which just need to be added (you can specify only the port number on which you connected your device
//  Finally, you have the Power module which is more of a logic module being activated

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
    Fct_pinout_init();
    Fct_Timer1_init();  // Timer 1 serves as the main clock for the code. It's this timer that run the Global Timestamp
    Fct_AD1_init(VUE32_ADC_CHANNEL); // The ADC will be used for whatever VUE32 we are, we just don't need all the value he's going to get
    Fct_Internal_Temp_init(); // Internal temperature is present on every VUE32
    
    
    // Depending of the board ID,
    // initialize the necessary modules and put
    // them in the function array
    if(VUE32_ID == VUE32_1)
    {
        //to fill
        //Send CMD to Controler
    }
    if(VUE32_ID == VUE32_2)
    {
        // to fill
        // Cooling Pump
        // Send speed sensors to OdB
        // Send Charger indicator and BMS

    }
    if(VUE32_ID == VUE32_3)
    {
        // Door1
        
    }
    if(VUE32_ID == VUE32_4)
    {
        // Door2
    }
    if(VUE32_ID == VUE32_5a)
    {
        Fct_PWM_init(VUE32_5A_PWM_MOTOR);
        MOTOR_A.max_current = VUE32_5A_MOTOR_A_MAX_CURRENT; 
        MOTOR_B.max_current = VUE32_5A_MOTOR_B_MAX_CURRENT;
        Fct_Wiper_init();
    }
    if(VUE32_ID == VUE32_5b)
    {
        Fct_Light_init();       //initialise the wipers pin configuration
    }
    if(VUE32_ID == VUE32_6)
    {
        // Re-Transmit to OdB the Steering Wheels angle
        
    }
    if(VUE32_ID == VUE32_7)
    {
        Fct_Speed_Sensor_Left_Front_Init();
        Fct_Speed_Sensor_Right_Front_Init();
    }
    if(VUE32_ID == VUE32_8)
    {
        Fct_Speed_Sensor_Right_Rear_Init();
        Fct_Speed_Sensor_Left_Rear_Init();
    }
    if(VUE32_ID == VUE32_9)
    {
        //to fill up
        
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

