#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2010 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 370
#


import string

# Create a string longer than 256 bytes to expose a too-small datatype in
# src/lib/string.py's find()
s = "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "0123456789012345678901234567890123456789" \
    "A"

loc_A = string.find(s, "A")
assert loc_A  == len(s) - 1
