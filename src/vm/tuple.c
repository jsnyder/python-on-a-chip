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
#define __FILE_ID__ 0x13
/**
 * Tuple Object Type
 *
 * Tuple object type operations.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/28   First.
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
tuple_loadFromImg(PmMemSpace_t memspace, uint8_t **paddr, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    uint8_t i = 0;
    uint8_t n = 0;

    /* get num objs in tuple */
    n = mem_getByte(memspace, paddr);

    /* create empty tuple */
    retval = tuple_new(n, r_ptuple);
    PM_RETURN_IF_ERROR(retval);

    /* load the next n objs into tuple */
    for (i = 0; i < n; i++)
    {
        retval = obj_loadFromImg(memspace,
                                 paddr,
                                 (pPmObj_t *)&(((pPmTuple_t)*r_ptuple)->val[i])
                                );
        PM_RETURN_IF_ERROR(retval);
    }
    return PM_RET_OK;
}


PmReturn_t
tuple_new(uint16_t n, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t size = 0;

    /* this size tuple not yet supported */
    /* XXX for larger tuple, break into segments */
    if (n > 100)
    {
        return PM_RET_EX_SYS;
    }

    /* calc size of struct to hold tuple */
    size = sizeof(PmTuple_t) + (n * sizeof(pPmObj_t));

    /* allocate a tuple */
    retval = heap_getChunk(size, (uint8_t **)r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    OBJ_SET_TYPE(**r_ptuple, OBJ_TYPE_TUP);
    /* set the number of objs in the tuple */
    ((pPmTuple_t)*r_ptuple)->length = n;
    /*
     * no need to null the ptrs
     * because tuple is filled this
     */
    return retval;
}


PmReturn_t
tuple_copy(pPmObj_t ptup, pPmObj_t * r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    pPmTuple_t pnew = C_NULL;
    uint8_t *pchunk;
    uint8_t *pdest;
    uint8_t *psrc;

    /* ensure type */
    if (OBJ_GET_TYPE(*ptup) != OBJ_TYPE_TUP)
    {
        return PM_RET_EX_SYS;
    }

    /* duplicate src tuple */
    retval = heap_getChunk(OBJ_GET_SIZE(*ptup), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pnew = (pPmTuple_t)pchunk;

    pdest = (uint8_t *)pnew;
    psrc = (uint8_t *)ptup;
    mem_copy(MEMSPACE_RAM, &pdest, &psrc, OBJ_GET_SIZE(*ptup));
    *r_ptuple = (pPmObj_t)pnew;
    return PM_RET_OK;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
