#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
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
