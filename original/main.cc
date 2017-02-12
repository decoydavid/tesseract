#include <bcm2835.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define TLC5940_N_AVAILABLE 	5
#define TLC5940_N 		1

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

uint16_t row_mask[16 * 8] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,  
};

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

void run_port_test(void) {

	set_pin(GSCLK, LOW);
	set_pin(DCPRG, LOW);
	set_pin(VPRG, LOW);
	set_pin(SCLK, LOW);
	set_pin(XLAT, LOW);
	set_pin(BLANK, LOW);
	set_pin(SIN, LOW);

	test_pin(GSCLK, "GSCLK - 18");
	test_pin(DCPRG, "DCPRG - 19");
	test_pin(VPRG, "VPRG - 27");
	test_pin(SCLK, "SCLK - 25");
	test_pin(XLAT, "XLAT - 24");
	test_pin(BLANK, "BLANK - 23");
	test_pin(SIN, "SIN - 26");
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
				bcm2835_delay(1);
				printf("1");
			} else {
				set_pin(SIN, LOW);
				bcm2835_delay(1);
				printf("0");
			}
			TLC5940_Pulse(SCLK);
			Counter++;
		}
	}
}

int iNumSclks = 0;

void set_pixel(uint16_t uiValue)
{
	for( int i = 0; i < 12; i++ )
	{
		if( (uiValue & 1) != 0 )
		{
			set_pin(SIN, HIGH);
		}
		else
		{
			set_pin(SIN, LOW);
		}
		TLC5940_Pulse(SCLK);
		++iNumSclks;
		TLC5940_Pulse(GSCLK);
		uiValue = uiValue >> 1;
	}
	
}

uint16_t uiData[8*8*8] = { 0 };

void set_all_pixels()
{

	for( int iLevel = 0; iLevel < 8; iLevel++ )
	{
	iNumSclks = 0;

	uint8_t firstCycleFlag = 0;
	uint8_t value = get_pin(VPRG);
	if (value > LOW) {
		set_pin(VPRG, LOW);
		printf("First cycle start: %d\n", get_pin(VPRG));
		bcm2835_delay(100);
		firstCycleFlag = 1;
	}
	
	
	set_pin(BLANK, LOW);
		uint16_t *pLevelData = &uiData[iLevel*8*8];
		for( int i = 0; i < 8; i++ )
		{
			for( int j = 0; j < 8; j++ )
			{
				set_pixel(0xffff);
			}
		}

/*
		for( int i = 0; i < 16; i++ )
		{
			if (i == 0)
			{
				printf("%d", (iLevel));
			}	
			set_pixel(row_mask[(iLevel * 16) + i]);
		}
		*/
		// Now send layer ID bank
		int iNumBitsInLayerID = 12*16;
		for( int i = 0; i < iNumBitsInLayerID; i++ )
		{
			//printf("[%d,%d],", (i/12), ((i/12) == (iLevel)));
			if( (i/12) == (15-iLevel) )
				set_pin(SIN, HIGH);
			else
				set_pin(SIN, LOW);
			TLC5940_Pulse(SCLK);
			TLC5940_Pulse(GSCLK);			
		}

	set_pin(BLANK, HIGH);

	TLC5940_Pulse(XLAT);			
	if (firstCycleFlag)
	{
		TLC5940_Pulse(SCLK);
		++iNumSclks;
		printf("First cycle end: %d\n", get_pin(VPRG));
		firstCycleFlag = 0;
	}
	}


	
}

void TLC5940_SetGS_And_GS_PWM(void) {
	

}
/*
    bcm2835_delay(1);
*/


