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
# System Test 026
# Tests new builtin functions
#

#
# Test ord()
#
c = ord("t")
assert c == 116

c = ord("\xff")
assert c == 0xff

c = ord("\0")
assert c == 0


#
# Test chr()
#
n = chr(0)
assert n == "\0"

n = chr(255)
assert n == "\xff"

n = chr(116)
assert n == "t"

i = 32
while i >= 0:
    assert ord(chr(i)) == i
    i -= 1

#
# Test abs()
#
n = 255
m = abs(n)
assert m == n
assert m is n

n = -42
m = abs(n)
assert m is not n
assert m == -n


#
# Test sum()
#
s = [2, 5, 6]
assert sum(s) == 13

s = (2, 5, 6)
assert sum(s) == 13
