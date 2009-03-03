/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x16


/**
 * VM Thread
 *
 * Encapsulating a frame pointer, a root code object and thread state.
 */


#include "pm.h"


PmReturn_t
thread_new(pPmObj_t pframe, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    pPmThread_t pthread = C_NULL;

    C_ASSERT(pframe != C_NULL);

    /* If it's not a frame, raise TypeError */
    if (OBJ_GET_TYPE(pframe) != OBJ_TYPE_FRM)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Allocate a thread */
    retval = heap_getChunk(sizeof(PmThread_t), (uint8_t **)r_pobj);
    PM_RETURN_IF_ERROR(retval);

    /* Set type, frame and initialize status */
    pthread = (pPmThread_t)*r_pobj;
    OBJ_SET_TYPE(pthread, OBJ_TYPE_THR);
    pthread->pframe = (pPmFrame_t)pframe;
    pthread->interpctrl = INTERP_CTRL_CONT;

    return retval;
}
