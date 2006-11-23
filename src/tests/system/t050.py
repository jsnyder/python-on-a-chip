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
# Feature Test for Issue #50
#
# Integrate __LINE__ into PM_RAISE
#
# To check that PM_RAISE works, I made a simple code snippet below that
# will exercise specific functions in int.c
#

n = 1

n0 = +n
assert n0 == 1

n1 = ~n
assert n1 == -2

n2 = -n
assert n2 == -1
