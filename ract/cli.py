""" Run the tesseract. """

import time

import click

from .cubes import CUBES
from .art import ART

CUBES = {cube.NAME: cube for cube in CUBES}
ART = {art.NAME: art for art in ART}


@click.command()
@click.option(
    "--cube", type=click.Choice(sorted(CUBES.keys())),
    help="How to render images to the cube.")
@click.option(
    "--art", type=click.Choice(sorted(ART.keys())),
    help="Artwork to render.")
@click.option(
    "--fps", default=60.,
    help="Frames to render each second. Default is 60.")
@click.option(
    "--seconds", default=10.,
    help="Number of seconds to run for. Default is 10.")
def ract(cube, art, fps, seconds):
    """ Run the tesseract. """
    cube = CUBES[cube]()
    art = ART[art]()

    art.setup(fps)
    cube.setup(fps)

    start = time.time()
    while time.time() - start < seconds:
        frame = art.next_frame()
        cube.render(frame)
        cube.tick()
