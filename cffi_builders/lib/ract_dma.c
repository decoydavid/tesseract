#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
//#include "ract_dma.h"

// RPI references
#define GSCLK           RPI_GPIO_P1_03
#define DCPRG           RPI_GPIO_P1_05
#define SCLK            RPI_GPIO_P1_08
#define XLAT            RPI_GPIO_P1_10
#define BLANK           RPI_GPIO_P1_11
#define SIN             RPI_GPIO_P1_12
#define VPRG            RPI_GPIO_P1_13
#define OUT             BCM2835_GPIO_FSEL_OUTP
// TLC5940 references
#define DC_LENGTH       6
#define GS_LENGTH       12
#define GS_CLOCK_CYCLES 4096
// Internal references
#define TRUE            0x1
#define FALSE           0x0

// Local global variables
uint8_t     u8_first_gs_cycle;
uint8_t     u8_debug_layer;

// Initialize the BCM
int initialize_RPI_GPIO(void) {
    int i_ret_val = bcm2835_init();
    printf("RPI GPIO interface initialized\n");
    return i_ret_val;
}

int close_RPI_GPIO(void) {
    int i_ret_val = bcm2835_close();
    printf("RPI GPIO interface closed\n");
    return i_ret_val;
}

// Set initial pin directions and initial values
void setup_interface(void) {
    bcm2835_gpio_fsel(GSCLK, OUT);
    bcm2835_gpio_fsel(DCPRG, OUT);
    bcm2835_gpio_fsel(VPRG, OUT);
    bcm2835_gpio_fsel(SCLK, OUT);
    bcm2835_gpio_fsel(XLAT, OUT);
    bcm2835_gpio_fsel(BLANK, OUT);
    bcm2835_gpio_fsel(SIN, OUT);
    set_pin(GSCLK, LOW);
    set_pin(DCPRG, LOW);
    set_pin(VPRG, HIGH);
    set_pin(SCLK, LOW);
    set_pin(XLAT, LOW);
    set_pin(BLANK, HIGH);
    u8_first_gs_cycle = TRUE;
    u8_debug_layer = FALSE;
    printf("Interface configured\n");
}

void enable_layer_debug(void) {
    u8_debug_layer = TRUE;
    printf("Layer debug enabled\n");
}

<<<<<<< Updated upstream
// Compensate for board protection logic flip
void set_pin(uint8_t u8_pin, uint8_t u8_level) {
    bcm2835_gpio_write(u8_pin, u8_level ? LOW : HIGH);
    bcm2835_gpio_write(u8_pin, u8_level ? LOW : HIGH);
}
=======
//// Compensate for board protection logic flip
//void set_pin(uint8_t u8_pin, uint8_t u8_level) {
//    if (u8_level > 0) {
//        bcm2835_gpio_write(u8_pin, LOW);
//        bcm2835_gpio_write(u8_pin, LOW);
//        bcm2835_gpio_write(u8_pin, LOW);
//        bcm2835_gpio_write(u8_pin, LOW);
//        bcm2835_gpio_write(u8_pin, LOW);
//    } else {
//        bcm2835_gpio_write(u8_pin, HIGH);
//        bcm2835_gpio_write(u8_pin, HIGH);
//        bcm2835_gpio_write(u8_pin, HIGH);
//        bcm2835_gpio_write(u8_pin, HIGH);
//        bcm2835_gpio_write(u8_pin, HIGH);
//    }
////    bcm2835_gpio_write(u8_pin, u8_level ? LOW : HIGH);
////    bcm2835_gpio_write(u8_pin, u8_level ? LOW : HIGH);
////    bcm2835_gpio_write(u8_pin, u8_level ? LOW : HIGH);
////    bcm2835_delayMicroseconds(100);
//}
>>>>>>> Stashed changes

void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len) {
    int i;
    set_pin(DCPRG, HIGH);
    set_pin(VPRG, HIGH);
    bcm2835_delay(100);
    for (i = 0; i < u16_data_len; i++) {
        send_dot_correction(u8_data[i]);
    }
    set_pin(XLAT, HIGH);
    set_pin(XLAT, LOW);
    printf("DC setup complete\n");
}

void send_dot_correction(uint8_t u8_dot_correction) {
    int i;
    uint8_t u8_bit;
    for (i = 0; i < DC_LENGTH; i++) {
        u8_bit = (u8_dot_correction >> i) & 0x01;
        set_pin(SIN, u8_bit);
        set_pin(SCLK, HIGH);
        set_pin(SCLK, LOW);
    }
}

/*
 *  Clear the GSCLK line and then toggle it the specified number of
 *  times.
 *
 *  :param int times:
 *      How many times to toggle the GSCLK. Each time the clock is
 *      toggled it increments by one. If the intensity value of
 *      an LED is greater than the current count, it is turned on.
 *      Otherwise it is turned off. The default value is 4096. Other
 *      counts won't cover the full grey-scale intensity range.
 *
 *  The GSCLK controls the PWM cycles of the LEDs and so must
 *  be continually clocked for the LEDs to be PWMed.
 */
