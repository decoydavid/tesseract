""" Build the DMA helper library. """

import sys
import cffi

from helpers import get_inc_dir, get_lib_dir, get_c_lib


ffi = cffi.FFI()

ffi.cdef("""
""")

sdl = ffi.set_source(
    "ract._ract_dma",
    libraries=[],
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
