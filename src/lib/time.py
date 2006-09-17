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
# Provides PyMite's time module, time
#
# USAGE
# -----
#
# import time
# t1 = time.clock()
# doStuff()
# t2 = time.clock()
# print t2 - t1
#
# LOG
# ---
#
# 2006/08/21    #28: Adapt native libs to use the changed func calls
# 2002/05/25    Created.
#


#### CONSTS


#### FUNCS

#
# Returns the current time in (?milli?)seconds
#
def clock():
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t ptime;

    /* Create int obj with current time */
#ifdef TARGET_DESKTOP
    retval = int_new((int)time(C_NULL), &ptime);
#else
# error time.clock is unimplemented for non-DESKTOP builds
    retval = int_new(0, &ptime);
#endif

    /* return time via stack */
    NATIVE_SET_TOS(ptime);
    return retval;
    """
    pass

# :mode=c:
