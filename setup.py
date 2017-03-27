import sys

from setuptools import setup


cffi_modules = [
    'cffi_builders/ract_dma_c_build.py:ffi',
]


setup(
    name="ract",
    version="0.0.1",
    url='http://github.com/decoydavid/tesseract',
    license='GPL-3+',
    description="A python controller for the tesseract.",
    long_description=open('README.rst', 'r').read(),
    packages=['ract'],
    include_package_data=True,
    scripts=[
    ],
    setup_requires=[
        'cffi>=1.3.0',
    ],
    cffi_modules=cffi_modules,
    install_requires=[
        'cffi>=1.3.0',
    ],
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',
        'Operating System :: POSIX',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.7',
        'Topic :: Software Development :: Libraries :: Python Modules',
    ],
)
