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
# System Test 205
# Add support for string format operation
#

i = 4
s1 = "test %d" % i
s2 = "test %d" % (i,)
assert s1 == s2 == "test 4"

i = 205
s1 = "test t%03d" % i
s2 = "test t%03d" % (i,)
print s1
assert s1 == s2 == "test t205"

f = -3.14
s1 = "test %f this" % f
s2 = "test %f this" % (f,)
assert s1 == s2 == "test -3.140000 this"

f = -3.14
s1 = "test %1.2f" % f
s2 = "test %1.2f" % (f,)
assert s1 == s2 == "test -3.14"

s = "this"
s1 = "test %s string" % s
s2 = "test %s string" % (s,)
assert s1 == s2 == "test this string"

d = 4
s = "score"
f = 7.0
s = "%d %s and %.0f years ago" % (d,s,f,)
print s
assert s == "4 score and 7 years ago"
