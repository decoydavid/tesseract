""" Star field simulation. """

import itertools
from random import random, randint

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, MIN_INTENSITY, TimeStepper)


class Star(object):
    def __init__(self, x, y, z, speed):
        self.x = x
        self.y = y
        self.z = z
        self.speed = speed


class StarField(ArtworkRenderer):
    """ Does what it says on the box. """

    NAME = 'star-field'
    SECONDS_PER_STEP = 0.1
    TOTAL_STARS = 50

    def __init__(self):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._stars = []
        self._frame = constant_frame()

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        for i in range(self.TOTAL_STARS):
            self._stars.append(Star(randint(0, 7), randint(0, 7), randint(0, 7), random() * 0.3))
        self._frame = constant_frame()

    def next_frame(self):
        if self._stepper.step():
            self._frame = constant_frame()
            for i in self._stars:
                

        return self._frame
