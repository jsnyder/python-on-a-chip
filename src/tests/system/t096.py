# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

#
# System Test 096
#
# Test for issue #96:
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
