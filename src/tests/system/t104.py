#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Test for Issue #104: Design and implement garbage collection
#
# Run code that will cause a GC and then run more code to see that things
# still work.
#

import sys

print "Heap =", sys.heap()

i = 170
r = range(i)
print "r = range(", i, ")"

print "Heap =", sys.heap()

while i > 0:
    i -= 1
    r[i] += 10
print "r[i] += 10; for all i"
print "Heap =", sys.heap()
print "Done."
