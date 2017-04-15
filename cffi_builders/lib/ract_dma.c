#include <stdio.h>
#include <bcm2835.h>

//#include "ract_dma.h"

//#define PIN   RPI_GPIO_P1_15

void setup_pin(void) {
    printf("Setting pin %d as output\n", RPI_GPIO_P1_15);
    bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_OUTP);
    printf("Set pin %d as output\n", RPI_GPIO_P1_15);
}

void set_pin(int value) {
	if (value == 1) {
	    printf("Setting pin ON\n");
		bcm2835_gpio_write(RPI_GPIO_P1_15, HIGH);
	    printf("Set pin ON\n");
	} else {
	    printf("Setting pin OFF\n");
		bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);
	    printf("Set pin OFF\n");
	}
}
