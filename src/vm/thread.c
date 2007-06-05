/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2002 Dean Hall
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#undef __FILE_ID__
#define __FILE_ID__ 0x16

/**
 * VM Thread
 *
 * Encapsulating a frame pointer, a root code object and thread state.
 *
 * Log
 * ---
 *
 * 2007/01/03   #75: First (P.Adelt)
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "pm.h"


/***************************************************************
 * Functions
 **************************************************************/

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
