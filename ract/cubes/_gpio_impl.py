""" Helper utilities for the simulated cube.

    These are in a separate module in order to avoid importing
    pygame and OpenGL when using other cube controllers.
"""

import faulthandler


class GpioCube(object):
    """ Control the tesseract by directly toggling pins using GPIO. """

    def __init__(self):
        pass

    def setup(self, fps):
        faulthandler.enable()
        self._fps = fps

    def teardown(self):
        pass

    def render(self, frame):
        pass

    def tick(self):
        pass
