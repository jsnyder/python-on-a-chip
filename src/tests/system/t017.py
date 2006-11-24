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
# System Test 017
# Tests implementation of seq_compare()
#


l1 = [2,5,6]
l2 = [2,5,6]
assert l1 == l2

l3 = [2,5,5]
assert l2 != l3

t1 = (2,5,6)
t2 = (2,5,6)
assert t1 == t2

t3 = (2,5,5)
assert t2 != t3
