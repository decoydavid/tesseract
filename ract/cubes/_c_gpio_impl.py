""" Helper utilities for the simulated cube.

    These are in a separate module in order to avoid importing
    pygame and OpenGL when using other cube controllers.
"""

import click
import faulthandler
import numpy as np
from ract._ract_dma_c import ffi
from ract._ract_dma_c import lib as ract_dma

from ract.utils import LAYER_MASKS

NO_CHIPS = 5
OUTPUTS_PER_CHIP = 16
DC_FULL_INTENSITY = 63


class CffiGpioCube(object):
    """ Raspberry Pi 1 hardware abstraction layer (HAL) for controlling the tesseract by directly toggling pins using
    GPIO.
    """

    def __init__(self, debug):
        """ Initialization
        """
        self._fps = None
        self._flattened_frame_layers = None
        self.RPI_GPIO_initialized = None
        self.mapping = np.array(range(0, 16, 2) + range(15, 0, -2) + range(16, 32, 2) + range(31, 16, -2) +
                           range(32, 48, 2) + range(47, 32, -2) + range(48, 64, 2) + range(63, 48, -2) +
                           range(64, 80, 1))
        self.reordered_layer = np.zeros(NO_CHIPS * OUTPUTS_PER_CHIP, dtype=np.uint16)
        self.debug = debug

    def setup(self, fps):
        """ Set up the cube hardware abstraction layer, which means:
         - instantiate a tesseract interface
         - set up the GPIO interface
         - clock in the LED dot-correction data
        :param fps:
        :return:
        """
        faulthandler.enable()
        # ract_dma.initialize_RPI_GPIO()
        # ract_dma.setup_interface()
        # if self.debug:
        #     ract_dma.enable_layer_debug()
        # dot_correction_data = np.full(NO_CHIPS * OUTPUTS_PER_CHIP, DC_FULL_INTENSITY, np.uint8)
        # c_pointer = ffi.cast("uint8_t *", ffi.from_buffer(dot_correction_data))
        # ract_dma.clock_in_dot_correction(c_pointer, len(dot_correction_data))
        ract_dma.initialize_RPI_GPIO()
        ract_dma.TLC5940_Init()
        ract_dma.TLC5940_ClockInDC()
        self._fps = fps
        self._flattened_frame_layers = None

    def teardown(self):
        """ Tear down the GPIO interface if it has been setup
        :return:
        """
        if self.RPI_GPIO_initialized:
            ract_dma.close_RPI_GPIO()

    def render(self, frame):
        """ Render data into a suitable format for the GPIO input
        :param frame:
        :return:
        """
        self._flattened_frame_layers = [np.concatenate((layer.reshape(64), mask))
                                        for layer, mask in zip(frame, LAYER_MASKS)]

    def tick(self):
        """ Call the gpio HAL to send one frame's worth of data to the raspberry pi
        :return:
        """
        for layer in self._flattened_frame_layers:
            np.put(self.reordered_layer, self.mapping, layer.astype(int))
            c_pointer = ffi.cast("uint16_t *", ffi.from_buffer(layer))
            ract_dma.set_gs_data(c_pointer, len(self.reordered_layer))
            ract_dma.TLC5940_SetGS_And_GS_PWM()
