#!/usr/local/bin/python

import random

N = 30
N = 300

NCHARS = ord('z') - ord('a') + 1

def sgen(n):
    d = n / NCHARS
    r = n % NCHARS
    s = 'z'*d + chr(ord('a')+r)
    return s

for x in range(0, N):
    for y in range(0, N):
        color = (x+y) % 2
        print "{},{},{}".format(sgen(x),sgen(y),color)
