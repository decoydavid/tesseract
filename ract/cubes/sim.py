""" Simulated cube that renders using pygame and OpenGL. """

from ract.interfaces import CubeController


class SimulatedController(CubeController):
    """ Simulated cube that renders using pygame and OpenGL. """

    NAME = 'sim'

    def setup(self, fps):
        from ._sim_impl import SimCube
        self._sim_cube = SimCube()
        self._sim_cube.setup(fps)

    def teardown(self):
        self._sim_cube.teardown()

    def render(self, frame):
        self._sim_cube.render(frame)

    def tick(self):
        self._sim_cube.tick()
