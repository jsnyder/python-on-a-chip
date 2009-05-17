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
# System Test 207
# Add support for the yield keyword
#
# To learn about generators: http://www.dabeaz.com/generators/Generators.pdf
#


# Generator-expressions

a = [1,2,3,4]
b = (2*x for x in a)
c = [2*x for x in a]
n = 0
for i in b:
    print i,
    assert i == c[n]
    n += 1
print


# Generator-iterators

def fib():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a+b

print "Fibonacci generator:",
for i in fib():
    print i,
    if i > 256:
        break
print

f = fib()
assert type(f) == 0x09
assert f.next() == 0
assert f.next() == 1
assert f.next() == 1
assert f.next() == 2
assert f.next() == 3
assert f.next() == 5
assert f.next() == 8


# Generator-coroutines

def show(n):
    i = 0
    while True:
        msg = (yield i)
        print "I'm going to say this", n, "times:", msg * n
        i += 1

s3 = show(3)
s4 = show(4)
assert s3.next() == 0
assert s4.next() == 0
assert s3.send("moo") == 1
assert s4.send("baa") == 1
assert s3.send("cow") == 2
assert s4.send("dog") == 2
