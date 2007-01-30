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
#define __FILE_ID__ 0x0B
/**
 * List Object Type
 *
 * List object type operations.
 *
 * Log
 * ---
 *
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/09   #75: Printing support (P.Adelt)
 * 2007/01/09   #75: implemented list_remove() and list_index() (P.Adelt)
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/22   First.
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
list_append(pPmObj_t plist, pPmObj_t pobj)
{
    PmReturn_t retval = PM_RET_STUB;

    C_ASSERT(plist != C_NULL);
    C_ASSERT(pobj != C_NULL);

    /* if plist is not a list, raise a TypeError exception */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* append object to list */
    retval = seglist_appendItem(((pPmList_t)plist)->val, pobj);
    PM_RETURN_IF_ERROR(retval);

    /* incr list length */
    ((pPmList_t)plist)->length++;

    return retval;
}


PmReturn_t
list_getItem(pPmObj_t plist, int16_t index, pPmObj_t *r_pobj)
{
    PmReturn_t retval;

    /* If it's not a list, raise TypeError */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Adjust the index */
    if (index < 0)
    {
        index += ((pPmList_t)plist)->length;
    }

    /* Check the bounds of the index */
    if ((index < 0) || (index >= ((pPmList_t)plist)->length))
    {
        PM_RAISE(retval, PM_RET_EX_INDX);
        return retval;
    }

    /* get item from seglist */
    retval = seglist_getItem(((pPmList_t)plist)->val, index, r_pobj);
    return retval;
}


PmReturn_t
list_insert(pPmObj_t plist, int16_t index, pPmObj_t pobj)
{
    PmReturn_t retval;
    int16_t len;

    C_ASSERT(plist != C_NULL);
    C_ASSERT(pobj != C_NULL);

    /* Raise a TypeError if plist is not a List */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        retval = PM_RET_EX_TYPE;
        PM_RETURN_IF_ERROR(retval);
    }

    /* Adjust an out-of-bounds index value */
    len = ((pPmList_t)plist)->length;
    if (index < 0)
    {
        index += len;
    }
    if (index < 0)
    {
        index = 0;
    }
    if (index > len)
    {
        index = len;
    }

    /* Insert the item in the container */
    retval = seglist_insertItem(((pPmList_t)plist)->val, pobj, index);
    PM_RETURN_IF_ERROR(retval);

    /* Increment the length of this list */
    ((pPmList_t)plist)->length++;
    return retval;
}


PmReturn_t
list_new(pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    pPmList_t plist = C_NULL;

    /* allocate a list */
    retval = heap_getChunk(sizeof(PmList_t), (uint8_t **)r_pobj);
    PM_RETURN_IF_ERROR(retval);

    /* set list type, empty the contents */
    plist = (pPmList_t)*r_pobj;
    OBJ_SET_TYPE(*plist, OBJ_TYPE_LST);
    plist->length = 0;
    /* create empty seglist */
    retval = seglist_new(&plist->val);
    return retval;
}


PmReturn_t
list_copy(pPmObj_t pobj, pPmObj_t *r_pobj)
{
    return list_replicate(pobj, 1, r_pobj);
}


PmReturn_t
list_replicate(pPmObj_t psrclist,
               int16_t n,
               pPmObj_t *r_pnewlist)
{
    PmReturn_t retval = PM_RET_OK;
    int8_t i = 0;
    int8_t j = 0;
    int8_t length = 0;
    pPmObj_t pitem = C_NULL;

    C_ASSERT(psrclist != C_NULL);
    C_ASSERT(r_pnewlist != C_NULL);

    /* If first arg is not a list, raise TypeError */
    if (OBJ_GET_TYPE(*psrclist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    length = ((pPmList_t)psrclist)->length;

    /* allocate new list */
    retval = list_new(r_pnewlist);
    PM_RETURN_IF_ERROR(retval);

    /* copy srclist the designated number of times */
    for (i = n; i > 0; i--)
    {
        /* iterate over the length of srclist */
        for (j = 0; j < length; j++)
        {
            retval = list_getItem(psrclist, j, &pitem);
            PM_RETURN_IF_ERROR(retval);
            retval = list_append(*r_pnewlist, pitem);
            PM_RETURN_IF_ERROR(retval);
        }
    }
    return retval;
}


PmReturn_t
list_setItem(pPmObj_t plist, int16_t index, pPmObj_t pobj)
{
    PmReturn_t retval;
    
    /* If it's not a list, raise TypeError */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Adjust the index */
    if (index < 0)
    {
        index += ((pPmList_t)plist)->length;
    }

    /* Check the bounds of the index */
    if ((index < 0) || (index >= ((pPmList_t)plist)->length))
    {
        PM_RAISE(retval, PM_RET_EX_INDX);
        return retval;
    }

    /* Set the item */    
    retval = seglist_setItem(((pPmList_t)plist)->val, pobj, index);
    return retval;
}

PmReturn_t
list_remove(pPmObj_t plist, pPmObj_t item)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t index;

    /* If it's not a list, raise TypeError */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    retval = list_index(plist, item, &index);
    PM_RETURN_IF_ERROR(retval);
    
    retval = seglist_removeItem(((pPmList_t)plist)->val, index);
    ((pPmList_t)plist)->length--;
    return retval;

}

PmReturn_t
list_index(pPmObj_t plist, pPmObj_t pitem, uint16_t* r_index)
{
    PmReturn_t retval = PM_RET_OK;
    pSeglist_t pseglist;
    pPmObj_t pobj;
    uint16_t index;
    
    /* If it's not a list, raise TypeError */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    
    pseglist = ((pPmList_t)plist)->val;
    
    for (index = 0; index < pseglist->sl_length; index++)
    {
        retval = seglist_getItem(pseglist, index, &pobj);
        PM_RETURN_IF_ERROR(retval);
        if (obj_compare(pobj, pitem) == C_SAME)
        {
            *r_index = index;
            return PM_RET_OK;
        }
    }

    return PM_RET_EX_VAL;
}

#ifdef HAVE_PRINT
PmReturn_t
list_print(pPmObj_t plist)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t index;
    pSeglist_t vals;
    pPmObj_t pobj1;

    C_ASSERT(plist != C_NULL);

    /* if it's not a list, raise TypeError */
    if (OBJ_GET_TYPE(*plist) != OBJ_TYPE_LST)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    
    plat_putByte('[');
    
    vals = ((pPmList_t)plist)->val;

    /* if dict is empty, raise KeyError */
    for (index = 0; index < ((pPmList_t)plist)->length; index++)
    {
        if (index != 0)
        {
            plat_putByte(',');
            plat_putByte(' ');
        }
        retval = seglist_getItem(vals, index, &pobj1);
        PM_RETURN_IF_ERROR(retval);
        retval = obj_print(pobj1, 1);
        PM_RETURN_IF_ERROR(retval);
    }

    return plat_putByte(']');
}
#endif /* HAVE_PRINT */


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
