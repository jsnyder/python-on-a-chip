# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

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
