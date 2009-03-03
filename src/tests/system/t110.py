#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 110
# Prevent IMPORT_NAME from reloading existing module
#
# This test shows that the list module is not reloaded.
# A regression of this test will result in a KeyError (zero not in list's attrs)
#

import list
list.zero = 0

import list
assert list.zero == 0
