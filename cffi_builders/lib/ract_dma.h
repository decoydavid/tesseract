
int initialize_RPI_GPIO(void);

int close_RPI_GPIO(void);
// Set initial pin directions and initial values
void setup_interface_pins(void);
// Compensate for board protection logic flip
void set_pin(uint8_t u8_pin, uint8_t u8_level);

void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len);

void send_dot_correction(uint8_t u8_dot_correction);

void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len);

void send_greyscale(uint16_t u16_greyscale);
// Signal that data has been latched in
void latch_data(void);
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
void toggle_gsclk(void);
