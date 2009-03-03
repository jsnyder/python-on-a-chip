#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 061 part B
# Testing two threads starting at the same time, each calculating a number
# and printing it
#


print "Thread B"
a = 666
b = -2
for i in range(10):
    a += i
    b -= i
print a*b
