/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x0E


/**
 * Module Object Type
 *
 * Module object type operations.
 */


#include "pm.h"


PmReturn_t
mod_new(pPmObj_t pco, pPmObj_t *pmod)
{
    PmReturn_t retval;
    uint8_t *pchunk;
    pPmObj_t pobj;

    /* If it's not a code obj, raise TypeError */
    if (OBJ_GET_TYPE(pco) != OBJ_TYPE_COB)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Alloc and init func obj */
    retval = heap_getChunk(sizeof(PmFunc_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    *pmod = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(*pmod, OBJ_TYPE_MOD);
    ((pPmFunc_t)*pmod)->f_co = (pPmCo_t)pco;

    /* Alloc and init attrs dict */
    retval = dict_new(&pobj);
    ((pPmFunc_t)*pmod)->f_attrs = (pPmDict_t)pobj;

    /* A module's globals is the same as its attrs */
    ((pPmFunc_t)*pmod)->f_globals = (pPmDict_t)pobj;

#ifdef HAVE_DEFAULTARGS
    /* Clear the default args (only used by funcs) */
    ((pPmFunc_t)*pmod)->f_defaultargs = C_NULL;
#endif /* HAVE_DEFAULTARGS */

    return retval;
}


PmReturn_t
mod_import(pPmObj_t pstr, pPmObj_t *pmod)
{
    PmMemSpace_t memspace;
    uint8_t const *imgaddr = C_NULL;
    pPmCo_t pco = C_NULL;
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj;

    /* If it's not a string obj, raise SyntaxError */
    if (OBJ_GET_TYPE(pstr) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_SYNTAX);
        return retval;
    }

    /* Try to find the image in the paths */
    retval = img_findInPaths(pstr, &memspace, &imgaddr);

    /* If img was not found, raise ImportError */
    if (retval == PM_RET_NO)
    {
        PM_RAISE(retval, PM_RET_EX_IMPRT);
        return retval;
    }

    /* Load img into code obj */
    retval = obj_loadFromImg(memspace, &imgaddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco = (pPmCo_t)pobj;

    return mod_new((pPmObj_t)pco, pmod);
}
