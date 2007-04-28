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
# System Test 113
#
# Regression test for issue #113:
# Fix the implementation of builtin map()
#

# Test setting each value to None
def noneify(a):
    return None
    
r = map(noneify, "test")

assert r == [None, None, None, None]


# Test adding a tuple pair
def addPair(a):
    return a[0] + a[1]
    
r = map(addPair, ((3,4),(5,6),(7,8)))

assert r == [7, 11, 15]
