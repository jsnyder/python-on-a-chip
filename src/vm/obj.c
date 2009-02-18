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
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/09   #75: Printing support (P.Adelt)
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
 * Functions
 **************************************************************/

PmReturn_t
obj_loadFromImg(PmMemSpace_t memspace,
                uint8_t const **paddr, pPmObj_t *r_pobj)
{
    PmReturn_t retval = PM_RET_OK;
    PmObj_t obj;


    /* Get the object descriptor */
    obj.od= (PmObjDesc_t)0x0000;
    OBJ_SET_TYPE(&obj, mem_getByte(memspace, paddr));

    switch (OBJ_GET_TYPE(&obj))
    {
        case OBJ_TYPE_NON:
            /* If it's the None object, return global None */
            *r_pobj = PM_NONE;
            break;

        case OBJ_TYPE_INT:
            /* Read an integer and create an integer object with the value */
            retval = int_new(mem_getInt(memspace, paddr), r_pobj);
            break;

#ifdef HAVE_FLOAT
        case OBJ_TYPE_FLT:
            /* Read a float and create an float object with the value */
            retval = float_new(mem_getFloat(memspace, paddr), r_pobj);
            break;
#endif /* HAVE_FLOAT */

        case OBJ_TYPE_STR:
            retval = string_loadFromImg(memspace, paddr, r_pobj);
            break;

        case OBJ_TYPE_TUP:
            retval = tuple_loadFromImg(memspace, paddr, r_pobj);
            break;

        case OBJ_TYPE_NIM:
            /* If it's a native code img, load into a code obj */
            retval = no_loadFromImg(memspace, paddr, r_pobj);
            break;

        case OBJ_TYPE_CIM:
            /* If it's a code img, load into a code obj */
            retval = co_loadFromImg(memspace, paddr, r_pobj);
            break;

        default:
            /* All other types should not be in an img obj */
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

    switch (OBJ_GET_TYPE(pobj))
    {
        case OBJ_TYPE_NON:
            /* None evaluates to false, so return true */
            return C_TRUE;

        case OBJ_TYPE_INT:
            /* Only the integer zero is false */
            return ((pPmInt_t)pobj)->val == 0;

#ifdef HAVE_FLOAT
        case OBJ_TYPE_FLT:
            /* The floats 0.0 and -0.0 are false */
            return (((pPmFloat_t)pobj)->val == 0.0) 
                || (((pPmFloat_t)pobj)->val == -0.0);
#endif /* HAVE_FLOAT */

        case OBJ_TYPE_STR:
            /* An empty string is false */
            return ((pPmString_t)pobj)->length == 0;

        case OBJ_TYPE_TUP:
            /* An empty tuple is false */
            return ((pPmTuple_t)pobj)->length == 0;

        case OBJ_TYPE_LST:
            /* An empty list is false */
            return ((pPmList_t)pobj)->length == 0;

        case OBJ_TYPE_DIC:
            /* An empty dict is false */
            return ((pPmDict_t)pobj)->length == 0;

        case OBJ_TYPE_BOOL:
            /* C int zero means false */
            return ((pPmBoolean_t)pobj)->val == 0;
            
        default:
            /*
             * The following types are always not false:
             * CodeObj, Function, Module, Class, ClassInstance.
             */
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

    switch (OBJ_GET_TYPE(pobj))
    {
        case OBJ_TYPE_TUP:
            /* Iterate over tuple to find item */
            for (i = 0; i < ((pPmTuple_t)pobj)->length; i++)
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
            if ((OBJ_GET_TYPE(pitem) != OBJ_TYPE_STR))
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

            /* Raise a ValueError if the string is more than 1 char */
            else if (((pPmString_t)pitem)->length != 1)
            {
                retval = PM_RET_EX_VAL;
                break;
            }

            /* Iterate over string to find char */
            c = ((pPmString_t)pitem)->val[0];
            for (i = 0; i < ((pPmString_t)pobj)->length; i++)
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
            for (i = 0; i < ((pPmList_t)pobj)->length; i++)
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

    /* Check if pointers are same */
    if (pobj1 == pobj2)
    {
        return C_SAME;
    }

    /* If types are different, objs must differ */
    if (OBJ_GET_TYPE(pobj1) != OBJ_GET_TYPE(pobj2))
    {
        return C_DIFFER;
    }

    /* Otherwise handle types individually */
    switch (OBJ_GET_TYPE(pobj1))
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
            /* #17: PyMite does not support Dict comparisons (yet) */
            return C_DIFFER;
    }

    /* All other types would need same pointer to be true */
    return C_DIFFER;
}


#ifdef HAVE_PRINT
PmReturn_t
obj_print(pPmObj_t pobj, uint8_t marshallString)
{
    PmReturn_t retval = PM_RET_OK;

    C_ASSERT(pobj != C_NULL);

    switch (OBJ_GET_TYPE(pobj))
    {
        case OBJ_TYPE_NON:
            if (marshallString)
            {
                plat_putByte('N');
                plat_putByte('o');
                plat_putByte('n');
                retval = plat_putByte('e');
            }
            break;
        case OBJ_TYPE_INT:
            retval = int_print(pobj);
            break;
#ifdef HAVE_FLOAT
        case OBJ_TYPE_FLT:
            retval = float_print(pobj);
            break;
#endif /* HAVE_FLOAT */
        case OBJ_TYPE_STR:
            retval = string_print(pobj, marshallString);
            break;
        case OBJ_TYPE_DIC:
            retval = dict_print(pobj);
            break;
        case OBJ_TYPE_LST:
            retval = list_print(pobj);
            break;
        case OBJ_TYPE_TUP:
            retval = tuple_print(pobj);
            break;

        case OBJ_TYPE_BOOL:
            if (((pPmBoolean_t)pobj)->val == C_TRUE)
            {
                plat_putByte('T');
                plat_putByte('r');
                plat_putByte('u');
            }
            else
            {
                plat_putByte('F');
                plat_putByte('a');
                plat_putByte('l');
                plat_putByte('s');
            }
            retval = plat_putByte('e');
            break;

        case OBJ_TYPE_COB:
        case OBJ_TYPE_MOD:
        case OBJ_TYPE_CLO:
        case OBJ_TYPE_FXN:
        case OBJ_TYPE_CLI:
        case OBJ_TYPE_CIM:
        case OBJ_TYPE_NIM:
        case OBJ_TYPE_NOB:
        case OBJ_TYPE_EXN:
        case OBJ_TYPE_SQI:
        case OBJ_TYPE_THR:
            if (marshallString)
            {
                retval = plat_putByte('\'');
                PM_RETURN_IF_ERROR(retval);
            }
            plat_putByte('<');
            plat_putByte('o');
            plat_putByte('b');
            plat_putByte('j');
            plat_putByte(' ');
            plat_putByte('t');
            plat_putByte('y');
            plat_putByte('p');
            plat_putByte('e');
            plat_putByte(' ');
            plat_putByte('0');
            plat_putByte('x');
            int_printHexByte(OBJ_GET_TYPE(pobj));
            plat_putByte(' ');
            plat_putByte('@');
            plat_putByte(' ');
            plat_putByte('0');
            plat_putByte('x');
            _int_printHex((int)pobj);
            retval = plat_putByte('>');
            if (marshallString)
            {
                retval = plat_putByte('\'');
            }
            break;

        default:
            /* Otherwise raise a TypeError */
            PM_RAISE(retval, PM_RET_EX_TYPE);
            break;
    }
    return retval;
}
#endif /* HAVE_PRINT */
