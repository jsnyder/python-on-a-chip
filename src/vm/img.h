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

#ifndef __IMG_H__
#define __IMG_H__

/**
 * Image header
 *
 * Created to eliminate a circular include
 * among mem, string and obj.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/17   First.
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


/***************************************************************
 * Prototypes
 **************************************************************/

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
