#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

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
