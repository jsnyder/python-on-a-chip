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
#define __FILE_ID__ 0x02
/**
 * Dict Object Type
 *
 * Dict object type operations.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/30   First.
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
dict_new(pPmObj_t * r_pdict)
{
    PmReturn_t retval = PM_RET_OK;
    pPmDict_t pdict = C_NULL;

    /* allocate a dict */
    retval = heap_getChunk(sizeof(PmDict_t), (uint8_t **)r_pdict);
    PM_RETURN_IF_ERROR(retval);

    /* init dict fields */
    pdict = (pPmDict_t)*r_pdict;
    OBJ_SET_TYPE(*pdict, OBJ_TYPE_DIC);
    pdict->length = 0;
    retval = seglist_new(&pdict->d_keys);
    PM_RETURN_IF_ERROR(retval);
    retval = seglist_new(&pdict->d_vals);
    return retval;
}


PmReturn_t
dict_clear(pPmObj_t pdict)
{
    PmReturn_t retval = PM_RET_OK;

    C_ASSERT(pdict != C_NULL);

    /* Raise TypeError if arg is not a dict */
    if (OBJ_GET_TYPE(*pdict) != OBJ_TYPE_DIC)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* clear length */
    ((pPmDict_t)pdict)->length = 0;

    /* clear the keys and values seglists if needed */
    if (((pPmDict_t)pdict)->d_keys != C_NULL)
    {
        PM_RETURN_IF_ERROR(seglist_clear(((pPmDict_t)pdict)->d_keys));
        retval = seglist_clear(((pPmDict_t)pdict)->d_vals);
    }
    return retval;
}


/*
 * Sets a value in the dict using the given key.
 *
 * Scans dict for the key.  If key val found, replace old
 * with new val.  If no key found, add key/val pair to dict.
 */
PmReturn_t
dict_setItem(pPmObj_t pdict, pPmObj_t pkey, pPmObj_t pval)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t indx = 0;

    C_ASSERT(pdict != C_NULL);
    C_ASSERT(pkey != C_NULL);
    C_ASSERT(pval != C_NULL);

    /* if it's not a dict, raise TypeError */
    if (OBJ_GET_TYPE(*pdict) != OBJ_TYPE_DIC)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* XXX if key is not hashable, raise TypeError */
    /* XXX if key's hash hasn't been calculated */

    /* check for matching key */
    retval = seglist_findEqual(((pPmDict_t)pdict)->d_keys, pkey, &indx);

    /* if found a matching key, replace val obj */
    if (retval == PM_RET_OK)
    {
        retval = seglist_setItem(((pPmDict_t)pdict)->d_vals, pval, indx);
        return retval;
    }

    /* if no matching key, insert the key,val pair */
    if (retval == PM_RET_NO)
    {
        retval = seglist_insertItem(((pPmDict_t)pdict)->d_keys, pkey, 0);
        PM_RETURN_IF_ERROR(retval);
        retval = seglist_insertItem(((pPmDict_t)pdict)->d_vals, pval, 0);
        PM_RETURN_IF_ERROR(retval);
        ((pPmDict_t)pdict)->length++;
        return PM_RET_OK;
    }
    return retval;
}


PmReturn_t
dict_getItem(pPmObj_t pdict, pPmObj_t pkey, pPmObj_t * r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    int16_t indx = 0;

    C_ASSERT(pdict != C_NULL);

    /* if it's not a dict, raise TypeError */
    if (OBJ_GET_TYPE(*pdict) != OBJ_TYPE_DIC)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* if dict is empty, raise KeyError */
    if (((pPmDict_t)pdict)->length <= 0)
    {
        PM_RAISE(retval, PM_RET_EX_KEY);
        return retval;
    }

    /* check for matching key */
    retval = seglist_findEqual(((pPmDict_t)pdict)->d_keys, pkey, &indx);
    /* if key not found, raise KeyError */
    if (retval == PM_RET_NO)
    {
        PM_RAISE(retval, PM_RET_EX_KEY);
    }
    /* return any other error */
    PM_RETURN_IF_ERROR(retval);

    /* key was found, get obj from vals */
    retval = seglist_getItem(((pPmDict_t)pdict)->d_vals, indx, r_pobj);
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
