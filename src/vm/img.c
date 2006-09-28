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
#define __FILE_ID__ 0x07
/**
 * Image routines
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

#include "pm.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

/*
 * An image identified by its first byte, the type OBJ_TYPE_CIM.
 * If the given address does not point to a byte with the
 * same value as OBJ_TYPE_CIM, the starting address is bogus
 * and the function returns.
 * Otherwise, it is assumed a valid image begins at that address
 * and it should be read for identification.
 * Root objects cannot be of type OBJ_TYPE_NIM (native objs).
 *
 * The name of the image is always the last entry
 * in the co_names field.  When the name is found,
 * the string is extracted, and--along with the memspace
 * and address info--is inserted into an entry in
 * the global struct which lists all modules.
 *
 * Multiple images are obtained by scanning the memory
 * immediately following the current until the type byte
 * no longer identifies a code image, or some other error
 * occurs.
 *
 * XXX Images with same module name will be blindly inserted
 * into list.  Need to support calling import twice on an obj
 * without filling memory.
 */
PmReturn_t
img_findInMem(PmMemSpace_t memspace, uint8_t **paddr)
{
    PmReturn_t retval = PM_RET_ERR;
    uint8_t *imgtop = 0;
    PmType_t type = 0;
    int16_t size = 0;
    uint8_t n = 0;
    pPmImgInfo_t pii = C_NULL;
    pPmObj_t pnamestr = C_NULL;
    uint8_t *pchunk;

    /* addr is top of img */
    imgtop = *paddr;
    /* get img's type byte */
    type = (PmType_t)mem_getByte(memspace, paddr);

    /* get all sequential images */
    while (type == OBJ_TYPE_CIM)
    {
        /* use size field to calc addr of next potential img */
        size = mem_getWord(memspace, paddr);

        /* get name of img */
        /* point to names tuple */
        *paddr = imgtop + CI_NAMES_FIELD;
        /* ensure it's a tuple */
        type = mem_getByte(memspace, paddr);
        if (type != OBJ_TYPE_TUP)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE, __LINE__);
            return retval;
        }
        /* get index of last obj in tuple */
        n = mem_getByte(memspace, paddr) - 1;
        /* point to names tuple */
        *paddr = imgtop + CI_NAMES_FIELD;
        /* load name at index */
        retval = img_getName(memspace, paddr, n, &pnamestr);
        PM_RETURN_IF_ERROR(retval);

        /* alloc and fill imginfo struct */
        retval = heap_getChunk(sizeof(PmImgInfo_t), &pchunk);
        PM_RETURN_IF_ERROR(retval);
        pii = (pPmImgInfo_t)pchunk;
        pii->ii_name = (pPmString_t)pnamestr;
        pii->ii_memspace = memspace;
        pii->ii_addr = imgtop;
        /* push struct into img stack */
        pii->next = gVmGlobal.pimglist;
        gVmGlobal.pimglist = pii;

        /* setup for next iteration */
        /* calc next imgtop */
        imgtop += size;
        /* point to next potential img */
        *paddr = imgtop;
        /* check if next is img */
        type = mem_getByte(memspace, paddr);
    }
    return retval;
}


PmReturn_t
img_getName(PmMemSpace_t memspace,
            uint8_t **paddr,
            uint8_t n,
            pPmObj_t *r_pname)
{
    PmType_t type;
    uint8_t b;
    PmReturn_t retval;

    /* XXX ensure it's a tuple */
    /* skip past type and size bytes */
    *paddr += 2;

    /* scan to last name */
    for ( ; n > 0; n--)
    {
        /* skip type byte, assuming string */
        (*paddr)++;
        /* skip the length of the string */
        b = mem_getByte(memspace, paddr);
        (*paddr) += b;
    }

    /* ensure it's a string */
    type = mem_getByte(memspace, paddr);
    if (type != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE, __LINE__);
        return retval;
    }

    /* backtrack paddr to point to top of string img */
    (*paddr)--;
    /* return name string obj */
    return obj_loadFromImg(memspace, paddr, r_pname);
}
