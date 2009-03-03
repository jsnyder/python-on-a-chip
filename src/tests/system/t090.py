#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Test for Issue #90: Create new lib function to return system time
# Ensure that time passes
#

import sys

t0 = sys.time()

print "t0 = ", t0

print "killing time..."
i=0
while i < 10000:
    j=0
    while j < 100:
        j += 1
    if i%100 == 0:
        print i / 100, " ",
    i += 1
print

t1 = sys.time()

if t1 <= t0:
    print "killing more time..."
    i=0
    while i < 10000:
        j=0
        while j < 1000:
            j += 1
        if i%100 == 0:
            print i / 100, " ",
        i += 1
    print

t1 = sys.time()
print "t1 = ", t1

assert t1 > t0
