#include <bcm2835.h>

#define PIN   RPI_GPIO_P1_15

void setup_pin(void) {
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
}

void set_pin(int value) {
	if (value == 1) {
		bcm2835_gpio_write(PIN, HIGH);
	} else {
		bcm2835_gpio_write(PIN, LOW);
	}
}
