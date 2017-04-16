
int initialize_RPI_GPIO(void);

int close_RPI_GPIO(void);
// Set initial pin directions and initial values
void setup_interface_pins(void);
// Compensate for board protection logic flip
void set_pin(uint8_t u8_pin, uint8_t u8_level);

void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len);

void send_dot_correction(uint8_t u8_dot_correction);

void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len);

