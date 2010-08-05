# This file is Copyright 2003, 2006, 2007, 2009, 2010 Dean Hall.
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
# System Test 291
# Fix GC so base classes are not collected
#

import sys


class Bar(object):
    def baz(self, ):
        return "baz"

class Foo(Bar):
    def faz(self, ):
        return "faz"

foo = Foo()
print foo.faz()
print foo.baz()

# Cause a GC
print "sys.heap() = ", sys.heap()
a = range(120) 
print "sys.heap() = ", sys.heap()

# Overwrite a reclaimed chunk
del a
b = range(50)

# Try to use a method from a base class
print foo
print foo.faz()
print foo.baz()

# A C assertion reveals regression: subclass is not of type class.
# This occurs because the chunk was GC'd accidentally and then
# was overwritten with another object:
#
#$ ./t291.out
#faz 
#baz 
#sys.heap() =  (2668, 8192) 
#sys.heap() =  (1200, 8192) 
#Error:     0xFC
#  Release: 0x08
#  FileId:  0x18
#  LineNum: 140
#Traceback (top first):
#  t291()
#  <module>.
#make: *** [t291.out] Error 252
