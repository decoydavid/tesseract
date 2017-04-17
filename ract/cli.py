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
@click.option(
    "--disp-timer", default=False, is_flag=True,
    help="Display timer of how long rendering and data transfer take.")
@click.option(
    "--debug", default=False, is_flag=True,
    help="Enable debugging.")
def ract(cube, art, fps, seconds, disp_timer, debug):
    """ Run the tesseract. """
    cube = CUBES[cube]()
    art = ART[art]()

    art.setup(fps)
    cube.setup(fps, debug)

    start = time.time()
    timer = time.time()
    while time.time() - start < seconds:
        frame = art.next_frame()
        cube.render(frame)
        if disp_timer:
            click.echo("Time to render art: %f" % (time.time() - timer))
            timer = time.time()
        cube.tick()
        if disp_timer:
            click.echo("Time to display art: %f" % (time.time() - timer))
            timer = time.time()

    cube.teardown()
