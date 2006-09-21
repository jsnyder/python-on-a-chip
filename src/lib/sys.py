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
# Provides PyMite's system module, sys
#
# USAGE
# -----
#
# import sys
#
# LOG
# ---
#
# 2006/08/31    #9: Fix BINARY_SUBSCR for case stringobj[intobj]
# 2006/08/21    Adapt native libs to use the changed func calls
# 2002/09/07    Created.
#

#### TODO
#modules = None #set ptr to dict w/native func
#platform = None #obtain from aux lib: platform.py
#memfree, platform/device, stdout, type (type consts?), rand
#ver = "0.1"            # XXX compile date & platform?
# Example: sys.version = '2.4.1 (#1, Feb 26 2006, 16:26:36) \n[GCC 4.0.0 20041026 (Apple Computer, Inc. build 4061)]'

#### CONSTS

maxint = 0x7FFFFFFF     # 2147483647


#### FUNCS

def exit(val):
    """__NATIVE__
    pPmObj_t pval = C_NULL;

    /* If no arg given, assume return 0 */
    if (NATIVE_GET_NUM_ARGS() == 0)
    {
        NATIVE_SET_TOS(PM_ZERO);
    }
    
    /* If 1 arg given, put it on stack */
    else if (NATIVE_GET_NUM_ARGS() == 1)
    {
        pval = NATIVE_GET_LOCAL(0);
        NATIVE_SET_TOS(pval);
    }

    /* If wrong number of args, raise TypeError */
    else
    {
        return PM_RAISE(PM_RET_EX_TYPE, __LINE__);
    }

    /* Raise the SystemExit exception */
    return PM_RAISE(PM_RET_EX_EXIT, __LINE__);
    """
    pass

# :mode=c:
