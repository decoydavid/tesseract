""" Tesseract utility functions. """

import time

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


class TimeStepper(object):
    """ An object that tracks time steps.

        :param float seconds_per_step:
            Seconds between steps. E.g. 0.1, 0.5, 2.5.
    """
    def __init__(self, seconds_per_step):
        self._seconds_per_step = seconds_per_step
        # ensure we take the first step straight away
        self._last_step = time.time() - (2 * seconds_per_step)

    def step(self):
        """ Returns True if enough time has passed for the next step. """
        now = time.time()
        if now - self._last_step >= self._seconds_per_step:
            self._last_step = now
            return True
        return False
