# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2009 Dean Hall
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
# Provides PyMite's string module.
#

"""__NATIVE__
#include <stdlib.h>
#include <string.h>
"""


digits = "0123456789"
hexdigits = "0123456789abcdefABCDEF"
letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"


#
# Returns the integer represented by the string a [in base b].
# Optional int arg, b, may be 0 or 2 through 36; otherwise it is a ValueError.
#
def atoi(a, b):
    """__NATIVE__
    pPmObj_t pa;
    pPmObj_t pb;
    uint8_t *pc;
    uint8_t *pend;
    long i;
    int8_t base;
    pPmObj_t pi;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a string or wrong number of args, */
    pa = NATIVE_GET_LOCAL(0);
    if ((OBJ_GET_TYPE(pa) != OBJ_TYPE_STR) || (NATIVE_GET_NUM_ARGS() < 1)
        || (NATIVE_GET_NUM_ARGS() > 2))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the base, if it exists; otherwise assume 10 */
    base = 10;
    if (NATIVE_GET_NUM_ARGS() == 2)
    {
        pb = NATIVE_GET_LOCAL(1);

        /* Raise a TypeError if 2nd arg is not an int */
        if (OBJ_GET_TYPE(pb) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        base = ((pPmInt_t)pb)->val;

        /* Raise ValueError if base is out of range */
        if ((base < 0) || (base == 1) || (base > 36))
        {
            PM_RAISE(retval, PM_RET_EX_VAL);
            return retval;
        }
    }

    /* Perform conversion */
    pend = C_NULL;
    pc = (uint8_t *)&(((pPmString_t)pa)->val);
    i = strtol((const char *)pc, (char **)&pend, base);

    /* Raise ValueError if there was a conversion error */
    if (*pend != C_NULL)
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    /* Create an int object to hold the result of the conversion */
    retval = int_new(i, &pi);

    NATIVE_SET_TOS(pi);

    return retval;
    """
    pass


#
# Returns the number of occurrences of substring s2 in string s1.
# WARNING: Does not match Python's behavior if s1 contains a null character.
#
def count(s1, s2):
    """__NATIVE__
    pPmObj_t ps1;
    pPmObj_t ps2;
    uint8_t *pc1;
    uint8_t *pc2;
    uint8_t *pscan;
    uint16_t pc1len;
    uint16_t pc2len;
    uint16_t n;
    pPmObj_t pn;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a string or wrong number of args, */
    ps1 = NATIVE_GET_LOCAL(0);
    ps2 = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(ps1) != OBJ_TYPE_STR) || (NATIVE_GET_NUM_ARGS() != 2)
        || (OBJ_GET_TYPE(ps2) != OBJ_TYPE_STR))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    pc1 = ((pPmString_t)ps1)->val;
    pc2 = ((pPmString_t)ps2)->val;
    pc1len = ((pPmString_t)ps1)->length;
    pc2len = ((pPmString_t)ps2)->length;
    n = 0;

    if (*pc2 != C_NULL)
    {
        pscan = (uint8_t *)strstr((const char *)pc1, (const char *)pc2);
        while (pscan != C_NULL)
        {
            n++;
            pscan += pc2len;
            if (pscan > pc1 + pc1len) break;
            pscan = (uint8_t *)strstr((const char *)pscan, (const char *)pc2);
        }
    }

    retval = int_new(n, &pn);

    NATIVE_SET_TOS(pn);

    return retval;
    """
    pass


#
# Returns the lowest index in s1 where substring s2 is found or -1 on failure.
# WARNING: Does not accept optional start,end arguments.
#
def find(s1, s2):
    """__NATIVE__
    pPmObj_t ps1;
    pPmObj_t ps2;
    uint8_t *pc1;
    uint8_t *pc2;
    uint8_t *pscan;
    int32_t n;
    pPmObj_t pn;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a string or wrong number of args, */
    ps1 = NATIVE_GET_LOCAL(0);
    ps2 = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(ps1) != OBJ_TYPE_STR) || (NATIVE_GET_NUM_ARGS() != 2)
        || (OBJ_GET_TYPE(ps2) != OBJ_TYPE_STR))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    pc1 = ((pPmString_t)ps1)->val;
    pc2 = ((pPmString_t)ps2)->val;
    n = -1;

    /* If the strings are non-null, try to find the index of the substring */
    if ((*pc1 != C_NULL) && (*pc2 != C_NULL))
    {
        pscan = (uint8_t *)strstr((const char *)pc1, (const char *)pc2);
        if (pscan != C_NULL)
        {
            n = pscan - pc1;
        }
    }

    retval = int_new(n, &pn);

    NATIVE_SET_TOS(pn);

    return retval;
    """
    pass


# :mode=c:
