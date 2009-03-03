#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 076
# Tests if print operation properly outputs string along with a newline.
# Also tests proper escaping when outputting strings in dicts and lists.
# printing integers, dicts and lists.
#

a = "123\x08456"
b = 987
c = [a,b]
d = {a:b}
e = (c,d)
print a
print b
print c
print d
print e
