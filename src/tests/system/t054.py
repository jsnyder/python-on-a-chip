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
# System Test 054
# Tests lists and dicts with lengths > 8 to test underlying seglist.
#


l = range(9)
assert l[0] == 0
assert l[8] == 8
assert l[-1] == 8

assert len(l) == 9

# TODO Activate once a solution for #47 is found
#l.remove(0)
#assert not 0 in l
#assert 1 in l
#assert len(l) == 8


d = {}
i = 9
while i >= 0:
    d[i] = i
    i -= 1
assert d[0] == 0
assert d[9] == 9
