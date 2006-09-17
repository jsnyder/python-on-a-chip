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
# Feature Test for Issue #2
# Regression Test for Issue #28
#
# Separate stdlib from user app
#
# The test below proves that push42() was called from the usrlib native code
# and assert was called from the stdlib native code.
#
"""__NATIVE__
/*
 * This is a regression test for issue #28.
 * Having this doc-level native block should not affect
 * the index of the native func below.
 */
"""

#
# Pushes the int, 42, onto the stack
#
def push42():
    """__NATIVE__
    pPyObj_t pint = C_NULL;
    PyReturn_t retval;

    retval = int_new((S32)42, &pint);
    NATIVE_SET_TOS(pint);

    return retval;
    """
    pass

foo = push42()
bar = 6 * 7
assert foo == bar
