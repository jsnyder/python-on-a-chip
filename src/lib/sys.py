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
# 2007/02/03    #89: Move plat module functions into sys module
# 2006/12/26   *#65: Create plat module with put and get routines
# 2007/02/03    #88: Create library function to return heap stats
# 2006/08/31    #9: Fix BINARY_SUBSCR for case stringobj[intobj]
# 2006/08/21    Adapt native libs to use the changed func calls
# 2002/09/07    Created.
#

#### TODO
# modules = None #set ptr to dict w/native func
# platform string or device id, rand
# ver = "0.1"            # XXX compile date & platform?
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
# Get a byte from the platform's default I/O
# Returns the byte in the LSB of the returned integer
#
def getb():
    """__NATIVE__
    uint8_t b;
    pPmObj_t pb;
    PmReturn_t retval;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    retval = plat_getByte(&b);
    PM_RETURN_IF_ERROR(retval);

    retval = int_new((int32_t)b, &pb);
    NATIVE_SET_TOS(pb);
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
    retval = heap_getAvail(&avail);
    retval = int_new(avail - sizeof(PmInt_t), &pavail);
    PM_RETURN_IF_ERROR(retval);

    /* Put the two heap values in the tuple */
    ((pPmTuple_t)ptup)->val[0] = pavail;
    ((pPmTuple_t)ptup)->val[1] = pmax;

    /* Return the tuple on the stack */
    NATIVE_SET_TOS(ptup);

    return retval;
    """
    pass


#
# Sends the LSB of the integer out the platform's default I/O
#
def putb(b):
    """__NATIVE__
    uint8_t b;
    pPmObj_t pb;
    PmReturn_t retval;

    pb = NATIVE_GET_LOCAL(0);

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* If arg is not an int, raise TypeError */
    if (OBJ_GET_TYPE(pb) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    b = ((pPmInt_t)pb)->val & 0xFF;
    retval = plat_putByte(b);
    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


#
# Runs the given function in a thread sharing the current global namespace
#
def runInThread(f):
    """__NATIVE__
    PmReturn_t retval;
    pPmObj_t pf;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* If arg is not a function, raise TypeError */
    pf = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pf) != OBJ_TYPE_FXN)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    retval = interp_addThread((pPmFunc_t)pf);
    return retval;
    """
    pass


#
# Returns the number of milliseconds since the PyMite VM was initialized
#
def time():
    """__NATIVE__
    uint32_t t;
    pPmObj_t pt;
    PmReturn_t retval;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the system time (milliseconds since init) */
    retval = plat_getMsTicks(&t);
    PM_RETURN_IF_ERROR(retval);

    /*
     * Raise ValueError if there is an overflow
     * (plat_getMsTicks is unsigned; int is signed)
     */
    if ((int32_t)t < 0)
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    /* Return an int object with the time value */
    retval = int_new((int32_t)t, &pt);
    NATIVE_SET_TOS(pt);
    return retval;
    """
    pass


# :mode=c:
