#ifndef __STRING_H__
#define __STRING_H__
/**
 * String Object Type
 *
 * String object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        string.h
 *
 * Log:
 *
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
            string_create((ms), (paddr), 1, (r_pstring))

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
    S8 length;

#if USE_STRING_CACHE
    /** ptr to next string in cache */
    struct PyString_s * next;
#endif /* USE_STRING_CACHE */

    /** null-term char array */
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
                          P_S8 * paddr,
                          S8 isimg,
                          pPyObj_t * r_pstring);

/**
 * Compare two String objects for equality.
 *
 * @param   pstr1 Ptr to first string
 * @param   pstr2 Ptr to second string
 * @return  C_TRUE if both objs are strings and are equal,
 *          C_FALSE otherwise.
 */
S8 string_isEqual(pPyObj_t, pPyObj_t);

/**
 * Create a copy of the given string obj.
 *
 * @param   pstr Ptr to source string.
 * @param   Return arg; Ptr to the new string obj.
 * @return  Return status
 */
PyReturn_t string_copy(pPyObj_t pstr, pPyObj_t * r_pstring);


#endif /* __STRING_H__ */