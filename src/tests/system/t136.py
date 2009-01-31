# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

#
# System Test 136
# Create module interface for compound datatypes
#

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
