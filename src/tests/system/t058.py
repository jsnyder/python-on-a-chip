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
