#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 136
# Create module interface for compound datatypes
#

import dict, list


# Tests for list
if 1:
    foo = [0]
    list.append(foo, 1)
    print foo

    list.extend(foo, [2, 2])
    print foo


    print list.count(foo, 1)
    print list.count(foo, 2)
    print list.count(foo, 42)

    print list.index(foo, 0)

    list.append(foo, "bob")
    print list.index(foo, "bob")
    #print list.index(foo, "z") # expects to raise a ValueError

    list.insert(foo, 0, "zero")
    list.insert(foo, -1, "penultimate")
    print foo

    print list.pop(foo)
    print list.pop(foo, 2)
    print foo

    list.remove(foo, 2)
    list.remove(foo, "zero")
    print foo


# Tests for dict
if 1:
    d = {}
    d[0] = "zero"
    d["one"] = 1
    print d
    print dict.keys(d)
    print dict.values(d)

    dict.clear(d)
    print d
    d['new'] = "more"
    print d

    print "d has key 'new' = ", dict.has_key(d, 'new')
    print "d has key 'old' = ", dict.has_key(d, 'old')
