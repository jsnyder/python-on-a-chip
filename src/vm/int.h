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

#ifndef __INT_H__
#define __INT_H__
/**
 * Integer Object Type
 *
 * Integer object type header.
 *
 * Log:
 *
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Integer obj
 *
 * 32b signed integer
 */
typedef struct PmInt_s
{
    /** object descriptor */
    PmObjDesc_t od;
    /** integer value */
    int32_t val;
} PmInt_t, *pPmInt_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a duplicate Integer object
 *
 * but let it be dynamic.
 * Created specifically for the index value in FOR_LOOP.
 *
 * @param   pint Pointer to int obj to duplicate.
 * @param   r_pint Return by ref, ptr to new int
 * @return  Return status
 */
PmReturn_t int_dup(pPmObj_t pint, pPmObj_t * r_pint);

/**
 * Create a new Integer object
 *
 * @param   n Value to assign int (signed 32-bit).
 * @param   r_pint Return by ref, ptr to new int
 * @return  Return status
 */
PmReturn_t int_new(int32_t val, pPmObj_t * r_pint);

/**
 * Implement the UNARY_POSITIVE bcode.
 *
 * Create a new int with the same value as the given int.
 *
 * @param   pobj Pointer to target object
 * @param   r_pint Return by ref, ptr to int
 */
PmReturn_t int_positive(pPmObj_t, pPmObj_t * r_pint);

/**
 * Implement the UNARY_NEGATIVE bcode.
 *
 * Create a new int with a value that is
 * the negative of the given int.
 *
 * @param   pobj Pointer to target object
 * @param   r_pint Return by ref, ptr to int
 * @return  Return status
 */
PmReturn_t int_negative(pPmObj_t pobj, pPmObj_t * r_pint);

/**
 * Implement the UNARY_INVERT bcode.
 *
 * Create a new int with a value that is
 * the bitwise inversion of the given int.
 *
 * @param   pobj Pointer to target object
 */
PmReturn_t int_bitInvert(pPmObj_t pobj, pPmObj_t * r_pint);

#endif /* __INT_H__ */
