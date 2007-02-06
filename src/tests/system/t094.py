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
# System Test 094
#
# Regression test for issue #94:
# Fix image integer loading so it re-uses static ints (-1,0,1).
#

kn1 = 1 - 2
k0 = kn1 + 1
k1 = k0 + 1

id1 = id(-1)
id2 = id(kn1)
assert id1 == id2

id1 = id(0)
id2 = id(k0)
assert id1 == id2

id1 = id(1)
id2 = id(k1)
assert id1 == id2
