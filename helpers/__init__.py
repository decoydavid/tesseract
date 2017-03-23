""" Helpers for cffi_builders. """

import os


def get_lib_dir():
    """ Return the library path. """
    return ['/usr/lib']


def get_inc_dir():
    """ Return the include directories libraries. """
    return ['/usr/include']


def get_c_lib(name):
    """ Return the contents of a C library. """
    filename = os.path.join(
        os.path.dirname(__file__), '..', 'cffi_builders', 'lib', name)
    with open(filename) as lib:
        return lib.read()


__all__ = [get_inc_dir, get_lib_dir, get_c_lib]
