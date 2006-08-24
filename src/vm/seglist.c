#undef __FILE_ID__
#define __FILE_ID__ 0x10
/**
 * Segmented list data type and operations
 *
 * The segmented list is used to implement the Python
 * List and Dict data types.
 * The segmented list is used in preference to the linked list
 * in order to reduce the memory overhead.
 *
 * List implementation:
 * When used in a List, the Seglist.currseg field points
 * to the last segment in the list.
 * The function seglist_appendItem() should be used to append
 * items to the List.
 * Inserting and deleting List items is a more complicated 
 * matter.
 *
 * Dict implementation:
 * The currseg field is meaningless since rootseg always
 * points to the current active segment.
 * The function seglist_pushItem() should be used to put
 * items in the Dict.
 * A Dict uses one Seglist for keys and another for values.
 * A Dict entry's (key, value) pair share the same index in
 * the Seglist.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        seglist.c
 *
 * Log:
 *
 * 2002/12/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "py.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/** 
 * Set this to 1 if seglist_clear() should manually free its segments.
 * Set this to 0 if seglist_clear() should do nothing
 * and let the GC reclaim objects. 
 */
#define SEGLIST_CLEAR_SEGMENTS 1


/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

PyReturn_t
seglist_appendItem(pSeglist_t pseglist, pPyObj_t pobj)
{
    PyReturn_t retval = PY_RET_OK;
    pSegment_t pseg = C_NULL;
    S8 i = 0;

    /* if this is first item in seg, alloc and link seg */
    if (pseglist->sl_lastindx == 0)
    {
        /* alloc and init new segment */
        retval = heap_getChunk(sizeof(Segment_t),
                               (P_VOID *)&pseg);
        PY_RETURN_IF_ERROR(retval);
        pseg->od.od_type = OBJ_TYPE_SEG;
        for (i = 1; i < SEGLIST_OBJS_PER_SEG; i++)
        {
            pseg->s_val[i] = C_NULL;
        }
        pseg->next = C_NULL;

        /* if this is the first seg, set as root */
        if (pseglist->sl_rootseg == C_NULL)
        {
            pseglist->sl_rootseg = pseg;
        }

        /* else append the seg to the end */
        else
        {
            pseglist->sl_lastseg->next = pseg;
        }

        /* either way, this is now the last segment */
        pseglist->sl_lastseg = pseg;
    }

    /* else get last seg */
    else
    {
        pseg = pseglist->sl_lastseg;
    }

    /* put object into segment */
    pseg->s_val[pseglist->sl_lastindx] = pobj;
    
    /* increment last index and reset if necessary */
    if (++(pseglist->sl_lastindx) >= SEGLIST_OBJS_PER_SEG)
    {
        pseglist->sl_lastindx = 0;
    }

    return retval;
}


void
seglist_clear(pSeglist_t pseglist)
{
    pSegment_t pseg1 = C_NULL;
    pSegment_t pseg2 = C_NULL;

#if SEGLIST_CLEAR_SEGMENTS
    /* deallocate all linked segments */
    pseg1 = ((pSeglist_t)pseglist)->sl_rootseg;
    while (pseg1 != C_NULL)
    {
        pseg2 = pseg1->next;
        heap_freeChunk((pPyObj_t)pseg1);
        pseg1 = pseg2;
    }
#endif

    /* clear seglist fields */
    ((pSeglist_t)pseglist)->sl_rootseg = C_NULL;
    ((pSeglist_t)pseglist)->sl_lastseg = C_NULL;
    ((pSeglist_t)pseglist)->sl_lastindx = 0;
}


PyReturn_t
seglist_findEqual(pSeglist_t pseglist,
                  pPyObj_t pobj,
                  S8 * r_segnum,
                  S8 * r_indx)
{
    pSegment_t pseg = C_NULL;
    S8 i = 0;

    /* if index is out of bounds, raise SystemError */
    if ((*r_indx < 0) || (*r_indx > SEGLIST_OBJS_PER_SEG))
    {
        return PY_RET_EX_SYS;
    }

    /* set pseg to the segnum'th segment in the list */
    pseg = pseglist->sl_rootseg;
    for (i = *r_segnum; i > 0; i--)
    {
        /*
         * if the given segnum is larger than
         * the number of segments, raise SystemError
         */
        if (pseg == C_NULL)
        {
            return PY_RET_EX_SYS;
        }
        pseg = pseg->next;
    }

    /* start search from this segment */
    while (pseg != C_NULL)
    {
        while (*r_indx < SEGLIST_OBJS_PER_SEG)
        {
            /* if seglist entry is null, we're past the end */
            if (pseg->s_val[*r_indx] == C_NULL)
            {
                return PY_RET_NO;
            }

            /*
             * if the two objs are equal, return affirmation
             * with segnum and indx referring to matching obj.
             */
            if (obj_isEqual(pobj, pseg->s_val[*r_indx]))
            {
                return PY_RET_OK;
            }
            (*r_indx)++;
        }

        /* move on to next segment */
        *r_indx = 0;
        pseg = pseg->next;
        (*r_segnum)++;
    }
    return PY_RET_NO;
}


PyReturn_t
seglist_getItem(pSeglist_t pseglist,
                S8 segnum,
                S8 segindx,
                pPyObj_t * r_pobj)
{
    pSegment_t pseg = pseglist->sl_rootseg;

    /* scan to proper seg, error check along the way */
    for (; segnum > 0; segnum--)
    {
        /* if went past last segment, return nothing */
        if (pseg == C_NULL)
        {
            return PY_RET_EX_SYS;
        }
        pseg = pseg->next;
    }

    /* if indx asks for obj beyond the seglist's last one */
    if ((pseg == pseglist->sl_lastseg)
        && (segindx >= pseglist->sl_lastindx))
    {
        return PY_RET_EX_SYS;
    }

    /* return ptr to obj in this seg at the index */
    *r_pobj = pseg->s_val[segindx];
    return PY_RET_OK;
}


PyReturn_t
seglist_insertItem(pSeglist_t pseglist,
                   pPyObj_t pobj,
                   S8 segnum,
                   S8 segindx)
{
    PyReturn_t retval = PY_RET_OK;
    pSegment_t pseg = C_NULL;
    pPyObj_t pobj1 = C_NULL;
    pPyObj_t pobj2 = C_NULL;
    S8 indx = 0;
    S8 i = 0;

    /* if the seglist has no segment, insert one */
    if (pseglist->sl_rootseg == C_NULL)
    {
        /* alloc and init segment */
        retval = heap_getChunk(sizeof(Segment_t),
                               (P_VOID *)&pseglist->sl_rootseg);
        PY_RETURN_IF_ERROR(retval);
        pseglist->sl_rootseg->od.od_type = OBJ_TYPE_SEG;

        /* seglist refers to the new segment */
        pseglist->sl_lastseg = pseglist->sl_rootseg;
        pseglist->sl_lastindx = 0;
        
        /* if past end of list */
        if ((segnum != 0) || (segindx != 0))
        {
            return PY_RET_EX_SYS;
        }

        /* insert obj in seglist */
        pseglist->sl_rootseg->s_val[0] = pobj;
        pseglist->sl_lastindx++;
        return PY_RET_OK;
    }
        
    /* else, iterate until pseg pts to segnum'th segment */
    for (pseg = pseglist->sl_rootseg; segnum > 0; segnum--)
    {
        pseg = pseg->next;

        /* if ran past end of list */
        /* XXX what about inserting several indices past end? 
         * Not knowing the numSegs in the seglist is a reason to dislike seglists.
         */
        if (pseg == C_NULL)
        {
            return PY_RET_EX_SYS;
        }
    }

    /* if indx asks for obj beyond the seglist's last one */
    if ((pseg == pseglist->sl_lastseg)
        && (segindx >= pseglist->sl_lastindx))
    {
        /* caller must convert this err to exception */
        return PY_RET_EX_SYS;
    }

    /* insert obj and ripple copy all those afterward */
    indx = segindx;
    pobj1 = pobj;
    while (pobj1 != C_NULL)
    {
        pobj2 = pseg->s_val[indx];
        pseg->s_val[indx] = pobj1;
        pobj1 = pobj2;
        indx++;

        /* if indx exceeds this seg and need to go to next */
        if ((indx >= SEGLIST_OBJS_PER_SEG) && (pobj1 != C_NULL))
        {
            /* create next seg if needed */
            if (pseg->next == C_NULL)
            {
                retval = heap_getChunk(sizeof(Segment_t),
                                       (P_VOID *)&pseg->next);
                /* 
                 * XXX exception with hosed list,
                 * need to roll-back!
                 */
                PY_RETURN_IF_ERROR(retval);

                /* init segment */
                pseg = pseg->next;
                pseg->od.od_type = OBJ_TYPE_SEG;
                for (i = 1; i < SEGLIST_OBJS_PER_SEG; i++)
                {
                    pseg->s_val[i] = C_NULL;
                }
                pseg->next = C_NULL;
                /* seglist's lastseg pts to new seg */
                pseglist->sl_lastseg = pseg;
                pseglist->sl_lastindx = 0; /* incr'd below */
                /* put obj in seg */
                pseg->s_val[0] = pobj1;
                pobj1 = C_NULL;
            }
            /* else skip to next seg and continue */
            else
            {
                pseg = pseg->next;
                indx = 0;
            }
        }
    }
    pseglist->sl_lastindx++;
    return retval;
}


PyReturn_t
seglist_new(pSeglist_t * r_pseglist)
{
    PyReturn_t retval = PY_RET_OK;

    retval = heap_getChunk(sizeof(Seglist_t),
                           (P_VOID *)r_pseglist);
    PY_RETURN_IF_ERROR(retval);

    (*r_pseglist)->od.od_type = OBJ_TYPE_SGL;
    (*r_pseglist)->sl_rootseg = C_NULL;
    (*r_pseglist)->sl_lastseg = C_NULL;
    (*r_pseglist)->sl_lastindx = 0;
    return retval;
}


PyReturn_t
seglist_setItem(pSeglist_t pseglist,
                pPyObj_t pobj,
                S8 segnum,
                S8 segindx)
{
    pSegment_t pseg = pseglist->sl_rootseg;

    /* scan to proper seg, error check along the way */
    for (; segnum > 0; segnum--)
    {
        pseg = pseg->next;

        /* if ran past end of list, raise SystemError */
        if (pseg == C_NULL)
        {
            return PY_RET_EX_SYS;
        }
    }

    /* if indx is beyond the seglist's end, raise SystemError */
    if ((pseg == pseglist->sl_lastseg) &&
        (segindx >= pseglist->sl_lastindx))
    {
        return PY_RET_EX_SYS;
    }

    /* set ptr to obj in this seg at the index */
    pseg->s_val[segindx] = pobj;
    return PY_RET_OK;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/