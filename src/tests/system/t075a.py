#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 061 part A
# Testing two threads starting at the same time, each calculating a number
# and printing it
#


print "Thread A"
x = -42
y = 12
for i in range(10):
    x += i
    y -= i
print x*y
