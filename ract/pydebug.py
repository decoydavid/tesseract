""" Pure Python debugging tools for the tesseract. """

import RPi.GPIO as GPIO


dc_data = [
    63,  # Channel 15
    63,  # Channel 14
    63,  # Channel 13
    63,  # Channel 12
    63,  # Channel 11
    63,  # Channel 10
    63,  # Channel 9
    63,  # Channel 8
    63,  # Channel 7
    63,  # Channel 6
    63,  # Channel 5
    63,  # Channel 4
    63,  # Channel 3
    63,  # Channel 2
    63,  # Channel 1
    63,  # Channel 0
]


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

sheet_correction_mapping = [
    6, 7, 0, 1, 3, 2, 5, 4
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

GSCLK = 3   # Orange
DCPRG = 5   # Brown
SCLK = 8    # White
XLAT = 10   # Blue
BLANK = 11  # Black
SIN = 12    # Red
VPRG = 13   # White / Green


def set_pin(pin, value):
    """ Set GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    if value:
        GPIO.output(pin, False)
        GPIO.output(pin, False)
        GPIO.output(pin, False)
        GPIO.output(pin, False)
        GPIO.output(pin, False)
    else:
        GPIO.output(pin, True)
        GPIO.output(pin, True)
        GPIO.output(pin, True)
        GPIO.output(pin, True)
        GPIO.output(pin, True)


def get_pin(pin):
    """ Read GPIO pin.

        This inverts the value set to compensate for the
        hardware inversion that happens in between the Pi
        and the LED driver chips.
    """
    return not GPIO.input(pin)


def test_pins():
    """ Toggle all pins high and low for testing.
    """
    for i, name in [
            [GSCLK, 'GSCLK'], [DCPRG, 'DCPRG'], [VPRG, 'VPRG'],
            [SCLK, 'SCLK'], [XLAT, 'XLAT'], [SIN, 'SIN'], [BLANK, 'BLANK']]:
        print('Toggling %s (pin %d)' % (name, i))
        set_pin(i, True)
        raw_input("High")
        set_pin(i, False)
        raw_input("Low")


def send_DC_byte(value_to_send, no_bits):
    for i in range(no_bits):
        bit = (value_to_send >> i) & 0x01
        set_pin(SIN, bit)
        set_pin(SCLK, True)
        set_pin(SCLK, False)


def send_GS_byte(value_to_send, no_bits):
    print(value_to_send)
    for i in range(no_bits):
        bit = (value_to_send >> i) & 0x01
        set_pin(SIN, bit)
        set_pin(SCLK, True)
        set_pin(SCLK, False)


def latch_data():
    set_pin(XLAT, True)
    set_pin(XLAT, False)


def clock_in_dot_correction(data):
    set_pin(DCPRG, True)
    set_pin(VPRG, True)
    for v in data:
        send_DC_byte(v, 6)
    latch_data()


def toggle_gsclk(times):
    for i in range(times):
        if i % 4096 == 0:
            set_pin(BLANK, True)
            set_pin(BLANK, False)
        set_pin(GSCLK, True)
        set_pin(GSCLK, False)


def clock_in_grey_scale_data(data_to_send):
    set_pin(BLANK, True)

    first_cycle_flag = 0
    if get_pin(VPRG):
        set_pin(VPRG, False)
        first_cycle_flag = 1
        print('GS in: First cycle')

    for v in data_to_send:
        send_GS_byte(v, 12)

    latch_data()
    set_pin(BLANK, False)

    if first_cycle_flag:
        set_pin(SCLK, True)
        set_pin(SCLK, False)
        first_cycle_flag = 0
        print('GS out: First cycle')


if __name__ == '__main__':
    print('Main')
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

    try:
        test_pins()
        clock_in_dot_correction(dc_data * 5)
        for layer in layer_mask:
            clock_in_grey_scale_data(gsData1 * 4 + layer)
            toggle_gsclk(1000)
        for i in sheet_correction_mapping:
            for j in range(8):
                for layer in layer_mask:
                    data = [0] * 16 * 4
                    data[i * 8 + j] = 4095
                    clock_in_grey_scale_data(data + layer)
                    toggle_gsclk(1000)

    except Exception as e:
        print('Exception caught %s' % e)
    finally:
        GPIO.cleanup()
