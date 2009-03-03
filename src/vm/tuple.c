/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

 
#undef __FILE_ID__
#define __FILE_ID__ 0x13


/**
 * Tuple Object Type
 *
 * Tuple object type operations.
 */

 
#include "pm.h"


/* The follwing value should match that in pmImgCreator.py */
#define MAX_TUPLE_LEN 253


PmReturn_t
tuple_loadFromImg(PmMemSpace_t memspace,
                  uint8_t const **paddr, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    uint8_t i = (uint8_t)0;
    uint8_t n = (uint8_t)0;

    /* Get num objs in tuple */
    n = mem_getByte(memspace, paddr);

    /* Create empty tuple */
    retval = tuple_new(n, r_ptuple);
    PM_RETURN_IF_ERROR(retval);

    /* Load the next n objs into tuple */
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

    /* Calc size of struct to hold tuple */
    size = sizeof(PmTuple_t) + (n * sizeof(pPmObj_t));

    /* Allocate a tuple */
    retval = heap_getChunk(size, (uint8_t **)r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    OBJ_SET_TYPE(*r_ptuple, OBJ_TYPE_TUP);

    /* Set the number of objs in the tuple */
    ((pPmTuple_t)*r_ptuple)->length = n;

    /* No need to null the ptrs because they are set by the caller */
    return retval;
}


PmReturn_t
tuple_replicate(pPmObj_t ptup, int16_t n, pPmObj_t *r_ptuple)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t length;
    int16_t i;
    int16_t j;

    /* Raise TypeError if object is not a Tuple */
    if (OBJ_GET_TYPE(ptup) != OBJ_TYPE_TUP)
    {
        PM_RAISE(retval, PM_RET_EX_SYS);
        return retval;
    }

    C_ASSERT(n >= 0);

    /* Allocate the new tuple */
    length = ((pPmTuple_t)ptup)->length;
    retval = tuple_new(length * n, r_ptuple);
    PM_RETURN_IF_ERROR(retval);

    /* Copy src tuple the designated number of times */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < length; j++)
        {
            ((pPmTuple_t)*r_ptuple)->val[length*i + j] =
                ((pPmTuple_t)ptup)->val[j];
        }
    }
    return retval;
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

    /* If it's not a tuple, raise TypeError */
    if (OBJ_GET_TYPE(ptup) != OBJ_TYPE_TUP)
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
