#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 161
# Improve filter for unsupported code
#


# Example of varargs
def foo1(a, *b):
    return a+b


# Example of keyword args
def foo2(a, **kwb):
    return a+b[42]


# Example of a generator
def foo3(a):
    i = 0
    while 1:
        yield i
        i += a
