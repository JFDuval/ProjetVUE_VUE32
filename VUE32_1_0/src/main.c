#include "def.h"

//Comments:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=> Do a Search in Files (CTRL+SHIFT+F) with "ToDo" to find incomplete
//   statements.


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int VUE32_ID = VUE32_GENERIC;

unsigned int pb_clk_test;

unsigned short current = 0;
unsigned char gfi_freq = 0;
extern unsigned short steering_angle;
unsigned int wheel_spdo1_kph = 0, wheel_spdo2_kph = 0;
unsigned char user_input = 0;

//vue32_i2c.c
extern short accel_x, accel_y, accel_z;

//interrupts.c
extern volatile unsigned int flag_1ms_a, flag_1ms_b;
unsigned int flag_fsm = 0;

//vue32_adc.c
extern volatile unsigned int flag_adc_filter;
extern unsigned int adc_mean[ADC_CH];

//wheel_sensor.c
extern unsigned int period_spdo1, period_spdo2;

//NetV USB-CDC
char USB_In_Buffer[64];
char USB_Out_Buffer[64];
BOOL stringPrinted;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Prototypes                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//OpenECoSys NetV
void init_default_variables(void);
void netv_proc_message(NETV_MESSAGE *message);
void update_variables(void);

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                        Main function                                     //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    //NetV USB-CDC
    unsigned char canAddr = 0;
    BootConfig *bootConfig = NULL;
	
    unsigned int fsm_step = 0;
    unsigned int auto_test = FAIL;

    //Config peripherals, pins, clock, ...
    config();
	
    //USB setup
    InitializeSystem();

    #if defined(USB_INTERRUPT)
    USBDeviceAttach();
    #endif

    //NetV:
    bootConfig = netv_get_boot_config();
    if (bootConfig)
    {
            //read configuration
            netv_read_boot_config(bootConfig);

            //safety
            bootConfig->module_state = BOOT_NORMAL;

            //verify if we have correct configuration
            //write it back if not updated
            if (bootConfig->table_version !=  MODULE_TABLE_VERSION
            || bootConfig->project_id != MODULE_PROJECT_ID
            || bootConfig->code_version != MODULE_CODE_VERSION)
            {
                    bootConfig->table_version = MODULE_TABLE_VERSION;
                    bootConfig->project_id = MODULE_PROJECT_ID;
                    bootConfig->code_version = MODULE_CODE_VERSION;

                    //Set to default address
                    bootConfig->module_id = 1;

                    //Writing back the boot config for the next version
                    netv_write_boot_config(bootConfig);
            }
    }

    //set variables to zero
    init_default_variables();

    //UPDATE NETV ADDRESS
    canAddr = bootConfig->module_id;	

    init_light_input();	//Test function - To be moved later
    /*
    init_wiper_input();

    //Test function - To be removed later
    while (1)
    {
	dummy = read_wiper_input();
	Nop();
	Nop();
	wiper_action(dummy);
	Nop();
	Nop();
    }

    //Test function - To be removed later
    while (1)
    {
	auto_test = test_code1_adc_and_dio();

	if (auto_test)
	    LED2 = 0;
	else
	    LED2 = 1;
    }
*/

    TRIS_DIO_GFI_FREQ = 1;  //make sure it's an input ToDo move
    
    while (1)
    {
	//ToDo
	if (flag_fsm)
	{
	    flag_fsm = 0;

	    switch (fsm_step)
	    {
		case 0:
		    fsm_step += 1;
		    break;

		case 1:
		    fsm_step += 1;
		    break;

		case 2:
		    fsm_step += 1;
		    break;

		case 3:
		    fsm_step = 0;
		    break;
	    }
	}

	//Filter ADC results
	if(flag_adc_filter)
	{
	    flag_adc_filter = 0;
	    filter_adc();
	    Nop();
	}

	//1ms timebase A
	if(flag_1ms_a)
	{
	    flag_1ms_a = 0;

	    #ifdef USE_I2C
	    read_adxl345(0x32);	    //I2C Polling
	    #endif

	    //GFI sensor
	    gfi_freq = gfi_freq_sensor();

	    //User input
	    user_input = read_light_input();	//ToDo
	}

        //1ms timebase B
	if(flag_1ms_a)
	{
            flag_1ms_b = 0;
            
            wheel_spdo1_kph = wheel_freq_to_kph(wheel_period_to_freq(period_spdo1));
            wheel_spdo2_kph = wheel_freq_to_kph(wheel_period_to_freq(period_spdo2));
        }

	//NetV on USB-CDC
	ProcessIO();
	update_variables();
	netv_transceiver(canAddr);

	//Can message processing
	can_recv_message();
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                           Functions                                      //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void config(void)
{
    SYSTEMConfigPerformance(80000000);
    pb_clk_test = SYSTEMConfig(SYSCLK, SYS_CFG_PCACHE);
    SYSTEMConfig(SYSCLK, SYS_CFG_PB_BUS);
    SYSTEMConfigPB(SYSCLK);
    INTEnableSystemMultiVectoredInt();

    //Disable JTAG port
    DDPCONbits.JTAGEN = 0;

    //Define inputs/outputs
    define_io();

    //Peripherals:
    init_adc();
    init_timers();
    init_output_compare();
    #ifdef USE_I2C
    init_i2c();
    init_adxl345();
    #endif
    //init_change_notification();
    init_can2();

    asm volatile ("ei"); //This routine enables the core to handle any pending interrupt requests
}

void netv_proc_message(NETV_MESSAGE *message)
{
    //EMPTY
}

void init_default_variables(void)
{
    memset(&g_globalNETVVariables, 0, sizeof(GlobalNETVVariables));
}

void update_variables(void)
{
    //ADC
    g_globalNETVVariables.adc[0] = (unsigned short) adc_mean[0];
    g_globalNETVVariables.adc[1] = (unsigned short) adc_mean[1];
    g_globalNETVVariables.adc[2] = (unsigned short) adc_mean[2];
    g_globalNETVVariables.adc[3] = (unsigned short) adc_mean[3];
    g_globalNETVVariables.adc[4] = (unsigned short) adc_mean[4];
    g_globalNETVVariables.adc[5] = (unsigned short) adc_mean[5];
    g_globalNETVVariables.adc[6] = (unsigned short) adc_mean[6];
    g_globalNETVVariables.adc[7] = (unsigned short) adc_mean[7];

    //DIOE
    g_globalNETVVariables.port = (unsigned short) PORT_DIO;

    //Accelerometer
    g_globalNETVVariables.accel_x = accel_x;
    g_globalNETVVariables.accel_y = accel_y;
    g_globalNETVVariables.accel_z = accel_z;

    //GFI
    g_globalNETVVariables.gfi_freq = gfi_freq;

    //Steering angle
    //g_globalNETVVariables.steering_angle = steering_angle;	ToDo Fix
    g_globalNETVVariables.steering_angle = PORTE;

    //User input
    g_globalNETVVariables.user_input = user_input;
}




//Config fuses
// SYSCLK = (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// SYSCLK = (8MHz Crystal/ 2 * 20 / 1) = 80MHz
// PBCLK = SYSCLK = 80MHz
#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = ON           	// Debugger Disabled for Starter Kit