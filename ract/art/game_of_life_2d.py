""" 2-D Game of Life with history. """

import numpy as np

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
    PATTERN = 'two-gliders'

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._frame = constant_frame()
        self._frame[0] = self._initial_population() * MAX_INTENSITY
        self._neighbours = np.array([
            [i, j] for i in (-1, 0, 1) for j in (-1, 0, 1)
            if i != 0 or j != 0
        ])

    def _initial_population(self):
        return INITIAL_CONDITIONS[self.PATTERN]

    def _update_life(self, layer):
        layer = layer / MAX_INTENSITY  # hackity hack
        counts = sum(
            np.roll(layer, (i, j), (0, 1))
            for i, j in self._neighbours)
        return (counts == 3) | (layer & (counts == 2))

    def _update_frame(self):
        new_frame = constant_frame()
        new_frame[1:8] = self._frame[0:7]
        new_frame[0] = self._update_life(self._frame[0]) * MAX_INTENSITY
        if not np.any(new_frame[0]):
            new_frame[0] = self._initial_population() * MAX_INTENSITY
        self._frame = new_frame

    def next_frame(self):
        if self._stepper.step():
            self._update_frame()
        return self._frame


INITIAL_CONDITIONS = {
    'glider': np.array([
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0],
        [0, 0, 1, 1, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
    ]),
    'two-gliders': np.array([
        [0, 1, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0, 0, 0],
        [1, 1, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
    ]),
    'r-pentomino': np.array([
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 1, 0, 0, 0],
        [0, 0, 1, 1, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
    ]),
    'houndstooth': np.array([
        [0, 1, 0, 0, 0, 1, 0, 0],
        [0, 1, 1, 1, 0, 1, 1, 1],
        [1, 1, 1, 0, 1, 1, 1, 0],
        [0, 0, 1, 0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0, 1, 0, 0],
        [0, 1, 1, 1, 0, 1, 1, 1],
        [1, 1, 1, 0, 1, 1, 1, 0],
        [0, 0, 1, 0, 0, 0, 1, 0],
    ]),
}
