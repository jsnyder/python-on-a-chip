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
