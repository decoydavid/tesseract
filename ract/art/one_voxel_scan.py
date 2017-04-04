""" Move one lit voxel around the full cube. """

import itertools

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, MIN_INTENSITY, TimeStepper)


class OneVoxelScan(ArtworkRenderer):
    """ Move one lit voxel around the full cube. """

    NAME = 'one-voxel-scan'
    SECONDS_PER_STEP = 0.1

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._step_count = 0
        self._index = list(itertools.product(
            range(8), range(8), range(8)
        ))
        self._frame = constant_frame()

    def next_frame(self):
        if self._stepper.step():
            old_index = self._index[self._step_count]
            self._step_count += 1
            self._step_count %= 512
            new_index = self._index[self._step_count]
            self._frame[old_index] = MIN_INTENSITY
            self._frame[new_index] = MAX_INTENSITY
        return self._frame
