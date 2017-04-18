""" Build the DMA helper library. """

import sys
import cffi

from helpers import get_inc_dir, get_lib_dir, get_c_lib


ffi = cffi.FFI()

ffi.cdef("""
void set_gs_data(uint16_t * u16_data, uint16_t u16_data_len);
void set_pin(int pin, int value);
uint8_t get_pin(int pin);
void TLC5940_Init(void);
void TLC5940_Pulse(int pin);
void test_pin(int pin, const char* name);
void TLC5940_ClockInDC(void);
void TLC5940_SetGS_And_GS_PWM(void);
""")

lib = ffi.set_source(
    "ract._ract_dma_c",
    libraries=['bcm2835'],
    include_dirs=get_inc_dir(),
    library_dirs=get_lib_dir(),
    source="""

    %(ract_dma_h)s

    %(ract_dma_c)s
    """ % {
        'ract_dma_h': get_c_lib('ract_dma.h'),
        'ract_dma_c': get_c_lib('ract_dma.c'),
    }
)


if __name__ == "__main__":
    ffi.compile()
