#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 164
# Add support for list comprehensions
#

l = [x for x in range(5)]
assert l == range(5)

l = [x*2 for x in range(5)]
print "[x*2 for x in range(5)] = ", l
assert l == range(0,10,2)

assert [ord(c) for c in "0123"] == [0x30, 0x31, 0x32, 0x33]

assert [x for x in ('a', 'b', 'c')] == ['a', 'b', 'c']


# Check 'if' after for comprehension
assert [x for x in range(10) if x%3 != 0] == [1,2, 4,5, 7,8 ]


# Check nested comprehensions
mat = [ [1, 2, 3], [4, 5, 6], [7, 8, 9], ]
assert [[row[i] for row in mat] for i in [0, 1, 2]] == [[1,4,7],[2,5,8],[3,6,9]]