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
# Regression Test for Issue #47
# Design and implement method for basic types
# to access their respective class methods
#

import string, sys

assert len(string.digits) == 10

assert string.atoi("42") == 42
assert string.atoi("0") == 0
assert string.atoi("-42") == -42
assert string.atoi("8675309") == 8675309
assert string.atoi("2147483647") == sys.maxint

assert string.atoi("42", 0) == 42
assert string.atoi("0", 0) == 0
assert string.atoi("-42", 0) == -42
assert string.atoi("8675309", 0) == 8675309
assert string.atoi("2147483647", 0) == sys.maxint

assert string.atoi("42", 16) == 66
assert string.atoi("0", 16) == 0
assert string.atoi("-42", 16) == -66
assert string.atoi("0x8675309", 16) == 140989193
assert string.atoi("0x7fffffff", 16) == sys.maxint

#string.atoi() # Expect TypeError (0xED)
#string.atoi(42) # Expect TypeError (0xED)
#string.atoi("42","10") # Expect TypeError (0xED)
#string.atoi("42", 10, 0) # Expect TypeError (0xED)
#string.atoi('c') # Expect ValueError (0xEE)
#string.atoi("10", 1) # Expect ValueError (0xEE)
#string.atoi("10", -1) # Expect ValueError (0xEE)
#string.atoi("10", 99) # Expect ValueError (0xEE)

assert string.count("timmy", "t") == 1
assert string.count("timmy", "m") == 2
assert string.count("timmy", "y") == 1
assert string.count("timmy", "z") == 0

assert string.count("cccccancun","c") == 6
assert string.count("cccccancun","n") == 2
assert string.count("cccccancun","C") == 0
assert string.count("cccccancun","\0") == 0

assert string.count("","") == 1
assert string.count("","a") == 0
assert string.count("a","") == 2
assert string.count("","\0") == 0
assert string.count("\0","\0") == 1
assert string.count("\0","") == 2

#string.count("") # Expect TypeError (0xED)
#string.count("","","") # Expect TypeError (0xED)
#string.count("",2) # Expect TypeError (0xED)
#string.count([],"") # Expect TypeError (0xED)

assert string.find("timmy", "t") == 0
assert string.find("timmy", "m") == 2
assert string.find("timmy", "y") == 4
assert string.find("timmy", "z") == -1
assert string.find("timmy", "M") == -1

assert string.find("","") == 0
assert string.find("","a") == -1
assert string.find("a","") == 0
assert string.find("","\0") == -1
assert string.find("\0","\0") == 0
assert string.find("\0","") == 0
assert string.find(" \0","") == 0
assert string.find(" \0","\0") == 1

#string.find("") # Expect TypeError (0xED)
#string.find("","","") # Expect TypeError (0xED)
#string.find("",2) # Expect TypeError (0xED)
#string.find([],"") # Expect TypeError (0xED)

