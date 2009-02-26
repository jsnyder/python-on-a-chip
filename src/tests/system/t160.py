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
# System Test 160
# Add support for string and tuple replication
#

# Test string replication
s = "farley" * 3
print s
assert s == "farleyfarleyfarley"
assert len(s) == 6*3
assert s*0 == ""
assert s*-42 == ""

# Test tuple replication
t = (2,5,6) * 3
print t
assert t == (2,5,6, 2,5,6, 2,5,6)
assert len(t) == 3*3
assert t*0 == ()
assert t*-42 == ()

# Also ensure list replication works
r = range(3) * 3
assert r == [0,1,2,0,1,2,0,1,2]
assert len(r) == 3*3
assert r*0 == []
assert r*-42 == []

# Just for fun
print [[3,]*3, "three"*3, ('e',)*3]*3
