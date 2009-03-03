/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __IMG_H__
#define __IMG_H__


/**
 * Image header
 *
 * Created to eliminate a circular include
 * among mem, string and obj.
 */


/** The maximum number of paths available in PmImgPaths */
#define PM_NUM_IMG_PATHS 4


typedef struct PmImgPaths_s
{
    PmMemSpace_t memspace[PM_NUM_IMG_PATHS];
    uint8_t const *pimg[PM_NUM_IMG_PATHS];
    uint8_t pathcount;
}
PmImgPaths_t, *pPmImgPaths_t;


/**
 * Iterates over all paths in the paths array until the named module is found.
 * Returns the memspace,address of the head of the module.
 *
 * @param pname Pointer to the name of the desired module
 * @param r_memspace Return by reference the memory space of the module
 * @param r_imgaddr Return by reference the address of the module's image
 * @return Return status
 */
PmReturn_t img_findInPaths(pPmObj_t pname, PmMemSpace_t *r_memspace,
    uint8_t const **r_imgaddr);

/**
 * Appends the given memspace and address to the image path array
 *
 * @param memspace The memspace
 * @param paddr The address
 * @return Return status
 */
PmReturn_t img_appendToPath(PmMemSpace_t memspace, uint8_t *paddr);

#endif /* __IMG_H__ */
