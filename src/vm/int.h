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
 * 2007/01/09   #75: Printing support (P.Adelt)
 * 2002/05/04   First.
 */

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
    /** Object descriptor */
    PmObjDesc_t od;

    /** Integer value */
    int32_t val;
} PmInt_t,
 *pPmInt_t;


/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Creates a duplicate Integer object
 *
 * Created specifically for the index value in FOR_LOOP.
 *
 * @param   pint Pointer to int obj to duplicate.
 * @param   r_pint Return by ref, ptr to new int
 * @return  Return status
 */
PmReturn_t int_dup(pPmObj_t pint, pPmObj_t *r_pint);

/**
 * Creates a new Integer object
 *
 * @param   n Value to assign int (signed 32-bit).
 * @param   r_pint Return by ref, ptr to new int
 * @return  Return status
 */
PmReturn_t int_new(int32_t val, pPmObj_t *r_pint);

/**
 * Implements the UNARY_POSITIVE bcode.
 *
 * Creates a new int with the same value as the given int.
 *
 * @param   pobj Pointer to target object
 * @param   r_pint Return by ref, ptr to int
 */
PmReturn_t int_positive(pPmObj_t, pPmObj_t *r_pint);

/**
 * Implements the UNARY_NEGATIVE bcode.
 *
 * Creates a new int with a value that is the negative of the given int.
 *
 * @param   pobj Pointer to target object
 * @param   r_pint Return by ref, ptr to int
 * @return  Return status
 */
PmReturn_t int_negative(pPmObj_t pobj, pPmObj_t *r_pint);

/**
 * Implements the UNARY_INVERT bcode.
 *
 * Creates a new int with a value that is
 * the bitwise inversion of the given int.
 *
 * @param   pobj Pointer to target object
 */
PmReturn_t int_bitInvert(pPmObj_t pobj, pPmObj_t *r_pint);

#ifdef HAVE_PRINT
/**
 * Sends out an integer object in decimal notation with MSB first.
 * The number is preceded with a "-" when necessary.
 *
 * @param pObj Ptr to int object
 * @return Return status
 */
PmReturn_t int_print(pPmObj_t pint);

/**
 * Prints the byte in ascii-coded hexadecimal out the platform output
 *
 * @param b Byte to print
 */
PmReturn_t int_printHexByte(uint8_t b);

/**
 * Prints the integer in ascii-coded hexadecimal out the platform output
 *
 * @param n Integer to print
 */
PmReturn_t _int_printHex(int32_t n);

/**
 * Prints the Int object in ascii-coded hexadecimal out the platform output
 *
 * @param pint Pointer to Int object
 */
PmReturn_t int_printHex(pPmObj_t pint);
#endif /* HAVE_PRINT */

/**
 * Returns by reference an integer that is x raised to the power of y.
 *
 * @param x The integer base
 * @param y The integer exponent
 * @param r_pn The return value of x ** y
 * @return Return status
 */
PmReturn_t int_pow(pPmObj_t px, pPmObj_t py, pPmObj_t *r_pn);

#endif /* __INT_H__ */
