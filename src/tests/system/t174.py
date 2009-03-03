#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 174
# Add support for keyword lambda
#

dx = 42
f1 = lambda x: x - dx
print map(f1, range(5))
assert f1(0) == -42

f2 = lambda x: x + dx
print map(f2, range(5))
assert f2(0) == 42
