#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 026
# Tests new builtin functions
#

#
# Test len()
#
assert len("") == 0
assert len("\x00") == 1
assert len("\x00\x00\x00\x00") == 4

#
# Test ord()
#
c = ord("t")
assert c == 116

c = ord("\xff")
assert c == 0xff

c = ord("\x00")
assert c == 0


#
# Test chr()
#
n = chr(0)
assert n == "\x00"

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
