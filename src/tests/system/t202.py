#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

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

#bar = Bar() # Expect TypeError (0xED) (too few args)
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
