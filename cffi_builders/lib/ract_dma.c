#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
//#include "ract_dma.h"

void set_pin(int value);


#define GSCLK           RPI_GPIO_P1_3
#define DCPRG           RPI_GPIO_P1_5
#define SCLK            RPI_GPIO_P1_8
#define XLAT            RPI_GPIO_P1_10
#define BLANK           RPI_GPIO_P1_11
#define SIN             RPI_GPIO_P1_12
#define VPRG            RPI_GPIO_P1_13
#define OUT             BCM2835_GPIO_FSEL_OUTP

#define DC_LENGTH       6

//#define PIN   RPI_GPIO_P1_15

// Initialize the BCM
int initialize_RPI_GPIO(void) {
    return bcm2835_init();
}

int close_RPI_GPIO(void) {
    return bcm2835_close();
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
    set_pin_low(GSCLK, False);
    set_pin_low(DCPRG, False);
    set_pin_high(VPRG, True);
    set_pin_low(SCLK, False);
    set_pin_low(XLAT, False);
    set_pin_high(BLANK, True);
}

// Compensate for board protection logic flip
void set_pin_low(uint8_t u8_pin) {
    bcm2835_gpio_write(u8_pin, HIGH);
}

// Compensate for board protection logic flip
void set_pin_high(uint8_t u8_pin) {
    bcm2835_gpio_write(u8_pin, LOW);
}

// Compensate for board protection logic flip
void set_pin(uint8_t u8_pin, uint8_t u8_level) {
    if (u8_level == 0) {
        bcm2835_gpio_write(u8_pin, HIGH);
    } else {
        bcm2835_gpio_write(u8_pin, LOW);
    }
}

void clock_in_dot_correction(uint8_t * u8_dot_correction, uint16_t u16_len_dot_correction) {
    int i;
    set_pin_high(DCPRG);
    set_pin_high(VPRG);
    for (i = 0; i < u16_len_dot_correction; i++) {
        send_dot_correction(u8_dot_correction[i]);
    }
    latch_data();
    set_pin_low(VPRG);
}

void send_dot_correction(u8 u8_dot_correction) {
    int i;
    for (i = 0; i < DC_LENGTH; i++) {
        bit = u8_dot_correction & (0x01 << i);
        set_pin(SIN, bit)
        set_pin(SCLK, True)
        set_pin(SCLK, False)
    }
}

void setPinByArray(uint8_t * intArray, int lenArray) {
    int i;
    for (i = 0; i < lenArray; i++) {
        if (intArray[i] == 0) {
            set_pin(0);
        } else {
            set_pin(1);
        }
        sleep(1);
    }
}

    def clock_in_grey_scale_data(self, data_to_send):
        set_pin(BLANK, True)

        for v in data_to_send:
            self.send_gs_byte(v)

        self.latch_data()
        set_pin(BLANK, False)

        if self._first_gs_cycle:
            # toggle SCLK one exta time on the first grey-scale clock in.
            set_pin(SCLK, True)
            set_pin(SCLK, False)
            self._first_gs_cycle = False
            self._echo('First grey-scale clock in complete')

    @staticmethod
    def send_gs_byte(value_to_send, no_bits=12):
        """ Clock in one grey-scale byte. """
        for i in range(no_bits):
            bit = (value_to_send >> i) & 0x01
            set_pin(SIN, bit)
            set_pin(SCLK, True)
            set_pin(SCLK, False)

    @staticmethod
    def latch_data():
        """ Signal that data has been latched in. """
        set_pin(XLAT, True)
        set_pin(XLAT, False)

    @staticmethod
    def toggle_gsclk(times=4096):
        """ Clear the GSCLK line and then toggle it the specified number of
            times.

            :param int times:
                How many times to toggle the GSCLK. Each time the clock is
                toggled it increments by one. If the intensity value of
                an LED is greater than the current count, it is turned on.
                Otherwise it is turned off. The default value is 4096. Other
                counts won't cover the full grey-scale intensity range.

            The GSCLK controls the PWM cycles of the LEDs and so must
            be continually clocked for the LEDs to be PWMed.
        """
        # clear GSCLK
        set_pin(BLANK, True)
        set_pin(BLANK, False)
        # increment the grey-scale count
        for i in xrange(times):
            set_pin(GSCLK, True)
            set_pin(GSCLK, False)


def set_pin(pin, value):
    """ Set GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    if value:
        GPIO.output(pin, False)
    else:
        GPIO.output(pin, True)


def get_pin(pin):
    """ Read GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    return not GPIO.input(pin)