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

PyReturn_t
mod_new(pPyCo_t pco, pPyFunc_t * pmod)
{
    PyReturn_t retval = PY_RET_OK;

    /* XXX ensure pco pts to code obj? */

    /* alloc and init func obj */
    retval = heap_getChunk(sizeof(PyFunc_t), (P_U8 *)pmod);
    PY_RETURN_IF_ERROR(retval);
    (*pmod)->od.od_type = OBJ_TYPE_MOD;
    (*pmod)->f_co = pco;

    /* alloc and init attrs dict */
    retval = dict_new((pPyObj_t *)&((*pmod)->f_attrs));
    return retval;
}


PyReturn_t
mod_import(pPyObj_t pstr, pPyFunc_t * pmod)
{
    pPyImgInfo_t pii = C_NULL;
    P_U8 imgaddr = C_NULL;
    pPyCo_t pco = C_NULL;
    PyReturn_t retval = PY_RET_OK;

    /* if it's not a string obj, raise SystemError */
    if (pstr->od.od_type != OBJ_TYPE_STR)
    {
        return PY_RET_EX_SYS;
    }

    /* iterate through the global img list */
    pii = gVmGlobal.pimglist;
    /* while not at end of list and string doesn't match */
    while ((pii != C_NULL)
           && (string_compare((pPyString_t)pstr, pii->ii_name) == C_DIFFER))
    {
        pii = pii->next;
    }

    /* if img was not found, raise ImportError */
    if (pii == C_NULL)
    {
        return PY_RET_EX_IMPRT;
    }

    /* make copy of addr */
    imgaddr = pii->ii_addr;

    /* load img into code obj */
    retval = obj_loadFromImg(pii->ii_memspace, &imgaddr, (pPyObj_t *)&pco);
    PY_RETURN_IF_ERROR(retval);

    return mod_new(pco, pmod);
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
