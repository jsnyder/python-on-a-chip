#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Test for Issue #149: Support the keyword del
#

import dict


#
# Tests for DELETE_SUBSCR bytecode
#
l = range(5)
print "del l[3]"
del l[3]
print l
assert l[3] == 4


d = {}
for n in range(5):
    d[n] = n
print "del d[3]"
del d[3]
assert 3 not in dict.keys(d)
print "d=", d


#
# Test for DELETE_NAME bytecode
#
del d
assert "d" not in dict.keys(locals())
print "keys(locals)=", dict.keys(locals())


#
# Test the DELETE_GLOBAL bytecode
#
def delglob():
    global l
    print "delglob's l=",l
    del l

delglob()
assert "l" not in dict.keys(globals())
print "globals=", dict.keys(globals())


#
# Test the DELETE_ATTR bytecode
#
delglob.foo = "foo"
print delglob.foo
del delglob.foo
#print delglob.foo # Expect AttributeError (0xE5)


#
# Test the DELETE_FAST bytecode
#
def delfast():
    i = 42
    del i
    assert i == None

delfast()
