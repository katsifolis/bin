#!/usr/bin/env python3

"""

Trees out the contents of the directory given

"""

import os, sys

def warn(s):
    print(s)
    sys.exit(1)

def treepy():
    if len(sys.argv) < 2:
        warn('no input given')


    
