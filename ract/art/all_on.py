""" Light all the LEDs. """

from ract.interfaces import ArtworkRenderer
from ract.utils import constant_frame, MAX_INTENSITY


class AllOn(ArtworkRenderer):
    """  Light all the LEDs. """

    NAME = 'all-on'
    SECONDS_PER_STEP = 0.1

    def setup(self, fps):
        self._frame = constant_frame(MAX_INTENSITY)

    def next_frame(self):
        return self._frame
