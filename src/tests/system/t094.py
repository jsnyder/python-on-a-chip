#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 094
# Fix image integer loading so it re-uses static ints (-1,0,1).
#

kn1 = 1 - 2
k0 = kn1 + 1
k1 = k0 + 1

id1 = id(-1)
id2 = id(kn1)
assert id1 == id2

id1 = id(0)
id2 = id(k0)
assert id1 == id2

id1 = id(1)
id2 = id(k1)
assert id1 == id2
