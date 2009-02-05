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
# Provides PyMite's dict module.
#

def clear(d):
    """__NATIVE__
    pPmObj_t pd;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a dict or wrong number of args, */
    pd = NATIVE_GET_LOCAL(0);
    if ((OBJ_GET_TYPE(pd) != OBJ_TYPE_DIC) || (NATIVE_GET_NUM_ARGS() != 1))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Clear the contents of the dict */
    retval = dict_clear(pd);
    PM_RETURN_IF_ERROR(retval);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def has_key(d, k):
    if k in dict.keys(d):
        return 1
    else:
        return 0


def keys(d):
    """__NATIVE__
    pPmObj_t pd;
    pPmObj_t pl;
    pPmObj_t pk;
    pSeglist_t psl;
    uint16_t i;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a dict or wrong number of args, */
    pd = NATIVE_GET_LOCAL(0);
    if ((OBJ_GET_TYPE(pd) != OBJ_TYPE_DIC) || (NATIVE_GET_NUM_ARGS() != 1))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Create empty list */
    retval = list_new(&pl);
    PM_RETURN_IF_ERROR(retval);
    NATIVE_PIN_OBJ(retval, pl);
    PM_RETURN_IF_ERROR(retval);

    /* Iterate through the keys seglist */
    psl = ((pPmDict_t)pd)->d_keys;
    for (i = 0; i < ((pPmDict_t)pd)->length; i++)
    {
        /* Get the key and append it to the list */
        retval = seglist_getItem(psl, i, &pk);
        PM_RETURN_IF_ERROR(retval);
        retval = list_append(pl, pk);
        PM_RETURN_IF_ERROR(retval);
    }

    /* Return the list of keys to the caller */
    NATIVE_SET_TOS(pl);

    return retval;
    """
    pass


def values(d):
    """__NATIVE__
    pPmObj_t pd;
    pPmObj_t pl;
    pPmObj_t pv;
    pSeglist_t psl;
    uint16_t i;
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if it's not a dict or wrong number of args, */
    pd = NATIVE_GET_LOCAL(0);
    if ((OBJ_GET_TYPE(pd) != OBJ_TYPE_DIC) || (NATIVE_GET_NUM_ARGS() != 1))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Create empty list */
    retval = list_new(&pl);
    PM_RETURN_IF_ERROR(retval);
    NATIVE_PIN_OBJ(retval, pl);
    PM_RETURN_IF_ERROR(retval);

    /* Iterate through the values seglist */
    psl = ((pPmDict_t)pd)->d_vals;
    for (i = 0; i < ((pPmDict_t)pd)->length; i++)
    {
        /* Get the value and append it to the list */
        retval = seglist_getItem(psl, i, &pv);
        PM_RETURN_IF_ERROR(retval);
        retval = list_append(pl, pv);
        PM_RETURN_IF_ERROR(retval);
    }

    /* Return the list of values to the caller */
    NATIVE_SET_TOS(pl);

    return retval;
    """
    pass


# :mode=c:
