/* Name: main.c
 * Author: Jeremy Dennis
 * Copyright:
 * License:
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
//#include "easyavr.h"

#define F_CPU 14745600UL
#define BAUDRATE 9600                               // define baudrate
#define BAUDPRESCALE ((F_CPU)/(BAUDRATE*16UL)-1)    // define baudprescaler for UBRR

// function to initialize UART
void uart_init (void)
{
    UBRRH = (BAUDPRESCALE>>8);                      // load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRRL = BAUDPRESCALE;                           // load lower 8-bits of the baud rate value into the low byte of the UBRR register
    UCSRB|= (1<<TXEN)|(1<<RXEN);                    // enable receiver and transmitter
    UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);       // 8bit data format
}

// function to send data
void uart_transmit (unsigned char data)
{
    while (!( UCSRA & (1<<UDRE)));                  // wait while register is free
    UDR = data;                                     // load data in the register
}

// function to receive data
unsigned char uart_recieve (void)
{
    while(!(UCSRA) & (1<<RXC));                     // wait while data is being received
    return UDR;                                     // return 8-bit data
}


int main(void) {
    uart_init();
//    PIN_AS_INPUT(DDRD, PIN0);
//    PIN_AS_OUTPUT(DDRD, PIN1);
    for (;;) {
        uart_transmit(36);
        _delay_ms(2000);
    }

}