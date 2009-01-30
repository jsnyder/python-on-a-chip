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
# Test for Issue #132: VM doesn't throw TypeError 
# when function has wrong number of arguments
#
# Run code that should cause a TypeError.
# See that it doesn't.  Fix the defect, and see that a TypeError occurs.
#
# Then REMOVE this test from the suite since it expects an error.
#

def foo(n):
    return n * 1
    
# Expect TypeError
foo(1, 2)
