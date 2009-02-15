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
# System Test 147
# Support Boolean type and True/False constants
#

print "True == ", True
print "False == ", False
print "not True == ", not True
print "not False == ", not False

assert True
assert not False

assert not True == False
assert not False == True

assert True == (0 == 0)
assert False == (0 == 1)

assert True == 1
assert 1 == True
assert False == 0
assert 0 == False

assert ('f','t','z')[False] == 'f'
assert ('f','t','z')[True] == 't'

assert range(3)[True] == 1
assert range(3)[False] == 0

d = {}
d[True] = "t"
d[False] = "f"

assert d[0] == "f"
assert d[1] == "t"

d = {}
d[0] = "f"
d[1] = "t"

assert d[False] == "f"
assert d[True] == "t"
