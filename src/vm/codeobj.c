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
#define __FILE_ID__ 0x01
/**
 * CodeObj Type
 *
 * CodeObj type operations.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/06/04   making co_names a tuple,
 *              removing nameoff and codeoff from img.
 * 2002/05/04   First.
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
co_loadFromImg(PmMemSpace_t memspace, uint8_t **paddr, pPmObj_t *r_pco)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj;
    pPmCo_t pco = C_NULL;
    uint8_t *pchunk;

    /* store ptr to top of code img (less type byte) */
    uint8_t *pci = *paddr - 1;

    /* get size of code img */
    uint16_t size = mem_getWord(memspace, paddr);

    /* allocate a code obj */
    retval = heap_getChunk(sizeof(PmCo_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pco = (pPmCo_t)pchunk;

    /* fill in the CO struct */
    OBJ_SET_TYPE(*pco, OBJ_TYPE_COB);
    pco->co_memspace = memspace;
    pco->co_codeimgaddr = pci;

    /* load names (tuple obj) */
    *paddr = pci + CI_NAMES_FIELD;
    retval = obj_loadFromImg(memspace, paddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco->co_names = (pPmTuple_t)pobj;

    /* load consts (tuple obj) assume it follows names */
    retval = obj_loadFromImg(memspace, paddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco->co_consts = (pPmTuple_t)pobj;

    /* start of bcode always follows consts */
    pco->co_codeaddr = *paddr;

    /* set addr to point one past end of img */
    *paddr = pci + size;

    *r_pco = (pPmObj_t)pco;
    return PM_RET_OK;
}


PmReturn_t
no_loadFromImg(PmMemSpace_t memspace, uint8_t **paddr, pPmObj_t *r_pno)
{
    PmReturn_t retval = PM_RET_OK;
    pPmNo_t pno = C_NULL;
    uint8_t *pchunk;

    /* allocate a code obj */
    retval = heap_getChunk(sizeof(PmNo_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pno = (pPmNo_t)pchunk;

    /* fill in the NO struct */
    OBJ_SET_TYPE(*pno, OBJ_TYPE_NOB);
    pno->no_argcount = mem_getByte(memspace, paddr);
    /* get index into native fxn table */
    pno->no_funcindx = (int16_t)mem_getWord(memspace, paddr);

    *r_pno = (pPmObj_t)pno;
    return PM_RET_OK;
}
