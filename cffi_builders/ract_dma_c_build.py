""" Build the DMA helper library. """

import sys
import cffi

from helpers import get_inc_dir, get_lib_dir, get_c_lib


ffi = cffi.FFI()

ffi.cdef("""
void initializeGpioInterface(void);
void setup_pin(void);
void set_pin(int value);
void setPinByArray(uint8_t * intArray, int lenArray);
#define HIGH ...
#define LOW ...
void bcm2835_gpio_write(uint8_t pin, uint8_t on);
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
