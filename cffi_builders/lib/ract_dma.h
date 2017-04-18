
int initialize_RPI_GPIO(void);

int close_RPI_GPIO(void);
// Set initial pin directions and initial values
void setup_interface(void);

void enable_layer_debug(void);
// Compensate for board protection logic flip
//void set_pin(uint8_t u8_pin, uint8_t u8_level);

void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len);

void send_dot_correction(uint8_t u8_dot_correction);

void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len);

void set_gs_data(uint16_t * u16_data, uint16_t u16_data_len);
void set_pin(int pin, int value);
uint8_t get_pin(int pin);
void TLC5940_Init(void);
void TLC5940_Pulse(int pin);
void test_pin(int pin, const char* name);
void TLC5940_ClockInDC(void);
void TLC5940_SetGS_And_GS_PWM(void);
