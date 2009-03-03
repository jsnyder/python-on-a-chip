#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 049
# Tests implementation of obj_isFalse() for Tuple, List and Dict.
#


t1 = ()
if t1:
    assert 0

t2 = (2,)
if not t2:
    assert 0

l1 = []
if l1:
    assert 0

l2 = [2,]
if not l2:
    assert 0

d1 = {}
if d1:
    assert 0
    
d2 = {2:2}
if not d2:
    assert 0
