#define BAUDRATE 9600                               // define baudrate
#define BAUDPRESCALE ((F_CPU)/(BAUDRATE*16UL)-1)    // define baudprescaler for UBRR

// function to initialize UART
void uart_init (void);

void uart_tx_char (uint8_t data);

void uart_tx_str (uint8_t* stringPtr);

uint8_t uart_rx (void);