""" Python wrapper for ract DMA helper. """

import click

from ract._ract_dma_c import ffi
from ract._ract_dma_c import lib as ract_dma


@click.command()
def ract_dma_run():
    ract_dma.setup_pin()
    ract_dma.set_pin(0)
    raw_input('...')
    ract_dma.set_pin(1)
    raw_input('...')
