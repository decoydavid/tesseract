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

    def __init__(self):
        """ Initialization
        """
        self._fps = None
        self._flattened_frame_layers = None
        self.RPI_GPIO_initialized = None

    def setup(self, fps):
        """ Set up the cube hardware abstraction layer, which means:
         - instantiate a tesseract interface
         - set up the GPIO interface
         - clock in the LED dot-correction data
        :param fps:
        :return:
        """
        faulthandler.enable()
        ract_dma.initialize_RPI_GPIO()
        ract_dma.setup_interface_pins()
        dot_correction_data = np.full(NO_CHIPS * OUTPUTS_PER_CHIP, DC_FULL_INTENSITY, np.uint8)
        c_pointer = ffi.cast("uint8_t *", ffi.from_buffer(dot_correction_data))
        ract_dma.clock_in_dot_correction(c_pointer, len(dot_correction_data))
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
            c_pointer = ffi.cast("uint16_t *", ffi.from_buffer(layer))
            ract_dma.clock_in_grey_scale_data(c_pointer, len(layer))
