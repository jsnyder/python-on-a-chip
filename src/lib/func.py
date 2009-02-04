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
# Provides PyMite's func module.
#

#
# Returns the names tuple of the function/module object
#
def co_names(f):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pfunc;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    pfunc = NATIVE_GET_LOCAL(0);
    NATIVE_SET_TOS((pPmObj_t)((pPmFunc_t)pfunc)->f_co->co_names);

    return retval;
    """
    pass


#
# Returns the constants tuple of the function/module object
#
def co_consts(f):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pfunc;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    pfunc = NATIVE_GET_LOCAL(0);
    NATIVE_SET_TOS((pPmObj_t)((pPmFunc_t)pfunc)->f_co->co_consts);

    return retval;
    """
    pass


# :mode=c:
