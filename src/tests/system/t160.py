#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 160
# Add support for string and tuple replication
#

# Test string replication
s = "farley" * 3
print s
assert s == "farleyfarleyfarley"
assert len(s) == 6*3
assert s*0 == ""
assert s*-42 == ""

# Test tuple replication
t = (2,5,6) * 3
print t
assert t == (2,5,6, 2,5,6, 2,5,6)
assert len(t) == 3*3
assert t*0 == ()
assert t*-42 == ()

# Also ensure list replication works
r = range(3) * 3
assert r == [0,1,2,0,1,2,0,1,2]
assert len(r) == 3*3
assert r*0 == []
assert r*-42 == []

# Just for fun
print [[3,]*3, "three"*3, ('e',)*3]*3
