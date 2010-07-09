# This file is Copyright 2003, 2006, 2007, 2009, 2010 Dean Hall.
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
# System Test 289
# Create bytearray datatype
#

b0 = bytearray("test")
b1 = bytearray(4)
b2 = bytearray([2,5,6,2])
b3 = bytearray((1,2,8,1))
b4 = bytearray(b0)
b5 = bytearray(['2',5,'6',2])
b6 = bytearray(('1','2',8,1))

# Test that the bytearrays all have the proper length
assert 4 == len(b0)
assert 4 == len(b1)
assert 4 == len(b2)
assert 4 == len(b3)
assert 4 == len(b4)
assert 4 == len(b5)
assert 4 == len(b6)

# Test that indexing into each bytearray returns an Integer
assert type(0) == type(b0[0])
assert type(0) == type(b1[0])
assert type(0) == type(b2[0])
assert type(0) == type(b3[0])
assert type(0) == type(b4[0])
assert type(0) == type(b5[0])
assert type(0) == type(b6[0])

# Test that the contents of each bytearray are proper
assert b0[0] == ord('t')
assert b0[1] == ord('e')
assert b0[2] == ord('s')
assert b0[3] == ord('t')

assert b1[0] == 0
assert b1[1] == 0
assert b1[2] == 0
assert b1[3] == 0

assert b2[0] == 2
assert b2[1] == 5
assert b2[2] == 6
assert b2[3] == 2

assert b3[0] == 1
assert b3[1] == 2
assert b3[2] == 8
assert b3[3] == 1

assert b4[0] == ord('t')
assert b4[1] == ord('e')
assert b4[2] == ord('s')
assert b4[3] == ord('t')

assert b5[0] == ord('2')
assert b5[1] == 5
assert b5[2] == ord('6')
assert b5[3] == 2

assert b6[0] == ord('1')
assert b6[1] == ord('2')
assert b6[2] == 8
assert b6[3] == 1

# Test setting contents (STORE_SUBSCR)
b1[0] = 't'
b1[1] = 'e'
b1[2] = 's'
b1[3] = 't'

# Test comparing contents
assert b1 == b0

# Test setting contents (STORE_SUBSCR)
b0[False] = 0x34
b0[True] = 0x32
assert b0[0] == ord('4')
assert b0[1] == ord('2')

print b0
