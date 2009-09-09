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
# System Test 243
# Fix cases where string contains an embedded null
#

s1 = "\0"
s2 = "a" + s1
s3 = s2 + "a"

assert s2 == "a\0"
assert s3 == "a\0a"

s2 = s1 + "a"
s3 = s2 + "\0"

assert s2 == "\0a"
assert s3 == "\0a\0"

s2 = "let's \0 try" + s1 + "something else\0"
assert s2 == "let's \0 try\0something else\0"
