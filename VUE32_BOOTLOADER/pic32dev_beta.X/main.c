#include "bsp.h"
#include "NETV32_Common.h"
#include "NETV32_Shared.h"
#include "NETV32_SerialDriver.h"

#include "USB-CDC_Microchip/usb.h"
#include "USB-CDC_Microchip/usb_function_cdc.h"
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "USB-CDC_Microchip\usb_device.h"
#include "USB-CDC_Microchip\usb.h"

#include <plib.h>
#include <p32xxxx.h>

#define	_CPU_NAME_	"32MX460F512H"
#define	FLASHEND	(512 * 1024L)
#define	RAMEND		(16 * 1024L)

#define FLASH_PROG_BASE		0x9D000000
#define USER_APP_ADDR 		0x9D001000

//LEDs
#define HBLED1 		PORTBbits.RB12
#define TRIS_HBLED1	TRISBbits.TRISB12
#define HBLED2		PORTBbits.RB13
#define TRIS_HBLED2	TRISBbits.TRISB13

/** V A R I A B L E S ********************************************************/
char USB_In_Buffer[64];
char USB_Out_Buffer[64];

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
void USBDeviceTasks(void);

//*****************************************************************************
//*	this routine was taken from the Microchip bootloader
static void  JumpToApp()
{
    void			(*fptr)(void);
    unsigned long	firstLongWord;

    fptr			=	(void (*)(void))USER_APP_ADDR;
    firstLongWord	=	(unsigned long)*((unsigned long *)USER_APP_ADDR);

    // Only jump if the memory isn't cleared
    if (firstLongWord != (unsigned long)0xFFFFFFFF)
    {
            fptr();
    }
}

//************************************************************************
static	void  delay_microSeconds(unsigned long microSeconds)
{
volatile unsigned long	tickCount;

	tickCount	=	(microSeconds * (80000000UL / 1000000)) / 9;

	while (tickCount > 0)
	{
		__asm__ volatile ("nop");
		tickCount--;
	}
}

//************************************************************************
static	void  delay_ms(unsigned long ms)
{
unsigned long	ii;

	for (ii = 0; ii< ms; ii++)
	{
		delay_microSeconds(1000);
	}
}

//*****************************************************************************
static void  	BootLED_Init()
{
    //HeartBeat LED
    HBLED1 = 0;
    TRIS_HBLED1 = 0;
    HBLED2 = 1;
    TRIS_HBLED2 = 0;
}

//*****************************************************************************
//*	this is for AVR compatiblility
#define	kFlashBufferSize	512
char			gFlashDataBuffer[kFlashBufferSize];
char			gPageBuffer[1024];

//*****************************************************************************
static void InitFlashBuffer(void)
{
unsigned int	ii;

	for (ii=0; ii<kFlashBufferSize; ii++)
	{
		gFlashDataBuffer[ii]	=	0xFF;
	}
}

//*****************************************************************************
//*	write 256 bytes of date
static void boot_page_write(long address)
{
void			*actualFlashAddress;
unsigned int	returnCode;

	actualFlashAddress	=	(void *)FLASH_PROG_BASE;
	actualFlashAddress	+=	address;

#ifdef _USE_WORD_WRITE_
	unsigned int ii;
	for (ii=0; ii<256; ii+=4)
	{
	unsigned long	theLongWord;

		theLongWord	=	(gFlashDataBuffer[ii + 3] & 0x0ff) << 24;
		theLongWord	+=	(gFlashDataBuffer[ii + 2] & 0x0ff) << 16;
		theLongWord	+=	(gFlashDataBuffer[ii + 1] & 0x0ff) << 8;
		theLongWord	+=	(gFlashDataBuffer[ii + 0] & 0x0ff);

		NVMWriteWord(actualFlashAddress, theLongWord);


		actualFlashAddress	+=	4;
	}
#else
	// Write 128 words
//	NVMWriteRow((void*)actualFlashAddress, (void *)gFlashDataBuffer);
//unsigned int NVMProgram(void * address, const void * data, unsigned int size, void* pagebuff);
	returnCode	=	NVMProgram(	actualFlashAddress,				//	Destination address to start writing from.
								(void *)gFlashDataBuffer,		//	Location of data to write.
								256,							//	Number of bytes to write.
								(void *)gPageBuffer);
#endif

}


//*****************************************************************************
static void boot_page_fill(long address, int data)
{
int				bufferOffset;

	bufferOffset	=	address % 256;

	gFlashDataBuffer[bufferOffset]		=	data & 0x0ff;
	gFlashDataBuffer[bufferOffset + 1]	=	(data >> 8) & 0x0ff;
}

