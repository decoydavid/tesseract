""" 3-D Game of Life. """

import numpy as np

from ract.interfaces import ArtworkRenderer
from ract.utils import MAX_INTENSITY, TimeStepper


class GameOfLife3D(ArtworkRenderer):
    """ 3-D Game of Life.

        An 8 x 8 x 8 game of life with periodic boundary conditions.
    """

    NAME = 'game-of-life-3d'
    SECONDS_PER_STEP = 0.1

    A, B = 5, 7  # living cell stays alive if it has A <= neighbours <= B
    C, D = 6, 6  # empty cell becomes alive if it has C <= neighbours <= D
    INITIAL_FRACTION = 0.8 * D / 26.  # 26 neighbours per cell

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._frame = self._initial_population() * MAX_INTENSITY
        self._neighbours = np.array([
            [i, j, k]
            for i in (-1, 0, 1) for j in (-1, 0, 1) for k in (-1, 0, 1)
            if i != 0 or j != 0 or k != 0
        ])

    def _initial_population(self):
        return (
            np.random.rand(8, 8, 8) < self.INITIAL_FRACTION).astype(np.uint16)

    def _update_life(self, frame):
        frame = frame / MAX_INTENSITY  # hackity hack
        counts = sum(
            np.roll(frame, (i, j, k), (0, 1, 2))
            for i, j, k in self._neighbours)
        return (
            ((frame) & (self.A <= counts) & (counts <= self.B)) |
            ((frame == 0) & (self.C <= counts) & (counts <= self.D))
        )

    def _update_frame(self):
        new_frame = self._update_life(self._frame) * MAX_INTENSITY
        if not np.any(new_frame) or np.all(self._frame == new_frame):
            new_frame = self._initial_population() * MAX_INTENSITY
        self._frame = new_frame

    def next_frame(self):
        if self._stepper.step():
            self._update_frame()
        return self._frame
