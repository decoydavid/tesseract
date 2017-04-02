""" GPIO cube that renders by directly toggling pins using GPIO. """

from ract.interfaces import CubeController


class GPIOController(CubeController):
    """ GPIO cube that renders by directly toggling pins using GPIO. """

    NAME = 'gpio'

    def setup(self, fps):
        from ._gpio_impl import GpioCube
        self._gpio_cube = GpioCube()
        self._gpio_cube.setup(fps)

    def teardown(self):
        self._gpio_cube.teardown()

    def render(self, frame):
        self._gpio_cube.render(frame)

    def tick(self):
        self._gpio_cube.tick()
