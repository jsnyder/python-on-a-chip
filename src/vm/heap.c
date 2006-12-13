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
 * 2006/11/15   #53: Fix Win32/x86 build break
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

/**
 * Static initial size of the heap.
 * A value should be provided by the makefile
 */
#ifndef HEAP_SIZE
#error HEAP_SIZE not defined by the build environment
#endif

/**
 * The maximum size a chunk can be.
 * Must be less than 256 since uint8_t is used to keep its size.
 * Set to 252 so it is 4 less than 256.
 * This helps with alignment for targets that need aligned
 * pointers such as TARGET_DESKTOP and TARGET_ARM and it doesn't
 * harm other targets.
 */
#define HEAP_MAX_CHUNK_SIZE 252

/** The minimum size a chunk can be */
#define HEAP_MIN_CHUNK_SIZE sizeof(PmHeapDesc_t)


/***************************************************************
 * Macros
 **************************************************************/

/**
 * Mark an object if it is not already marked
 * with the curent val
 */
#define HEAP_MARK_IF_UNMARKED(pobj, rval)   \
            if (((pobj) != C_NULL) && \
                (OBJ_GET_GCVAL(*pobj) != pmHeap.gcval)) \
                    rval = heap_markObj((pPmObj_t)pobj)


/***************************************************************
 * Types
 **************************************************************/

typedef struct PmHeap_s
{
    /** Global declaration of heap. */
    uint8_t base[HEAP_SIZE];

    /** Ptr to list of free chunks; sorted smallest to largest. */
    pPmHeapDesc_t pfreelist;

    /** Ptr to clean heap (the big chunks) */
    pPmHeapDesc_t pcleanheap;

    /** The amount of heap space available (free) */
    uint16_t avail;

    /** Garbage collector marking value */
    uint8_t gcval;

    /** Flag to dis/allow automatic garbage collection */
    uint8_t do_auto_gc;
} PmHeap_t, *pPmHeap_t;


/***************************************************************
 * Globals
 **************************************************************/

/** The PyMite heap */
static PmHeap_t pmHeap;


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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
            break;

        case OBJ_TYPE_TUP:
            i = ((pPmTuple_t)pobj)->length;
            /* mark tuple head */
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
            /* mark the keys seglist */
            HEAP_MARK_IF_UNMARKED(((pPmList_t)pobj)->val,
                                  retval);
            break;

        case OBJ_TYPE_DIC:
            /* mark the dict head */
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
            /* mark the previous block */
            HEAP_MARK_IF_UNMARKED(((pPmBlock_t)pobj)->next,
                                  retval);
            break;

        case OBJ_TYPE_SEG:
            /* mark the segment obj head */
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
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
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
            /* mark the root segment */
            HEAP_MARK_IF_UNMARKED(
                ((pSeglist_t)pobj)->sl_rootseg,
                retval);
            break;

        case OBJ_TYPE_SQI:
            /* Mark the sequence iterator obj head */
            OBJ_SET_GCVAL(*pobj, pmHeap.gcval);
            
            /* Mark the sequence */
            HEAP_MARK_IF_UNMARKED(((pPmSeqIter_t)pobj)->si_sequence, retval);
            PM_RETURN_IF_ERROR(retval);
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

    /* Toggle the GC marking value so it differs from last pass */
    pmHeap.gcval ^= 1;

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


static
PmReturn_t
heap_sweep(void)
{
    PmReturn_t retval = PM_RET_OK;
    unsigned int pchunk;
    unsigned int pheapend;

    pchunk = (unsigned int)pmHeap.base;
    pheapend = pchunk + HEAP_SIZE - HEAP_MIN_CHUNK_SIZE;

    /* Traverse the heap */
    while (pchunk < pheapend)
    {
        /* Free unmarked chunks that aren't already free */
        if (!OBJ_GET_GCFREE(*(pPmObj_t)pchunk)
            && (OBJ_GET_GCVAL(*(pPmObj_t)pchunk) != pmHeap.gcval))
        {
            retval = heap_freeChunk((pPmObj_t)pchunk);
            PM_RETURN_IF_ERROR(retval);
        }

        /* Proceed to chunk next in memory */
        pchunk = pchunk + OBJ_GET_SIZE(*(pPmObj_t)pchunk);
    }

    return retval;
}


