#include "stdafx.h"
#include "abLattice.h"
#include "abGenerator.h"
#include "abWaveGenerator.h"
#include "abBouncyBallGenerator.h"
#include "abExpandingSphereGenerator.h"
#include "abStarfieldGenerator.h"
#include "abFlockGenerator.h"
#include "abTextGenerator.h"
#include "abTextFileGenerator.h"
#include "abTorusGenerator.h"
#include "abRingsGenerator.h"
#include "abBubblesGenerator.h"
#include "abExploderGenerator.h"
#include "abFillGenerator.h"
#include "abWormholeGenerator.h"
#include "abCheckerboardGenerator.h"
#ifdef OPENGL_RENDER
#include "abBitmapTestGenerator.h"
#endif
#include "abClothGenerator.h"
#include "abSpinnyClothGenerator.h"
#include "abBitFlipGenerator.h"
#include "abSpherifyGenerator.h"

#include <typeinfo>
#include <vector>
#include <sys/time.h>

#ifdef OPENGL_RENDER
/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}


void checkSDLError(int line = -1)
{
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
			printf("SDL Error: %s\n", error);
			if (line != -1)
					printf(" + line: %i\n", line);
			SDL_ClearError();
        }
#endif
}


SDL_Window *mainwindow; /* Our window handle */
#endif

Lattice *m_pLattice = NULL;
std::vector<Generator *> m_vecGenerators;
int m_iActiveGeneratorIndex = 0;

