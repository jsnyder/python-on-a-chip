#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 095
# Fix sys.heap() so it doesn't overwrite the static const 0 integer obj
#

import sys

h = sys.heap()

assert h[0] != (1-1)
