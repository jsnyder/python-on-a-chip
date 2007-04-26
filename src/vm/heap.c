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
 * 2007/02/02   #87: Redesign the heap
 * 2007/01/09   #75: Added thread type, fail correctly w/o GC (P.Adelt)
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
 * The chunk size is limited by the od_size field in the object descriptor.
 * Currently, that field is 8 bits.  Since the heap allocator already rounds
 * requested chunk sizes up to the next multiple of four, the lower two bits
 * are alway zero.  So, we can shift this adjusted size value to the right
 * two places which allows larger effective sizes.
 * The maximum size is now (2^10 - 1 == 1023), but it must be a multiple of
 * four to maintain alignment on some 32-bit platforms, so it becomes 1020.
 */
#define HEAP_MAX_CHUNK_SIZE 1020

/** The minimum size a chunk can be */
#define HEAP_MIN_CHUNK_SIZE sizeof(PmHeapDesc_t)


/***************************************************************
 * Types
 **************************************************************/

typedef struct PmHeap_s
{
    /** Ptr to list of free chunks; sorted smallest to largest. */
    pPmHeapDesc_t pfreelist;

    /** Ptr to clean heap (the big chunk) */
    uint8_t *pcleanheap;

    /** The number of bytes in the clean heap */
    uint16_t cleanheapavail;

    /** The amount of heap space available (free) */
    uint16_t avail;

    /** Global declaration of heap. */
    uint8_t base[HEAP_SIZE];
} PmHeap_t,
 *pPmHeap_t;


/***************************************************************
 * Globals
 **************************************************************/

/** The PyMite heap */
static PmHeap_t pmHeap;


/***************************************************************
 * Functions
 **************************************************************/

/*
 * Initializes the heap state variables
 */
PmReturn_t
heap_init(void)
{
    /* Init heap globals */
    pmHeap.pfreelist = C_NULL;
    pmHeap.pcleanheap = pmHeap.base;
    pmHeap.cleanheapavail = HEAP_SIZE;
    pmHeap.avail = HEAP_SIZE;

    string_cacheInit();

    return PM_RET_OK;
}


/**
 * Obtains a chunk of memory from the heap
 *
 * If there is enough memory in the cleanheap
 * a chunk is obtained from there;
 * otherwise, the first chunk of sufficient size is obtained
 * from the freelist.
 *
 * @param size Requested chunk size
 * @param r_pchunk Return ptr to chunk
 * @return Return status
 */
static PmReturn_t
heap_getChunkImpl(uint16_t size, uint8_t **r_pchunk)
{
    PmReturn_t retval;
    pPmHeapDesc_t pchunk1;
    pPmHeapDesc_t pchunk2;

    /* If there is enough memory in the cleanheap */
    if (pmHeap.cleanheapavail >= size)
    {
        /* Obtain a chunk, adjust the cleanheap and reduce the sizes */
        *r_pchunk = pmHeap.pcleanheap;
        pmHeap.pcleanheap += size;
        pmHeap.cleanheapavail -= size;
        pmHeap.avail -= size;

        /* Set the chunk's descriptor bits */
        pchunk1 = (pPmHeapDesc_t)*r_pchunk;
        OBJ_SET_SIZE(*pchunk1, size);

        /* Move the cleanheap remnant to the freelist if it is small enough */
        if (pmHeap.cleanheapavail <= HEAP_MAX_CHUNK_SIZE)
        {
            /*
             * TODO: this is optional since cleanheap will be whittled away
             * to a size the prevents the containing "if" to never be true
             */
        }

        return PM_RET_OK;
    }

    /* Otherwise, try to get a chunk from the freelist */
    if (pmHeap.pfreelist != C_NULL)
    {
        /* If the first chunk fits, use it */
        if (OBJ_GET_SIZE(*pmHeap.pfreelist) >= size)
        {
            *r_pchunk = (uint8_t *)pmHeap.pfreelist;
            pmHeap.avail -= OBJ_GET_SIZE(*pmHeap.pfreelist);
            pmHeap.pfreelist = pmHeap.pfreelist->next;
            return PM_RET_OK;
        }

        /* Linear search for a chunk size equal or greater than requested */
        pchunk1 = pmHeap.pfreelist;
        pchunk2 = pmHeap.pfreelist->next;
        if (pchunk2 != C_NULL)
        {
            while ((pchunk2->next != C_NULL)
                   && (OBJ_GET_SIZE(*pchunk2) < size))
            {
                pchunk1 = pchunk2;
                pchunk2 = pchunk2->next;
            }
        }

        /* If a chunk fits, use it */
        if (OBJ_GET_SIZE(*pchunk2) >= size)
        {
            *r_pchunk = (uint8_t *)pchunk2;
            pmHeap.avail -= OBJ_GET_SIZE(*pchunk2);
            pchunk1->next = pchunk2->next;
            return PM_RET_OK;
        }
    }

    /* No chunk of appropriate size was found, raise OutOfMemory exception */
    *r_pchunk = C_NULL;
    PM_RAISE(retval, PM_RET_EX_MEM);
    return retval;
}


/*
 * Allocates chunk of memory.
 * Filters out invalid sizes.
 * Rounds the size up to the next multiple of 4.
 * Obtains a chunk of at least the desired size.
 */
PmReturn_t
heap_getChunk(uint16_t requestedsize, uint8_t **r_pchunk)
{
    PmReturn_t retval;
    uint16_t adjustedsize;

    /* Ensure size request is valid */
    if (requestedsize > HEAP_MAX_CHUNK_SIZE)
    {
        PM_RAISE(retval, PM_RET_EX_MEM);
        return retval;
    }

    if (requestedsize < HEAP_MIN_CHUNK_SIZE)
    {
        requestedsize = HEAP_MIN_CHUNK_SIZE;
    }

    /*
     * Round up the size to a multiple of 4 bytes.
     * This maintains alignment on ARM7 and desktop (x86) platforms (required).
     * This also increases the reusability of chunks by making more of them
     * have a like size.  This also creates discrete chunk sizes that may help
     * search for chunk sizes quickly (depending on the implementation).
     */
    adjustedsize = ((requestedsize + 3) & ~3);

    /* Attempt to get a chunk */
    retval = heap_getChunkImpl(adjustedsize, r_pchunk);

    /* Ensure that the pointer is 4-byte aligned */
    C_ASSERT(((int)*r_pchunk & 3) == 0);

    return retval;
}


/* Inserts a chunk into the free list.  Caller must adjust heap state vars */
static PmReturn_t
heap_insert(pPmObj_t ptr)
{
    uint8_t size = OBJ_GET_SIZE(*ptr);
    pPmHeapDesc_t oldchunk = (pPmHeapDesc_t)ptr;
    pPmHeapDesc_t pchunk1;
    pPmHeapDesc_t pchunk2;

    /* If free list is empty or old chunk is smallest, add to head of list */
    if ((pmHeap.pfreelist == C_NULL)
        || (OBJ_GET_SIZE(*pmHeap.pfreelist) >= size))
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


/* Releases chunk to the free list */
PmReturn_t
heap_freeChunk(pPmObj_t ptr)
{
    PmReturn_t retval;

    /* Ensure the chunk falls within the heap */
    C_ASSERT(((uint8_t *)ptr >= pmHeap.base)
             && ((uint8_t *)ptr < pmHeap.base + HEAP_SIZE));

    /* Insert the chunk into the freelist */
    retval = heap_insert(ptr);
    PM_RETURN_IF_ERROR(retval);

    /* Increase heap available amount */
    pmHeap.avail += OBJ_GET_SIZE(*ptr);
    return retval;
}


/* Returns, by reference, the number of bytes available in the heap */
PmReturn_t
heap_getAvail(uint16_t *r_avail)
{
    *r_avail = pmHeap.avail;
    return PM_RET_OK;
}