/**
 * Obtains a chunk of memory using a hybrid best fit algorithm.
 *
 * Stage 1:
 * Searches the free list for a chunk that is the requested size.
 * If found, that chunk is used.
 *
 * Stage 2:
 * If no chunk is found yet and the clean heap is large enough,
 * a new chunk is carved out of the clean heap and that chunk is used.
 *
 * Stage 3:
 * If no chunk is found yet and a larger-than-requested free list chunk
 * was found in Stage 1, that chunk is used.
 *
 * If still nothing, sets r_pchunk to null and raises an out-of-mem exception.
 *
 * @param size Requested chunk size
 * @param r_pchunk Return ptr to chunk
 * @return Return status
 */
static
PmReturn_t
heap_getChunkImpl(uint8_t size, uint8_t **r_pchunk)
{
    PmReturn_t retval;
    pPmHeapDesc_t pchunk1 = C_NULL;
    pPmHeapDesc_t pchunk2 = C_NULL;
    pPmHeapDesc_t pchunk3 = C_NULL;

    /* Stage 1: Check the free list for chunk of exact size (Best Fit) */
    if (pmHeap.pfreelist != C_NULL)
    {
        /* If the first chunk is the best fit, use it */
        if (OBJ_GET_SIZE(*pmHeap.pfreelist) == size)
        {
            *r_pchunk = (uint8_t *)pmHeap.pfreelist;
            pmHeap.avail -= OBJ_GET_SIZE(*pmHeap.pfreelist);
            pmHeap.pfreelist = pmHeap.pfreelist->next;
            return PM_RET_OK;
        }
        /* pchunk1 may be larger than requested (may use it in Stage 3) */

        /* Linear search for a chunk size equal or greater than requested */
        pchunk1 = pmHeap.pfreelist;
        pchunk2 = pmHeap.pfreelist->next;
        if (pchunk2 != C_NULL)
        {
            while ((pchunk2->next != C_NULL) && (OBJ_GET_SIZE(*pchunk2) < size))
            {
                 pchunk1 = pchunk2;
                 pchunk2 = pchunk2->next;
            }
        }

        /* If pchunk2 is the best fit, use it */
        if ((pchunk2 != C_NULL) && (OBJ_GET_SIZE(*pchunk2) == size))
        {
            *r_pchunk = (uint8_t *)pchunk2;
            pmHeap.avail -= OBJ_GET_SIZE(*pchunk2);
            pchunk1->next = pchunk2->next;
            return PM_RET_OK;
        }
        /* pchunk2 may be larger than requested (may use it in Stage 3) */
    }

    /* Stage 2: Check the clean heap (Best Fit) */
    /* If clean heap chunk is not big enough, free it and try next clean page */
    if ((pmHeap.pcleanheap != C_NULL)
        && (size > OBJ_GET_SIZE(*pmHeap.pcleanheap)))
    {
        pchunk3 = pmHeap.pcleanheap;
        pmHeap.pcleanheap = pmHeap.pcleanheap->next;
        pmHeap.avail -= OBJ_GET_SIZE(*pchunk3);
        heap_freeChunk((pPmObj_t)pchunk3);
    }

    /* If clean heap is big enough, get a chunk from it */
    if ((pmHeap.pcleanheap != C_NULL)
        && (OBJ_GET_SIZE(*pmHeap.pcleanheap) >= size))
    {
        /* If potential remnant is too small, use the entire chunk */
        if ((OBJ_GET_SIZE(*pmHeap.pcleanheap) - size) < HEAP_MIN_CHUNK_SIZE)
        {
            pchunk2 = pmHeap.pcleanheap;
            pmHeap.pcleanheap = pmHeap.pcleanheap->next;
        }

        /* Else carve chunk out of back of clean heap */
        else
        {
            /* Reduce the size of the clean heap */
            OBJ_SET_SIZE(*pmHeap.pcleanheap,
                         OBJ_GET_SIZE(*pmHeap.pcleanheap) - size);

            /* Create a new chunk and set its size */
            pchunk2 = (pPmHeapDesc_t)((uint8_t *)pmHeap.pcleanheap
                                      + OBJ_GET_SIZE(*pmHeap.pcleanheap));
            OBJ_SET_SIZE(*pchunk2, size);
        }

        /* Return the chunk and reduce heap available amount */
        *r_pchunk = (uint8_t *)pchunk2;
        pmHeap.avail -= size;
        return PM_RET_OK;
    }

    /* Stage 3: Try first fit from Stage 1 */

    /* If pchunk1 from Stage 1 is large enough, use it (First Fit) */
    if ((pchunk1 != C_NULL) && (OBJ_GET_SIZE(*pchunk1) >= size))
    {
        C_ASSERT(pchunk1 == pmHeap.pfreelist);

        *r_pchunk = (uint8_t *)pchunk1;
        pmHeap.avail -= OBJ_GET_SIZE(*pchunk1);
        pmHeap.pfreelist = pmHeap.pfreelist->next;
        return PM_RET_OK;
    }

    /* If pchunk2 from Stage 1 is large enough, use it (First Fit) */
    if ((pchunk2 != C_NULL) && (OBJ_GET_SIZE(*pchunk2) >= size))
    {
        *r_pchunk = (uint8_t *)pchunk2;
        pmHeap.avail -= OBJ_GET_SIZE(*pchunk2);
        pchunk1->next = pchunk2->next;
        return PM_RET_OK;
    }

    /* No chunk of appropriate size was found, return out-of-mem exception */
    *r_pchunk = C_NULL;
    PM_RAISE(retval, PM_RET_EX_MEM);
    return retval;
}


