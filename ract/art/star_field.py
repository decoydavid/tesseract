""" Star field simulation. """

import itertools
from random import random, randint
from math import ceil, floor
import numpy as np

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
    SECONDS_PER_STEP = 0.05
    TOTAL_STARS = 70

    def __init__(self):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._stars = []
        self._frame = constant_frame()

    def setup(self, fps):
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        for i in range(self.TOTAL_STARS):
            self._stars.append(Star(random() * 7, random() * 7, random() * 7, random() * 0.1 + 0.1))
        self._frame = constant_frame()

    def next_frame(self):
        if self._stepper.step():
            self._frame = constant_frame()
            for i in range(len(self._stars)):
                star = self._stars[i]
                print(star.x, star.y, star.z)
                a = {(int(ceil(star.x)), int(ceil(star.y)), int(ceil(star.z))),
                     (int(ceil(star.x)), int(ceil(star.y)), int(floor(star.z))),
                     (int(ceil(star.x)), int(floor(star.y)), int(ceil(star.z))),
                     (int(ceil(star.x)), int(floor(star.y)), int(floor(star.z))),
                     (int(floor(star.x)), int(ceil(star.y)), int(ceil(star.z))),
                     (int(floor(star.x)), int(ceil(star.y)), int(floor(star.z))),
                     (int(floor(star.x)), int(floor(star.y)), int(ceil(star.z))),
                     (int(floor(star.x)), int(floor(star.y)), int(floor(star.z)))}
                j = np.array((star.x, star.y, star.z))
                distances = [np.linalg.norm(j - np.array(_star)) for _star in a]
                for _star, _dist in zip(a, distances):
                    self._frame[_star] += MAX_INTENSITY * max(0, 1 - _dist)
                star.z += star.speed
                if star.z > 7 or star.z < 0:
                    self._stars[i] = Star(random() * 7, random() * 7, 0, random() * 0.1 + 0.1)

        return self._frame
