#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Regression Test for Issue #9
# Fix BINARY_SUBSCR for case stringobj[intobj]
#

import sys

s = "test"
if s[0] != 't':
    sys.exit(1)
