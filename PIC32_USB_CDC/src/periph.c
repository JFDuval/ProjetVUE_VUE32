#include "periph.h"
#include "def.h"

void define_io(void)
{
	//Analog
	TRISB = 0xFFFF;	//All inputs
	
	//HeartBeat LED
	HBLED1 = 0;
	TRIS_HBLED1 = 0;
        HBLED2 = 1;
	TRIS_HBLED2 = 0;
	
//	//SPI1
//	TRIS_SPI_CS = 1;
//	TRIS_SPI_DI = 1;
//	TRIS_SPI_DO = 0;
//	TRIS_SPI_CLK = 1;
//	
//	//Sensors
//	TRIS_FS_D_INT = 1;
//	TRIS_FS_P_INT = 1;
//	TRIS_FS_M_INT = 1;
//	FS_D_CS = 0;		//Shared with PGC
//	TRIS_FS_D_CS = 0;
//	FS_P_CS = 0;
//	TRIS_FS_P_CS = 0;
//	FS_M_CS = 0;
//	TRIS_FS_M_CS = 0;
//	
//	//I2C
//	TRIS_SCL = 1;
//	TRIS_SDA = 1;	
//
}

void setup_core_timer(void)
{
	// configure the core timer roll-over rate (100msec)
    OpenCoreTimer(CORE_TICK_RATE);

    // set up the core timer interrupt with a prioirty of 2 and zero sub-priority
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));

    // enable device multi-vector interrupts
    INTEnableSystemMultiVectoredInt();
}	

void setup_spi1(void)	//EtherCAT
{
	//Need to be configured properly fot the ET1200
	//...
	
 //   unsigned int    config=SPI_CON_MODE16|SPI_CON_SMP|SPI_CON_ON|SPI_CON_MSTEN|SPI_CONFIG_MSSEN;    // SPI configuration word

//    SpiChnOpen(1, config, 16);    // divide fpb by 4, configure the I/O ports. Not using SS in this example
}

void setup_spi2_3_4(void)	//Fingers
{
    unsigned int    config=SPI_CON_MODE16|SPI_CON_SMP|SPI_CON_ON|SPI_CON_MSTEN|SPI_CONFIG_MSSEN;    // SPI configuration word

    SpiChnOpen(2, config, 16);    // divide fpb by 4, configure the I/O ports. Not using SS in this example
    SpiChnOpen(3, config, 16);
    SpiChnOpen(4, config, 16);
}

void setup_adc(void)
{	
	//AN2 to AN12 as analog inputs
	
    // configure and enable the ADC
    CloseADC10();    // ensure the ADC is off before setting the configuration

    // define setup parameters for OpenADC10
                // Turn module on | ouput in integer | trigger mode auto | disable autosample
    #define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF

    // define setup parameters for OpenADC10
                // ADC ref external    | disable offset test    | disable scan mode | perform 1 samples | use single buffer | don't use alternate mode
    #define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF

    // define setup parameters for OpenADC10
    //                   use ADC internal clock | set sample time
    #define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15


    // define setup parameters for OpenADC10
    // do not assign channels to scan
    #define PARAM4    SKIP_SCAN_ALL


    // define setup parameters for OpenADC10
                // set AN4 and AN5 as analog inputs
    #define PARAM5    ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN6_ANA | ENABLE_AN7_ANA | ENABLE_AN8_ANA | ENABLE_AN9_ANA | ENABLE_AN10_ANA | ENABLE_AN11_ANA | ENABLE_AN12_ANA

        // use ground as neg ref for A | use AN4 for input A      |  use ground as neg ref for A | use AN5 for input B

     // configure to sample AN4 & AN5
    //SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 |  ADC_CH0_NEG_SAMPLEB_NVREF | ADC_CH0_POS_SAMPLEB_AN5); // configure to sample AN4 & AN5
    AD1CHSbits.CH0NA = 0;	//Vref-
    AD1CHSbits.CH0SA = 2;	//Sample AN2 first
    OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using parameter define above
    AD1PCFG = 0xE003;	//AN2-AN12 only
    
    ConfigIntADC10(ADC_INT_PRI_6  | ADC_INT_ON);

    EnableADC10(); // Enable the ADC
}
