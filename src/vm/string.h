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

#ifndef __STRING_H__
#define __STRING_H__
/**
 * String Object Type
 *
 * String object type header.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/28   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** Set to nonzero to enable string cache */
#define USE_STRING_CACHE 1


/***************************************************************
 * Macros
 **************************************************************/

/** 
 * load string from image
 *
 * @param ms memoryspace paddr points to
 * @param paddr address in memoryspace of source string
 */
#define string_loadFromImg(ms, paddr, r_pstring) \
            string_create((ms), (paddr), (U8)1, (r_pstring))

/** 
 * create string from UTF-8 string in RAM
 *
 * @param s address in RAM of source string
 * @param r_pstring Return arg; addr of ptr to string
 */
#define string_new(s, r_pstring) \
            string_create(MEMSPACE_RAM, (s), 0, (r_pstring))

/***************************************************************
 * Types
 **************************************************************/

/**
 * String obj
 *
 * Null terminated array of chars.
 */
typedef struct PyString_s
{
    /** object descriptor */
    PyObjDesc_t od;

    /** length of string */
    U8 length;

#if USE_STRING_CACHE
    /** ptr to next string in cache */
    struct PyString_s * next;
#endif /* USE_STRING_CACHE */

    /** 
     * Null-term char array
     *
     * Use length 1 here so that string-alloc function can use
     * "sizeof(PyString_t) + len" and there will be room for the null-term
     */
    U8          val[1];
} PyString_t, *pPyString_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a new String obj.
 * If n is zero, load from a String image.
 *      A string image has the following structure:
 *          -type:      S8 - OBJ_TYPE_STRING
 *          -length:    U8 - number of bytes in the string
 *          -string:    U8[] - array of chars with null term
 *
 * If n is not zero, create from a C string.
 * Return ptr to String obj.
 *
 * Obtain space for String from the heap.
 * Copy string from memspace.
 * Leave contents of paddr pointing one byte past end of str.
 *
 * THE PROGRAMMER SHOULD NOT CALL THIS FUNCTION DIRECTLY.
 * Instead, use one of the two macros string_loadFromImg()
 * or string_new().
 *
 * @param   memspace memory space where *paddr points
 * @param   paddr ptr to ptr to null term UTF-8 string or image.
 * @param   isimg if 0, create from C string;
 *          else load from image.
 * @param   Return arg; ptr to String obj
 * @return  Return status
 */
PyReturn_t string_create(PyMemSpace_t memspace,
                          P_U8 *paddr,
                          U8 isimg,
                          pPyObj_t *r_pstring);

/**
 * Create a new String object from a single character.
 *
 * @param   c the character to become the string
 * @param   r_psting Return arg; ptr to String obj
 * @return  Return status
 */
PyReturn_t string_newFromChar(U8 c, pPyObj_t *r_pstring);

/**
 * Compare two String objects for equality.
 *
 * @param   pstr1 Ptr to first string
 * @param   pstr2 Ptr to second string
 * @return  C_SAME if the strings are equivalent, C_DIFFER otherwise
 */
S8 string_compare(pPyString_t, pPyString_t);

/**
 * Create a copy of the given string obj.
 *
 * @param   pstr Ptr to source string.
 * @param   Return arg; Ptr to the new string obj.
 * @return  Return status
 */
PyReturn_t string_copy(pPyObj_t pstr, pPyObj_t *r_pstring);


#endif /* __STRING_H__ */
