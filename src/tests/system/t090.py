# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

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
