""" Light all the LEDs. """

from ract.interfaces import ArtworkRenderer
from ract.utils import constant_frame, MAX_INTENSITY


class TestCorners(ArtworkRenderer):
    """  Light all the LEDs. """

    NAME = 'test-corners'
    SECONDS_PER_STEP = 0.1

    def setup(self, fps):
        self._frame = constant_frame()
        self._frame[0][0][0] = MAX_INTENSITY
        self._frame[0][0][7] = MAX_INTENSITY
        self._frame[0][7][0] = MAX_INTENSITY
        self._frame[0][7][7] = MAX_INTENSITY
        self._frame[7][0][0] = MAX_INTENSITY
        self._frame[7][0][7] = MAX_INTENSITY
        self._frame[7][7][0] = MAX_INTENSITY
        self._frame[7][7][7] = MAX_INTENSITY

    def next_frame(self):
        return self._frame
