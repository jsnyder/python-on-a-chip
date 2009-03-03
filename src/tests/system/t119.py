#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 119
# Print Python traceback on exception
#

def divzero(n):
    print "In divzero"
    a = n/0

def foo():
    divzero(42)

def bar():
    foo()
    
def baz():
    bar()

if ismain():
    print "calling baz()"
#    baz()  # expect exception and traceback
