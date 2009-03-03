#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 102
# Implement the remaining IMPORT_ bytecodes
#

# Test IMPORT_FROM
from sys import maxint
assert maxint == 0x7fffffff

# Test IMPORT_STAR
from sys import *
assert type(heap) == 0x08
assert type(exit) == 0x08
