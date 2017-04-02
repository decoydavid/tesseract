""" Package for tesseract cube controllers. """

from .sim import SimulatedController
from .gpio import GPIOController

CUBES = [
    SimulatedController,
    GPIOController,
]
