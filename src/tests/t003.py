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
# System Test 003
# Unrelated to issue #3.
#
# A module that has two simple functions,
# and calls them via main().
#


def a(a1, a2):
    """
    Return the sum of a1 and a2.
    """
    return a1 + a2


def b(b1, b2):
    """
    Return the difference between b1 and b2.
    """
    return b1 - b2


def main():
    a(2, 5)
    b(2, 6)
    return


main()
