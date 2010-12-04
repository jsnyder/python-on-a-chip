# This file is Copyright 2010 Dean Hall.
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

#
# System Test 374
# A regression results in a TypeError.
# Proper execution runs to completion.
#


def __gc_test(val):
    """__NATIVE__
    pPmObj_t pval;
    int32_t nval;
    PmReturn_t retval = PM_RET_OK;

    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    pval = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pval) != OBJ_TYPE_INT)
    {
        printf("-- type check -- [actual type: %d]\\n", OBJ_GET_TYPE(pval));
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    nval = ((pPmInt_t)pval)->val;

    printf("%d [%d]\\n", nval-2, nval);

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def gc_test(p):
    __gc_test(p + 2)


i = 0
while i < 256:
    gc_test(i)
    i += 1
