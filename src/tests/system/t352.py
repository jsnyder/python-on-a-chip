#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2010 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 352
# Fix modulus with negative integers
#

a = 2
n = 3

print "      2 % 3 in pymite:", (a % n), " and in cpython:", 2
print "   (-2) % 3 in pymite:", ((-a) % n), " and in cpython:", 1
print "   2 % (-3) in pymite:", (a % (-n)), " and in cpython:", -1
print "(-2) % (-3) in pymite:", ((-a) % (-n)), " and in cpython:", -2

assert (a % n) == 2
assert ((-a) % n) == 1
assert (a % (-n)) == -1
assert ((-a) % (-n)) == -2

assert 12 % 1 == 0
assert 12 % -1 == 0

# Division

assert -3 / 4 == -1
assert -4 / 3 == -2
assert 12 / 1 == 12
assert 12 / -1 == -12


import sys
assert (-sys.maxint-1) % -1 == 0

print "Expect OverflowError"
assert  (-sys.maxint-1) / -1