""" Dots spiral up and down between the floor and ceiling as per dor-rise-fall,
but in an order as opposed to randomly. """

import itertools
from random import random, shuffle
from math import floor, ceil

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, MIN_INTENSITY, TimeStepper)


class SpiralRiseFall(ArtworkRenderer):
    """ Move sprial of pixels between the floor and the ceiling """

    NAME = 'spiral-rise-fall'
    SECONDS_PER_STEP = 0.05
    SECONDS_BETWEEN_MOVES = 2
    DOTS_TO_MOVE = 35
    DOTS = 8 * 8

    def __init__(self):
        self._stepper = None
        self._step_count = None
        self._dot_grid = None
        self._dot_height = None
        self._dot_velocity = None
        self._move_time = None
        self._move_order = []
        self._frame = None
        self._dot_to_move = None

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._step_count = 0
        self._dot_grid = list(itertools.product(
            range(8), range(8)
        ))
        self._dot_height = [0] * self.DOTS
        self._dot_velocity = [0] * self.DOTS
        self._move_time = self.SECONDS_BETWEEN_MOVES
        # generate spiral
        x_pos = 4
        y_pos = 4
        move_dir = -1
        move_length = 1
        move_order = []
        while x_pos != 0 and y_pos != 0:
            for i in range(move_length):
                move_order.append((x_pos, y_pos))
                x_pos += move_dir
            for i in range(move_length):
                move_order.append((x_pos, y_pos))
                y_pos += move_dir
            move_length += 1
            move_dir *= -1
        for i in range(move_length):
            move_order.append((x_pos, y_pos))
            x_pos += move_dir
        for i in move_order:
            self._move_order.append(self._dot_grid.index(i))
        self._frame = constant_frame()

    def next_frame(self):
        if self._stepper.step():
            if self._move_time <= 0:
                start_velocity = 0.1
                for i in self._move_order:
                    self._dot_velocity[i] = start_velocity
                    start_velocity *= 0.75
                    print(start_velocity)

                self._move_time = 1000000
            else:
                self._move_time -= self.SECONDS_PER_STEP
            for i in range(self.DOTS):
                self._dot_height[i] = self._dot_height[i] + self._dot_velocity[i]
                self._dot_velocity[i] *= 2
                if self._dot_height[i] > 7:
                    self._dot_height[i] = 7
                    self._dot_velocity[i] = 0
                elif self._dot_height[i] < 0:
                    self._dot_height[i] = 0
                    self._dot_velocity[i] = 0

            self._frame = constant_frame()
            indexes_to_update = zip([int(i) for i in self._dot_height],
                                    [j[0] for j in self._dot_grid],
                                    [j[1] for j in self._dot_grid])
            _indexes_to_update = zip([i for i in self._dot_height],
                                     [j[0] for j in self._dot_grid],
                                     [j[1] for j in self._dot_grid])
            for z, y, x in _indexes_to_update:
                a = {(ceil(x), ceil(y), ceil(z)),
                     (ceil(x), ceil(y), floor(z)),
                     (ceil(x), floor(y), ceil(z)),
                     (ceil(x), floor(y), floor(z)),
                     (floor(x), ceil(y), ceil(z)),
                     (floor(x), ceil(y), floor(z)),
                     (floor(x), floor(y), ceil(z)),
                     (floor(x), floor(y), floor(z))}
                print(a)
            for index in indexes_to_update:
                self._frame[index] = MAX_INTENSITY
        return self._frame
