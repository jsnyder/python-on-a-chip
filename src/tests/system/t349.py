#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2010 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 349
#

d1 = {}
d1[1] = "one"

d2 = {}
d2[2] = "two"


import dict
rv = dict.update(d1, d2)

assert rv == None
assert d1 == {1:"one", 2:"two"}
assert d2 == {2:"two"}
