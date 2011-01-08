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
# System Test 376
# Regression will show "TypeError detected by seq.c:254"
# because it's trying to iterate over a dict.
#


d = {0:None, 1:"one", 2:"two"}

for i in d:
    assert i in d

k1,k2,k3 = d
assert k1 in d and k2 in d and k3 in d

s = sum(d)
assert s == 3

# Requires HAVE_BYTEARRAY
#b = bytearray(range(10))
#assert sum(b) == 45
