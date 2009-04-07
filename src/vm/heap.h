/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __HEAP_H__
#define __HEAP_H__


/**
 * VM Heap
 *
 * VM heap header.
 */


/**
 * The threshold of heap.avail under which the interpreter will run the GC
 * just before starting a native session.
 */
#define HEAP_GC_NF_THRESHOLD (1024)


#ifdef __DEBUG__
#define DEBUG_PRINT_HEAP_AVAIL(s) \
    do { uint16_t n; heap_getAvail(&n); printf(s "heap avail = %d\n", n); } \
    while (0)
#else
#define DEBUG_PRINT_HEAP_AVAIL(s)
#endif


/**
 * Initializes the heap for use.
 *
 * @return  nothing.
 */
PmReturn_t heap_init(void);

/**
 * Returns a free chunk from the heap.
 *
 * The chunk will be at least the requested size.
 * The actual size can be found in the return chunk's od.od_size.
 *
 * @param   requestedsize Requested size of the chunk in bytes.
 * @param   r_pchunk Addr of ptr to chunk (return).
 * @return  Return code
 */
PmReturn_t heap_getChunk(uint16_t requestedsize, uint8_t **r_pchunk);

/**
 * Places the chunk back in the heap.
 *
 * @param   ptr Pointer to object to free.
 */
PmReturn_t heap_freeChunk(pPmObj_t ptr);

/** @return  Return number of bytes available in the heap */
#if HEAP_SIZE > 65535
uint32_t
#else
uint16_t
#endif
  heap_getAvail(void);

#ifdef HAVE_GC
/**
 * Runs the mark-sweep garbage collector
 *
 * @return  Return code
 */
PmReturn_t heap_gcRun(void);

/**
 * Enables (if true) or disables automatic garbage collection
 *
 * @param   bool Value to enable or disable auto GC
 * @return  Return code
 */
PmReturn_t heap_gcSetAuto(uint8_t auto_gc);
#endif /* HAVE_GC */

#endif /* __HEAP_H__ */
