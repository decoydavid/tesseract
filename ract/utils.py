""" Tesseract utility functions. """

import numpy as np

MIN_INTENSITY = 0
MAX_INTENSITY = 4095


def constant_frame(intensity=MIN_INTENSITY):
    """ Return a tesseract frame where every pixel has a constant intensity.

    :return np.array:
        An 8 x 8 x 8 tesseract frame.
    """
    return np.full((8, 8, 8), intensity, np.uint16)
