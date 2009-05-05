#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 233
#
# Replication was introduced in issue #160 (original trac).
# The system test t160 does not exercise the BINARY_MULTIPLY bytecode!
# It turns out the Python compiler will automatically expand sequence*integerconstant
# When integerconstant is <= 20.  So these tests use 30 so that BINARY_MULTIPLY
# is exercised and the replication functions are called.
#


# Test string replication
s = "farley" * 30
print s
assert s == "farleyfarleyfarley" * 10
assert len(s) == 6*30

mul = 0
assert "farley" * mul == ""
mul = -42
assert "farley" * mul == ""

# Test tuple replication
t = (2,5,6) * 30
print t
assert t == (2,5,6, 2,5,6, 2,5,6) * 10
assert len(t) == 3*30

mul = 0
assert (2,5,6) * mul == ()
mul = -42
assert (2,5,6) * mul == ()

# Also ensure list replication works
r = range(3) * 30
assert r == [0,1,2,0,1,2,0,1,2] * 10
assert len(r) == 3*30

mul = 0
assert [0,1,2] * mul == []
mul = -42
assert [0,1,2] * mul == []

# Just for fun
print [[3,]*30, "three"*30, ('e',)*30]*30
