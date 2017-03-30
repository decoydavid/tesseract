""" GPIO cube that renders by directly toggling pins using GPIO. """

from ract.interfaces import CubeController


class GPIOController(CubeController):
    """ GPIO cube that renders by directly toggling pins using GPIO. """

    NAME = 'gpio'

    def setup(self, fps):
        pass

    def render(self, frame):
        pass

    def tick(self):
        pass
