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

#undef __FILE_ID__
#define __FILE_ID__ 0x06
/**
 * VM Heap
 *
 * VM heap operations.
 * All of PyMite's dynamic memory is obtained from this heap.
 * The heap provides dynamic memory on demand.
 *
 * Log
 * ---
 *
 * 2006/09/14   #27: Fix S16/U16 are 32-bits on DESKTOP
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2003/02/10   Started GC marking fxns.
 * 2002/08/31   Implemented freelist when chunk is deleted.
 * 2002/04/30   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "pm.h"


/***************************************************************
 * Constants
 **************************************************************/

/** A flag to profile heap object allocation sizes */
#define HEAP_MEASURE    0


/***************************************************************
 * Macros
 **************************************************************/

/**
 * Mark an object if it is not already marked
 * with the curent val
 */
#define HEAP_MARK_IF_UNMARKED(pobj, rval)   \
            if (((pobj) != C_NULL) && \
                (OBJ_GET_GCVAL(*pobj) != heap_gcval)) \
                    rval = heap_markObj((pPmObj_t)pobj)


/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/** ptr to list of free chunks */
static pPmHeapDesc_t pfreelist;

/** ptr to clean heap (the big chunk) */
static pPmHeapDesc_t pcleanheap;

#if HEAP_MEASURE
/** Size of heap histogram table */
#define HIST_TABLE_SIZE 20
/** An array to hold the heap size histogram. */
static int8_t * heaphist[HIST_TABLE_SIZE];
#endif /* HEAP_MEASURE */

/** garbage collector marking value */
static uint8_t heap_gcval = 0;


/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

/*
 * Garbage Collector Functions
 */

/**
 * Mark the given object and the objects it references.
 *
 * @param   pobj An object that is not already marked live.
 * @return  Return code
 */
