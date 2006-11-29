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
#define __FILE_ID__ 0x0F
/**
 * Object Type
 *
 * Object type operations.
 *
 * Log
 * ---
 *
 * 2006/09/20   #35: Macroize all operations on object descriptors
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
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
obj_loadFromImg(PmMemSpace_t memspace, uint8_t **paddr, pPmObj_t * r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    PmObjDesc_t od;

    /* get the object descriptor */
    od.od_type = (PmType_t)mem_getByte(memspace, paddr);

    switch (od.od_type)
    {
        /* if it's the None object, return global None */
        case OBJ_TYPE_NON:
            /* make sure *paddr gets incremented */
            *r_pobj = PM_NONE;
            break;

        /* if it's a simple type */
        case OBJ_TYPE_INT:
        case OBJ_TYPE_FLT:
            /* allocate simple obj */
            retval = heap_getChunk(sizeof(PmInt_t), (uint8_t **)r_pobj);
            PM_RETURN_IF_ERROR(retval);

            /* Set the object's type */
            OBJ_SET_TYPE(**r_pobj, od.od_type);

            /* Read in the object's value (little endian) */
            ((pPmInt_t)*r_pobj)->val = mem_getInt(memspace, paddr);
            break;

        case OBJ_TYPE_STR:
            retval = string_loadFromImg(memspace, paddr, r_pobj);
            break;

        case OBJ_TYPE_TUP:
            retval = tuple_loadFromImg(memspace, paddr, r_pobj);
            break;

        /* if it's a native code img, load into a code obj */
        case OBJ_TYPE_NIM:
            retval = no_loadFromImg(memspace, paddr, r_pobj);
            break;

        /* if it's a code img, load into a code obj */
        case OBJ_TYPE_CIM:
            retval = co_loadFromImg(memspace, paddr, r_pobj);
            break;

        /* All other types should not be in an img obj */
        default:
            PM_RAISE(retval, PM_RET_EX_SYS);
            break;
    }
    return retval;
}


/* Returns true if the obj is false */
int8_t
obj_isFalse(pPmObj_t pobj)
{
    C_ASSERT(pobj != C_NULL);

    /* return true if it's None */
    switch (OBJ_GET_TYPE(*pobj))
    {
        /* None evaluates to false */
        case OBJ_TYPE_NON:
            return C_FALSE;

        /* Only the integer zero is false */
        case OBJ_TYPE_INT:
            return ((pPmInt_t)pobj)->val == 0;

        /* An empty string is false */
        case OBJ_TYPE_STR:
            return ((pPmString_t)pobj)->length == 0;

        /* An empty tuple is false */
        case OBJ_TYPE_TUP:
            return ((pPmTuple_t)pobj)->length == 0;

        /* An empty list is false */
        case OBJ_TYPE_LST:
            return ((pPmList_t)pobj)->length == 0;

        /* An empty dict is false */
        case OBJ_TYPE_DIC:
            return ((pPmDict_t)pobj)->length == 0;

        /*
         * The following types are always not false:
         * CodeObj, Function, Module, Class, ClassInstance.
         */
        default:
            return C_FALSE;
    }
}


/* Returns true if the item is in the container object */
PmReturn_t
obj_isIn(pPmObj_t pobj, pPmObj_t pitem)
{
    PmReturn_t retval = PM_RET_NO;
    pPmObj_t ptestItem;
    int16_t i;
    uint8_t c;

    switch(OBJ_GET_TYPE(*pobj))
    {
        case OBJ_TYPE_TUP:
            /* Iterate over tuple to find item */
            for (i=0; i<((pPmTuple_t)pobj)->length; i++)
            {
                PM_RETURN_IF_ERROR(tuple_getItem(pobj, i, &ptestItem));

                if (obj_compare(pitem, ptestItem) == C_SAME)
                {
                    retval = PM_RET_OK;
                    break;
                }
            }
            break;

        case OBJ_TYPE_STR:
            /* Raise a TypeError if item is not a string */
            if ((OBJ_GET_TYPE(*pitem) != OBJ_TYPE_STR))
            {
                retval = PM_RET_EX_TYPE;
                break;
            }

            /* Empty string is alway present */
            if (((pPmString_t)pitem)->length == 0)
            {
                retval = PM_RET_OK;
                break;
            }

            /* Raise a ValueError exception if the string is more than 1 char */
            else if (((pPmString_t)pitem)->length != 1)
            {
                retval = PM_RET_EX_VAL;
                break;
            }

            /* Iterate over string to find char */
            c = ((pPmString_t)pitem)->val[0];
            for (i=0; i<((pPmString_t)pobj)->length; i++)
            {
                if (c == ((pPmString_t)pobj)->val[i])
                {
                    retval = PM_RET_OK;
                    break;
                }
            }
            break;

        case OBJ_TYPE_LST:
            /* Iterate over list to find item */
            for (i=0; i<((pPmList_t)pobj)->length; i++)
            {
                PM_RETURN_IF_ERROR(list_getItem(pobj, i, &ptestItem));

                if (obj_compare(pitem, ptestItem) == C_SAME)
                {
                    retval = PM_RET_OK;
                    break;
                }
            }
            break;

        case OBJ_TYPE_DIC:
            /* Check if the item is one of the keys of the dict */
            retval = dict_getItem(pobj, pitem, &ptestItem);
            if (retval == PM_RET_EX_KEY)
            {
                retval = PM_RET_NO;
            }
            break;

        default:
            retval = PM_RET_EX_TYPE;
            break;
    }

    return retval;
}


