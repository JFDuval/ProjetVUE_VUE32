#include "serial.h"
#include <plib.h>
#include "bsp.h"
#include "NETV32_SerialDriver.h"

// UART 1 interrupt handler
// it is set at priority level 2
void __ISR(_UART1_VECTOR, ipl2) IntUART1Handler(void)
{
        // Is this an RX interrupt?
        if(INTGetFlag(INT_SOURCE_UART_RX(UART1)))
        {

            mPORTDToggleBits(BIT_5);

            //Process data
            serial_usart_interrupt_handler();

            // Clear the RX interrupt Flag
            INTClearFlag(INT_SOURCE_UART_RX(UART1));
        }

        // We don't care about TX interrupt right now...
        /*
        if ( INTGetFlag(INT_SOURCE_UART_TX(UART1)) )
        {
                INTClearFlag(INT_SOURCE_UART_TX(UART1));
        }
        */
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                           Functions                                      //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

void setup_usart1(void)
{

    //Configure UART
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    //Set Baud Rate
    UARTSetDataRate(UART1, SYS_XTAL_FREQ, DESIRED_BAUDRATE);

    //Configure UART1 RX Interrupt
    INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
    INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART1), INT_SUB_PRIORITY_LEVEL_0);
}

void putc_usart1(char data)
{
    mPORTDToggleBits(BIT_7);

    //Send data to UART
    UARTSendDataByte(UART1, data);

    //wait for transmission complete
    while(!UARTTransmissionHasCompleted(UART1));

}

char getc_usart1(void)
{
    return UARTGetDataByte(UART1);
}

char busy_usart1(void)
{
    return (!UARTTransmitterIsReady(UART1));
}

char datardy_usart1(void)
{
    return UARTReceivedDataIsAvailable(UART1);
}

void gets_usart1(char *buffer, unsigned char len)
{

        unsigned char i = 0;// Length counter
        unsigned char data = 0;

        for(i=0;i<len;i++)                      // Only retrieve len characters
        {
                while(!datardy_usart1());       // Wait for data to be received

                data = getc_usart1();           // Get a character from the USART
                                                // and save in the string
                *buffer = data;
                buffer++;                       // Increment the string pointer
        }

}

void puts_usart1(char *data)
{
        do
        {  // Transmit a byte
                while(busy_usart1());
                putc_usart1(*data);
        } while( *data++ );
}
