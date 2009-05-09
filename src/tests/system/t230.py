# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
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
# System Test 230
# Fix classes during ipm
# This test checks for a regression: __NATIVE__ __init__ method pushed None
# on the stack causing trouble.
#
"""__NATIVE__
#include <stdio.h>
"""


class File():

    def __init__(self, fn):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pfn;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        FILE *pf;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the arg, throw type exception if needed */
        pfn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pfn) != OBJ_TYPE_STR)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Open the file in write/bin mode */
        pf = fopen((const char *)((pPmString_t)pfn)->val, "wb");

        /* Save the pointer to file as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)pf, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def close(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        FILE *pf;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Close the file */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pf = (FILE *)((pPmInt_t)pn)->val;
        fclose(pf);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass

f1 = File("zem")
print "Created instance: File('zem')"
f1.close()
print "File closed"
