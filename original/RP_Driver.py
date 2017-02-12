
import time

import RPi.GPIO as GPIO


dCData = [
    [1, 1, 1, 1, 1, 1], # Channel 15
    [1, 1, 1, 1, 1, 1], # Channel 14
    [1, 1, 1, 1, 1, 1], # Channel 13
    [1, 1, 1, 1, 1, 1], # Channel 12
    [1, 1, 1, 1, 1, 1], # Channel 11
    [1, 1, 1, 1, 1, 1], # Channel 10
    [1, 1, 1, 1, 1, 1], # Channel 9
    [1, 1, 1, 1, 1, 1], # Channel 8
    [1, 1, 1, 1, 1, 1], # Channel 7
    [1, 1, 1, 1, 1, 1], # Channel 6
    [1, 1, 1, 1, 1, 1], # Channel 5
    [1, 1, 1, 1, 1, 1], # Channel 4
    [1, 1, 1, 1, 1, 1], # Channel 3
    [1, 1, 1, 1, 1, 1], # Channel 2
    [1, 1, 1, 1, 1, 1], # Channel 1
    [1, 1, 1, 1, 1, 1] # Channel 0
    ]

dCData_dec = [
    63, # Channel 15
    63, # Channel 14
    63, # Channel 13
    63, # Channel 12
    63, # Channel 11
    63, # Channel 10
    63, # Channel 9
    63, # Channel 8
    63, # Channel 7
    63, # Channel 6
    63, # Channel 5
    63, # Channel 4
    63, # Channel 3
    63, # Channel 2
    63, # Channel 1
    63 # Channel 0
    ]

gsData1 = [
    4095, # Channel 15
    4095, # Channel 14
    4095, # Channel 13
    4095, # Channel 12
    4095, # Channel 11
    4095, # Channel 10
    4095, # Channel 9
    4095, # Channel 8
    4095, # Channel 7
    4095, # Channel 6
    4095, # Channel 5
    4095, # Channel 4
    4095, # Channel 3
    4095, # Channel 2
    4095, # Channel 1
    4095 # Channel 0
    ]   

gsData0 = [
    0, # Channel 15
    0, # Channel 14
    0, # Channel 13
    0, # Channel 12
    0, # Channel 11
    0, # Channel 10
    0, # Channel 9
    0, # Channel 8
    0, # Channel 7
    0, # Channel 6
    0, # Channel 5
    0, # Channel 4
    0, # Channel 3
    0, # Channel 2
    0, # Channel 1
    0 # Channel 0
    ]   

GSCLK = 3   #Orange
DCPRG = 5   #Brown
VPRG = 7    #White/Green
SCLK = 8    #White
XLAT = 10   #Blue
BLANK = 11  #Black
SIN = 12    #Red

def test_pins():
    for i, name in [[GSCLK, 'GSCLK'], [DCPRG, 'DCPRG'], [VPRG, 'VPRG'],
                    [SCLK, 'SCLK'], [XLAT, 'XLAT'], [SIN, 'SIN']]:
        print('Toggling %s' % name)
        GPIO.output(i, True)
        time.sleep(1)
        GPIO.output(i, False)
    
def send_DC_byte(value_to_send, no_bits):
    byte = [0] * no_bits
    print(value_to_send)
    for i in range(no_bits):
        byte[i] = (value_to_send >> i) & 0x01
        GPIO.output(SIN, byte[i])
        GPIO.output(SCLK, True)
        GPIO.output(SCLK, False)

def send_GS_byte(value_to_send, no_bits):
    byte = [0] * no_bits
    print(value_to_send)
    for i in range(no_bits):
        byte[i] = (value_to_send >> i) & 0x01
        GPIO.output(SIN, byte[i])
        GPIO.output(SCLK, True)
        GPIO.output(SCLK, False)
        GPIO.output(GSCLK, True)
        GPIO.output(GSCLK, False)

def latch_data():
    GPIO.output(XLAT, True)
    GPIO.output(XLAT, False)

def clock_in_dot_correction():
    GPIO.output(DCPRG, True)
    GPIO.output(VPRG, True)
    for i in range(len(dCData_dec)):
        send_DC_byte(dCData_dec[i], 6)
    latch_data()

def clock_in_grey_scale_data(data_to_send):
    first_cycle_flag = 0
    data_sets_to_send = 1
    i = 0
    data_set = 0
    GPIO.output(BLANK, True)
    GPIO.output(BLANK, False)
    if GPIO.input(VPRG):
        GPIO.output(VPRG, False)
        first_cycle_flag = 1
        print('GS in: First cycle')

    while i < 4096:
        if data_set < data_sets_to_send:
            for j in range(len(data_to_send)):
                send_GS_byte(data_to_send[i], 12)
            data_set += 1
            i += 192
        else:
            i += 1
            GPIO.output(GSCLK, True)
            GPIO.output(GSCLK, False)
    latch_data()
    if first_cycle_flag:
        GPIO.output(SCLK, True)
        GPIO.output(SCLK, False)
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
    GPIO.output(GSCLK, False)
    GPIO.output(DCPRG, False)
    GPIO.output(VPRG, True)
    GPIO.output(SCLK, False)
    GPIO.output(XLAT, False)
    GPIO.output(BLANK, True)
  
    try:
        #test_pins()
        clock_in_dot_correction()
        time.sleep(1)
        clock_in_grey_scale_data(gsData1)
        time.sleep(1)
        clock_in_grey_scale_data(gsData0)
        time.sleep(1)
        clock_in_grey_scale_data(gsData1)
        time.sleep(1)
        clock_in_grey_scale_data(gsData0)
        '''
        for i in range(4095):
            data = [i] * 16
            t0 = time.time()
            while 0.1 > time.time() - t0:
                clock_in_grey_scale_data(data)

        '''
    except Exception as e:
        print('Exception caught %s' % e)
    finally:
        GPIO.cleanup()