void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len) {
    uint16_t u16_gs_clk_counter;
    uint16_t u16_gs_data_counter;
    uint8_t u8_bit;
    uint16_t u16_i;
    int i;

    if (u8_first_gs_cycle == TRUE) {
        set_pin(VPRG, LOW);
        bcm2835_delay(100);
    }
    if (u8_debug_layer) {
        for (i = 0; i < u16_data_len; i++) {
            printf("%d", u16_data[i] / 4095);
        }
        printf("\n");
    }
    u16_gs_clk_counter = 0;
    u16_gs_data_counter = 0;
    set_pin(BLANK, LOW);

    for (u16_gs_data_counter = 0; u16_gs_data_counter < u16_data_len; u16_gs_data_counter++) {
        for (u16_i = 0; u16_i < GS_LENGTH; u16_i++) {
            u8_bit = (u16_data[u16_gs_data_counter] >> u16_i) & 0x01;
            set_pin(SIN, u8_bit);
            set_pin(SCLK, HIGH);
            set_pin(SCLK, LOW);
            set_pin(GSCLK, HIGH);
            set_pin(GSCLK, LOW);
            u16_gs_clk_counter++;
        }
    }
    for (;u16_gs_clk_counter < GS_CLOCK_CYCLES; u16_gs_clk_counter++) {
        set_pin(GSCLK, HIGH);
        set_pin(GSCLK, LOW);
    }

    set_pin(BLANK, HIGH);
    set_pin(XLAT, HIGH);
    set_pin(XLAT, LOW);
    if (u8_first_gs_cycle == TRUE) {
        u8_first_gs_cycle = FALSE;
        set_pin(SCLK, HIGH);
        set_pin(SCLK, LOW);
        printf("GC first transfer complete\n");
    }
}

#define TLC5940_N_AVAILABLE 	5
#define TLC5940_N 		5

uint8_t dcData[96 * TLC5940_N_AVAILABLE] = {
// MSB            LSB
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4 15, 14
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 4 1, 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3 15, 14
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 3 1, 0
/**/	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2 15, 14
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 2, 1, 0/**/
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1 15, 14
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 1 1, 0
/**/	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0 15, 14
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// Channel 0, 1, 0/**/
};

uint8_t gsData[192 * TLC5940_N_AVAILABLE] = {
// MSB                              	LSB
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	 		// Channel 15
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 14
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 13
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,			// Channel 12
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,			// Channel 11
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,			// Channel 10
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,			// Channel 9
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,			// Channel 8
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,			// Channel 7
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,			// Channel 6
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,			// Channel 5
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 4
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 3
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 2
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// Channel 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1			// Channel 0
};

void set_gs_data(uint16_t * u16_data, uint16_t u16_data_len) {
    uint16_t u16_gs_data_counter;
    uint16_t u16_counter = 0;
    uint16_t u16_i;
    uint8_t u8_bit;
    for (u16_gs_data_counter = 0; u16_gs_data_counter < u16_data_len; u16_gs_data_counter++) {
        for (u16_i = 0; u16_i < GS_LENGTH; u16_i++) {
            u8_bit = (u16_data[u16_gs_data_counter] >> u16_i) & 0x01;
            gsData[u16_counter] = u8_bit;
            u16_counter++;
        }
    }
}

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

void TLC5940_Pulse(int pin) {
	set_pin(pin, HIGH);
/*
	set_pin(pin, HIGH);
	set_pin(pin, HIGH);
	set_pin(pin, HIGH);
	set_pin(pin, LOW);
	set_pin(pin, LOW);
	set_pin(pin, LOW);
*/
	set_pin(pin, LOW);
}

void test_pin(int pin, const char* name) {
    int input;
    set_pin(pin, HIGH);
    printf("Set pin %s: %d\n", name, pin);
    scanf("%d", &input);
    set_pin(pin, LOW);
    printf("Clear pin %s: %d\n", name, pin);
    scanf("%d", &input);
}

void TLC5940_ClockInDC(void) {
	set_pin(DCPRG, HIGH);
	set_pin(VPRG, HIGH);
	bcm2835_delay(100);
	printf("DC: %d, %d\n", TLC5940_N, sizeof(dcData));
	printf("GS: %d, %d\n", TLC5940_N, sizeof(gsData));

	uint16_t Counter = 0;

	for (;;) {
		if (Counter > TLC5940_N * 96 - 1) {
			TLC5940_Pulse(XLAT);
			break;
		} else {
			if (dcData[Counter] == 1) {
				set_pin(SIN, HIGH);
				printf("1");
			} else {
				set_pin(SIN, LOW);
				printf("0");
			}
			TLC5940_Pulse(SCLK);
			Counter++;
		}
	}
}

void TLC5940_SetGS_And_GS_PWM(void) {
	uint8_t firstCycleFlag = 0;
	uint8_t value = get_pin(VPRG);
	if (value > LOW) {
		set_pin(VPRG, LOW);
		printf("First cycle start: %d\n", get_pin(VPRG));
		bcm2835_delay(100);
		firstCycleFlag = 1;
	}

	uint16_t GSCLK_Counter = 0;
	uint16_t Data_Counter = 0;

	set_pin(BLANK, LOW);
	for (;;) {
		if (GSCLK_Counter > TLC5940_N * 192 - 1) {
//		if (GSCLK_Counter > 4095) {
			set_pin(BLANK, HIGH);
			TLC5940_Pulse(XLAT);
			if (firstCycleFlag) {
				TLC5940_Pulse(SCLK);
				printf("First cycle end: %d\n", get_pin(VPRG));
				firstCycleFlag = 0;
//				printf("\n");
			}
			break;
		} else {
			//if (!(Data_Counter > TLC5940_N * 192 - 1))
			{
				if (gsData[Data_Counter] == 1) {
					set_pin(SIN, HIGH);
//					printf("1");
				} else {
					set_pin(SIN, LOW);
//					printf("0");
				}
				TLC5940_Pulse(SCLK);
				Data_Counter++;
			}
		}
		TLC5940_Pulse(GSCLK);
		GSCLK_Counter++;
	}
}