/*
 * Initializes the heap to a list of large chunks
 */
PmReturn_t
heap_init(void)
{
    pPmHeapDesc_t pchunk = C_NULL;
    uint16_t size = 0;

    /* Zero all memory in the heap (optional?) and other heap globals */
    sli_memset((uint8_t *)&pmHeap, '\0', sizeof(PmHeap_t));
    pmHeap.pfreelist = C_NULL;
    pmHeap.gcval = 0;

    /* Set amount of heap space remaining */
    pmHeap.avail = HEAP_SIZE;

    /* pcleanheap pts to list of large chunks */
    pmHeap.pcleanheap = (pPmHeapDesc_t)&pmHeap.base;
    pchunk = pmHeap.pcleanheap;

    /* Init list of large chunks */
    size = HEAP_SIZE;
    while (size > HEAP_MAX_CHUNK_SIZE)
    {
        OBJ_SET_SIZE(*pchunk, HEAP_MAX_CHUNK_SIZE);
        OBJ_SET_GCFREE(*pchunk, C_TRUE);
        pchunk->next = (pPmHeapDesc_t)((uint8_t *)pchunk + HEAP_MAX_CHUNK_SIZE);
        size -= HEAP_MAX_CHUNK_SIZE;
        pchunk = pchunk->next;
    }

    /* If last fragment can be a chunk, set its fields */
    if(size >= HEAP_MIN_CHUNK_SIZE)
    {
        OBJ_SET_SIZE(*pchunk, size);
        OBJ_SET_GCFREE(*pchunk, C_TRUE);
        pchunk->next = C_NULL;
    }

    /* If last fragment can't be a chunk, terminate penultimate chunk */
    else
    {
        pchunk = (pPmHeapDesc_t)((uint8_t *)pchunk - HEAP_MAX_CHUNK_SIZE);
        pchunk->next = C_NULL;

        /* Reduce heap available amount by size of unused last fragment */
        pmHeap.avail -= size;
    }

    return PM_RET_OK;
}


