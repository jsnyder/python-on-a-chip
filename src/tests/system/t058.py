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
# System Test 058
# Tests implementation of keyword "in" for Tuple, List and String
#


t = (2,5,6)
assert 2 in t
assert 5 in t
assert 6 in t
assert 8 not in t
assert "c" not in t

l = [2,5,6]
assert 2 in l
assert 5 in l
assert 6 in l
assert 8 not in l
assert "c" not in l

s = "256"
assert "2" in s
assert "5" in s
assert "6" in s
assert "8" not in s
assert "c" not in s

d = {2:2, 5:"5", 6:None}
assert 2 in d
assert 5 in d
assert 6 in d
assert 8 not in d
assert "5" not in d
assert "c" not in d