#ifdef OPENGL_RENDER
void Render()
{
	static float fAngle = 3.141592f/4.0f;
	fAngle -= 0.005f;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
 	gluPerspective(60.0f, 1.0f, 0.1f, 100.0f);
 	glViewport(0, 0, 512, 512);


	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	float fZoom = 4.0f;
	gluLookAt(fZoom * sinf(fAngle), fZoom * cosf(fAngle), 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	m_pLattice->Render();

	/* Swap our back buffer to the front */
	SDL_GL_SwapWindow(mainwindow);

}
#endif

#include <bcm2835.h>

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

int pin_mask[16 * 4] = {
         0,  2,  4,  6,  8, 10, 12, 14,
        15, 13, 11,  9,  7,  5,  3,  1,
        16, 18, 20, 22, 24, 26, 28, 30,
        31, 29, 27, 25, 23, 21, 19, 17,
        32, 34, 36, 38, 40, 42, 44, 46,
        47, 45, 43, 41, 39, 37, 35, 33,
        48, 50, 52, 54, 56, 58, 60, 62,
        63, 61, 59, 57, 55, 53, 51, 49,
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
/* Our program's entry point */
int main(int argc, char *argv[])
{
#ifdef OPENGL_RENDER
    SDL_GLContext maincontext; /* Our opengl context handle */

    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    /* Request opengl 3.2 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow("afrikaburn prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);


    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

#endif
	srand(time(NULL));
	m_pLattice = new Lattice(8, 1.6f);

#ifdef OPENGL_RENDER
	m_vecGenerators.push_back(new BitmapTestGenerator());
#endif
	m_vecGenerators.push_back(new SpherifyGenerator());
	m_vecGenerators.push_back(new BitFlipGenerator(m_pLattice->GetResolution()));
	m_vecGenerators.push_back(new SpinnyClothGenerator());
	m_vecGenerators.push_back(new ClothGenerator());
	m_vecGenerators.push_back(new CheckerboardGenerator());
	m_vecGenerators.push_back(new WormholeGenerator());
	//m_vecGenerators.push_back(new FillGenerator(m_pLattice->GetResolution()));
	m_vecGenerators.push_back(new ExploderGenerator());
	m_vecGenerators.push_back(new BubblesGenerator());
	m_vecGenerators.push_back(new RingsGenerator());
	m_vecGenerators.push_back(new TorusGenerator());
	m_vecGenerators.push_back(new TextGenerator(m_pLattice->GetResolution()));
  m_vecGenerators.push_back(new TextFileGenerator(m_pLattice->GetResolution()));
	//m_vecGenerators.push_back(new FlockGenerator(50, 0.05f));
	m_vecGenerators.push_back(new StarfieldGenerator(550, 0.05f));
	m_vecGenerators.push_back(new StarfieldGenerator(100, 0.01f));
	m_vecGenerators.push_back(new StarfieldGenerator(10, 0.05f));
	m_vecGenerators.push_back(new WaveGenerator());
	m_vecGenerators.push_back(new BouncyBallGenerator());
	m_vecGenerators.push_back(new ExpandingSphereGenerator());
	m_iActiveGeneratorIndex = rand() % m_vecGenerators.size();


if (!bcm2835_init()) {
        printf("ERROR: unable to initialise bcm2835 GPIO. %d");
        return 1;
    }
    TLC5940_Init();
    TLC5940_ClockInDC();	// try it both with and without this line
    printf("1\n");
	int iTemp = 0;
	int iNextDuration = 15 + rand() % 15;
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	time_t iLastSwitchSecs = ts.tv_sec;
	while(1)
	{
		//printf("%d", iTemp);
		m_vecGenerators[m_iActiveGeneratorIndex]->Update(*m_pLattice);
		//printf("%d", iTemp);
		for(int i = 0; i < 8; i++ )
		{
        		memset(gsData, 0x00, sizeof(gsData));

			for( int j = 0; j < 8; j++)
			{
				//int zxc = (j + 2) % 8;
				for( int k = 0; k < 8; k++ )
				{
					unsigned char ucValue = m_pLattice->GetValue(j,k,(7-i));
					/* GRAYSCALE TEST
					for( int m = 0; m < 8; m++ )
					{
						if( (ucValue & 1) != 0 )
							gsData[zxc*8*12+k*12+m] = 1;
						ucValue = ucValue >> 1;
					}*/
                                        int pin_no = pin_mask[j * 8 + k];
					if( ucValue > 125 )
						// memset(&gsData[zxc*8*12+k*12], 0x01, 12);
                                                memset(&gsData[pin_no * 12], 0x01, 12);
				}
			}
			//memset(gsData, 0x01, 16*4*12);
        		for( int j = 0; j < 16; j++ )
			{
				if( row_mask[i*16+j] != 0 )
					memset(&gsData[16*4*12+j*12], 0x01, 12);
			}
           		TLC5940_SetGS_And_GS_PWM();
		}
		//printf("Finished one iteration!");
		clock_gettime(CLOCK_REALTIME, &ts);

		iTemp++;
		if( ts.tv_sec - iLastSwitchSecs > iNextDuration )
		{
			iTemp = 0;
			m_iActiveGeneratorIndex = rand() % m_vecGenerators.size();
			//m_iActiveGeneratorIndex = (m_iActiveGeneratorIndex+1) % m_vecGenerators.size();
			printf("Switching to generator %d\n", m_iActiveGeneratorIndex);
			iLastSwitchSecs = ts.tv_sec;
			iNextDuration = 15 + rand() % 15;
		}
	}

#ifdef OPENGL_RENDER
    /* Clear our buffer with a red background */
	bool bFinished = false;
	SDL_Event evt;
	while (!bFinished)
	{
		m_vecGenerators[m_iActiveGeneratorIndex]->Update(*m_pLattice);
		Render();

		//handle events
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
				case SDL_KEYDOWN:
				//keyboard[event.key.keysym.sym] = false;
				break;
				case SDL_KEYUP:
				//keyboard[event.key.keysym.sym] = true;
				if( evt.key.keysym.sym == SDLK_SPACE )
				{
					m_iActiveGeneratorIndex = (m_iActiveGeneratorIndex + 1) % m_vecGenerators.size();
				}
				break;
				case SDL_QUIT:
				bFinished = true;
				break;
			}
		}
	}
#endif

	delete m_pLattice;

#ifdef OPENGL_RENDER
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
#endif
 	printf("Shutting down");
    return 0;
}
