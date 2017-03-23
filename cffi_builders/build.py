#!/usr/bin/env python
import os
import subprocess
import sys


def main():
    directory = os.path.dirname(__file__)
    for builder in os.listdir(directory):
        if not builder.endswith('_build.py'):
            continue
        fn = os.path.join(directory, builder)
        subprocess.check_call((sys.executable, fn))


if __name__ == '__main__':
    main()
