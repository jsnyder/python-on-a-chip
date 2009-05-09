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
# System Test 113
#
# Regression test for issue #113:
# Fix the implementation of builtin map()
#

# Test setting each value to None
def noneify(a):
    return None
    
r = map(noneify, "test")

assert r == [None, None, None, None]


# Test adding a tuple pair
def addPair(a):
    return a[0] + a[1]
    
r = map(addPair, ((3,4),(5,6),(7,8)))

assert r == [7, 11, 15]
