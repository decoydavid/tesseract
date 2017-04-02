""" Tesseract utility functions. """

import numpy as np

# Driver chip intensity range (2**12 steps)
MIN_INTENSITY = 0
MAX_INTENSITY = 4095

# Mapping from driver chip controller lines to Raspberry Pi GPIO pins
GSCLK = 3   # Orange
DCPRG = 5   # Brown
SCLK = 8    # White
XLAT = 10   # Blue
BLANK = 11  # Black
SIN = 12    # Red
VPRG = 13   # White / Green

# Mapping from physical sheet index to control line sheet positions
SHEET_CORRECTION_MAPPING = [
    6, 7, 0, 1, 3, 2, 5, 4
]


def constant_frame(intensity=MIN_INTENSITY):
    """ Return a tesseract frame where every pixel has a constant intensity.

    :return np.array:
        An 8 x 8 x 8 tesseract frame.
    """
    return np.full((8, 8, 8), intensity, np.uint16)
