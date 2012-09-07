#include "def.h"

//ToDo:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// => CAN
// => Lecture accéléro


//Comments:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=> Do a Search in Files (CTRL+SHIFT+F) with "ToDo" to find incomplete
//   statements.


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unsigned int VUE32_ID = VUE32_4;

unsigned int flag_fsm = 0;
unsigned int pb_clk_test;

//vue32_i2c.c
extern short accel_x, accel_y, accel_z;

//interrupts.c
extern volatile unsigned int flag_1ms;

//vue32_adc.c
extern volatile unsigned int flag_adc_filter;
extern unsigned int adc_mean[ADC_CH];

//NetV USB-CDC
char USB_In_Buffer[64];
char USB_Out_Buffer[64];
BOOL stringPrinted;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                         Prototypes                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

static void InitializeSystem(void);
void ProcessIO(void);
void USBDeviceTasks(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();

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
	

    //Test function - To be removed later
    init_adxl345();
    /*
    ShortDelay(50*US_TO_CT_TICKS);
    while(1)
    {

	dummy = read_adxl345(0x32);
	//init_adxl345();
	ShortDelay(1000*US_TO_CT_TICKS);
    }*/

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

	//I2C Polling
	if(flag_1ms)
	{
	    flag_1ms = 0;
	    read_adxl345(0x32);
	}

	//NetV on USB-CDC
	ProcessIO();
	update_variables();
	netv_transceiver(canAddr);
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
    init_i2c();
    init_change_notification();

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
}

static void InitializeSystem(void)
{
// The USB specifications require that USB peripheral devices must never source
// current onto the Vbus pin.  Additionally, USB peripherals should not source
//  current on D+ or D- when the host/hub is not actively powering the Vbus line.
// When designing a self powered (as opposed to bus powered) USB peripheral
// device, the firmware should make sure not to turn on the USB module and D+
// or D- pull up resistor unless Vbus is actively powered.  Therefore, the
// firmware needs some means to detect when Vbus is being powered by the host.
// A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// can be used to detect when Vbus is high (host actively powering), or low
// (host is shut down or otherwise not supplying power).  The USB firmware
// can then periodically poll this I/O pin to know when it is okay to turn on
// the USB module/D+/D- pull up resistor.  When designing a purely bus powered
// peripheral device, it is not possible to source current on D+ or D- when the
// host is not actively providing power on Vbus. Therefore, implementing this
// bus sense feature is optional.  This firmware can be made to use this bus
// sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
// HardwareProfile.h file.
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

// If the host PC sends a GetStatus (device) request, the firmware must respond
// and let the host know if the USB peripheral device is currently bus powered
// or self powered.  See chapter 9 in the official USB specifications for details
// regarding this request.  If the peripheral device is capable of being both
// self and bus powered, it should not return a hard coded value for this request.
// Instead, firmware should check if it is currently self or bus powered, and
// respond accordingly.  If the hardware has been configured like demonstrated
// on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
// currently selected power source.  On the PICDEM FS USB Demo Board, "RA2"
// is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
// has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
// to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;    // See HardwareProfile.h
    #endif

    USBDeviceInit();    //usb_device.c.  Initializes USB module SFRs and firmware
                        //variables to known states.
}//end InitializeSystem


/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{
    // If suspended, do nothing.
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    //NetV Function:
    netv32_usb_task();

    // Service the USB CDC driver
    CDCTxService();

} // End ProcessIO


// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
    // Insert appropriate code here for the desired
    // application behavior.  If the microcontroller will be put to sleep, a
    // process similar to that shown below may be used:

    /* Example power saving code.

    ConfigureIOPinsForLowPower();
    SaveStateOfAllInterruptEnableBits();
    DisableAllInterruptEnableBits();

    // Should enable at least USBActivityIF as a wake source
    EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();
    Sleep();

    // Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
    RestoreStateOfAllPreviouslySavedInterruptEnableBits();

    // Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
    RestoreIOPinsToNormal();

    // IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is
    // cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause
    //  to not work as intended.
    */

}


