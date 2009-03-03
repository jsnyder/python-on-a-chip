#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
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
