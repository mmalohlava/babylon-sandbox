#!/usr/local/bin/python
import random

rand = random.SystemRandom(42)
NROWS=20000

DISTRIB = [0.83345, 0.02382, 0.02626, 0.02871, 0.01875, 0.013345, 0.00997, 0.00804, 0.005965, 0.004805, 0.026885]
CUM_DISTRIB = [ sum(DISTRIB[:i+1]) for i in xrange(len(DISTRIB)) ] 

print "x,y,color"
for i in range(0, NROWS):
    x = rand.random()
    y = rand.random()
    ci = rand.random()
    p = 0
    while (ci > CUM_DISTRIB[p]): p = p + 1
    print "{},{},C{}".format(x,y,p)
