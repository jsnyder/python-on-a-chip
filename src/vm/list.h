#ifndef __LIST_H__
#define __LIST_H__
/**
 * List Object Type
 *
 * List object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        list.h
 *
 * Log:
 *
 * 2003/02/11   Refactored to pobj/return status model.
 * 2002/04/22   First.
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
 * List obj
 *
 * Mutable ordered sequence of objects.
 * Contains ptr to linked list of nodes.
 */
typedef struct PyList_s
{
    /** object descriptor */
    PyObjDesc_t od;
    /** list length; number of objs linked */
    S16 length;
    /** ptr to linked list of nodes */
    pSeglist_t val;
} PyList_t, *pPyList_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Allocate a new List object.
 *
 * If there is not enough memory to allocate the List,
 * the return status will indicate an OutOfMemoryError
 * that must be passed up to the interpreter.
 * Otherwise, a ptr to the list is returned by reference
 * and the return status is OK.
 *
 * @param   r_pobj Return; addr of ptr to obj
 * @return  Return status
 */
PyReturn_t list_new(pPyObj_t *r_pobj);

/**
 * Get the object in the list at the index.
 *
 * @param   pobj Ptr to list obj
 * @param   index Index into list
 * @param   r_pobj Return; ptr to return obj
 * @return  Return status
 */
PyReturn_t list_getItem(pPyObj_t plist,
                        S16 index,
                        pPyObj_t *r_pobj);

/**
 * Set the item in the list at the index.
 *
 * @param   pobj1 Ptr to list
 * @param   index Index int
 * @param   pobj2 Ptr to obj
 * @return  Return status
 */
PyReturn_t list_setItem(pPyObj_t pobj1,
                        S16 index,
                        pPyObj_t pobj2);

/**
 * Make a copy of the given list.
 *
 * Allocate the necessary memory for root and nodes.
 * Duplicate ptrs to objs.
 *
 * @param   pobj Ptr to source list
 * @param   r_pobj Return; Addr of ptr to return obj
 * @return  Return status
 */
PyReturn_t list_copy(pPyObj_t pobj, pPyObj_t * r_pobj);

/**
 * Append the given obj to the end of the given list.
 *
 * Allocate the memory for the node.
 * Do not copy obj, just reuse ptr.
 *
 * @param   plist Ptr to list
 * @param   pobj Ptr to item to append
 * @return  Return status
 */
PyReturn_t list_append(pPyObj_t plist, pPyObj_t pobj);

/**
 * Create a new list with the contents of psrclist
 * copied pint number of times.
 * This implements the python code "[0,...] * N"
 * where the list can be any list and N is an integer.
 *
 * @param   pobj1 The source list to replicate
 * @param   pobj2 The integer number of times to replicate it
 * @param   r_pobj Return; new list with its contents set.
 * @return  Return status
 */
PyReturn_t list_replicate(pPyObj_t psrclist,
                          pPyObj_t pint,
                          pPyObj_t * r_pnewlist);

/**
 * Insert the object into the list at the desired index.
 *
 * @param   plist Ptr to list obj
 * @param   pobj Ptr to obj to insert
 * @param   index Index of where to insert obj
 * @return  Return status
 */
PyReturn_t list_insert(pPyObj_t plist,
                       pPyObj_t pobj,
                       S8 index);

/* XXX TODO - redo these using pobj / return status */
#if 0
S8              list_count(pPyObj_t plist);
void            list_extend(pPyObj_t plista, PyObj_t plistb);
void            list_index(pPyObj_t plist, PyObj_t pitem);
pPyObj_t        list_pop(pPyObj_t plist);
void            list_remove(pPyObj_t plist, PyObj_t item);
void            list_reverse(pPyObj_t plist)
void            list_sort(pPyObj_t plist)
#endif

#endif /* __LIST_H__ */