/*
 * High-level interface to get an allocated chunk of memory.
 * Filters out invalid sizes.  Rounds up to the next multiple of 4 for
 * 32-bit architectures.  Obtains a chunk of at least the desired size.
 * Performs GC if necessary and the global auto GC flag is enabled.
 */
PmReturn_t
heap_getChunk(uint8_t size, uint8_t **r_pchunk)
{
    PmReturn_t retval;

    /* Ensure size request is valid */
    C_ASSERT(size < HEAP_MAX_CHUNK_SIZE);

    if (size < HEAP_MIN_CHUNK_SIZE)
    {
        size = HEAP_MIN_CHUNK_SIZE;
    }

#if defined(TARGET_ARM) || defined(TARGET_DESKTOP)
    /* Round up to a multiple of 4 bytes (to maintain alignment) */
    size = ((size + 3) & ~3);
#endif

    /* If a chunk is available, return with it */
    retval = heap_getChunkImpl(size, r_pchunk);
#if defined(TARGET_ARM) || defined(TARGET_DESKTOP)
    C_ASSERT(((uint32_t)*r_pchunk & 3) == 0);
#endif

    /* If first attempt yielded no chunk and auto GC flag is asserted, run GC */
    if ((retval == PM_RET_EX_MEM) && (pmHeap.do_auto_gc))
    {
        retval = heap_markRoots();
        PM_RETURN_IF_ERROR(retval);

        retval = heap_sweep();
        PM_RETURN_IF_ERROR(retval);

        /* now, if a chunk is available, return with it */
        retval = heap_getChunkImpl(size, r_pchunk);
    }

    /* Indicate chunk is no longer free */
    OBJ_SET_GCFREE(**(pPmObj_t *)r_pchunk, C_FALSE);

    return retval;
}


/* Release chunk to free list which is sorted smallest to largest */
PmReturn_t
heap_freeChunk(pPmObj_t ptr)
{
    pPmHeapDesc_t oldchunk = (pPmHeapDesc_t)ptr;
    uint8_t size = OBJ_GET_SIZE(*ptr);
    pPmHeapDesc_t pchunk1;
    pPmHeapDesc_t pchunk2;

    C_ASSERT(((uint8_t *)ptr >= pmHeap.base)
             && ((uint8_t *)ptr < pmHeap.base + HEAP_SIZE));

    /* Indicate chunk is free and increase heap available amount */
    OBJ_SET_GCFREE(*ptr, C_TRUE);
    pmHeap.avail += OBJ_GET_SIZE(*ptr);

    /* If free list is empty or oldchunk is smallest, add to head of list */
    if ((pmHeap.pfreelist == C_NULL) || (OBJ_GET_SIZE(*pmHeap.pfreelist) >= size))
    {
        oldchunk->next = pmHeap.pfreelist;
        pmHeap.pfreelist = oldchunk;
        return PM_RET_OK;
    }

    /* If free list has only one item, append oldchunk */
    if (pmHeap.pfreelist->next == C_NULL)
    {
        oldchunk->next = C_NULL;
        pmHeap.pfreelist->next = oldchunk;
        return PM_RET_OK;
    }

    /* Scan free list for insertion point */
    pchunk1 = pmHeap.pfreelist;
    pchunk2 = pmHeap.pfreelist->next;
    while ((pchunk2->next != C_NULL) && (OBJ_GET_SIZE(*pchunk2) < size))
    {
        pchunk1 = pchunk2;
        pchunk2 = pchunk2->next;
    }

    /* Insert chunk into free list */
    oldchunk->next = pchunk2;
    pchunk1->next = oldchunk;

    return PM_RET_OK;
}


PmReturn_t
heap_getAvail(uint16_t *r_avail)
{
    *r_avail = pmHeap.avail;
    return PM_RET_OK;
}


PmReturn_t
heap_collectGarbage(void)
{
    PM_RETURN_IF_ERROR(heap_markRoots());
    return heap_sweep();
}


PmReturn_t
heap_setAutoGc(uint8_t bool)
{
    pmHeap.do_auto_gc = bool;
    return PM_RET_OK;
}
