#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 080
# Regression test for issue #80: Fix bytecode DUP_TOPX.
#

d = {}
d[0] = 42
d[0] += 99
assert d[0] == 141

r = range(3)
r[1] += 99
assert r[1] == 100
