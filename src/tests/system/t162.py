#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 162
# Implement builtin function dir()
#


# Check dir on globals
print "dir() = ",dir()
assert dir() == ["__bi"]


# Check dir on a function
def foo():
    pass
d = dir()
assert "__bi" in d and "foo" in d
assert dir(foo) == []

foo.bar = "bar"
assert dir(foo) == ["bar"]


# Check dir on a module
import sys
d = dir()
assert "sys" in d
d = dir(sys)
print "dir(sys) = ",d
assert "heap" in d
