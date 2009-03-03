#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 017
# Tests implementation of seq_compare()
#


l1 = [2,5,6]
l2 = [2,5,6]
assert l1 == l2

l3 = [2,5,5]
assert l2 != l3

t1 = (2,5,6)
t2 = (2,5,6)
assert t1 == t2

t3 = (2,5,5)
assert t2 != t3
