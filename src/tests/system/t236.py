# This file is Copyright 2009 Dean Hall.
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
# System Test 236
# Fix SLICE_0
#

s1 = "test"
s2 = s1[:]
assert s1 == s2
assert id(s1) == id(s2)

t1 = (1,2,3)
t2 = t1[:]
assert t1 == t2
assert id(t1) == id(t2)

l1 = [1,2,3]
l2 = l1[:]
assert l1 == l2
assert id(l1) != id(l2)
