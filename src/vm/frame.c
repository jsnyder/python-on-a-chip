/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x03


/**
 * VM Frame
 *
 * VM frame operations.
 */


#include "pm.h"


PmReturn_t
frame_new(pPmObj_t pfunc, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t fsize = 0;
    int8_t stacksz = (int8_t)0;
    int8_t nlocals = (int8_t)0;
    pPmCo_t pco = C_NULL;
    pPmFrame_t pframe = C_NULL;
    uint8_t const *paddr = C_NULL;
    uint8_t *pchunk;

    /* Get fxn's code obj */
    pco = ((pPmFunc_t)pfunc)->f_co;

    /* TypeError if passed func's CO is not a true COB */
    if (OBJ_GET_TYPE(pco) != OBJ_TYPE_COB)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get sizes needed to calc frame size */
    paddr = pco->co_codeimgaddr + CI_STACKSIZE_FIELD;
    stacksz = mem_getByte(pco->co_memspace, &paddr);

    /* Now paddr points to CI_NLOCALS_FIELD */
    nlocals = mem_getByte(pco->co_memspace, &paddr);
    fsize = sizeof(PmFrame_t) + (stacksz + nlocals - 1) * sizeof(pPmObj_t);

    /* Allocate a frame */
    retval = heap_getChunk(fsize, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pframe = (pPmFrame_t)pchunk;

    /* Set frame fields */
    OBJ_SET_TYPE(pframe, OBJ_TYPE_FRM);
    pframe->fo_back = C_NULL;
    pframe->fo_func = (pPmFunc_t)pfunc;
    pframe->fo_memspace = pco->co_memspace;

    /* Init instruction pointer, line number and block stack */
    pframe->fo_ip = pco->co_codeaddr;
    pframe->fo_blockstack = C_NULL;

    /* Get globals and attrs from the function object */
    pframe->fo_globals = ((pPmFunc_t)pfunc)->f_globals;
    pframe->fo_attrs = ((pPmFunc_t)pfunc)->f_attrs;

    /* Empty stack points to one past locals */
    pframe->fo_sp = &(pframe->fo_locals[nlocals]);

    /* By default, this is a normal frame, not an import call one */
    pframe->fo_isImport = 0;

    /* Return ptr to frame */
    *r_pobj = (pPmObj_t)pframe;
    return retval;
}
