/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

/**
 * System Test 075
 * Testing two threads starting at the same time, each calculating a number
 * and printing it.
 */

#include "pm.h"
#include "stdio.h"


extern unsigned char usrlib_img[];


int main(void)
{
    /* replicate pm_run()'s functionality to allow two initial threads. */
    PmReturn_t retval;
    pPmObj_t pmodA;
    pPmObj_t pmodB;
    pPmObj_t pstring;
    uint8_t const *pmodstrA = (uint8_t const *)"t075a";
    uint8_t const *pmodstrB = (uint8_t const *)"t075b";

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    /* Import modules from global struct */
    retval = string_new(&pmodstrA, &pstring);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmodA);
    PM_RETURN_IF_ERROR(retval);

    retval = string_new(&pmodstrB, &pstring);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmodB);
    PM_RETURN_IF_ERROR(retval);

    /* Load builtins into thread */
    retval = global_setBuiltins((pPmFunc_t)pmodA);
    retval = global_setBuiltins((pPmFunc_t)pmodB);
    PM_RETURN_IF_ERROR(retval);
    
    /* Interpret the module's bcode */
    retval = interp_addThread((pPmFunc_t)pmodA);
    retval = interp_addThread((pPmFunc_t)pmodB);
    PM_RETURN_IF_ERROR(retval);
    retval = interpret(INTERP_RETURN_ON_NO_THREADS);

    return retval;
}