int8_t
obj_compare(pPmObj_t pobj1, pPmObj_t pobj2)
{
    C_ASSERT(pobj1 != C_NULL);
    C_ASSERT(pobj2 != C_NULL);

    /* check if pointers are same */
    if (pobj1 == pobj2)
    {
        return C_SAME;
    }

    /* if types are different, objs must differ */
    if (OBJ_GET_TYPE(*pobj1) != OBJ_GET_TYPE(*pobj2))
    {
        return C_DIFFER;
    }

    /* else handle types individually */
    switch (OBJ_GET_TYPE(*pobj1))
    {
        case OBJ_TYPE_NON:
            return C_SAME;

        case OBJ_TYPE_INT:
        case OBJ_TYPE_FLT:
            return ((pPmInt_t)pobj1)->val ==
                   ((pPmInt_t)pobj2)->val ? C_SAME : C_DIFFER;

        case OBJ_TYPE_STR:
            return string_compare((pPmString_t)pobj1, (pPmString_t)pobj2);

        case OBJ_TYPE_TUP:
        case OBJ_TYPE_LST:
            return seq_compare(pobj1, pobj2);

        case OBJ_TYPE_DIC:
        default:
            /* XXX fix these */
            return C_DIFFER;
    }

    /* all other types would need same pointer to be true */
    return C_DIFFER;
}


/*
 * Compares two sequence objects
 * Assumes both objects are of same type (guaranteed by obj_compare)
 */
int8_t
seq_compare(pPmObj_t pobj1, pPmObj_t pobj2)
{
    int16_t l1;
    int16_t l2;
    pPmObj_t pa;
    pPmObj_t pb;
    PmReturn_t retval;
    int8_t retcompare;

    /* Get the lengths of supported types or return differ */
    if (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_TUP)
    {
        l1 = ((pPmTuple_t)pobj1)->length;
        l2 = ((pPmTuple_t)pobj2)->length;
    }
    else if (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_LST)
    {
        l1 = ((pPmList_t)pobj2)->length;
        l2 = ((pPmList_t)pobj2)->length;
    }
    else
    {
        return C_DIFFER;
    }

    /* Return if the lengths differ */
    if (l1 != l2)
    {
        return C_DIFFER;
    }

    /* Compare all items in the sequences */
    while (--l1 >= 0)
    {
        retval = seq_getSubscript(pobj1, l1, &pa);
        if (retval != PM_RET_OK)
        {
            return C_DIFFER;
        }
        retval = seq_getSubscript(pobj2, l1, &pb);
        if (retval != PM_RET_OK)
        {
            return C_DIFFER;
        }
        retcompare = obj_compare(pa, pb);
        if (retcompare != C_SAME)
        {
            return retcompare;
        }
    }

    return C_SAME;
}


/* Returns the object sequence[index] */
PmReturn_t
seq_getSubscript(pPmObj_t pobj, int16_t index, pPmObj_t *r_pobj)
{
    PmReturn_t retval;
    uint8_t c;

    switch (OBJ_GET_TYPE(*pobj))
    {
        case OBJ_TYPE_STR:
            /* Adjust for negative index */
            if (index < 0)
            {
                index += ((pPmString_t)pobj)->length;
            }

            /* Raise IndexError if index is out of bounds */
            if ((index < 0) || (index > ((pPmString_t)pobj)->length))
            {
                PM_RAISE(retval, PM_RET_EX_INDX);
                break;
            }

            /* Get the character from the string */
            c = ((pPmString_t)pobj)->val[index];

            /* Create a new string from the character */
            retval = string_newFromChar(c, r_pobj);
            break;

        case OBJ_TYPE_TUP:
            /* Get the tuple item */
            retval = tuple_getItem(pobj, index, r_pobj);
            break;

        case OBJ_TYPE_LST:
            /* Get the list item */
            retval = list_getItem(pobj, index, r_pobj);
            break;

        default:
            /* Raise TypeError, unsubscriptable object */
            PM_RAISE(retval, PM_RET_EX_TYPE);
            break;
    }

    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
