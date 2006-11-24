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
# System Test 049
# Tests implementation of obj_isFalse() for Tuple, List and Dict.
#


t1 = ()
if t1:
    assert 0

t2 = (2,)
if not t2:
    assert 0

l1 = []
if l1:
    assert 0

l2 = [2,]
if not l2:
    assert 0

d1 = {}
if d1:
    assert 0
    
d2 = {2:2}
if not d2:
    assert 0
