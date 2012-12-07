#include "offboard_sensors.h"
#include "def.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                    Constants and variables                               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                          Functions                                       //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

//Returns the current in Amps
short read_current(unsigned short adc_in, unsigned short adc_vbat)
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
    //Correction => @3.12v VCC
    offset = (unsigned short)((float)batt_volt * 0.04463);
    //1.523mV/A = 0.473A/bit
    gain = ((float)batt_volt/12000)*0.473;

    adc_in = (adc_in*24)/10;
    float dummy = (((float)adc_in - offset)/gain);
    return (short)dummy;
}


//Bosch Yaw-rate and Lateral acceleration sensor
    //Supply voltage: 12VDC
    //Reference voltage: 2.5V. Span: 0.65V - 4.35V
    //Resistive divider: 10k and 3.24k, Vo = 0.755Vin. 4.35V => 3.285V
    //Our reference voltage will then be 0.755*2.5V = 1.888V = 586 bits

    //Yaw-rate: 100 deg/s max, 18mV/deg/s, so ±1.8V*0.755 = ±1.36V = ±422bits
    //0.237 deg/s/bit

    //Lateral acceleration: 1.8g max, 1000mV/g, so ±1.8V*0.755 = ±1.36V = ±422bits
    //4.265e-3g/bit
short read_yaw(unsigned short adc_yaw)
{
    short yaw_rate = 0;

    //Yaw-rate * 1000
    yaw_rate = 237*((short)adc_yaw - 490);

    return yaw_rate;
}

short read_lateral(unsigned short adc_lateral)
{
    short lateral = 0;

    //Lateral acceleration * 100000
    lateral = 427*((short)adc_lateral - 490);

    return lateral;
}

//IR155-3204 Isometer - Ground fault interrupt sensor
//Note: Might oscillate between 2 values at "illegal" frequencies, like 3Hz.
//	Should not happen on the real product.
//Output value: Byte, MSB = Fault, bit 6 = 0Hz High/Low, LSBs = Frequency
unsigned char gfi_freq_sensor(void)
{
    //This function needs to be called each ~1ms
    //Maximum frequency: 50Hz (20ms)

    static unsigned short pin_state = 0, last_pin_state = 0;
    static unsigned short counter = 0;
    static unsigned short result = FREQ_0HZ;

    //Count period
    counter += 1;

    //Read DIOE1:
    pin_state = DIO_GFI_FREQ;

    //If there is a frequency on the pin:
    if(pin_state)
    {
	if(!last_pin_state)
	{
	    //Rising edge detected

	    if((counter >= COUNT_50HZ-2) && (counter <= COUNT_50HZ+1))
	    {
		result = FREQ_50HZ;
	    }
	    else if((counter >= COUNT_40HZ-1) && (counter <= COUNT_40HZ+2))
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

    //Output byte
    result = (result | (DIO_GFI_STATE << 7) | (pin_state << 6));

    last_pin_state = pin_state;

    return result;
}
