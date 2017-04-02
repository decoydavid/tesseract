""" Helper utilities for the simulated cube.

    These are in a separate module in order to avoid importing
    pygame and OpenGL when using other cube controllers.
"""

import click
import faulthandler
import RPi.GPIO as GPIO

from ract.utils import (
    GSCLK, DCPRG, SCLK, XLAT, BLANK, SIN, VPRG)


class GpioCube(object):
    """ Raspberry Pi 1 hardware abstraction layer (HAL) for controlling the tesseract by directly toggling pins using
    GPIO.
    """

    def __init__(self):
        """ Initialization
        """
        self._fps = None
        self._flattened_frame = None
        self._tesseract = None
        self._gpio_setup = False

    def setup(self, fps):
        """ Set up the cube hardware abstraction layer, which means:
         - instantiate a tesseract interface
         - set up the GPIO interface
         - clock in the LED dot-correction data
        :param fps:
        :return:
        """
        faulthandler.enable()
        self._tesseract = GpioTesseract()
        self._tesseract.setup()
        self._gpio_setup = True
        self._tesseract.clock_in_dot_correction(self._tesseract.default_dot_correction())
        self._fps = fps
        self._flattened_frame = None

    def teardown(self):
        """ Tear down the GPIO interface if it has been setup
        :return:
        """
        if self._gpio_setup:
            self._tesseract.teardown()

    def render(self, frame):
        """ Render data into a suitable format for the GPIO input
        :param frame:
        :return:
        """
        self._flattened_frame = frame.reshape(512)

    def tick(self):
        """ Call the gpio HAL to send one frame's worth of data to the raspberry pi
        :return:
        """
        self._tesseract.clock_in_grey_scale_data(self._flattened_frame)


class GpioTesseract(object):
    """ Control the tesseract using GPIO. """

    def __init__(self):
        # utilites for echoing and waiting for user input.
        self._echo = click.echo
        self._pause = click.pause

    def setup(self):
        self._first_gs_cycle = True

        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(GSCLK, GPIO.OUT)
        GPIO.setup(DCPRG, GPIO.OUT)
        GPIO.setup(VPRG, GPIO.OUT)
        GPIO.setup(SCLK, GPIO.OUT)
        GPIO.setup(XLAT, GPIO.OUT)
        GPIO.setup(BLANK, GPIO.OUT)
        GPIO.setup(SIN, GPIO.OUT)
        set_pin(GSCLK, False)
        set_pin(DCPRG, False)
        set_pin(VPRG, True)
        set_pin(SCLK, False)
        set_pin(XLAT, False)
        set_pin(BLANK, True)

    def teardown(self):
        GPIO.cleanup()

    def test_pins(self):
        """ Toggle all pins high and low for testing.
        """
        for i, name in [
            [GSCLK, 'GSCLK'], [DCPRG, 'DCPRG'], [VPRG, 'VPRG'],
            [SCLK, 'SCLK'], [XLAT, 'XLAT'], [SIN, 'SIN'], [BLANK, 'BLANK'],
        ]:
            self._echo('Toggling %s (pin %d)' % (name, i))
            set_pin(i, True)
            self._echo('  pin high')
            self._pause()
            set_pin(i, False)
            self._echo('  pin low')
            self._pause()

    def default_dot_correction(self):
        # set all 16 LED lines on all 5 chips to maximum brightness
        return [63] * 16 * 5

    def clock_in_dot_correction(self, data=None):
        """ Clock in the LED dot / brightness correction factors.
        """
        if data is None:
            data = self.default_dot_correction()
        set_pin(DCPRG, True)
        set_pin(VPRG, True)
        for v in data:
            self.send_dc_byte(v)
        self.latch_data()
        set_pin(VPRG, False)

    def send_dc_byte(self, value_to_send, no_bits=6):
        """ Clock in one dot correction byte. """
        for i in range(no_bits):
            bit = (value_to_send >> i) & 0x01
            set_pin(SIN, bit)
            set_pin(SCLK, True)
            set_pin(SCLK, False)

    def clock_in_grey_scale_data(self, data_to_send):
        set_pin(BLANK, True)

        for v in data_to_send:
            self.send_gs_byte(v)

        self.latch_data()
        set_pin(BLANK, False)

        if self._first_gs_cycle:
            # toggle SCLK one exta time on the first grey-scale clock in.
            set_pin(SCLK, True)
            set_pin(SCLK, False)
            self._first_gs_cycle = False
            self._echo('First grey-scale clock in complete')

    def send_gs_byte(self, value_to_send, no_bits=12):
        """ Clock in one grey-scale byte. """
        for i in range(no_bits):
            bit = (value_to_send >> i) & 0x01
            set_pin(SIN, bit)
            set_pin(SCLK, True)
            set_pin(SCLK, False)

    def latch_data(self):
        """ Signal that data has been latched in. """
        set_pin(XLAT, True)
        set_pin(XLAT, False)

    def toggle_gsclk(self, times=4096):
        """ Clear the GSCLK line and then toggle it the specified number of
            times.

            :param int times:
                How many times to toggle the GSCLK. Each time the clock is
                toggled it increments by one. If the intensity value of
                an LED is greater than the current count, it is turned on.
                Otherwise it is turned off. The default value is 4096. Other
                counts won't cover the full grey-scale intensity range.

            The GSCLK controls the PWM cycles of the LEDs and so must
            be continually clocked for the LEDs to be PWMed.
        """
        # clear GSCLK
        set_pin(BLANK, True)
        set_pin(BLANK, False)
        # increment the grey-scale count
        for i in xrange(times):
            set_pin(GSCLK, True)
            set_pin(GSCLK, False)


def set_pin(pin, value):
    """ Set GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    if value:
        GPIO.output(pin, False)
    else:
        GPIO.output(pin, True)


def get_pin(pin):
    """ Read GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    return not GPIO.input(pin)
