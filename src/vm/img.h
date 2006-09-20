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
 typedef struct PmImgInfo_s
 {
    /** the image's name as a String obj */
    pPmString_t         ii_name;
    /** the memory space in which the image is located */
    PmMemSpace_t        ii_memspace:8;
    /** the starting address of the image */
    P_U8                ii_addr;
    /** ptr to next image ID struct */
    struct PmImgInfo_s  *next;
 } PmImgInfo_t, *pPmImgInfo_t;


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
PmReturn_t img_findInMem(PmMemSpace_t memspace, P_U8 *paddr);

/**
 * Load a string obj from the names tuple at the given index.
 *
 * @param   memspace Memory space to use.
 * @param   paddr Ptr to address of names tuple image.
 * @param   n Index into tuple.
 * @param   r_pname Return parm, name string
 * @return  Return status
 */
PmReturn_t img_getName(PmMemSpace_t memspace,
                       P_U8 *paddr,
                       U8 n,
                       pPmObj_t * r_pname);


#endif /* __TEMPLATE_H__ */
