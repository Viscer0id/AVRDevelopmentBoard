#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "uart.h"

#define F_CPU 14745600UL

int main(void) {
    uart_init();
    char message[] = "UART on ATMega8 9600 baud, no parity, 1 stop bit.\n";

    while (1) {
        uart_tx_str(message);
        _delay_ms(1000);
    }
}