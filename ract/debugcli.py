""" Pure Python debugging tools for the tesseract. """

import click

from ract.cubes._gpio_impl import GpioTesseract
from ract.utils import SHEET_CORRECTION_MAPPING

gsData1 = [
    4095,  # Channel 15
    4095,  # Channel 14
    4095,  # Channel 13
    4095,  # Channel 12
    4095,  # Channel 11
    4095,  # Channel 10
    4095,  # Channel 9
    4095,  # Channel 8
    4095,  # Channel 7
    4095,  # Channel 6
    4095,  # Channel 5
    4095,  # Channel 4
    4095,  # Channel 3
    4095,  # Channel 2
    4095,  # Channel 1
    4095,  # Channel 0
]


gsData0 = [
    0,  # Channel 15
    0,  # Channel 14
    0,  # Channel 13
    0,  # Channel 12
    0,  # Channel 11
    0,  # Channel 10
    0,  # Channel 9
    0,  # Channel 8
    0,  # Channel 7
    0,  # Channel 6
    0,  # Channel 5
    0,  # Channel 4
    0,  # Channel 3
    0,  # Channel 2
    0,  # Channel 1
    0,  # Channel 0
]

layer_mask = [
    [0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4095],
]


@click.command()
def ractdebug():
    ract = GpioTesseract()
    ract.setup()

    try:
        ract.test_pins()
        ract.clock_in_dot_correction()
        for layer in layer_mask:
            ract.clock_in_grey_scale_data(gsData1 * 4 + layer)
            ract.toggle_gsclk(1000)
        for i in SHEET_CORRECTION_MAPPING:
            for j in range(8):
                for layer in layer_mask:
                    data = [0] * 16 * 4
                    data[i * 8 + j] = 4095
                    ract.clock_in_grey_scale_data(data + layer)
                    ract.toggle_gsclk(1000)

    except Exception as e:
        print('Exception caught %s' % e)
    finally:
        ract.teardown()
