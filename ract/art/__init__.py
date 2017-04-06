""" Package for tesseract art renders. """

from .one_voxel_scan import OneVoxelScan
from .game_of_life_2d import GameOfLife2D
from .worm_simulator import WormSimulator

ART = [
    OneVoxelScan,
    GameOfLife2D,
    WormSimulator,
]
