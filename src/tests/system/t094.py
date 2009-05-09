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
# System Test 094
# Fix image integer loading so it re-uses static ints (-1,0,1).
#

kn1 = 1 - 2
k0 = kn1 + 1
k1 = k0 + 1

id1 = id(-1)
id2 = id(kn1)
assert id1 == id2

id1 = id(0)
id2 = id(k0)
assert id1 == id2

id1 = id(1)
id2 = id(k1)
assert id1 == id2
