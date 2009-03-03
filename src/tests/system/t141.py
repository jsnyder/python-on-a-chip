#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

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
r = map(chr, range(start, start+35))
t = map(type, r)
print "r = ", r
print "t = ", t
print "Heap =", sys.heap()

start = ord('A')
r = map(chr, range(start, start+35))
print "r = ", r
print "Heap =", sys.heap()

print "Done."