static
PmReturn_t
heap_markObj(pPmObj_t pobj)
{
    PmReturn_t retval = PM_RET_OK;
    int8_t i = 0;

    switch (OBJ_GET_TYPE(*pobj))
    {
        /* objects with no other obj refs */
        case OBJ_TYPE_NON:
        case OBJ_TYPE_INT:
        case OBJ_TYPE_FLT:
        case OBJ_TYPE_STR:
        case OBJ_TYPE_NOB:
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            break;

        case OBJ_TYPE_TUP:
            i = ((pPmTuple_t)pobj)->length;
            /* mark tuple head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark each obj in tuple */
            while (--i >= 0)
            {
                HEAP_MARK_IF_UNMARKED(
                    ((pPmTuple_t)pobj)->val[i],
                    retval);
                PM_RETURN_IF_ERROR(retval);
            }
            break;

        case OBJ_TYPE_LST:
            /* mark the list */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the keys seglist */
            HEAP_MARK_IF_UNMARKED(((pPmList_t)pobj)->val,
                                  retval);
            break;

        case OBJ_TYPE_DIC:
            /* mark the dict head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the keys seglist */
            HEAP_MARK_IF_UNMARKED(((pPmDict_t)pobj)->d_keys,
                                  retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the vals seglist */
            HEAP_MARK_IF_UNMARKED(((pPmDict_t)pobj)->d_vals,
                                  retval);
            break;

        case OBJ_TYPE_COB:
            /* mark the code obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the names tuple */
            HEAP_MARK_IF_UNMARKED(((pPmCo_t)pobj)->co_names,
                                  retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the consts tuple */
            HEAP_MARK_IF_UNMARKED(((pPmCo_t)pobj)->co_consts,
                                  retval);
            break;

        case OBJ_TYPE_MOD:
        case OBJ_TYPE_FXN:
            /* Module and Func objs are implemented via the PmFunc_t */
            /* mark the func obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the code obj */
            HEAP_MARK_IF_UNMARKED(((pPmFunc_t)pobj)->f_co, retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the attr dict */
            HEAP_MARK_IF_UNMARKED(((pPmFunc_t)pobj)->f_attrs, retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the default args tuple */
            HEAP_MARK_IF_UNMARKED(((pPmFunc_t)pobj)->f_defaultargs, retval);
            break;

        case OBJ_TYPE_CLO:
        case OBJ_TYPE_CLI:
        case OBJ_TYPE_EXN:
            /* mark the obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the attrs dict */
            HEAP_MARK_IF_UNMARKED(((pPmClass_t)pobj)->cl_attrs, retval);
            break;

        /* An obj in ram should not be of these types */
        case OBJ_TYPE_CIM:
        case OBJ_TYPE_NIM:
            return PM_RET_ERR;

        case OBJ_TYPE_FRM:
        {
            pPmObj_t pobj2 = C_NULL;
            /* mark the frame obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the previous frame */
            HEAP_MARK_IF_UNMARKED(((pPmFrame_t)pobj)->fo_back,
                                  retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the fxn obj */
            HEAP_MARK_IF_UNMARKED(((pPmFrame_t)pobj)->fo_func,
                                  retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the blockstack */
            HEAP_MARK_IF_UNMARKED(
                ((pPmFrame_t)pobj)->fo_blockstack,
                retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the attrs dict */
            HEAP_MARK_IF_UNMARKED(((pPmFrame_t)pobj)->fo_attrs,
                                  retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark the globals dict */
            HEAP_MARK_IF_UNMARKED(
                ((pPmFrame_t)pobj)->fo_globals,
                retval);
            PM_RETURN_IF_ERROR(retval);
            /* mark each obj in the locals list and the stack */
            while (pobj2 < (pPmObj_t)((pPmFrame_t)pobj)->fo_sp)
            {
                HEAP_MARK_IF_UNMARKED(pobj2, retval);
                PM_RETURN_IF_ERROR(retval);
                pobj2++;
            }
            break;
        }

        case OBJ_TYPE_BLK:
            /* mark the block obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the previous block */
            HEAP_MARK_IF_UNMARKED(((pPmBlock_t)pobj)->next,
                                  retval);
            break;

        case OBJ_TYPE_SEG:
            /* mark the segment obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark each obj in the segment */
            for (i = 0; i < SEGLIST_OBJS_PER_SEG; i++)
            {
                HEAP_MARK_IF_UNMARKED(
                    ((pSegment_t)pobj)->s_val[i],
                    retval);
                PM_RETURN_IF_ERROR(retval);
            }
            /* mark the next segment */
            HEAP_MARK_IF_UNMARKED(((pSegment_t)pobj)->next,
                                  retval);
            break;

        case OBJ_TYPE_SGL:
            /* mark the seglist obj head */
            OBJ_SET_GCVAL(*pobj, heap_gcval);
            /* mark the root segment */
            HEAP_MARK_IF_UNMARKED(
                ((pSeglist_t)pobj)->sl_rootseg,
                retval);
            break;
    }
    return retval;
}


static
PmReturn_t
heap_markImgInfoStruct(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmImgInfo_t pii = C_NULL;

    pii = gVmGlobal.pimglist;

    /* mark the list of img info structs */
    while (pii != C_NULL)
    {
        /* mark the img name string object */
        HEAP_MARK_IF_UNMARKED(pii->ii_name, retval);

        /* exit on any error */
        PM_RETURN_IF_ERROR(retval);
        pii = pii->next;
    }
    return retval;
}


/**
 * Mark the root objects of the interpreter.
 *
 * Marks each root object, and all linked objects,
 * so the collector will ignore live objects.
 * Uses a 2-bit value to mark an object.
 * The value is global to this file and is incremented
 * with each call to this function.
 * The collector should ignore objects that are marked
 * with the current value.
 *
 * @return  Return code
 */
static
PmReturn_t
heap_markRoots(void)
{
    PmReturn_t retval = PM_RET_OK;
    /* increment the GC marking value; modulo 2-bits */
    heap_gcval++;
    heap_gcval &= 0x03;

    /* mark each root object */
    /*
     * do not need to mark:
     *  root module because frame ptr reaches it.
     *  native frame because it's never active during GC.
     */
    /* the image info struct is special; it has no obj header */
    retval = heap_markImgInfoStruct();
    PM_RETURN_IF_ERROR(retval);
    /* mark the builtins dict */
    HEAP_MARK_IF_UNMARKED(PM_PBUILTINS, retval);
    PM_RETURN_IF_ERROR(retval);
    /* mark the "code" string */
    HEAP_MARK_IF_UNMARKED(PM_CODE_STR, retval);
    return retval;
}


/*
 * Heap (de)allocation functions
 */
void
heap_init(void)
{
    pPmHeapDesc_t pchunk = C_NULL;
    uint16_t size = 0;

    /* zero all memory in the heap (optional?) */
    sli_memset((uint8_t *)&gVmGlobal.heap, '\0', sizeof(gVmGlobal.heap));

    /* init global amount of heap space remaining */
    gVmGlobal.heap.avail = HEAP_SIZE;

    /* pcleanheap pts to list of large chunks */
    pcleanheap = (pPmHeapDesc_t)&gVmGlobal.heap.base;
    pchunk = pcleanheap;

    /* init list of large chunks */
    size = HEAP_SIZE;
    while (size > HEAP_MAX_CHUNK_SIZE)
    {
        OBJ_SET_SIZE(*pchunk, HEAP_MAX_CHUNK_SIZE);
        pchunk->next = (pPmHeapDesc_t)((uint8_t *)pchunk + HEAP_MAX_CHUNK_SIZE);
        size -= HEAP_MAX_CHUNK_SIZE;
        pchunk = pchunk->next;
    }

    /* set fields of last fragment */
    OBJ_SET_SIZE(*pchunk, size);
    pchunk->next = C_NULL;

#if HEAP_MEASURE
    /* to show where list starts; need to add 1 to result */
    heaphist[0] = 0xFF;
#endif
}


/**
 * Obtain a chunk of memory using hybrid best fit.
 *
 * Search the free list for a chunk that is
 * large enough to meet the requested size,
 * but not HEAP_MAX_FRAG_SIZE bytes more.
 * If no such chunk is found, carve a chunk
 * out of the clean heap, if available.
 * If still nothing, use the free list chunk
 * if large enough (without FRAG limit).
 * If still nothing, return null.
 *
 * @param size Requested chunk size
 * @param r_pchunk Return ptr to chunk
 * @return Return status
 */
static
PmReturn_t
heap_getChunk0(uint8_t size, uint8_t **r_pchunk)
{
    pPmHeapDesc_t pchunk1 = C_NULL;
    pPmHeapDesc_t pchunk2 = C_NULL;

#if HEAP_MEASURE
    /* if larger than hist table, store in 0th element */
    if (size-HEAP_MIN_CHUNK_SIZE >= HIST_TABLE_SIZE)
    {
        heaphist[0]++;
    }

    /* else count the size */
    else
    {
        heaphist[size-HEAP_MIN_CHUNK_SIZE-1]++;
    }
#endif /* HEAP_MEASURE */

    /* if the free list has chunks, search it */
    if (pfreelist != C_NULL)
    {
        /* start at beginning of free list */
        pchunk1 = pfreelist;

        /* if first chunk is best fit */
        if ((OBJ_GET_SIZE(*pchunk1) >= size) &&
            (OBJ_GET_SIZE(*pchunk1) <= (size + HEAP_MAX_FRAG_SIZE)))
        {
            /* relink list and return first chunk */
            pfreelist = pfreelist->next;
            /* reduce heap available amount */
            gVmGlobal.heap.avail -= OBJ_GET_SIZE(*pchunk1);
            *r_pchunk = (uint8_t *)pchunk1;
            return PM_RET_OK;
        }

        /* else search list for proper sized chunk */
        while ((pchunk1->next != C_NULL) &&
               (OBJ_GET_SIZE(*pchunk1->next) < size))
        {
             pchunk1 = pchunk1->next;
        }

        /*
         * if this is not the last chunk,
         * and it's a best fit, unlink and use it.
         * if not, we might use pchunk1->next later (first fit).
         */
        if ((pchunk1->next != C_NULL) &&
            (OBJ_GET_SIZE(*pchunk1->next) <=
             (size + HEAP_MAX_FRAG_SIZE)))
        {
            /* unlink chunk */
            pchunk2 = pchunk1->next;
            pchunk1->next = pchunk1->next->next;
            /* reduce heap available amount */
            gVmGlobal.heap.avail -= OBJ_GET_SIZE(*pchunk2);
            *r_pchunk = (uint8_t *)pchunk2;
            return PM_RET_OK;
        }
    }

    /* if nothing from free list, check the clean heap */
    if (pcleanheap != C_NULL)
    {
        /*
         * if the clean heap is not large enough
         * put the fragment in the free list
         */
        if (OBJ_GET_SIZE(*pcleanheap) < size)
        {
            pchunk2 = pcleanheap;
            /* try the next clean heap */
            pcleanheap = pcleanheap->next;
            /* XXX be sure this doesn't count toward freemem */
            heap_freeChunk((pPmObj_t)pchunk2);
        }

        /*
         * carve chunk out of back of clean heap
         * if there is one and it is large enough
         */
        if ((pcleanheap != C_NULL) &&
            ((OBJ_GET_SIZE(*pcleanheap) - size) >= 0))
        {

            /*
             * if potential clean heap remnant is too small,
             * use the entire chunk and setup next clean heap
             */
            if ((OBJ_GET_SIZE(*pcleanheap) - size) < HEAP_MIN_CHUNK_SIZE)
            {
                pchunk2 = pcleanheap;
                pcleanheap = pcleanheap->next;
            }

            /* else carve chunk out of clean heap */
            else
            {
                OBJ_SET_SIZE(*pcleanheap, OBJ_GET_SIZE(*pcleanheap) - size);
                pchunk2 = (pPmHeapDesc_t)((uint8_t *)pcleanheap 
                                          + OBJ_GET_SIZE(*pcleanheap));
                OBJ_SET_SIZE(*pchunk2, size);
            }

            /* reduce heap available amount */
            gVmGlobal.heap.avail -= size;
            *r_pchunk = (uint8_t *)pchunk2;
            return PM_RET_OK;
        }
    }

    /*
     * if nothing from clean heap,
     * try first fit (again) ignoring the FRAG limit
     */
    if ((pchunk1 != C_NULL)
        && (pchunk1->next != C_NULL)
        && (OBJ_GET_SIZE(*pchunk1->next) >= size))
    {
        pchunk2 = pchunk1->next;
        pchunk1->next = pchunk1->next->next;
        /* reduce heap available amount */
        gVmGlobal.heap.avail -= OBJ_GET_SIZE(*pchunk2);
        *r_pchunk = (uint8_t *)pchunk2;
        return PM_RET_OK;
    }

    /* no chunk of that size available */
    *r_pchunk = C_NULL;
    return PM_RET_ERR;
}


/*
 * Filter out invalid sizes.
 * Obtain a chunk of at least the desired size
 * from the heap.  Perform GC if necessary.
 */
PmReturn_t
heap_getChunk(uint8_t size, uint8_t **r_pchunk)
{
    PmReturn_t retval;

    /* halt if size request is invalid */
    if ((size < HEAP_MIN_CHUNK_SIZE)
#if HEAP_MAX_CHUNK_SIZE != 255
        || (size > HEAP_MAX_CHUNK_SIZE)
#endif
       )
    {
        PM_ERR(__LINE__);
    }

    /* if a chunk is available, return with it */
    retval = heap_getChunk0(size, r_pchunk);
    if (retval == PM_RET_OK)
    {
        return retval;
    }

    /* XXX GC isn't tested yet, halt here */
    /* PM_ERR(__LINE__); */

    /* else collect garbage */
    heap_markRoots();
    /* XXX heap_sweep();*/

    /* now, if a chunk is available, return with it */
    retval = heap_getChunk0(size, r_pchunk);
    if (retval == PM_RET_OK)
    {
        return PM_RET_OK;
    }

    /* else return out-of-memory exception */
    return PM_RET_EX_MEM;
}


/*
 * Release chunk to free list.
 * Free list is sorted smallest to largest.
 */
void
heap_freeChunk(pPmObj_t ptr)
{
    pPmHeapDesc_t oldchunk = (pPmHeapDesc_t)ptr;
    uint8_t size = OBJ_GET_SIZE(*ptr);
    pPmHeapDesc_t pchunk1;
    pPmHeapDesc_t pchunk2;

    /* increase heap available amount */
    gVmGlobal.heap.avail += OBJ_GET_SIZE(*ptr);

    /* if freelist is empty or oldchunk is smallest */
    if ((pfreelist == C_NULL) ||
        (OBJ_GET_SIZE(*pfreelist) >= size))
    {
        oldchunk->next = pfreelist;
        pfreelist = oldchunk;
        return;
    }

    /* sentinel1 at start of list */
    pchunk1 = pfreelist;
    /* sentinel2 leads sentinel1 */
    pchunk2 = pchunk1->next;

    /* scan freelist for insertion point */
    while ((pchunk2 != C_NULL) &&
           (OBJ_GET_SIZE(*pchunk2) < size))
    {
        pchunk1 = pchunk2;
        pchunk2 = pchunk2->next;
    }

    /* link chunk */
    oldchunk->next = pchunk2;
    pchunk1->next = oldchunk;
    return;
}

