#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define BUTTON_A_PIN 17 //Aktiv lav
#define BUTTON_B_PIN 26

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;


void all_led_on(void) {
    GPIO->OUTSET = (1<<13) | (1<<14) | (1<<15);
    
    for (int i = 4; i <= 12; i++) {
        GPIO->OUTCLR = (1 << i);
    }
}

void all_led_off(void) {
    GPIO->OUTCLR = (1<<13) | (1<<14) | (1<<15);
}


int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;

	int sleep = 0;
	while(1){
	    
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << BUTTON_B_PIN))) { 
	           all_led_on();
        }
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
        if (!(GPIO->IN & (1 << BUTTON_A_PIN))){
		    all_led_off();
        }
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}

