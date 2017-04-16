""" Python wrapper for ract DMA helper. """

# import click
#
# from ract._ract_dma_c import ffi
# from ract._ract_dma_c import lib as ract_dma
# import numpy as np
#
#
# @click.command()
# def ract_dma_run():
#     ract_dma.initializeGpioInterface()
#     ract_dma.setup_pin()
#     ract_dma.set_pin(0)
#     raw_input('...')
#     ract_dma.set_pin(1)
#     raw_input('...')
#     ract_dma.set_pin(0)
#     raw_input('...')
#     flash_array = np.zeros(10, dtype=np.uint8)
#     flash_array[1] = 1
#     flash_array[3] = 1
#     flash_array[5] = 1
#     flash_array[7] = 1
#     flash_array[9] = 1
#     c_pointer = ffi.cast("uint8_t *", ffi.from_buffer(flash_array))
#     ract_dma.setPinByArray(c_pointer, len(flash_array))
#     raw_input('...END')
