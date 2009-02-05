# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
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
