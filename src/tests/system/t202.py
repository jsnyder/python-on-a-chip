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
# System Test 202
# Implement classes in the vm
#


print "testing Foo..."
class Foo(object):
    def foo(self,):
        print "In foo."

foo = Foo()
foo.foo()
assert type(Foo) == 0x07
assert type(foo) == 0x09


print "testing Bar..."
class Bar(Foo):
    def __init__(self, val):
        self.v = val # STORE_ATTR for instance not yet implemented

    a=42

    def foo(self,):
        print "In Bar's foo."

bar = Bar(99)
bar.foo()
assert bar.a == 42
assert bar.v == 99


print "Testing Baz..."
class Baz(object, Bar):
    def foo(self,):
        print "In Baz's foo."
baz = Baz(100)
baz.foo()
assert baz.a == 42
assert baz.v == 100

# Test how unknown attr fails
#print baz.zilch # Expect AttributeError (0xE5)

print "Expect TypeError:"
bar = Bar() # Expect TypeError (0xED) (too few args)
