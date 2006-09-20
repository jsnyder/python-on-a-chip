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
#define __FILE_ID__ 0x0E
/**
 * Module Object Type
 *
 * Module object type operations.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/04   First.
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

PmReturn_t
mod_new(pPmObj_t pco, pPmObj_t * pmod)
{
    PmReturn_t retval;
    P_U8 pchunk;

    /* if it's not a code obj, raise TypeError */
    if (pco->od.od_type != OBJ_TYPE_COB)
    {
        return PM_RET_EX_TYPE;
    }

    /* alloc and init func obj */
    retval = heap_getChunk(sizeof(PmFunc_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    *pmod = (pPmObj_t)pchunk;
    (*pmod)->od.od_type = OBJ_TYPE_MOD;
    ((pPmFunc_t)*pmod)->f_co = (pPmCo_t)pco;

    /* alloc and init attrs dict */
    retval = dict_new((pPmObj_t *)&((pPmFunc_t)*pmod)->f_attrs);
    return retval;
}


PmReturn_t
mod_import(pPmObj_t pstr, pPmObj_t * pmod)
{
    pPmImgInfo_t pii = C_NULL;
    P_U8 imgaddr = C_NULL;
    pPmCo_t pco = C_NULL;
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj;

    /* if it's not a string obj, raise SyntaxError */
    if (pstr->od.od_type != OBJ_TYPE_STR)
    {
        return PM_RET_EX_SYNTAX;
    }

    /* iterate through the global img list */
    pii = gVmGlobal.pimglist;
    /* while not at end of list and string doesn't match */
    while ((pii != C_NULL)
           && (string_compare((pPmString_t)pstr, pii->ii_name) == C_DIFFER))
    {
        pii = pii->next;
    }

    /* if img was not found, raise ImportError */
    if (pii == C_NULL)
    {
        return PM_RET_EX_IMPRT;
    }

    /* make copy of addr */
    imgaddr = pii->ii_addr;

    /* load img into code obj */
    retval = obj_loadFromImg(pii->ii_memspace, &imgaddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco = (pPmCo_t)pobj;

    return mod_new((pPmObj_t)pco, pmod);
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
