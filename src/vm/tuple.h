#ifndef __TUPLE_H__
#define __TUPLE_H__
/**
 * Tuple Object Type
 *
 * Tuple object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        tuple.h
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

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Tuple obj
 *
 * Immutable ordered sequence.
 * Contains array of ptrs to objs.
 */
typedef struct PyTuple_s
{
    /** object descriptor */
    PyObjDesc_t od;
    /** 
	 * length of tuple
     * I don't expect a tuple to ever exceed 255 elements,
     * but if I set this type to S8, a 0-element tuple 
	 * is to small to be allocated.
	 */
    S16         length;
    /** array of ptrs to objs */
    pPyObj_t    val[0];
} PyTuple_t, *pPyTuple_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a Tuple by loading a tuple image from memory.
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
PyReturn_t tuple_loadFromImg(PyMemSpace_t, 
                             P_VOID *, 
                             pPyObj_t * r_ptuple);

/**
 * Allocate space for a new Tuple.
 * Return a pointer to the tuple.
 *
 * @param   n the number of elements the tuple will contain
 * @param   r_ptuple Return by ref, ptr to new tuple
 * @return  Return status
 */
PyReturn_t tuple_new(S16 n, pPyObj_t * r_ptuple);

/**
 * Create a copy of the tuple.
 *
 * Must allocate the necessary memory.
 * Duplicate ptrs to objs.
 *
 * @param   ptup Ptr to source tuple.
 * @param   r_ptuple Return arg; Ptr to new tuple.
 * @return  Return status
 */
PyReturn_t tuple_copy(pPyObj_t ptup, pPyObj_t * r_ptuple);

#endif /* __TUPLE_H__ */
