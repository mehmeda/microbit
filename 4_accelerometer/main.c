#include "twi.h"
#include "../2_uart/uart.h"
#include <stdlib.h>

#define ACC_ADDRESS 0x1D
#define WHO_AM_I_ADDRESS 0x01

int main() {
    twi_init();
    uart_init();
    uart_send('1');



    uint8_t * data_buffer;
    data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));



    twi_multi_read(ACC_ADDRESS, WHO_AM_I_ADDRESS, 6, data_buffer);

    //if (data_buffer[0] == 0x5A) {
    while(1) {
        uart_send('D');
    }
    //}
}
