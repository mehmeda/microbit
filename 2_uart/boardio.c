#include "boardio.h"
#include "gpio.h"
#include <stdint.h>

#define BUTTON_A_PIN 17 //Aktiv lav
#define BUTTON_B_PIN 26


void buttons_init() {
    GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;
}

int button_A() {
    if (!(GPIO->IN & (1 << BUTTON_A_PIN))){
		    return 1;
    }
    return 0;
}

int button_B() {
    if (!(GPIO->IN & (1 << BUTTON_B_PIN))){
		    return 1;
    }
    return 0;
}

void all_led_on() {
    GPIO->OUTSET = (1<<13) | (1<<14) | (1<<15);
    
    for (int i = 4; i <= 12; i++) {
        GPIO->OUTCLR = (1 << i);
    }
}

void all_led_off() {
    GPIO->OUTCLR = (1<<13) | (1<<14) | (1<<15);
}

void led_init() {
    	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

}


