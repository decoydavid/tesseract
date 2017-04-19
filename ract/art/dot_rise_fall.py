""" Arrange half of the dots on the ceiling and half on
the floor and randomly have them move to swap sides. """

import itertools
from random import random, shuffle
from math import floor

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, MIN_INTENSITY, TimeStepper)


class DotRiseFall(ArtworkRenderer):
    """ Move pixels between the floor and the ceiling """

    NAME = 'dot-rise-fall'
    SECONDS_PER_STEP = 0.05
    SECONDS_MAX_MOVE_WINDOW = 5
    DOTS_TO_MOVE = 35
    DOTS = 8 * 8

    def __init__(self):
        self._stepper = None
        self._step_count = None
        self._dot_grid = None
        self._dot_height = None
        self._dot_velocity = None
        self._move_time = None
        self._frame = None

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._step_count = 0
        self._dot_grid = list(itertools.product(
            range(8), range(8)
        ))
        self._dot_height = [0] * self.DOTS
        self._dot_velocity = [0] * self.DOTS
        self._move_time = random() * self.SECONDS_MAX_MOVE_WINDOW
        random_heights = range(self.DOTS)
        shuffle(random_heights)
        random_heights = random_heights[len(random_heights) / 2:]
        for height in random_heights:
            self._dot_height[height] = 7
        self._frame = constant_frame()

    def next_frame(self):
        if self._stepper.step():
            if self._move_time <= 0:
                self._move_time = random() * self.SECONDS_MAX_MOVE_WINDOW
                for i in range(self.DOTS_TO_MOVE):
                    random_dot = int(floor(random() * self.DOTS))
                    if self._dot_velocity[random_dot] == 0:
                        self._dot_velocity[random_dot] = 0.5 if self._dot_height[random_dot] is 0 else -0.5
            for i in range(self.DOTS):
                self._dot_height[i] = int(self._dot_height[i] + self._dot_velocity[i])
                self._dot_velocity[i] *= 1.2
                if self._dot_height[i] > 7:
                    self._dot_height[i] = 7
                    self._dot_velocity[i] = 0
                elif self._dot_height[i] < 0:
                    self._dot_height[i] = 0
                    self._dot_velocity[i] = 0
            self._move_time -= self.SECONDS_PER_STEP

            self._frame = constant_frame()
            indexes_to_update = zip(self._dot_height,
                                    [j[0] for j in self._dot_grid],
                                    [j[1] for j in self._dot_grid])
            for index in indexes_to_update:
                self._frame[index] = MAX_INTENSITY
        return self._frame
