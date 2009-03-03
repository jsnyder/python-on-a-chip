#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 147
# Support Boolean type and True/False constants
#

print "True == ", True
print "False == ", False
print "not True == ", not True
print "not False == ", not False

assert True
assert not False

assert not True == False
assert not False == True

assert True == (0 == 0)
assert False == (0 == 1)

assert True == 1
assert 1 == True
assert False == 0
assert 0 == False

assert ('f','t','z')[False] == 'f'
assert ('f','t','z')[True] == 't'

assert range(3)[True] == 1
assert range(3)[False] == 0

d = {}
d[True] = "t"
d[False] = "f"

assert d[0] == "f"
assert d[1] == "t"

d = {}
d[0] = "f"
d[1] = "t"

assert d[False] == "f"
assert d[True] == "t"
