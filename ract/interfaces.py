""" Interface / base classes. """


class CubeController(object):
    """ A controller for displaying images on the tesseract.

        The rendering loop will look something like::

            cube.setup(fps=60)
            art.setup(fps=60)
            while True:
                frame = art.next_frame()
                cube.render(frame)
                cube.tick()
    """
    def setup(self, fps):
        """ Perform any setup needed.

            :param float fps:
                The frames per second that the artwork will be rendered at.
        """

    def render(self, frame):
        """ This method arranges for the frame to be clocked in.

            :param numpy.array frame:
                The frame to render. An 8 x 8 x 8 numpy array.
        """
        pass

    def tick(self):
        """ This method arranges for the GSCLK line to be toggled
            so that the frame continues to display.
        """
        pass


class ArtworkRenderer(object):
    """ Renders an artwork as a series of frames.
    """
    def setup(self, fps):
        """ Perform any setup needed.

            :param float fps:
                The frames per second that the artwork will be rendered at.
        """

    def next_frame(self):
        """ Return the next frame to be rendered.

            :return numpy.array:
                The frame to render. An 8 x 8 x 8 numpy array.
        """


def registry(cls):
    """ Return a dictionary mapping names of sub-classes of an interface
        class to the sub-classes.
    """
    return {
        subcls.__name__: subcls for subcls in cls.__subclasses__()
    }