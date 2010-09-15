# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

#
# System Test 136
# Create module interface for compound datatypes
#

import dict, list


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

    list.insert(foo, 0, "zero")
    list.insert(foo, -1, "penultimate")
    print foo

    print list.pop(foo)
    print list.pop(foo, 2)
    print foo

    list.remove(foo, 2)
    list.remove(foo, "zero")
    print foo

    list.append(foo, "bob")
    print list.index(foo, "bob")
    print list.index(foo, "z") # expects a ValueError

