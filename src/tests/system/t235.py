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
# System Test 235
#

import list


l = []
for i in xrange(3):
    print i
    list.append(l, i)

assert l == range(3)

# Results in an AssertionError because the generator's StopIteration is
# not caught; there is no SETUP_LOOP bytecode for this code
# [x/2. for x in xrange(10) if x%2 == 0]
