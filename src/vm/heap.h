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
 * 2006/11/15   #53: Fix Win32/x86 build break
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

/***************************************************************
 * Macros
 **************************************************************/

#ifdef __DEBUG__
#define DEBUG_PRINT_HEAP_AVAIL(s) \
    do { uint16_t n; heap_getAvail(&n); printf(s "heap avail = %d\n", n); } \
    while (0)
#else
#define DEBUG_PRINT_HEAP_AVAIL(s)
#endif


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
PmReturn_t heap_init(void);

/**
 * Returns a free chunk from the heap.
 *
 * The chunk will be at least the requested size.
 * The actual size can be found in the return
 * chunk's od.od_size.
 * Garbage will be collected if necessary.
 *
 * @param   requestedsize Requested size of the chunk in bytes.
 * @param   r_pchunk Addr of ptr to chunk (return).
 * @return  Return code
 */
PmReturn_t heap_getChunk(uint16_t requestedsize, uint8_t **r_pchunk);

/**
 * Place the chunk back in the heap.
 *
 * @param   ptr Pointer to object to free.
 */
PmReturn_t heap_freeChunk(pPmObj_t);

/**
 * Returns the number of bytes available in the heap
 *
 * @param   r_avail Return arg; number of bytes available in the heap
 * @return  Return code
 */
PmReturn_t heap_getAvail(uint16_t *r_avail);

#endif /* __HEAP_H__ */
