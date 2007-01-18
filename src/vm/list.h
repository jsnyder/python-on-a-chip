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

#ifndef __LIST_H__
#define __LIST_H__
/**
 * List Object Type
 *
 * List object type header.
 *
 * Log:
 *
 * 2007/01/09   #75: Printing support (P.Adelt)
 * 2007/01/09   #75: implemented list_remove() and list_index() (P.Adelt)
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
typedef struct PmList_s
{
    /** object descriptor */
    PmObjDesc_t od;
    /** list length; number of objs linked */
    int16_t length;
    /** ptr to linked list of nodes */
    pSeglist_t val;
} PmList_t, *pPmList_t;


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
PmReturn_t list_new(pPmObj_t *r_pobj);

/**
 * Get the object in the list at the index.
 *
 * @param   pobj Ptr to list obj
 * @param   index Index into list
 * @param   r_pobj Return; ptr to return obj
 * @return  Return status
 */
PmReturn_t list_getItem(pPmObj_t plist,
                        int16_t index,
                        pPmObj_t *r_pobj);

/**
 * Set the item in the list at the index.
 *
 * @param   pobj1 Ptr to list
 * @param   index Index int
 * @param   pobj2 Ptr to obj
 * @return  Return status
 */
PmReturn_t list_setItem(pPmObj_t pobj1,
                        int16_t index,
                        pPmObj_t pobj2);

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
PmReturn_t list_copy(pPmObj_t pobj, pPmObj_t * r_pobj);

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
PmReturn_t list_append(pPmObj_t plist, pPmObj_t pobj);

/**
 * Create a new list with the contents of psrclist
 * copied pint number of times.
 * This implements the python code "[0,...] * N"
 * where the list can be any list and N is an integer.
 *
 * @param   psrclist The source list to replicate
 * @param   n The integer number of times to replicate it
 * @param   r_pnewlist Return; new list with its contents set.
 * @return  Return status
 */
PmReturn_t list_replicate(pPmObj_t psrclist,
                          int16_t n,
                          pPmObj_t * r_pnewlist);

/**
 * Insert the object into the list at the desired index.
 *
 * @param   plist Ptr to list obj
 * @param   pobj Ptr to obj to insert
 * @param   index Index of where to insert obj
 * @return  Return status
 */
PmReturn_t list_insert(pPmObj_t plist,
                       int16_t index,
                       pPmObj_t pobj);

/**
 * Remove a given object from the list.
 * 
 * @param   plist Ptr to list obj
 * @param   item Ptr to object to be removed
 * @return  Return status
 */
PmReturn_t list_remove(pPmObj_t plist,
                       pPmObj_t item);

/**
 * Find the first index of the item that matches pitem.
 * Returns an ValueError Exception if the item is not found.
 * 
 * @param   plist Ptr to list obj
 * @param   item Ptr to object to be removed
 * @param   r_index Addr of the variable for index
 * @return  Return status
 */
PmReturn_t list_index(pPmObj_t plist,
                      pPmObj_t pitem,
                      uint16_t* r_index);

#ifdef HAVE_PRINT
/**
 * Print out a list. Uses obj_print() to print elements.
 * 
 * @param pobj Object to print.
 * @return Return status
 */
PmReturn_t list_print(pPmObj_t pobj);
#endif /* HAVE_PRINT */

/* XXX TODO - redo these using pobj / return status */
#if 0
S8              list_count(pPmObj_t plist);
void            list_extend(pPmObj_t plista, PmObj_t plistb);
pPmObj_t        list_pop(pPmObj_t plist);
void            list_reverse(pPmObj_t plist)
void            list_sort(pPmObj_t plist)
#endif

#endif /* __LIST_H__ */
