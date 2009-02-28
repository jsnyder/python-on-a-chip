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
# System Test 164
# Add support for list comprehensions
#

l = [x for x in range(5)]
assert l == range(5)

l = [x*2 for x in range(5)]
print "[x*2 for x in range(5)] = ", l
assert l == range(0,10,2)

assert [ord(c) for c in "0123"] == [0x30, 0x31, 0x32, 0x33]

assert [x for x in ('a', 'b', 'c')] == ['a', 'b', 'c']


# Check 'if' after for comprehension
assert [x for x in range(10) if x%3 != 0] == [1,2, 4,5, 7,8 ]


# Check nested comprehensions
mat = [ [1, 2, 3], [4, 5, 6], [7, 8, 9], ]
assert [[row[i] for row in mat] for i in [0, 1, 2]] == [[1,4,7],[2,5,8],[3,6,9]]