#include "uart.h"
#include "boardio.h"

int main(void) {
    uart_init();
    buttons_init();
    led_init();
    while(1) {
        if (button_A()) {
            all_led_on();
            uart_send('A');
        }
        if (button_B()) {
            all_led_off();
            uart_send('B');
        }
        
        int timer = 10000;
        while (timer--);
    }
}
