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
# Provides PyMite's platform module, plat.
#
# USAGE
# -----
#
# ``import plat``
#
# LOG
# ---
#
# 2006/12/26    #65: Create plat module with put and get routines
#

#
# Get a byte from the platform's default I/O
# Returns the byte in the LSB of the returned number
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
# Sends the LSB of the number out the platform's default I/O
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
    if (OBJ_GET_TYPE(*pb) != OBJ_TYPE_INT)
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
# Prints a string to the default I/O.
# Does not append a "\n" on its own (like Python's print statement and C's puts)
# but it does convert "\n" to "\r\n" (a convenience for Win32 terminals)
#
def puts(s):
    for c in s:
        if (c == "\n"):
            plat.putb(13)
        plat.putb(ord(c))

#:mode=c:
