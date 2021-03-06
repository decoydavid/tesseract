""" Package for tesseract art renders. """

from .all_on import AllOn
from .one_voxel_scan import OneVoxelScan
from .game_of_life_2d import GameOfLife2D
from .game_of_life_3d import GameOfLife3D
from .worm_simulator import WormSimulator
from .test_corners import TestCorners
from .dot_rise_fall import DotRiseFall

ART = [
    AllOn,
    OneVoxelScan,
    GameOfLife2D,
    GameOfLife3D,
    WormSimulator,
    TestCorners,
    DotRiseFall,
]
