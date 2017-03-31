""" Helper utilities for the simulated cube.

    These are in a separate module in order to avoid importing
    pygame and OpenGL when using other cube controllers.
"""

import itertools

import faulthandler

import pygame
import OpenGL.GL as gl
import OpenGL.GLU as glu
import numpy as np


class SimCube(object):
    """ Simulate the tesseract using pygame. """

    def __init__(self):
        self._display_mode = (
            pygame.HWSURFACE |
            pygame.OPENGL |
            pygame.DOUBLEBUF |
            pygame.RESIZABLE
        )

    def setup(self, fps):
        faulthandler.enable()
        pygame.init()
        screen_size = (500, 500)

        gl_init(screen_size, self._display_mode)
        self._clock = pygame.time.Clock()
        self._tesseract = Tesseract(300)
        self._fps = fps

    def teardown(self):
        pygame.quit()

    def render(self, frame):
        pass

    def tick(self):
        cube = self._tesseract
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (
                    event.type == pygame.KEYDOWN
                    and event.key == pygame.K_ESCAPE):
                return
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    cube.rotate_x(15)
                elif event.key == pygame.K_w:
                    cube.rotate_x(-15)
                elif event.key == pygame.K_a:
                    cube.rotate_y(15)
                elif event.key == pygame.K_s:
                    cube.rotate_y(-15)
                elif event.key == pygame.K_z:
                    cube.rotate_z(15)
                elif event.key == pygame.K_x:
                    cube.rotate_z(-15)
            elif event.type == pygame.VIDEORESIZE:
                screen_size = event.size
                gl_init(screen_size, self._display_mode)
        self._tesseract.display()
        pygame.display.flip()
        self._clock.tick(self._fps)


class Tesseract(object):
    """ Render the tesseract using OpenGL. """

    BACKGROUND = [0.5, 0.5, 0.5, 1.0]
    VOXEL_OFF = [0.9, 0.9, 0.9, 0.5]
    VOXEL_ON = [0, 0, 1.0, 0.5]

    VOXEL_SHAPE = np.array([8, 8, 8])
    VOXEL_WIDTHS = 0.3 / VOXEL_SHAPE

    TOP_FACE = np.array([
        [0, 0, 0],
        [0, 0, 1],
        [0, 1, 1],
        [0, 1, 0],
    ]) * VOXEL_WIDTHS

    BOTTOM_FACE = np.array([
        [1, 0, 0],
        [1, 0, 1],
        [1, 1, 1],
        [1, 1, 0],
    ]) * VOXEL_WIDTHS

    def __init__(self, size):
        self.size = size
        self.rx = self.ry = self.rz = 0

        self.verts = []
        self.colours = []

        for pos in itertools.product(
            *(np.linspace(0., 1., num=v, endpoint=False)
              for v in self.VOXEL_SHAPE)):
            self.add_voxel(np.array(pos), 1.0)

        self.verts = np.array(self.verts)
        self.colours = np.array(self.colours)

    def _do_rotate(self, cur, delta):
        cur += delta
        cur %= 360
        if cur < 0:
            cur += 360
        return cur

    def rotate_x(self, delta):
        self.rx = self._do_rotate(self.rx, delta)

    def rotate_y(self, delta):
        self.ry = self._do_rotate(self.ry, delta)

    def rotate_z(self, delta):
        self.rz = self._do_rotate(self.rz, delta)

    def add_voxel(self, pos, intensity, colour=VOXEL_OFF):
        """ Add a single voxel. """
        top_face = pos + self.TOP_FACE
        bottom_face = pos + self.BOTTOM_FACE

        tf = [[i * self.size for i in v] for v in top_face]
        bf = [[i * self.size for i in v] for v in bottom_face]

        self.add_face([tf[2], tf[1], bf[1], bf[2]], colour)
        self.add_face([tf[3], tf[2], bf[2], bf[3]], colour)

        self.add_face(tf, colour)
        self.add_face(list(reversed(bf)), colour)

        self.add_face([tf[1], tf[0], bf[0], bf[1]], colour)
        self.add_face([tf[0], tf[3], bf[3], bf[0]], colour)

    def add_face(self, corners, colour):
        """ Add a square face. """
        tl, tr, br, bl = corners

        self.verts.extend([tl, tr, br])
        self.colours.extend([colour] * 3)

        self.verts.extend([br, bl, tl])
        self.colours.extend([colour] * 3)

    def display(self):
        gl.glEnable(gl.GL_CULL_FACE)
        gl.glClearColor(*self.BACKGROUND)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        gl.glLoadIdentity()

        glu.gluLookAt(-self.size, -self.size, -self.size, 0, 0, 0, 0, 0, 1)

        # We want to rotate about the centre of the cube, so
        # shift, rotate, shift back
        gl.glTranslate(self.size / 2.0, self.size / 2.0, self.size / 2.0)
        gl.glRotatef(self.rx, 1, 0, 0)
        gl.glRotatef(self.ry, 0, 1, 0)
        gl.glRotatef(self.rz, 0, 0, 1)
        gl.glTranslate(-self.size / 2.0, -self.size / 2.0, -self.size / 2.0)

        gl.glEnableClientState(gl.GL_VERTEX_ARRAY)
        gl.glEnableClientState(gl.GL_COLOR_ARRAY)

        gl.glVertexPointerf(self.verts)
        gl.glColorPointerf(self.colours)

        gl.glDrawArrays(gl.GL_TRIANGLES, 0, len(self.verts))

        gl.glDisableClientState(gl.GL_COLOR_ARRAY)
        gl.glDisableClientState(gl.GL_VERTEX_ARRAY)


def gl_init(screen_size, display_mode):
    """ Initialize display for OpenGL. """
    pygame.display.set_mode(screen_size, display_mode)

    gl.glEnable(gl.GL_DEPTH_TEST)

    gl.glViewport(0, 0, *screen_size)
    viewport = gl.glGetIntegerv(gl.GL_VIEWPORT)

    gl.glMatrixMode(gl.GL_PROJECTION)
    gl.glLoadIdentity()

    glu.gluPerspective(60.0, float(viewport[2]) / float(viewport[3]),
                       0.1, 2000.0)

    gl.glMatrixMode(gl.GL_MODELVIEW)
    gl.glLoadIdentity()
