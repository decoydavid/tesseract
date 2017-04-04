""" 2-D Game of Life with history. """

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, TimeStepper)


class GameOfLife2D(ArtworkRenderer):
    """ 2-D Game of Life with history.

        Each frame contains the last eight steps of history of a game
        of life.
    """

    NAME = 'game-of-life-2d'
    SECONDS_PER_STEP = 0.1

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._frame = constant_frame()

    def _update_frame(self):
        new_frame = constant_frame()
        new_frame[1:8] = self._frame[0:7]
        cnt = self._stepper.count() % 8
        new_frame[0][0][cnt] = MAX_INTENSITY
        self._frame = new_frame

    def next_frame(self):
        if self._stepper.step():
            self._update_frame()
        return self._frame
