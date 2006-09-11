#ifndef __HEAP_H__
#define __HEAP_H__
/**
 * VM Heap
 *
 * VM heap header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
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

/** The maximum size a chunk can be */
#define HEAP_MAX_CHUNK_SIZE 255

/** The minimum size a chunk can be */
#define HEAP_MIN_CHUNK_SIZE sizeof(PyHeapDesc_t)


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

typedef struct PyHeapDesc_s
{
    /** object descriptor (only the size field is relevant */
    PyObjDesc_t od;
    /** ptr to next chunk */
    struct PyHeapDesc_s * next;
} PyHeapDesc_t, *pPyHeapDesc_t;


typedef struct PyHeap_s
{
    /** the amount of heap space available */
    U16 avail;

    /** Global declaration of heap. */
    U8 base[HEAP_SIZE];
} PyHeap_t, *pPyHeap_t;



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
PyReturn_t heap_getChunk(U8 size, P_U8 *r_pchunk);

/**
 * Place the chunk back in the heap.
 *
 * @param   ptr Pointer to object to free.
 */
void heap_freeChunk(pPyObj_t);

#endif /* __HEAP_H__ */
