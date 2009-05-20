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
# System Test 141
# String cache not handled by GC
#
# Creates a bunch of strings, removes references to them,
# creates another bunch of strings causing a GC.
# Expect enough space for the second bunch of strings.
# This test is tuned for an 8 KB heap.
#

import sys

print "Heap =", sys.heap()

start = ord('a')
r = map(chr, range(start, start+36))
t = map(type, r)
print "r = ", r
print "t = ", t
print "Heap =", sys.heap()

start = ord('A')
r = map(chr, range(start, start+36))
print "r = ", r
print "Heap =", sys.heap()

print "Done."
