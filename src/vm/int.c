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
#define __FILE_ID__ 0x08
/**
 * Integer Object Type
 *
 * Integer object type operations.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/04   First.
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
int_dup(pPyObj_t pint, pPyObj_t * r_pint)
{
    PyReturn_t retval = PY_RET_OK;

    /* allocate new int */
    retval = heap_getChunk(sizeof(PyInt_t), (P_U8 *)r_pint);
    PY_RETURN_IF_ERROR(retval);

    /* copy value */
    (*r_pint)->od.od_type = OBJ_TYPE_INT;
    ((pPyInt_t)*r_pint)->val = ((pPyInt_t)pint)->val;
    return retval;
}


PyReturn_t
int_new(S32 n, pPyObj_t * r_pint)
{
    PyReturn_t retval = PY_RET_OK;

    /* if n is 0,1,-1, return global int */
    if (n == 0) 
    {
        *r_pint = PY_ZERO;
        return PY_RET_OK;
    }
    if (n == 1) 
    {
        *r_pint = PY_ONE;
        return PY_RET_OK;
    }
    if (n == -1) 
    {
        *r_pint = PY_NEGONE;
        return PY_RET_OK;
    }

    /* XXX search for int in pool? */

    /* else create and return new int obj */
    retval = heap_getChunk(sizeof(PyInt_t), (P_U8 *)r_pint);
    PY_RETURN_IF_ERROR(retval);
    (*r_pint)->od.od_type = OBJ_TYPE_INT;
    ((pPyInt_t)*r_pint)->val = n;
    return retval;
}


PyReturn_t
int_positive(pPyObj_t pobj, pPyObj_t * r_pint)
{    
    /* ensure it's an int */
    if (pobj->od.od_type != OBJ_TYPE_INT)
    {
        return PY_RET_EX_TYPE;
    }
    
    /* create new int obj */
    return int_new(((pPyInt_t)pobj)->val, r_pint);
}


PyReturn_t
int_negative(pPyObj_t pobj, pPyObj_t * r_pint)
{
    /* ensure it's an int */
    if (pobj->od.od_type != OBJ_TYPE_INT)
    {
        return PY_RET_EX_TYPE;
    }

    /* create new int obj */
    return int_new(-((pPyInt_t)pobj)->val, r_pint);
}


PyReturn_t
int_bitInvert(pPyObj_t pobj, pPyObj_t * r_pint)
{
    /* ensure it's an int */
    if (pobj->od.od_type != OBJ_TYPE_INT)
    {
        return PY_RET_EX_TYPE;
    }

    /* create new int obj */
    return int_new(~((pPyInt_t)pobj)->val, r_pint);
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
