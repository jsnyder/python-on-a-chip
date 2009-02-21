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
# Test for Issue #90: Create new lib function to return system time
#
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
