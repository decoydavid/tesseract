""" Move one lit voxel around the full cube. """

import itertools
import numpy as np
from random import randint, shuffle

from ract.interfaces import ArtworkRenderer
from ract.utils import (
    constant_frame, MAX_INTENSITY, MIN_INTENSITY, TimeStepper)


class Worm(object):
    UP = np.array([1, 0, 0])
    DOWN = np.array([-1, 0, 0])
    RIGHT = np.array([0, 1, 0])
    LEFT = np.array([0, -1, 0])
    IN = np.array([0, 0, 1])
    OUT = np.array([0, 0, -1])
    DIRECTIONS = [UP, DOWN, RIGHT, LEFT, IN, OUT]
    WORM_INTENSITY = int(MAX_INTENSITY * 2 / 3)

    def __init__(self, segment, direction, alive=True):
        """ Create a worm
        :param segment:
        :param direction:
        """
        self.segments = [segment]
        self.direction = direction
        self.alive = alive

    def add_segment(self, new_segment):
        """ Add new segment to worm
        :param new_segment:
        :return:
        """
        self.segments.append(new_segment)

    def head(self):
        """ Return head segment
        :return:
        """
        return self.segments[-1]

    def head_x(self):
        """ Return head x position
        :return:
        """
        return self.segments[-1][0]

    def head_y(self):
        """ Return head y position
        :return:
        """
        return self.segments[-1][1]

    def head_z(self):
        """ Return head z position
        :return:
        """
        return self.segments[-1][2]


class WormSimulator(ArtworkRenderer):
    """ Move a growing worm around the cube til it crashes without options. """

    NAME = 'worm-sim'
    SECONDS_PER_STEP = 0.2

    def __init__(self):
        """ Instantiation """
        self._frame = None
        self._worms = None
        self._stepper = None

    def setup(self, fps, number_of_worms=1):
        """ Initialize worms. The head is always the last item in the list
        :param fps:
        :param number_of_worms:
        :return:
        """
        self._stepper = TimeStepper(self.SECONDS_PER_STEP)
        self._frame = constant_frame()
        self._worms = []
        for worm in range(number_of_worms):
            self._worms.append(self._setup_worm())
        for worm in self._worms:
            self._frame[worm.head_x()][worm.head_y()][worm.head_z()] = \
                Worm.WORM_INTENSITY

    @staticmethod
    def _setup_worm():
        """ Initialize a worm
        :return:
        """
        worm = Worm(np.array([randint(0, 7), randint(0, 7), randint(0, 7)]),
                    Worm.DIRECTIONS[randint(0, 5)])
        return worm

    def _move_worm(self):
        """ Try to add a section to each worm as follows:
        1. Make a shuffled list of all moves.
        2. Check if the current move for the worm is legal and apply if possible
         and exit.
        3. If the list of moves has been exhausted raise WormDied.
        3. Take move from the list of moves and make the current move that move
        :return:
        """
        for worm in self._worms:
            moves = Worm.DIRECTIONS[:]
            shuffle(moves)
            try:
                while True:
                    new_move = worm.head() + worm.direction
                    if self._move_valid(new_move):
                        worm.add_segment(new_move)
                        break
                    worm.direction = moves[0]
                    del(moves[0])
            except IndexError:
                worm.alive = False
                self._worm_death(worm)

    def _move_valid(self, move):
        """ Legal moves are within the box and not into a piece of worm.
        :param move: Proposed move
        :return boolean:
        """
        try:
            occupied = self._frame[move[0]][move[1]][move[2]]
            if occupied > MIN_INTENSITY:
                return False
            if not all(list(move > -1)):
                return False
            return True
        except IndexError:
            return False

    def _worm_death(self, worm):
        """ Animate worm death. Worm flashes brightly on death
        :param worm:
        :return:
        """
        print("worm dies")
        for segment in worm.segments:
            self._frame[segment[0]][segment[1]][segment[2]] = MAX_INTENSITY

    def _worm_birth(self):
        """ Check if we need to rebirth a worm
        :return:
        """
        for worm in self._worms:
            if not worm.alive:
                print("worm lives")
                for segment in worm.segments:
                    self._frame[segment[0]][segment[1]][segment[2]] = \
                        MIN_INTENSITY
                dead_worm_index = self._worms.index(worm)
                self._worms[dead_worm_index] = self._setup_worm()

    def next_frame(self):
        if self._stepper.step():
            self._worm_birth()
            self._move_worm()
            for worm in self._worms:
                self._frame[worm.head_x()][worm.head_y()][worm.head_z()] = \
                    Worm.WORM_INTENSITY
        return self._frame
