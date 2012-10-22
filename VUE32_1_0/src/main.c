#include "def.h"

//Comments:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=> Do a Search in Files (CTRL+SHIFT+F) with "ToDo" to find incomplete
//   statements.
//=> At the end of this file there is a listing of board specific functions.


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned char VUE32_ID = VUE32_6;
unsigned int pb_clk_test;
unsigned char gfi_freq = 0;
unsigned short wheel_spdo1_kph = 0, wheel_spdo2_kph = 0;
unsigned char user_input = 0;
unsigned short accel = 0;

//vue32_can.c
extern unsigned short steering_angle;

//vue32_i2c.c
extern short accel_x, accel_y, accel_z;

//offboard_sensors.c
extern short yaw_rate, lateral;

//interrupts.c
extern volatile unsigned int flag_1ms_a, flag_1ms_b;
unsigned int flag_fsm = 0;
extern volatile unsigned char spd1_moving, spd2_moving;

//vue32_adc.c
extern volatile unsigned char flag_adc_filter;
extern unsigned short adc_mean[ADC_CH];
extern char board_temp, current;
extern unsigned short board_volt;
extern unsigned short pedal_accelerator, pedal_brake;

//wheel_sensor.c
extern unsigned short spdo1_mean, spdo2_mean;

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

//Returns the average of the 4 speed sensors, in kph
/*
unsigned char vehicle_spd(void)
{
    unsigned int temp = 0;

    temp =  gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] + \
            gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL];
    temp >>= 4;

    return (temp/10);
}
*/

void delay_clk_a(void)
{
    unsigned int i = 0;

    for(i = 0; i < 13; i++)
        Nop();
}

void delay_clk_b(void)
{
    unsigned int i = 0;

    for(i = 0; i < 10; i++)
        Nop();
}

void serial_out(unsigned short word)
{
    unsigned short mask = 0x8000;
    unsigned char i = 0;

    DIO_DISP_CLK = 0;
    for(i = 0; i < 16; i++)
    {
        DIO_DISP_DATA = ((word & mask) >> (15 - i));
        Nop(); Nop(); Nop();
        DIO_DISP_CLK = 1;
        delay_clk_a();
        DIO_DISP_CLK = 0;
        delay_clk_b();
        mask = mask >> 1;
    }
    delay_clk_b();
    DIO_DISP_DATA = 0;
    DIO_DISP_CLK = 0;
}

