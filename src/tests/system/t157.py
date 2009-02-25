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
# System Test 157
# Support default args
#

def foo1(a=42, b=6, c=7):
    return (a, b, c)

print "foo1()=", foo1()
assert foo1() == (42, 6, 7)
assert foo1("forty two") == ("forty two", 6, 7)
assert foo1("forty two", 9) == ("forty two", 9, 7)
assert foo1("forty two", 9, ("test",)) == ("forty two", 9, ("test",))
#assert foo1("forty two", 9, ("test",), "TypeError (0xED") == ("forty two", 9, ("test",))


def foo2(a, b=6, c=7):
    return (a, b, c)

print "foo2(42)=", foo2(42)
#assert foo2() == (42, 6, 7) # Expect TypeError (0xED) too few args
assert foo2("forty two") == ("forty two", 6, 7)
assert foo2("forty two", 9) == ("forty two", 9, 7)
assert foo2("forty two", 9, ("test",)) == ("forty two", 9, ("test",))
#assert foo2("forty two", 9, ("test",), "TypeError (0xED)") == ("forty two", 9, ("test",))


def foo3(a, b, c=7):
    return (a, b, c)

print "foo3(42, 6)=", foo2(42, 6)
#assert foo3() == (42, 6, 7) # Expect TypeError (0xED) too few args
assert foo3("forty two", 6) == ("forty two", 6, 7)
assert foo3("forty two", 6, 9) == ("forty two", 6, 9)
assert foo3("forty two", 6, ("test",)) == ("forty two", 6, ("test",))
#assert foo3("forty two", 9, ("test",), "TypeError (0xED)") == ("forty two", 9, ("test",))
