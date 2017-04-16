""" Build the DMA helper library. """

import sys
import cffi

from helpers import get_inc_dir, get_lib_dir, get_c_lib


ffi = cffi.FFI()

ffi.cdef("""
int initialize_RPI_GPIO(void);
int close_RPI_GPIO(void);
void setup_interface_pins(void);
void set_pin(uint8_t u8_pin, uint8_t u8_level);
void clock_in_dot_correction(uint8_t * u8_data, uint16_t u16_data_len);
void send_dot_correction(uint8_t u8_dot_correction);
void clock_in_grey_scale_data(uint16_t * u16_data, uint16_t u16_data_len);
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
