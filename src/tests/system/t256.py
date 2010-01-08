# This file is Copyright 2009 Dean Hall.
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
# System Test 256
# Add support for closures
#


callback_table = {}
HOOK_1S = 1002
HOOK_ADC = 1003


def doNothing(f):
    print "in doNothing"
    return f


def setHook(event):
    print "in setHook"
    def _sh(f):
        print "in _sh"
        callback_table[event] = f
        return f
    return _sh


@doNothing
@setHook(HOOK_1S)
def onOneSecond():
    print "in onOneSecond"


@setHook(HOOK_ADC)
@doNothing
def onAdcReady():
    print "in onAdcReady"


print "callback_table: ", callback_table

assert callback_table[1002] == onOneSecond
assert callback_table[1003] == onAdcReady
print "Closure test 1 passes"


####

def filter(f, s):
    return [x for x in s if f(x)]

def isEven(n):
    return n % 2 == 0

class Employee():
    def __init__(self,):
        self.salary = 100

def highPaid1(emps):
    threshold = 150
    return filter(lambda e: e.salary > threshold, emps)

def paidMore(amount):
    return lambda x: filter(lambda e: e.salary > amount, x)
highPaid2 = paidMore(150)

john = Employee()
john.salary = 200
john.isManager = False

employees = [john, Employee(), Employee()]
assert highPaid1(employees) == [john,]
assert highPaid2(employees) == [john,]
print "Closure test 2 passes"


####

def foo(a,b,c):
    def bar():
        def baz():
            return a+b+c
        return baz
    return bar()
f = foo(1,2,3)
print f
assert f() == 6
print "Closure test 3 passes"
