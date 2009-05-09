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
