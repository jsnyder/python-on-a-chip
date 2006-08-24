#ifndef __INT_H__
#define __INT_H__
/**
 * Integer Object Type
 *
 * Integer object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        int.h
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
typedef struct PyInt_s
{
    /** object descriptor */
    PyObjDesc_t od;
    /** integer value */
    S32         val;
} PyInt_t, *pPyInt_t;


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
PyReturn_t int_dup(pPyObj_t pint, pPyObj_t * r_pint);

/**
 * Create a new Integer object
 *
 * @param   n Value to assign int (signed 32-bit).
 * @param   r_pint Return by ref, ptr to new int
 * @return  Return status
 */
PyReturn_t int_new(S32 val, pPyObj_t * r_pint);

/**
 * Implement the UNARY_POSITIVE bcode.
 *
 * Create a new int with the same value as the given int.
 *
 * @param   pobj Pointer to target object
 * @param   r_pint Return by ref, ptr to int
 */
PyReturn_t int_positive(pPyObj_t, pPyObj_t * r_pint);

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
PyReturn_t int_negative(pPyObj_t pobj, pPyObj_t * r_pint);

/**
 * Implement the UNARY_INVERT bcode.
 *
 * Create a new int with a value that is
 * the bitwise inversion of the given int.
 *
 * @param   pobj Pointer to target object
 */
PyReturn_t int_bitInvert(pPyObj_t pobj, pPyObj_t * r_pint);

#endif /* __INT_H__ */
