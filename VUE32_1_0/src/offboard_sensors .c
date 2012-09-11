#include "offboard_sensors.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

short yaw_rate = 0, lateral = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Returns the current in Amps
short read_current(unsigned int adc_in, unsigned int adc_vbat)
{
    //Supply voltage: 12VDC
    //Resistive divider: 10k and 26.7k, Vo = 0.272Vin. 12V => 3.27V
    //Zero value: Vcc/2 = 1.65V = 512bits
    //5.6 mV N* ± 1.3 @ 12 Vdc and N = 1
    //Sensitivity after divider = 5.6mV*N*0.272 = 1.523mV*N
    //Max 400A, 1 turn: 1.523mV*1*400A = 609mV = 189bits
    //400A/189bits = 2.11A/bit ~2A/bit
    //Output is ratiometric - we need to compensate for voltage fluctuations
    //Source: http://www.filur.net/PDF/Honeywell/toka/CSLA1EL.pdf

    unsigned short batt_volt = (unsigned short)read_vbat(adc_vbat);
    unsigned short offset = 0;
    float gain = 0.0;

    //Offset = ((0.272/2)*Vbatt)/3300mV)*1024bits
    //Test: Vbat = 11.85V, Offset = (0.136*11850)/3300)*1024 = 500
    //Equivalent to 0.0422*Vbatt
    offset = (unsigned short)((float)batt_volt * 0.0422);
    //1.523mV/A = 0.473A/bit
    gain = ((float)batt_volt/12000)*0.473;

    return (int)((float)(adc_in - offset)/gain);
}

//Bosch Yaw-rate and Lateral acceleration sensor
void read_yaw_lateral(unsigned int adc_yaw, unsigned int adc_lateral)
{
    //Supply voltage: 12VDC
    //Reference voltage: 2.5V. Span: 0.65V - 4.35V
    //Resistive divider: 10k and 3.24k, Vo = 0.755Vin. 4.35V => 3.285V
    //Our reference voltage will then be 0.755*2.5V = 1.888V = 586 bits

    //Yaw-rate: 100 deg/s max, 18mV/deg/s, so ±1.8V*0.755 = ±1.36V = ±422bits
    //0.237 deg/s/bit

    //Lateral acceleration: 1.8g max, 1000mV/g, so ±1.8V*0.755 = ±1.36V = ±422bits
    //4.265e-3g/bit

    //Yaw-rate * 1000
    yaw_rate = 237*(adc_yaw - 586);

    //Lateral acceleration * 100000
    lateral = 427*(adc_lateral - 586);
}

//IR155-3204 Isometer - Ground fault interrupt sensor
//ToDo Test in progress - do not like low Freq...
unsigned short gfi_freq_sensor(void)
{
    //This function needs to be called each ~1ms
    //Maximum frequency: 50Hz (20ms)

    static unsigned short pin_state = 0, last_pin_state = 0;
    static unsigned short counter = 0;
    static unsigned short result = FREQ_0HZ;

    //Count period
    counter += 1;

    //Read DIOE0:
    pin_state = DIO_GFI_FREQ;

    //If there is a frequency on the pin:
    if(pin_state)
    {
	if(!last_pin_state)
	{
	    //Rising edge detected

	    if(counter <= COUNT_50HZ)
	    {
		result = FREQ_50HZ;
	    }
	    else if((counter >= COUNT_40HZ-2) && (counter <= COUNT_40HZ+2))
	    {
		result = FREQ_40HZ;
	    }
	    else if((counter >= COUNT_30HZ-3) && (counter <= COUNT_30HZ+3))
	    {
		result = FREQ_30HZ;
	    }
	    else if((counter >= COUNT_20HZ-5) && (counter <= COUNT_20HZ+5))
	    {
		result = FREQ_20HZ;
	    }
	    else if((counter >= COUNT_10HZ-10) && (counter <= COUNT_10HZ+10))
	    {
		result = FREQ_10HZ;
	    }

	    counter = 0;    //Reset counter
	}
    }

    //Otherwise:
    if(counter >= COUNT_0HZ)
    {
	counter = 0;
	result = FREQ_0HZ;
    }

    last_pin_state = pin_state;

    return result;
}

//0 = Error, 1 = OK
unsigned short gfi_state_sensor(void)
{
    //Read DIOE1:
    TRIS_DIO_GFI_STATE = 1;  //make sure it's an input ToDo move

    return DIO_GFI_STATE;
}