#define	PIC32_PAGE_SIZE         4096
#define	EEPROM_SIZE		4096
//*****************************************************************************
//*	Erase the entire chip
//*	this looks at each 4096 byte block, if it is already all 0xff, then it is left alone,
//*	if even one byte is non-0xff, then the entire block gets erasased
//*****************************************************************************
static void boot_chip_erase(void)
{
unsigned char	*actualFlashAddress;
unsigned int	returnCode;
unsigned int	ii;
unsigned char	erasePage;

	actualFlashAddress	=	(unsigned char *)FLASH_PROG_BASE;
	while ((long)actualFlashAddress < (FLASH_PROG_BASE + FLASHEND - EEPROM_SIZE ))
	{
		//*	look through the page and make sure it needs to be erased
		erasePage	=	0;
		for (ii=0; ii<PIC32_PAGE_SIZE; ii++)
		{
			if (actualFlashAddress[ii] != 0x0ff)
			{
				erasePage	=	1;
				break;
			}
		}
		if (erasePage)
		{
			returnCode	=	NVMErasePage(actualFlashAddress);
		}


		actualFlashAddress	+=	PIC32_PAGE_SIZE;
	}
}

//*****************************************************************************
static unsigned int	pgm_read_word_far(unsigned long argAddress)
{
unsigned int	theData;
unsigned char	*memoryPtr;

	memoryPtr	=	(char *)FLASH_PROG_BASE;

	theData	=	(memoryPtr[argAddress + 1] & 0x00ff) << 8;
	theData	+=	(memoryPtr[argAddress] & 0x00ff);


	return(theData);
}

//*****************************************************************************
void init_default_variables(void)
{
    memset(&g_globalNETVVariables, 0, sizeof(GlobalNETVVariables));
}

//*****************************************************************************
int main()
{
    BootLED_Init();

    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above.
    SYSTEMConfig(SYS_XTAL_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Timout for the bootloader stage
    unsigned long   boot_timeout	=	10 * 100000;		//*	should be about 10 seconds

    //set variables to zero
    init_default_variables();

    //Open USB
    netv32_init_usb_cdc();

	//USB setup
	InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    //DEVCFG3bits.FVBUSONIO = 0;	//VBUSON is IO

	//Main loop
	while (1)
	{
		#if defined(USB_POLLING)
        // Check bus status and service USB interrupts.
        USBDeviceTasks();
        // Interrupt or polling method.  If using polling, must call
        // this function periodically.  This function will take care
        // of processing and responding to SETUP transactions
        // (such as during the enumeration process when you first
        // plug in).  USB hosts require that USB devices should accept
        // and process SETUP packets in a timely fashion.  Therefore,
        // when using polling, this function should be called
        // frequently (such as once about every 100 microseconds) at any
        // time that a SETUP packet might reasonably be expected to
        // be sent by the host to your device.  In most cases, the
        // USBDeviceTasks() function does not take very long to
        // execute (~50 instruction cycles) before it returns.
        #endif

        // Application-specific tasks.
        // Application related code may be added here, or in the ProcessIO() function.
            BYTE numBytesRead;

            //Blink the LEDs according to the USB device status

            //
            // User Application USB tasks
            //

            // If suspended, do nothing.
            if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

            // If character received, echo it
            if(mUSBUSARTIsTxTrfReady())
            {
                numBytesRead = getsUSBUSART(USB_Out_Buffer,64);
                if(numBytesRead != 0)
                {
                    BYTE i;

                    #ifdef NETV

                    #else
                    for(i=0;i<numBytesRead;i++)
                    {
                        USB_In_Buffer[i] = USB_Out_Buffer[i];
                    }

                    putUSBUSART(USB_In_Buffer,numBytesRead);	//Echo
                    HBLED1 ^= 1; //Toggle LEDs
                    HBLED2 ^= 1;
                    #endif
                }
            }

            // Service the USB CDC driver
            CDCTxService();
	}
/*
    while (1)
    {
        boot_timer		=	0;
        boot_state		=	0;
        rcvCharCounter	=	0;


        InitFlashBuffer();

        while (boot_state == 0)
        {
                while ((!(Serial_Available())) && (boot_state == 0))		// wait for data
                {
                        delay_microSeconds(10);
                        boot_timer++;
                        if (boot_timer > boot_timeout)
                        {
                                boot_state	=	1; // (after ++ -> boot_state=2 bootloader timeout, jump to main 0x00000 )
                        }


                        //*	this blinks the LED during waiting
                        if ((boot_timer % _BLINK_LOOP_COUNT_) == 0)
                        {
                            HBLED1 ^= 1; //Toggle LEDs
                            HBLED2 ^= 1;
                        }
                }
                boot_state++; // ( if boot_state=1 bootloader received byte from UART, enter bootloader mode)
        }



        netv32_usb_task();

        //Right now will never come out of this function (blocking on serial port)
        netv_transceiver(canAddr);
        update_variables();
    }*/
}
//*****************************************************************************



//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                           Fonctions                                      //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


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

void netv_proc_message(NETV_MESSAGE *message)
{
    // Handle messages here
}

