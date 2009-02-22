# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2009 Dean Hall
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
