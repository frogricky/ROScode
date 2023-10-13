# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 19:49:45 2023

@author: HungYing
"""

import time

try:
    while True:
        time.sleep(1)
        print("a")
except KeyboardInterrupt:
    print('interrupted!')