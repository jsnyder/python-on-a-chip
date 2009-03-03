#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 056
# Tests implementation of *_POWER bytecodes
#


x = 2 ** 8
assert x == 256

x = 4
x = x ** x
assert x == 256
