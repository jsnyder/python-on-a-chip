/**
 * PyMite User API
 *
 * High-level functions to initialize and run PyMite
 *
 * @author      Dean Hall
 * @copyright   Copyright 2006 Dean Hall.  All rights reserved.
 *
 * Log
 * ---
 *
 * 2006/09/16   #16: Create pm_init() that does the initial housekeeping
 */

#include "py.h"


extern unsigned char stdlib_img[];


PyReturn_t pm_init(PyMemSpace_t memspace, P_U8 pusrimg)
{
    PyReturn_t retval;
    P_U8 pimg;

    /* Initialize the heap and the globals */
    heap_init();
    retval = global_init();
    PY_RETURN_IF_ERROR(retval);

    /* Load std image info */
    pimg = (P_U8)&stdlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* Load usr image info if given */
    if (pusrimg != C_NULL)
    {
        pimg = pusrimg;
        retval = img_findInMem(memspace, &pimg);
    }

    return retval;
}


PyReturn_t pm_run(P_U8 modstr)
{
    PyReturn_t retval;
    pPyFunc_t pmod;
    pPyObj_t pstring;
    P_U8 pmodstr = modstr;

    /* Import module from global struct */
    retval = string_new(&pmodstr, &pstring);
    PY_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmod);
    PY_RETURN_IF_ERROR(retval);

    /* Load builtins into root module */
    retval = global_loadBuiltins(pmod);
    PY_RETURN_IF_ERROR(retval);

    /* Interpret the module's bcode */
    retval = interpret(pmod);

    return retval;
}
