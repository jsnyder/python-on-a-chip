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
# System Test 160
# Add support for string and tuple replication
#

# Test string replication
s = "farley" * 3
print s
assert s == "farleyfarleyfarley"
assert len(s) == 6*3
assert s*0 == ""
assert s*-42 == ""

# Test tuple replication
t = (2,5,6) * 3
print t
assert t == (2,5,6, 2,5,6, 2,5,6)
assert len(t) == 3*3
assert t*0 == ()
assert t*-42 == ()

# Also ensure list replication works
r = range(3) * 3
assert r == [0,1,2,0,1,2,0,1,2]
assert len(r) == 3*3
assert r*0 == []
assert r*-42 == []

# Just for fun
print [[3,]*3, "three"*3, ('e',)*3]*3
