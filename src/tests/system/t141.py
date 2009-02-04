# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2009 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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

r = map(chr, range(ord('a'), 135))
print "r = ", r

print "Heap =", sys.heap()

for i in range(len(r)):
    r[i] = chr(ord(r[i]) - 32)
print "r = ", r

print "Heap =", sys.heap()
print "Done."
