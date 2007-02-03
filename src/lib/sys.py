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
    PmReturn_t retval;

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
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise the SystemExit exception */
    PM_RAISE(retval, PM_RET_EX_EXIT);
    return retval;
    """
    pass


#
# Returns a tuple containing the amout of heap available and the maximum
#
def heap():
    """__NATIVE__
    PmReturn_t retval;
    pPmObj_t pavail;
    pPmObj_t pmax;
    pPmObj_t ptup;
    uint16_t avail;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Allocate a tuple to store the return values */
    retval = tuple_new(2, &ptup);
    PM_RETURN_IF_ERROR(retval);

    /* Get the maximum heap size */
    retval = int_new(HEAP_SIZE, &pmax);
    PM_RETURN_IF_ERROR(retval);

    /* Allocate an int to hold the amount of heap available */
    retval = int_new(0, &pavail);
    PM_RETURN_IF_ERROR(retval);

    /* Now that all objs are allocated, get the available heap */
    retval = heap_getAvail(&avail);
    PM_RETURN_IF_ERROR(retval);
    ((pPmInt_t)pavail)->val = avail;

    /* Put the two heap values in the tuple */
    ((pPmTuple_t)ptup)->val[0] = pavail;
    ((pPmTuple_t)ptup)->val[1] = pmax;

    /* Return the tuple on the stack */
    NATIVE_SET_TOS(ptup);

    return retval;
    """
    pass


# :mode=c:
