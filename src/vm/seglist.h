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

#ifndef __SEGLIST_H__
#define __SEGLIST_H__
/**
 * Segmented List data structure
 *
 * A seglist is a linked list of segments.
 * A segment is an array of ptrs to objects
 * (with a pointer to the next segment).
 * Seglists are used to implement Lists and Dicts.
 *
 * This implementation of Seglist is straight.
 * That is, the next pointer in the final segment
 * contains C_NULL.
 *
 * This implementation of Seglist is dense.
 * That is, there are no gaps in a segment.
 * All entries point to an object, except entries
 * that are beyond the index of the last item.
 *
 * Log:
 *
 * 2006/11/18   #54: Change seglist API
 * 2002/12/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** Defines the length of the object array in a segment */
#define SEGLIST_OBJS_PER_SEG 8


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/** Segment - an array of ptrs to objs */
typedef struct Segment_s
{
    /** object descriptor */
    PmObjDesc_t od;
    /** array of ptrs to objs */
    pPmObj_t s_val[SEGLIST_OBJS_PER_SEG];
    /** ptr to next segment */
    struct Segment_s *next;
} Segment_t, *pSegment_t;


/** Seglist - linked list of segments with current index info */
typedef struct Seglist_s
{
    /** object descriptor */
    PmObjDesc_t od;
    /** ptr to first segment in list */
    pSegment_t sl_rootseg;
    /** ptr to last segment */
    pSegment_t sl_lastseg;
    /** index of (one past) last obj in last segment */
    int16_t sl_length;
} Seglist_t, *pSeglist_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Put the new object at the end of the list.
 * This is intended for the List type where
 * the List index matches the order of the Seglist index.
 * Make room if necessary by adding new segments.
 *
 * @param pseglist Ptr to seglist to scan
 * @param indx Index of object to obtain
 * @return Return status
 */
PmReturn_t seglist_appendItem(pSeglist_t pseglist, pPmObj_t pobj);


/**
 * Clear the the seglist by unlinking the root segment.
 * OPTION:  if SEGLIST_CLEAR_SEGMENTS is 1,
 *          deallocate each segment (could let GC get it)
 *
 * @param pseglist Ptr to seglist to empty
 */
PmReturn_t seglist_clear(pSeglist_t pseglist);


/**
 * Finds the first obj equal to pobj in the seglist.
 * Starts searching the list at the given segnum and indx.
 *
 * @param   pseglist The seglist to search
 * @param   pobj The object to match
 * @param   r_index Return arg; the index of where to start the search.
 *          If a match is found, return the index by reference.
 *          If no match is found, this value is undefined.
 * @return  Return status; PM_RET_OK means a matching object
 *          was found.  PM_RET_ERR otherwise.
 */
PmReturn_t seglist_findEqual(pSeglist_t pseglist,
                             pPmObj_t pobj,
                             int16_t *r_index);


/**
 * Get the item in the seglist at the given coordinates.
 * The segment number and the index within the segment
 * are the coordinates of the object to get.
 *
 * @param   pseglist Ptr to seglist to scan
 * @param   index Index of item to get
 * @param   r_pobj Return arg; Ptr to object at the index
 * @return  Return status; PM_RET_OK if object found.
 *          PM_RET_ERR otherwise.
 */
PmReturn_t seglist_getItem(pSeglist_t pseglist,
                           int16_t index,
                           pPmObj_t *r_pobj);


/**
 * Allocate a new empty seglist
 *
 * @param   r_pseglist return; Address of ptr to new seglist
 * @return  Return status
 */
PmReturn_t seglist_new(pSeglist_t *r_pseglist);


/**
 * Put the item in the next available slot in the first
 * available segment.
 * This is intended for the Dict type where
 * the Seglist index is insignificant.
 * Pushing an object assures it will be found early
 * during a call to seglist_findEqual().
 *
 * @param   pseglist Ptr to seglist in which object is placed.
 * @param   pobj Ptr to object which is inserted.
 * @param   index Index into seglist before which item is inserted
 * @return  Return status; PM_RET_OK if the item was inserted.
 *              Any error condition comes from heap_getChunk.
 */
PmReturn_t seglist_insertItem(pSeglist_t pseglist,
                              pPmObj_t pobj,
                              int16_t index);

/**
 * Put the item in the designated slot and segment.
 * This is intended to be used after seglist_findEqual()
 * returns the proper indeces.
 *
 * @param   pseglist Ptr to seglist in which object is placed.
 * @param   pobj Ptr to object which is set.
 * @param   index Index into seglist of where to put object.
 * @return  Return status; PM_RET_OK if object is set.
 *              PM_RET_ERR otherwise.
 */
PmReturn_t seglist_setItem(pSeglist_t pseglist,
                           pPmObj_t pobj,
                           int16_t index);

#endif /* __SEGLIST_H__ */
