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
# System Test 162
# Implement builtin function dir()
#


# Check dir on globals
print "dir() = ",dir()
assert dir() == ["__bi"]


# Check dir on a function
def foo():
    pass
d = dir()
assert "__bi" in d and "foo" in d
assert dir(foo) == []

foo.bar = "bar"
assert dir(foo) == ["bar"]


# Check dir on a module
import sys
d = dir()
assert "sys" in d
d = dir(sys)
print "dir(sys) = ",d
assert "heap" in d
