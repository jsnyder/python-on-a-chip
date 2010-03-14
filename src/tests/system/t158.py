#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 158
# Fix builtin sum() to support float
#


l1 = [1, 2, 3]
assert sum(l1) == 6
print l1

l2 = [1, 2, 3, 4.0]
assert sum(l2) == 10.0
print l2

l3 = [1.0, 2.0, 3.0]
assert sum(l3) == 6.0                  
print l3

# PyMite VM uses float type, not double; so this test passes here,
# but would fail if run on the CPython VM.
l4 = [1.1, 2.2, 3.3]
assert sum(l4) != 6.6   # Rounding issue causes not-equal
print l4

l5 = [1.1, 2.2, 3.3, 4.4]
assert sum(l5) == 11.0
print l5
