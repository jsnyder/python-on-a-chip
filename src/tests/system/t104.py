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
