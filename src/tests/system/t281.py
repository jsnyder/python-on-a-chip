#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2010 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 281
# Fix float comparisons
#

a = 3.4e-15
b = 3.5e-15
print "a == b ?", a == b
assert not (a == b)
assert a != b
