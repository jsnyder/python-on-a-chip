# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

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
