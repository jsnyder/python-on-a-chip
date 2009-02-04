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
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/10   #75: Printing support (P.Adelt)
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/28   First.
 */

/***************************************************************
 * Constants
 **************************************************************/

/** Set to nonzero to enable string cache.  DO NOT REMOVE THE DEFINITION. */
#define USE_STRING_CACHE 1


/***************************************************************
 * Macros
 **************************************************************/

/**
 * Load string from image
 *
 * @param ms memoryspace paddr points to
 * @param paddr address in memoryspace of source string
 */
#define string_loadFromImg(ms, paddr, r_pstring) \
            string_create((ms), (paddr), (uint8_t)1, (r_pstring))

/**
 * Creates String object from character array in RAM
 *
 * @param paddr pointer to address of source string
 * @param r_pstring Return arg; addr of ptr to string
 */
#define string_new(paddr, r_pstring) \
            string_create(MEMSPACE_RAM, (paddr), (uint8_t)0, (r_pstring))

/***************************************************************
 * Types
 **************************************************************/

/**
 * String obj
 *
 * Null terminated array of chars.
 */
typedef struct PmString_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /** Length of string */
    uint16_t length;

#if USE_STRING_CACHE
    /** Ptr to next string in cache */
    struct PmString_s *next;
#endif                          /* USE_STRING_CACHE */

    /**
     * Null-term char array
     *
     * Use length 1 here so that string-alloc function can use
     * "sizeof(PmString_t) + len" and there will be room for the null-term
     */
    uint8_t val[1];
} PmString_t,
 *pPmString_t;


/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Creates a new String obj.
 * If n is zero, load from a String image.
 *      A string image has the following structure:
 *          -type:      int8 - OBJ_TYPE_STRING
 *          -length:    uint16 - number of bytes in the string
 *          -val:       uint8[] - array of chars with null term
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
 * @param   paddr ptr to ptr to null term character array or image.
 * @param   isimg if 0, create from C string;
 *          else load from image.
 * @param   Return arg; ptr to String obj
 * @return  Return status
 */
PmReturn_t string_create(PmMemSpace_t memspace, uint8_t const **paddr,
                         uint8_t isimg, pPmObj_t *r_pstring);

/**
 * Creates a new String object from a single character.
 *
 * @param   c the character to become the string
 * @param   r_psting Return arg; ptr to String obj
 * @return  Return status
 */
PmReturn_t string_newFromChar(uint8_t const c, pPmObj_t *r_pstring);

/**
 * Compares two String objects for equality.
 *
 * @param   pstr1 Ptr to first string
 * @param   pstr2 Ptr to second string
 * @return  C_SAME if the strings are equivalent, C_DIFFER otherwise
 */
int8_t string_compare(pPmString_t, pPmString_t);

#ifdef HAVE_PRINT
/**
 * Sends out a string object bytewise. Escaping and framing is configurable
 * via marshall.
 *
 * @param pobj Ptr to string object
 * @param marshall If 0, print out string as is. Otherwise escape unprintable
 *                 characters and surround string with single quotes.
 * @return Return status
 */
PmReturn_t string_print(pPmObj_t pstr, uint8_t marshall);
#endif /* HAVE_PRINT */

/**
 * Clears the string cache if one exists.
 * Called by heap_init()
 *
 * @return Return status
 */
PmReturn_t string_cacheInit(void);


/** Returns a pointer to the base of the string cache */
PmReturn_t string_getCache(pPmString_t **r_ppstrcache);
#endif /* __STRING_H__ */