void refresh_display(void)
{
    unsigned short word1 = 0xA000;
    unsigned short word2 = 0x8000;
    unsigned short word3 = 0x8000;
    unsigned short tmp1 = 0;

    //Test mode:
    word1 = 0b1011100100101010; //100kph, Left, High, Drive
    word2 = 0b1001100101001011; //50%, 25C
    word3 = 0b0000010100111001; //1337km

    //Real one:
/*
    //Word 1 construction:
    word1 |= ((vehicle_spd() & 0x7F) << 6);     //Speed
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00010000) << 1); //Left
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00100000) >> 1); //Right
    word1 |= ((gResourceMemory[E_ID_FRONTLIGHTCONTROL] & 0b00000011));      //Beams
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00010000) >> 1);               //Drive
    word1 |= ((gResourceMemory[E_ID_DPR] & 0b00100000) >> 3);               //Reverse

    //Word 2 construction:
    tmp1 = ((gResourceMemory[E_ID_MOTOR_TEMP1] + gResourceMemory[E_ID_MOTOR_TEMP1]) >> 1);
    word2 |= (tmp1 & 0x7F);                                                 //Temp
    word2 |= ((E_ID_BATT_LEVEL & 0x7F) << 7);

    //Word 3 construction:
    word3 |= (gResourceMemory[E_ID_ODOMETER] & 0xFFFF);
    */

    //Clock data out
    serial_out(word1);
    serial_out(word2);
    serial_out(word3);
}


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

    unsigned short ts0_buf = 0, ts1_buf = 0;

    //Config peripherals, pins and clock
    config();
    board_specific_config();

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

    //Most of the functions in the while(1) loop are timed by Timer1
    while (1)
    {
	//Filter ADC results
	if(flag_adc_filter)
	{
	    flag_adc_filter = 0;
	    filter_adc();
	    board_specific_adc_decode();
	}

	//1ms timebase A
	if(flag_1ms_a)
	{
	    flag_1ms_a = 0;

	    if(VUE32_ID == VUE32_6)
	    {
		#ifdef USE_I2C
		read_adxl345(0x32);	    //I2C Polling
		#endif
	    }

	    //GFI sensor
	    if(VUE32_ID == VUE32_2)
		gfi_freq = gfi_freq_sensor();

	    //User input
	    if(VUE32_ID == VUE32_4)
            {
		user_input = read_light_input();
                light_action(user_input);
            }
	    if(VUE32_ID == VUE32_6)
		user_input = read_wiper_input();
	    if(VUE32_ID == VUE32_5)
		user_input = read_dpr_key();
	}

        //1ms timebase B
	if(flag_1ms_b)
	{
            flag_1ms_b = 0;

	    //Speed sensors
	    if((VUE32_ID == VUE32_2) || (VUE32_ID == VUE32_7))
	    {
		asm volatile ("di"); //Disable int
		filter_wheel();
		asm volatile ("ei"); //Enable int
		wheel_spdo1_kph = wheel_period_to_kph(spdo1_mean, spd1_moving);
	    }
	    
	    if(VUE32_ID == VUE32_3)
	    {
		asm volatile ("di"); //Disable int
		filter_wheel();
		asm volatile ("ei"); //Enable int
		wheel_spdo1_kph = wheel_period_to_kph(spdo1_mean, spd1_moving);
		wheel_spdo2_kph = wheel_period_to_kph(spdo2_mean, spd2_moving);

	    }

	    //ToDo Power Out

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
    init_can1();

    asm volatile ("ei"); //Enables the core to handle any pending interrupt requests
}

void board_specific_config(void)
{
    if(VUE32_ID == VUE32_GENERIC)
    {
	Nop();
    }
    else if(VUE32_ID == VUE32_1)
    {
	Nop();
    }
    else if(VUE32_ID == VUE32_2)
    {
	//Ground fault inputs
	TRIS_DIO_GFI_STATE = 1;
	TRIS_DIO_GFI_FREQ = 1;

	//Speed sensor
	init_change_notification();
    }
    else if(VUE32_ID == VUE32_3)
    {
	//CAN for the drives
	//init_can2();	    //ToDo Enable

	//Speed sensor
	init_change_notification();
    }
    else if(VUE32_ID == VUE32_4)
    {
	//Light lever
	init_light_input();
    }
    else if(VUE32_ID == VUE32_5)
    {
	//CAN for the steering angle sensor
	//init_can2();	//ToDo Enable

	//Parking lever, key
	init_dpr_key();
    }
    else if(VUE32_ID == VUE32_6)
    {
	#ifdef USE_I2C
	init_i2c();
	init_adxl345();
	#endif

	//Wiper lever
	init_wiper_input();
    }
    else if(VUE32_ID == VUE32_7)
    {
	//CAN for the BMS
	//init_can2();	//ToDo Enable

	//Speed sensor
	init_change_notification();
    }
}

//OpenECoSys Network Viewer:
//==========================

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
    unsigned char powerout = 0;    //ToDo Remove

    //ADC ToDo simplify
    g_globalNETVVariables.adc[0] = adc_mean[0];
    g_globalNETVVariables.adc[1] = adc_mean[1];
    g_globalNETVVariables.adc[2] = adc_mean[2];
    g_globalNETVVariables.adc[3] = adc_mean[3];
    g_globalNETVVariables.adc[4] = adc_mean[4];
    g_globalNETVVariables.adc[5] = adc_mean[5];
    g_globalNETVVariables.adc[6] = adc_mean[6];
    g_globalNETVVariables.adc[7] = adc_mean[7];

    //DIOE
    g_globalNETVVariables.port = (unsigned short) PORT_DIO;

    //Accelerometer
    g_globalNETVVariables.accel_x = accel_x;
    g_globalNETVVariables.accel_y = accel_y;
    g_globalNETVVariables.accel_z = accel_z;

    //GFI
    g_globalNETVVariables.gfi_freq = gfi_freq;

    //Steering angle
    g_globalNETVVariables.steering_angle = steering_angle;

    //User input
    g_globalNETVVariables.user_input = user_input;

    //Board ID
    g_globalNETVVariables.vue32_id = VUE32_ID;

    //Onboard sensors
    g_globalNETVVariables.board_temp = board_temp;
    g_globalNETVVariables.board_volt = board_volt;

    //Wheel speed
    g_globalNETVVariables.spdo1_kph = wheel_spdo1_kph;
    g_globalNETVVariables.spdo2_kph = wheel_spdo2_kph;

    //Power out manual test: ToDo Remove
    powerout = g_globalNETVVariables.power_out;
    //power_out(1, powerout);
    //power_out(2, powerout);
    //power_out(3, powerout);
    //power_out(4, powerout*5);

    g_globalNETVVariables.pedal_accelerator = pedal_accelerator;
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
#pragma config DEBUG    = ON           	// Debugger enabled
