#include <stdio.h>
#include <bcm2835.h>
//#include "ract_dma.h"

#define PIN   RPI_GPIO_P1_15

void setup_pin(void) {
    printf("Setting pin %d as output", PIN);
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
}

void set_pin(int value) {
	if (value == 1) {
	    printf("Set pin ON");
		bcm2835_gpio_write(PIN, HIGH);
	} else {
	    printf("Set pin OFF");
		bcm2835_gpio_write(PIN, LOW);
	}
}
