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

#ifndef __HEAP_H__
#define __HEAP_H__
/**
 * VM Heap
 *
 * VM heap header.
 *
 * Log
 * ---
 *
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/08/31   Implemented freelist when chunk is deleted.
 * 2002/04/30   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/**
 * Static initial size of the heap.
 * A value should be provided by the makefile
 *
 * PORT:    Set the size of the entire heap.
 */
#ifndef HEAP_SIZE
#error HEAP_SIZE not defined by the build environment
#endif

/**
 * The maximum amount of internal fragmentation
 * (in bytes) allowed in an allocated chunk.
 *
 * PORT:    Set the desired frag limit.
 */
#define HEAP_MAX_FRAG_SIZE  2

/**
 * The maximum size a chunk can be.
 * Must be less than 256 since uint8_t is used to keep its size.
 * Set to 252 so it is 4 less than 256.
 * This helps with alignment for TARGET_ARM and doesn't harm other targets.
 */
#define HEAP_MAX_CHUNK_SIZE 252

/** The minimum size a chunk can be */
#define HEAP_MIN_CHUNK_SIZE sizeof(PmHeapDesc_t)


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

typedef struct PmHeapDesc_s
{
    /** object descriptor (only the size field is relevant */
    PmObjDesc_t od;
    /** ptr to next chunk */
    struct PmHeapDesc_s * next;
} PmHeapDesc_t, *pPmHeapDesc_t;


typedef struct PmHeap_s
{
    /** the amount of heap space available */
    uint16_t avail;

    /** Global declaration of heap. */
    uint8_t base[HEAP_SIZE];
} PmHeap_t, *pPmHeap_t;



/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Initialize the heap for use.
 *
 * Set the heap as one big chunk.
 *
 * @return  nothing.
 */
void heap_init(void);

/**
 * Returns a free chunk from the heap.
 *
 * The chunk will be at least the requested size.
 * The actual size can be found in the return
 * chunk's od.od_size.
 * Garbage will be collected if necessary.
 *
 * @param   size Size of the chunk in bytes.
 * @param   r_pchunk Addr of ptr to chunk (return).
 * @return  Return code
 */
PmReturn_t heap_getChunk(uint8_t size, uint8_t **r_pchunk);

/**
 * Place the chunk back in the heap.
 *
 * @param   ptr Pointer to object to free.
 */
void heap_freeChunk(pPmObj_t);

#endif /* __HEAP_H__ */
