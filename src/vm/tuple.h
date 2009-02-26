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

#ifndef __TUPLE_H__
#define __TUPLE_H__

/**
 * Tuple Object Type
 *
 * Tuple object type header.
 *
 * Log
 * ---
 *
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/28   First.
 */

/***************************************************************
 * Types
 **************************************************************/

/**
 * Tuple obj
 *
 * Immutable ordered sequence.  Contains array of ptrs to objs.
 */
typedef struct PmTuple_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /**
     * Length of tuple
     * I don't expect a tuple to ever exceed 255 elements,
     * but if I set this type to int8_t, a 0-element tuple
     * is too small to be allocated.
     */
    int16_t length;

    /** Array of ptrs to objs */
    pPmObj_t val[0];
} PmTuple_t,
 *pPmTuple_t;


#define tuple_copy(src, dest) tuple_replicate((src), 1, (dest))

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Creates a Tuple by loading a tuple image from memory.
 *
 * Obtain space for tuple from the heap.
 * Load all objs within the tuple img.
 * Leave contents of paddr pointing one byte past end of
 * last obj in tuple.
 *
 * The tuple image has the following structure:
 *      -type:      S8 - OBJ_TYPE_TUPLE
 *      -length     U8 - N number of objects in the tuple.
 *                  N objects follow in the stream.
 *
 * @param   memspace memory space.
 * @param   paddr ptr to ptr to tuple in memspace
 * @return  new tuple with fields and objs filled in.
 *          return by reference: paddr points one byte
 *          past end of last obj in tuple.
 */
PmReturn_t tuple_loadFromImg(PmMemSpace_t memspace,
                             uint8_t const **paddr, pPmObj_t *r_ptuple);

/**
 * Allocates space for a new Tuple.  Returns a pointer to the tuple.
 *
 * @param   n the number of elements the tuple will contain
 * @param   r_ptuple Return by ref, ptr to new tuple
 * @return  Return status
 */
PmReturn_t tuple_new(uint16_t n, pPmObj_t *r_ptuple);

/**
 * Replicates a tuple, n number of times to create a new tuple
 *
 * Copies the pointers (not the objects).
 *
 * @param   ptup Ptr to source tuple.
 * @param   n Number of times to replicate the tuple.
 * @param   r_ptuple Return arg; Ptr to new tuple.
 * @return  Return status
 */
PmReturn_t tuple_replicate(pPmObj_t ptup, int16_t n, pPmObj_t *r_ptuple);

/**
 * Gets the object in the tuple at the index.
 *
 * @param   pobj Ptr to tuple obj
 * @param   index Index into tuple
 * @param   r_pobj Return; ptr to return obj
 * @return  Return status
 */
PmReturn_t tuple_getItem(pPmObj_t ptup, int16_t index, pPmObj_t *r_pobj);

#ifdef HAVE_PRINT
/**
 * Prints out a tuple. Uses obj_print() to print elements.
 *
 * @param pobj Object to print.
 * @return Return status
 */
PmReturn_t tuple_print(pPmObj_t pobj);
#endif /* HAVE_PRINT */

#endif /* __TUPLE_H__ */
