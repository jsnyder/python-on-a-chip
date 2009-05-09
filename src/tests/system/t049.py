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
# System Test 049
# Tests implementation of obj_isFalse() for Tuple, List and Dict.
#


t1 = ()
if t1:
    assert 0

t2 = (2,)
if not t2:
    assert 0

l1 = []
if l1:
    assert 0

l2 = [2,]
if not l2:
    assert 0

d1 = {}
if d1:
    assert 0
    
d2 = {2:2}
if not d2:
    assert 0
