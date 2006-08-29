#ifndef __IMG_H__
#define __IMG_H__
/**
 * Image header
 *
 * Created to eliminate a circular include
 * among mem, string and obj.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        img.h
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/17   First.
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
 * Image information struct.
 *
 * This struct holds the location information of a code image.
 * The VM maintains one linked list of these structs
 * as the sole list to search when a named code object
 * is to be loaded.
 */
 typedef struct PyImgInfo_s
 {
    /** the image's name as a String obj */
    pPyString_t         ii_name;
    /** the memory space in which the image is located */
    PyMemSpace_t        ii_memspace:8;
    /** the starting address of the image */
    P_U8                ii_addr;
    /** ptr to next image ID struct */
    struct PyImgInfo_s  *next;
 } PyImgInfo_t, *pPyImgInfo_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Scan code images in memory.
 *
 * Find consecutive code images in the given memory space
 * starting at the given address.  Store (name, address)
 * info for use when interpreter needs to load a module.
 *
 * @param   memspace the memory space to search.
 * @param   paddr ptr to address value to start search.
 * @return  Return status
 */
PyReturn_t img_findInMem(PyMemSpace_t memspace, P_U8 *paddr);

/**
 * Load a string obj from the names tuple at the given index.
 *
 * @param   memspace Memory space to use.
 * @param   paddr Ptr to address of names tuple image.
 * @param   n Index into tuple.
 * @param   r_pname Return parm, name string
 * @return  Return status
 */
PyReturn_t img_getName(PyMemSpace_t memspace,
                       P_U8 *paddr,
                       U8 n,
                       pPyObj_t * r_pname);


#endif /* __TEMPLATE_H__ */
