#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 051
# Tests implementation of FOR_ITER bytecode
#


s = (2,5,6)
n = 0
for i in s:
    assert s[n] == i
    n += 1


s = [2,5,6]
n = 0
for i in s:
    assert s[n] == i
    n += 1


s = "256"
n = 0
for i in s:
    assert s[n] == i
    n += 1
