#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

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
