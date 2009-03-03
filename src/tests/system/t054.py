#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 054
# Tests lists and dicts with lengths > 8 to test underlying seglist.
#


l = range(9)
assert l[0] == 0
assert l[8] == 8
assert l[-1] == 8

assert len(l) == 9

# TODO Activate once a solution for #47 is found
#l.remove(0)
#assert not 0 in l
#assert 1 in l
#assert len(l) == 8


d = {}
i = 9
while i >= 0:
    d[i] = i
    i -= 1
assert d[0] == 0
assert d[9] == 9
