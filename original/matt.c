#include <bcm2835.h>
#include <stdio.h>
#include <string.h>

#define GSCLK  RPI_GPIO_P1_03  //Orange
#define DCPRG  RPI_GPIO_P1_05  //Brown
#define SCLK   RPI_GPIO_P1_08  //White
#define XLAT   RPI_GPIO_P1_10  //Blue
#define BLANK  RPI_GPIO_P1_11  //Black
#define SIN    RPI_GPIO_P1_12  //Red
#define VPRG   RPI_GPIO_P1_13  //White/Green

void set_pin(int pin, int value) {
	if (value == HIGH) {
		bcm2835_gpio_write(pin, LOW);
		bcm2835_gpio_write(pin, LOW);
		bcm2835_gpio_write(pin, LOW);
		bcm2835_gpio_write(pin, LOW);
		bcm2835_gpio_write(pin, LOW);
	} else {
		bcm2835_gpio_write(pin, HIGH);
		bcm2835_gpio_write(pin, HIGH);
		bcm2835_gpio_write(pin, HIGH);
		bcm2835_gpio_write(pin, HIGH);
		bcm2835_gpio_write(pin, HIGH);
	}
}

uint8_t get_pin(int pin) {
	uint8_t value = bcm2835_gpio_lev(pin);
	if (value == HIGH) {
		return LOW;
	} else {
		return HIGH;
	}
}

void TLC5940_Init(void) {
	bcm2835_gpio_fsel(GSCLK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DCPRG, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(VPRG, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(SCLK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(XLAT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(BLANK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(SIN, BCM2835_GPIO_FSEL_OUTP);

	set_pin(GSCLK, LOW);
	set_pin(DCPRG, LOW);
	set_pin(VPRG, HIGH);
	set_pin(SCLK, LOW);
	set_pin(XLAT, LOW);
	set_pin(BLANK, HIGH);
}

void Pulse(int pin)
{
	set_pin(pin, HIGH);
	set_pin(pin, LOW);

}

#define TLC5940_N 		5

void WTF(void) {
	uint8_t firstCycleFlag = 0;
	uint8_t value = get_pin(VPRG);
	
	uint16_t GSCLK_Counter = 0;
	uint16_t Data_Counter = 0;
	
	set_pin(BLANK, LOW);
	for (;;) {
		if (GSCLK_Counter > TLC5940_N * 192 - 1) {
			set_pin(BLANK, HIGH);
			Pulse(XLAT);			
			if (firstCycleFlag) {
				Pulse(SCLK);
				printf("First cycle end: %d\n", get_pin(VPRG));
				firstCycleFlag = 0;
			}
			break;
		} else {
			if (!(Data_Counter > TLC5940_N * 192 - 1)) {
				if ((rand() % 2) == 0) {
					set_pin(SIN, HIGH);
				} else {
					set_pin(SIN, LOW);
				}
				Pulse(SCLK);
				Data_Counter++;
			}
		}
		Pulse(GSCLK);
		GSCLK_Counter++;
	}
}

int main(int argc, const char **argv)
{
	if (!bcm2835_init()) {
		printf("ERROR: unable to initialise bcm2835 GPIO. %d");
		return 1;
	}
	TLC5940_Init();

	while(1)
	{
		WTF();
		bcm2835_delay(100);
	}
}