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
# System Test 162
# Implement builtin function dir()
#


# Check dir on globals
print "dir() = ",dir()
assert dir() == ["__bi"]


# Check dir on a function
def foo():
    pass
d = dir()
assert "__bi" in d and "foo" in d
assert dir(foo) == []

foo.bar = "bar"
assert dir(foo) == ["bar"]


# Check dir on a module
import sys
d = dir()
assert "sys" in d
d = dir(sys)
print "dir(sys) = ",d
assert "heap" in d
