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
# System Test 259
# Add filter() function to builtins
#

e = filter(lambda x: x%2 == 0, range(5))
assert e == [0, 2, 4]
print "filter() test 1 passes."


e = filter(lambda x: x%2 == 2, range(5))
assert e == []
print "filter() test 2 passes."


e = filter(lambda x: True, range(0))
assert e == []
print "filter() test 3 passes."


e = filter(lambda x: True, [])
assert e == []
print "filter() test 4 passes."


e = filter(lambda x: x%2 == 0, (1,3,5))
assert e == []
print "filter() test 5 passes."


# The following code should throw a TypeError
#filter(2, range(5))

# The following code should throw a TypeError
#filter(lambda x: x%2 == 0, 5)
