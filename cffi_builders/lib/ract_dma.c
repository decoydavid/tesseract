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
uint8_t u8_first_gs_cycle = FALSE;

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
void setup_interface_pins(void) {
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
    printf("Interface configured\n");
}

// Compensate for board protection logic flip
void set_pin(uint8_t u8_pin, uint8_t u8_level) {
    bcm2835_gpio_write(u8_pin, (u8_level & HIGH) ? LOW : HIGH);
}

void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len) {
    int i;
    set_pin(DCPRG, HIGH);
    set_pin(VPRG, HIGH);
    for (i = 0; i < u16_data_len; i++) {
        send_dot_correction(u8_data[i]);
    }
    latch_data();
    set_pin(VPRG, LOW);
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

void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len) {
    int i;
    set_pin(BLANK, HIGH);
    for (i = 0; i < u16_data_len; i++) {
        send_greyscale(u16_data[i]);
    }
    latch_data();
    set_pin(BLANK, LOW);

    if (u8_first_gs_cycle == TRUE) {
        // toggle SCLK one exta time on the first grey-scale clock in
        set_pin(SCLK, HIGH);
        set_pin(SCLK, LOW);
        u8_first_gs_cycle = FALSE;
        printf("GC first transfer complete\n");
    }
}

void send_greyscale(uint16_t u16_greyscale) {
    int i;
    uint8_t u8_bit;
    for (i = 0; i < GS_LENGTH; i++) {
        u8_bit = (u16_greyscale >> i) & 0x01;
        set_pin(SIN, u8_bit);
        set_pin(SCLK, HIGH);
        set_pin(SCLK, LOW);
    }
}

// Signal that data has been latched in
void latch_data(void) {
    set_pin(XLAT, HIGH);
    set_pin(XLAT, LOW);
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
void toggle_gsclk(void) {
    int i;
    set_pin(BLANK, HIGH);
    set_pin(BLANK, LOW);
    for (i = 0; i < GS_CLOCK_CYCLES; i++) {
        set_pin(GSCLK, HIGH);
        set_pin(GSCLK, LOW);
    }
}
