#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

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
#map(map, range(5)) # Expect TypeError (0xED)
