#include "uart.h"
#include "boardio.h"
#include <stdio.h>

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    do {
            letter = uart_read();
    } while(letter == '\0');
    *str = letter;
    return 1;
}

int main(void) {
    uart_init();
    buttons_init();
    led_init();
    iprintf("\n\rNorway has %d counties. \n\r", 18);


    iprintf("Give me a number\n\r");

    int a;
    //iprintf("%d", a);
    scanf("%d", &a);
    iprintf("Your number is %d", a);
    iprintf("\n\r");

    int led_status = 0;
    while(1) {

        if (button_A()) {
            all_led_on();
            led_status = 1;
            uart_send('A');
        }
        if (button_B()) {
            all_led_off();
            led_status = 0;
            uart_send('B');
        }

        if (uart_read() != '\0') {
            if (led_status) {
                all_led_off();
                led_status = 0;
            } else {
                all_led_on();
                led_status = 1;

            }
        }


        int timer = 10000;
        while (timer--);

    }
}
