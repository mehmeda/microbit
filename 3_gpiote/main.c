#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

#define BUTTON_A_PIN 17 //Aktiv lav

void gpiote_init() {
    //set pins
    GPIOTE->CONFIG[0] = (1 << 0) | (BUTTON_A_PIN << 8) | (2 << 16);
    GPIOTE->CONFIG[1] = (3 << 0) | (13 << 8) | (3 << 16) | (0 << 20);
    GPIOTE->CONFIG[2] = (3 << 0) | (14 << 8) | (3 << 16) | (0 << 20);
    GPIOTE->CONFIG[3] = (3 << 0) | (15 << 8) | (3 << 16) | (0 << 20);
}

void ppi_init() {
    for (int i = 0; i < 3; ++i) {
        PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i+1]);
        PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[0]);
        PPI->CHENSET = (1 << i);
    }
}



int main() {
    //Setter opp jordingspinnene
    for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
    gpiote_init();
    ppi_init();
    while (1) {
        // Do nothing.
    }
}
