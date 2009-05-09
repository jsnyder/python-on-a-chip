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
# System Test 147
# Support Boolean type and True/False constants
#

print "True == ", True
print "False == ", False
print "not True == ", not True
print "not False == ", not False

assert True
assert not False

assert not True == False
assert not False == True

assert True == (0 == 0)
assert False == (0 == 1)

assert True == 1
assert 1 == True
assert False == 0
assert 0 == False

assert ('f','t','z')[False] == 'f'
assert ('f','t','z')[True] == 't'

assert range(3)[True] == 1
assert range(3)[False] == 0

d = {}
d[True] = "t"
d[False] = "f"

assert d[0] == "f"
assert d[1] == "t"

d = {}
d[0] = "f"
d[1] = "t"

assert d[False] == "f"
assert d[True] == "t"
