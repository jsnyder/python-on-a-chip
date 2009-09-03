# This file is Copyright 2009 Dean Hall.
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
# System Test 242
# Add support for string concatenation
#

s1 = "test"
s2 = "this"
assert s1 + s2 == "testthis"

s3 = ""
assert s1 + s3 == s1
assert s3 + s1 == s1

# Uncomment when issue 243 is fixed
#assert s1 + "\0" == "test\0"
#assert "\0" + s1 == "\0test"

print "String concatenation " + s1 + " passes"
