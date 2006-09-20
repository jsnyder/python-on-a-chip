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
#define __FILE_ID__ 0x03
/**
 * VM Frame
 *
 * VM frame operations.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "pm.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

PmReturn_t
frame_new(pPmObj_t pfunc, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t fsize = 0;
    int8_t stacksz = 0;
    int8_t nlocals = 0;
    pPmCo_t pco = C_NULL;
    pPmFrame_t pframe = C_NULL;
    uint8_t *paddr = C_NULL;
    uint8_t *pchunk;

    /* get fxn's code obj */
    pco = ((pPmFunc_t)pfunc)->f_co;

    /* TypeError if passed func's CO is not a true COB */
    if (pco->od.od_type != OBJ_TYPE_COB)
    {
        return PM_RET_EX_TYPE;
    }

    /* get sizes needed to calc frame size */
    paddr = pco->co_codeimgaddr + CI_STACKSIZE_FIELD;
    stacksz = mem_getByte(pco->co_memspace, &paddr);
    nlocals = mem_getByte(pco->co_memspace, &paddr);
    fsize = sizeof(PmFrame_t) + (stacksz + nlocals) *
            sizeof(pPmObj_t);
    /* allocate a frame */
    retval = heap_getChunk(fsize, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pframe = (pPmFrame_t)pchunk;

    /* set frame fields */
    pframe->od.od_type = OBJ_TYPE_FRM;
    pframe->fo_back = C_NULL;
    pframe->fo_func = (pPmFunc_t)pfunc;
    pframe->fo_memspace = pco->co_memspace;
    /* init instruction pointer, line number and block stack */
    pframe->fo_ip = pco->co_codeaddr;
    pframe->fo_line = 0;
    pframe->fo_blockstack = C_NULL;
    /* init globals dict to NULL, interpreter will set it */
    pframe->fo_globals = C_NULL;
    /* frame's attrs points to func/mod/class's attrs dict */
    pframe->fo_attrs = ((pPmFunc_t)pfunc)->f_attrs;
    /* empty stack points to one past locals */
    pframe->fo_sp = &(pframe->fo_locals[nlocals]);

    /* return ptr to frame */
    *r_pobj = (pPmObj_t)pframe;
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
