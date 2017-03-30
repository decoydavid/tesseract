""" Helper utilities for the simulated cube.

    These are in a separate module in order to avoid importing
    pygame and OpenGL when using other cube controllers.
"""

import faulthandler

import pygame
import OpenGL.GL as gl
import OpenGL.GLU as glu


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

    WHITE = [1.0, 1.0, 1.0, 1.0]
    GREY = [0.8, 0.8, 0.8, 1.0]
    BLUE = [0, 0, 1.0, 1.0]

    def __init__(self, size):
        self.size = size
        self.rx = self.ry = self.rz = 0

        self.verts = []
        self.colours = []
        self.add_voxel(0, 0, 0, 1.0)

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

    def add_voxel(self, x, y, z, intensity):
        """ Add a single voxel. """
        top_face = [
            [0, 0, 0],
            [0, 0, 1],
            [0, 1, 1],
            [0, 1, 0],
        ]
        bottom_face = [
            [1, 0, 0],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 0],
        ]
        tf = [[i * self.size for i in v] for v in top_face]
        bf = [[i * self.size for i in v] for v in bottom_face]

        self.add_face([tf[2], tf[1], bf[1], bf[2]], self.BLUE)
        self.add_face([tf[3], tf[2], bf[2], bf[3]], self.BLUE)

        self.add_face(tf, self.BLUE)
        self.add_face(list(reversed(bf)), self.BLUE)

        self.add_face([tf[1], tf[0], bf[0], bf[1]], self.BLUE)
        self.add_face([tf[0], tf[3], bf[3], bf[0]], self.BLUE)

    def add_face(self, corners, colour):
        """ Add a square face. """
        tl, tr, br, bl = corners

        self.verts.extend([tl, tr, br])
        self.colours.extend([colour] * 3)

        self.verts.extend([br, bl, tl])
        self.colours.extend([colour] * 3)

    def display(self):
        gl.glEnable(gl.GL_CULL_FACE)
        gl.glClearColor(0.5, 0.5, 0.5, 1)
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