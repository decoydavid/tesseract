
int initialize_RPI_GPIO(void);
void set_gs_data(uint16_t * u16_data, uint16_t u16_data_len);
void set_pin(int pin, int value);
uint8_t get_pin(int pin);
void TLC5940_Init(void);
void TLC5940_Pulse(int pin);
void test_pin(int pin, const char* name);
void TLC5940_ClockInDC(void);
void TLC5940_SetGS_And_GS_PWM(void);
