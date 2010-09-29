# This file is Copyright 2010 Oscar Lindberg.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
# 
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

"""__NATIVE__
#include <ma.h>
"""

def maWait(ms):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pms = C_NULL;
    int ms;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    /* Raise TypeError if arg is not an int */
    pms = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pms) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    ms = ((pPmInt_t)pms)->val;
    maWait(ms);

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass

print "MoPync - bringing the Guido goodness to the world of MoSync"
maWait(0)
print "I'm done!"

