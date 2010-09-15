# This file is Copyright 2010 Dean Hall.
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
# System Test 334
#

print "hex(42) == %x" % 42

a = 42
s = "%x" % a
print s
assert s == "2a"

S = "%X" % a
print S
assert S == "2A"

# For now, expect TypeError, in future, convert float to int and expect it to work
print "Expect TypeError"
b = 3.14
p = "%x" % b
assert p == "3"