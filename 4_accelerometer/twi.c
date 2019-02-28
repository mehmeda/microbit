#include "twi.h"
#include "../2_uart/gpio.h"
#include "../2_uart/uart.h"

#define SDA_PIN 30
#define SCL_PIN	0
#define FREQUENCY_K100 0x01980000


void twi_init() {
    GPIO->PIN_CNF[SDA_PIN] =  (1<<10)|(1<<9)|(1<<3)|(1<<2);//(6<<8) | (3<<2);
    GPIO->PIN_CNF[SCL_PIN] =  (1<<10)|(1<<9)|(1<<3)|(1<<2);//(6<<8) | (3<<2);

    TWIO->TXDSENT = 0;
    TWIO->RXDREADY = 0;
    TWIO->ERROR = 0;

    TWIO->PSELSCL = 0;//SCL_PIN;
    TWIO->PSELSDA = 30;//SDA_PIN;

    TWIO->FREQUENCY = 0x01980000;//FREQUENCY_K100;
    //TWIO->SHORTS = 1;

    TWIO->ENABLE = 5;
}

void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t *data_buffer
    ) {
    TWIO->ADDRESS = slave_address;
    TWIO->STARTTX = 1;

    TWIO->TXDSENT = 0;
    TWIO->TXD = start_register;

    while (!TWIO->TXDSENT) {uart_send('A');}
    TWIO->TXDSENT = 0;

    TWIO->STARTRX = 1;
    TWIO->RXDREADY = 0;
    int i;
    for (i = 0; i < registers_to_read - 1; i++) {
        while(!TWIO->RXDREADY){uart_send('B');}
        TWIO->RXDREADY = 0;
        data_buffer[i] = TWIO->RXD;
    }
    TWIO->STOP = 1;
    while(!TWIO->RXDREADY){uart_send('C');}
    TWIO->RXDREADY = 0;
    data_buffer[i] = TWIO->RXD;
}