/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *                  suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *                  mode, the host may wake the device back up by sending non-
 *                  idle state signalling.
 *
 *                  This call back is invoked when a wakeup from USB suspend
 *                  is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
    // If clock switching or other power savings measures were taken when
    // executing the USBCBSuspend() function, now would be a good time to
    // switch back to normal full power run mode conditions.  The host allows
    // a few milliseconds of wakeup time, after which the device must be
    // fully back to normal, and capable of receiving and processing USB
    // packets.  In order to do this, the USB module must receive proper
    // clocking (IE: 48MHz clock must be available to SIE for full speed USB
    // operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

    // Typically, user firmware does not need to do anything special
    // if a USB error occurs.  For example, if the host sends an OUT
    // packet to your device, but the packet gets corrupted (ex:
    // because of a bad connection, or the user unplugs the
    // USB cable during the transmission) this will typically set
    // one or more USB error interrupt flags.  Nothing specific
    // needs to be done however, since the SIE will automatically
    // send a "NAK" packet to the host.  In response to this, the
    // host will normally retry to send the packet again, and no
    // data loss occurs.  The system will typically recover
    // automatically, without the need for application firmware
    // intervention.

    // Nevertheless, this callback function is provided, such as
    // for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 *                  firmware must process the request and respond
 *                  appropriately to fulfill the request.  Some of
 *                  the SETUP packets will be for standard
 *                  USB "chapter 9" (as in, fulfilling chapter 9 of
 *                  the official USB specifications) requests, while
 *                  others may be specific to the USB device class
 *                  that is being implemented.  For example, a HID
 *                  class device needs to be able to respond to
 *                  "GET REPORT" type of requests.  This
 *                  is not a standard USB chapter 9 request, and
 *                  therefore not handled by usb_device.c.  Instead
 *                  this request should be handled by class specific
 *                  firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckCDCRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *                  called when a SETUP, bRequest: SET_DESCRIPTOR request
 *                  arrives.  Typically SET_DESCRIPTOR requests are
 *                  not used in most applications, and it is
 *                  optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 *                  SET_CONFIGURATION (wValue not = 0) request.  This
 *                  callback function should initialize the endpoints
 *                  for the device's usage according to the current
 *                  configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    CDCInitEP();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 *                  peripheral devices to wake up a host PC (such
 *                  as if it is in a low power suspend to RAM state).
 *                  This can be a very useful feature in some
 *                  USB applications, such as an Infrared remote
 *                  control	receiver.  If a user presses the "power"
 *                  button on a remote control, it is nice that the
 *                  IR receiver can detect this signalling, and then
 *                  send a USB "command" to the PC to wake up.
 *
 *                  The USBCBSendResume() "callback" function is used
 *                  to send this special USB signalling which wakes
 *                  up the PC.  This function may be called by
 *                  application firmware to wake up the PC.  This
 *                  function should only be called when:
 *
 *                  1.  The USB driver used on the host PC supports
 *                      the remote wakeup capability.
 *                  2.  The USB configuration descriptor indicates
 *                      the device is remote wakeup capable in the
 *                      bmAttributes field.
 *                  3.  The USB host PC is currently sleeping,
 *                      and has previously sent your device a SET
 *                      FEATURE setup packet which "armed" the
 *                      remote wakeup capability.
 *
 *                  This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()

 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;

    USBResumeControl = 1;       // Start RESUME signaling

    delay_count = 1800U;        // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}


/*******************************************************************
 * Function:        void USBCBEP0DataReceived(void)
 *
 * PreCondition:    ENABLE_EP0_DATA_RECEIVED_CALLBACK must be
 *                  defined already (in usb_config.h)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called whenever a EP0 data
 *                  packet is received.  This gives the user (and
 *                  thus the various class examples a way to get
 *                  data that is received via the control endpoint.
 *                  This function needs to be used in conjunction
 *                  with the USBCBCheckOtherReq() function since
 *                  the USBCBCheckOtherReq() function is the apps
 *                  method for getting the initial control transfer
 *                  before the data arrives.
 *
 * Note:            None
 *******************************************************************/
#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void)
{
}
#endif


/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }
    return TRUE;
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