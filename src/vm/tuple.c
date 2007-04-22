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
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
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

/* The follwing value should match that in pmImgCreator.py */
#define MAX_TUPLE_LEN 253


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
tuple_loadFromImg(PmMemSpace_t memspace,
                  uint8_t const **paddr, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    uint8_t i = (uint8_t)0;
    uint8_t n = (uint8_t)0;

    /* get num objs in tuple */
    n = mem_getByte(memspace, paddr);

    /* create empty tuple */
    retval = tuple_new(n, r_ptuple);
    PM_RETURN_IF_ERROR(retval);

    /* load the next n objs into tuple */
    for (i = (uint8_t)0; i < n; i++)
    {
        retval = obj_loadFromImg(memspace,
                                 paddr,
                                 (pPmObj_t *)&(((pPmTuple_t)*r_ptuple)->
                                               val[i]));
        PM_RETURN_IF_ERROR(retval);
    }
    return PM_RET_OK;
}


PmReturn_t
tuple_new(uint16_t n, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t size = 0;

    /* Raise a SystemError for a Tuple that is too large */
    if (n > MAX_TUPLE_LEN)
    {
        PM_RAISE(retval, PM_RET_EX_SYS);
        return retval;
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
tuple_copy(pPmObj_t ptup, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    pPmTuple_t pnew = C_NULL;
    uint8_t *pchunk;
    uint8_t *pdest;
    uint8_t const *psrc;

    /* ensure type */
    if (OBJ_GET_TYPE(*ptup) != OBJ_TYPE_TUP)
    {
        PM_RAISE(retval, PM_RET_EX_SYS);
        return retval;
    }

    /* duplicate src tuple */
    retval = heap_getChunk(OBJ_GET_SIZE(*ptup), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pnew = (pPmTuple_t)pchunk;

    pdest = (uint8_t *)pnew;
    psrc = (uint8_t const *)ptup;
    mem_copy(MEMSPACE_RAM, &pdest, &psrc, OBJ_GET_SIZE(*ptup));
    *r_ptuple = (pPmObj_t)pnew;
    return PM_RET_OK;
}


PmReturn_t
tuple_getItem(pPmObj_t ptup, int16_t index, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;

    /* Adjust for negative index */
    if (index < 0)
    {
        index += ((pPmTuple_t)ptup)->length;
    }

    /* Raise IndexError if index is out of bounds */
    if ((index < 0) || (index > ((pPmTuple_t)ptup)->length))
    {
        PM_RAISE(retval, PM_RET_EX_INDX);
    }

    /* Get the tuple item */
    *r_pobj = ((pPmTuple_t)ptup)->val[index];

    return retval;
}

#ifdef HAVE_PRINT
PmReturn_t
tuple_print(pPmObj_t ptup)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t index;

    C_ASSERT(ptup != C_NULL);

    /* if it's not a tuple, raise TypeError */
    if (OBJ_GET_TYPE(*ptup) != OBJ_TYPE_TUP)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    plat_putByte('(');

    for (index = 0; index < ((pPmTuple_t)ptup)->length; index++)
    {
        if (index != 0)
        {
            plat_putByte(',');
            plat_putByte(' ');
        }
        retval = obj_print(((pPmTuple_t)ptup)->val[index], 1);
        PM_RETURN_IF_ERROR(retval);
    }

    return plat_putByte(')');
}
#endif /* HAVE_PRINT */

/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
