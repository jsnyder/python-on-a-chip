#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Test for Issue #132: VM doesn't throw TypeError 
# when function has wrong number of arguments
#
# Run code that should cause a TypeError.
# See that it doesn't.  Fix the defect, and see that a TypeError occurs.
#
# Then REMOVE this test from the suite since it expects an error.
#

def foo(n):
    return n * 1
    
# Expect TypeError
foo(1, 2)
