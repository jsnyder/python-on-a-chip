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

    /* if either obj is null, raise ValueError exception */
    if ((plist == C_NULL) || (pobj == C_NULL))
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    /* if pobj1 is not a list, raise a TypeError exception */
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
    /* XXX test for max length? */

    return retval;
}


PmReturn_t
list_getItem(pPmObj_t plist, int16_t index, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_STUB;
    int16_t segnum = 0;
    int16_t segindx = 0;

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

    /* convert list index into seglist index */
    segnum = index / SEGLIST_OBJS_PER_SEG;
    segindx = index % SEGLIST_OBJS_PER_SEG;

    /* get item from seglist */
    retval = seglist_getItem(((pPmList_t)plist)->val,
                             segnum,
                             segindx,
                             r_pobj);
    return retval;
}


PmReturn_t
list_insert(pPmObj_t plist, pPmObj_t pobj, int8_t index)
{
    PmReturn_t retval = PM_RET_STUB;
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

    /* exception if any args are null */
    if ((psrclist == C_NULL)
        || (r_pnewlist == C_NULL))
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

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
list_setItem(pPmObj_t pobj1, int16_t index, pPmObj_t pobj2)
{
    PmReturn_t retval = PM_RET_STUB;
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
