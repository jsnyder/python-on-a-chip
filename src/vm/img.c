#undef __FILE_ID__
#define __FILE_ID__ 0x07
/**
 * Image routines
 *
 * Created to eliminate a circular include
 * among mem, string and obj.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        img.c
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

#include "py.h"


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
PyReturn_t
img_findInMem(PyMemSpace_t memspace, P_U8 *paddr)
{
    PyReturn_t retval = PY_RET_ERR;
    P_U8 imgtop = 0;
    PyType_t type = 0;
    S16 size = 0;
    S8 n = 0;
    pPyImgInfo_t pii = C_NULL;
    pPyObj_t pnamestr = C_NULL;

    /* addr is top of img */
    imgtop = *paddr;
    /* get img's type byte */
    type = (PyType_t)mem_getByte(memspace, paddr);

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
            return PY_RET_EX_TYPE;
        }
        /* get index of last obj in tuple */
        n = mem_getByte(memspace, paddr) - 1;
        /* point to names tuple */
        *paddr = imgtop + CI_NAMES_FIELD;
        /* load name at index */
        retval = img_getName(memspace, paddr, n, &pnamestr);
        PY_RETURN_IF_ERROR(retval);

        /* alloc and fill imginfo struct */
        retval = heap_getChunk(sizeof(PyImgInfo_t), (P_U8 *)&pii);
        PY_RETURN_IF_ERROR(retval);
        pii->ii_name = (pPyString_t)pnamestr;
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


PyReturn_t
img_getName(PyMemSpace_t memspace, P_U8 *paddr, U8 n, pPyObj_t * r_pname)
{
    PyType_t type;
    U8 b;
    
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
        return PY_RET_EX_TYPE;
    }
    
    /* backtrack paddr to point to top of string img */
    (*paddr)--;
    /* return name string obj */
    return obj_loadFromImg(memspace, paddr, r_pname);
}
