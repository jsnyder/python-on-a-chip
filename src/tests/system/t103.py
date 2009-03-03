#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 103
# Implement obj_print() for other object types
#

import sys

def f(a,b):
    return a+b
    
#
# If the following throws an exception, it's a regression
#
print f, sys