int main(void) {

    int mode = 1;
    char buffer;
    printf("Main start: mode?\n");

    std::cin >> mode;
    printf("\nMode: %d\n", mode);

    if (!bcm2835_init()) {
        printf("ERROR: unable to initialise bcm2835 GPIO. %d");
        return 1;
    }
    TLC5940_Init();
    TLC5940_ClockInDC();	// try it both with and without this line
    
    switch(mode) {
	case 7:
	{
		for( int i = 0; i < 8; i++ )
		for( int j = 0; j < 8; j++ )
		for( int k = 0; k < 8; k++ )
		{
				uiData[i*8*8+j*8+k] = 0xffff;
		}

		for (;;) {
            		set_all_pixels();
		}
	}
	break;
	case 9:
	{
	uint16_t uiValue = 0;
	int delay = 0;
	for (;;) {
            set_all_pixels();
		if (delay > 500) {
			
			static uint16_t iTest = 0;
			uiData[iTest] = 0;
			++iTest;
			iTest = iTest % 16;
			uiData[iTest] = 0xffff;
			printf("toggle\n");
			for(int i = 0; i < 4; i++ )
			{
			for(int j = 0; j < 4; j++ )
			{
				printf("%d ", uiData[i*4+j]);
			}
			printf("\n");
			}
			delay = 0;
		}
		delay++;
        }
	}
	break;
    case 0:
	run_port_test();
	break;
    case 1:
        for (;;) {
            TLC5940_SetGS_And_GS_PWM();
        }
        break;
    case 2:
    {
        static int scrollPos = 0;
	static int scrollDelay = 50;
        memset(gsData, 0x00, 192);
        for (;;) {
            gsData[scrollPos] = 1;
            TLC5940_SetGS_And_GS_PWM();
            gsData[scrollPos] = 0;
            if (--scrollDelay <= 0) {
                scrollDelay = 50;
                scrollPos++;
            }
            if (scrollPos >= 192) {
                scrollPos = 0;
            }
        }
        break;
    }
    case 3:
    {
        #define normaBrightness 255
	static int pulse = -1;
	static uint16_t brightness = normaBrightness;
	static uint8_t brightnessArray[12];
        int i = 0;
        memset(gsData, 0x00, 192);
        for (;;) {	
            for (i = 0; i < 8; i++) {
                gsData[i + 183] = (brightness >> i) & 0x01;
            }
            if (brightness <= 0) {
                printf("Resetting brightness");
                brightness = normaBrightness;
            } else {
                brightness --;
            }
            TLC5940_SetGS_And_GS_PWM();
        }
        break;
    }
    case 8:
    {
	printf("LED cube diagonal\n");
	static int set = 0;
	static int scrollDelay = 50;
	static int pos = 0;
	static int index = 0;
        memset(gsData, 0x00, sizeof(gsData));
        index = (12 + ((pos + 0) % 4)) * 12;
	memset(&gsData[index], 0x01, 12);
        index = (28 + ((pos + 1) % 4)) * 12;
	memset(&gsData[index], 0x01, 12);
        index = (44 + ((pos + 2) % 4)) * 12;
	memset(&gsData[index], 0x01, 12);
        index = (60 + ((pos + 3) % 4)) * 12;
	memset(&gsData[index], 0x01, 12);
        index = (76 + ((pos + 0) % 4)) * 12;
	memset(&gsData[index], 0x01, 12);
        for (;;) {
            TLC5940_SetGS_And_GS_PWM();
            if (--scrollDelay <= 0) {
                scrollDelay = 5;
	        memset(gsData, 0x00, sizeof(gsData));
	        /*index = (12 + ((pos + 0) % 8)) * 12;
		memset(&gsData[index], 0x01, 12);
	        index = (28 + ((pos + 1) % 8)) * 12;
		memset(&gsData[index], 0x01, 12);
	        index = (44 + ((pos + 2) % 8)) * 12;
		memset(&gsData[index], 0x01, 12);
	        index = (60 + ((pos + 3) % 8)) * 12;
		memset(&gsData[index], 0x01, 12);*/
	        index = (76 + ((pos + 0) % 8)) * 12;
		memset(&gsData[index], 0x01, 12);
/*
		printf("pos = %d\n", pos % 4);
		for (set = 0; set < sizeof(gsData); set++) {
			printf("%u,", (uint8_t)gsData[set]);
			if (set % 192 == 0) {
				printf("\n");
			}
		}
		printf("\n"); 
*/
		pos++;
            }
        }
        break;
    }
	
    default:
        printf("ERROR: invalid mode");
        return 1;
        break;
    }
    return 0;
}
