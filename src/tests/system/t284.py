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
# System Test 284
#

print "Exercising string.join()"

import string


assert string.join('') == ''
assert string.join('','') == ''
assert string.join("foo",'') == "foo"


e1 = ()
e2 = []
t = ("check", "this", "out")
l = ["check", "this", "out"]
j = ('', '\x00', '\x04', '\n', ' ', '!', '\xff', "foo")

for c in j:
    je1 = string.join(e1, c)
    je2 = string.join(e2, c)
    assert je1 == ''
    assert je2 == ''

    jt = string.join(t, c)
    jl = string.join(l, c)
    print jt
    assert jt == jl

    jt = string.join(t)
    jl = string.join(l)
    assert jt == jl


assert string.join("chicken", 'Z') == "cZhZiZcZkZeZn"
