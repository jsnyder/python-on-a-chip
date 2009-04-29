/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x04


/**
 * Function Object Type
 *
 * Function object type operations.
 */


#include "pm.h"


PmReturn_t
func_new(pPmObj_t pco, pPmObj_t pglobals, pPmObj_t *r_pfunc)
{
    PmReturn_t retval = PM_RET_OK;
    pPmFunc_t pfunc = C_NULL;
    uint8_t *pchunk;
    pPmObj_t pobj;

    C_ASSERT(OBJ_GET_TYPE(pco) != OBJ_TYPE_COB
             || OBJ_GET_TYPE(pco) != OBJ_TYPE_NOB);
    C_ASSERT(OBJ_GET_TYPE(pglobals) == OBJ_TYPE_DIC);

    /* Allocate a func obj */
    retval = heap_getChunk(sizeof(PmFunc_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pfunc = (pPmFunc_t)pchunk;

    /* Init func */
    OBJ_SET_TYPE(pfunc, OBJ_TYPE_FXN);
    pfunc->f_co = (pPmCo_t)pco;

    /* Create attrs dict for regular func (not native) */
    if (OBJ_GET_TYPE(pco) == OBJ_TYPE_COB)
    {
        retval = dict_new(&pobj);
        PM_RETURN_IF_ERROR(retval);
        pfunc->f_attrs = (pPmDict_t)pobj;

        /* Store the given globals dict */
        pfunc->f_globals = (pPmDict_t)pglobals;
    }
    else
    {
        pfunc->f_attrs = C_NULL;
    }

#ifdef HAVE_DEFAULTARGS
    /* Clear default args (will be set later, if at all) */
    pfunc->f_defaultargs = C_NULL;
#endif /* HAVE_DEFAULTARGS */

    *r_pfunc = (pPmObj_t)pfunc;
    return PM_RET_OK;
}
