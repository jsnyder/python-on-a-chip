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
# System Test 190
# Fix segfault when num args is fewer than expected
#

def foo():
    return "foo"

def foo1(a=42):
    return a+1

def foo2(a,b=42):
    return a+b


print foo()

print foo1()
print foo1(1)

print foo2(1)
print foo2(1,2)


# NOTE: uncomment each of the following lines one at a time and test

#print foo(1) # Expect TypeError (0xED)
#print foo1(1,2) # Expect TypeError (0xED)
#print foo2() # Expect TypeError (0xED)
#print foo2(1,2,3) # Expect TypeError (0xED)

# If the following line causes a segfault, it's a regression.
print "Expect TypeError:"
map(map, range(5)) # Expect TypeError (0xED)
