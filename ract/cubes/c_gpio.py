""" GPIO cube that renders by directly toggling pins using GPIO. """

from ract.interfaces import CubeController


class CffiGpioController(CubeController):
    """ GPIO cube that renders by directly toggling pins using GPIO via CFFI. """

    NAME = 'c_gpio'

    def setup(self, fps):
        from ._c_gpio_impl import CffiGpioCube
        self._gpio_cube = CffiGpioCube()
        self._gpio_cube.setup(fps)

    def teardown(self):
        self._gpio_cube.teardown()

    def render(self, frame):
        self._gpio_cube.render(frame)

    def tick(self):
        self._gpio_cube.tick()
