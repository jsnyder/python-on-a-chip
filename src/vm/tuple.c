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

#include "py.h"


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

PyReturn_t
tuple_loadFromImg(PyMemSpace_t memspace, P_U8 *paddr, pPyObj_t *r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    U8 i = 0;
    U8 n = 0;

    /* get num objs in tuple */
    n = mem_getByte(memspace, paddr);

    /* create empty tuple */
    retval = tuple_new(n, r_ptuple);
    PY_RETURN_IF_ERROR(retval);

    /* load the next n objs into tuple */
    for (i = 0; i < n; i++)
    {
        retval = obj_loadFromImg(memspace,
                                 paddr,
                                 (pPyObj_t *)&(((pPyTuple_t)*r_ptuple)->val[i])
                                );
        PY_RETURN_IF_ERROR(retval);
    }
    return PY_RET_OK;
}


PyReturn_t
tuple_new(U16 n, pPyObj_t * r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    U16 size = 0;

    /* this size tuple not yet supported */
    /* XXX for larger tuple, break into segments */
    if (n > 100)
    {
        return PY_RET_EX_SYS;
    }

    /* calc size of struct to hold tuple */
    size = sizeof(PyTuple_t) + (n * sizeof(pPyObj_t));

    /* allocate a tuple */
    retval = heap_getChunk(size, (P_U8 *)r_ptuple);
    PY_RETURN_IF_ERROR(retval);
    (*r_ptuple)->od.od_type = OBJ_TYPE_TUP;
    /* set the number of objs in the tuple */
    ((pPyTuple_t)*r_ptuple)->length = n;
    /*
     * no need to null the ptrs
     * because tuple is filled this
     */
    return retval;
}


PyReturn_t
tuple_copy(pPyObj_t ptup, pPyObj_t * r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    pPyTuple_t pnew = C_NULL;

    /* ensure type */
    if (ptup->od.od_type != OBJ_TYPE_TUP)
    {
        return PY_RET_EX_SYS;
    }

    /* duplicate src tuple */
    retval = heap_getChunk(ptup->od.od_size, (P_U8 *)&pnew);
    PY_RETURN_IF_ERROR(retval);

    mem_copy(MEMSPACE_RAM, (P_U8 *)&pnew, (P_U8 *)&ptup, ptup->od.od_size);
    *r_ptuple = (pPyObj_t)pnew;
    return PY_RET_OK;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
