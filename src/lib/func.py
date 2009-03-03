#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
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
