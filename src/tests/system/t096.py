#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 096
# Create library function to spawn a new thread
#

import sys

sharedVar = 42


def f1():
    global sharedVar
    print "f1: sharedVar is ", sharedVar
    while sharedVar == 42:
        pass
    print "f1: sharedVar is ", sharedVar

    
def f2():
    global sharedVar
    print "f2: killing time..."
    for i in range(32):
        print i,
    print
    print "f2: setting sharedVar to 99"
    sharedVar = 99

sys.runInThread(f2)
sys.runInThread(f1)
