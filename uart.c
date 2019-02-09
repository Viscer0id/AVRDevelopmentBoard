#include <avr/io.h>
#include "uart.h"

// function to initialize UART
void uart_init (void)
{
    UBRRH = (BAUDPRESCALE>>8);                      // load upper 8-bits of the baud prescale value into the high byte of the UBRR register
    UBRRL = BAUDPRESCALE;                           // load lower 8-bits of the baud prescale value into the low byte of the UBRR register
    UCSRB|= (1<<TXEN)|(1<<RXEN);                    // enable UART receiver and transmitter
    UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);       // 8bit data format, one stop bit, no parity
}

// function to transmit byte
void uart_tx_char (uint8_t data)
{
    while (!( UCSRA & (1<<UDRE)));                  // wait until register is ready to accept data (bit UDRE set in register UCSRA)
    UDR = data;                                     // load data into the UDR register
}

// function to send string of data
void uart_tx_str (uint8_t* stringPtr)
{
    while(*stringPtr != 0x00){                      // check if there is more data to send, strings are terminated with a null character, so the last char is always 0
        uart_tx_char(*stringPtr);                   // transmit using our function to transmit
        stringPtr++;                                // move to the next byte in the string
    }
}

// function to receive byte
uint8_t uart_rx (void)
{
    while(!(UCSRA) & (1<<RXC));                     // wait until register has finished receiving and is ready to be read (bit RXC set in register UCSRA)
    return UDR;                                     // return the data from UDR register
}