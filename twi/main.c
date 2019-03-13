#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "twi.h"
#include "utility.h"
#include "accel.h"
#include "ubit_led_matrix.h"

int main(){
	uart_init();

    utility_print(&uart_send, "Starting\n\r");
    ubit_led_matrix_init();

	twi_init();

    accel_init();

    int data_buffer[3];
    int x_dot, y_dot;


    int i = 0;
    while(1)
    {
        accel_read_x_y_z(data_buffer);


        x_dot = data_buffer[0] / 50;
        y_dot = data_buffer[1] / 50;

        ubit_led_matrix_light_only_at(x_dot, y_dot);
        if (i%1000 == 0) {
            utility_print(
                &uart_send,
                "X: %6d Y: %6d Z: %6d\n\r",
                data_buffer[0],
                data_buffer[1],
                data_buffer[2]
            );
        }
        i++;
    }

	return 0;
}
