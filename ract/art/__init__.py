""" Package for tesseract art renders. """

from .all_on import AllOn
from .one_voxel_scan import OneVoxelScan
from .game_of_life_2d import GameOfLife2D
from .game_of_life_3d import GameOfLife3D

ART = [
    AllOn,
    OneVoxelScan,
    GameOfLife2D,
    GameOfLife3D,
]
