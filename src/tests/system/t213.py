# This file is Copyright 2009 Dean Hall.
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
# System Test 213
# Add support for Python 2.6 bytecodes
#

# None of tests below are able to create the bytecodes new to Python 2.6.
# So the tests are commented out.

# Test the *_TRUE_DIVIDE bytecodes
#n = 4
#d = 5
#z = 0

#assert n/d == 0.8
#assert n//d == 0

# The following should result in a ZeroDivisionError
#r = n/z

# Test the STORE_MAP bytecode
#d = {}
#d[0] = 0
#d = {0: 0}
