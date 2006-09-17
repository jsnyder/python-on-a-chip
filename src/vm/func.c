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
#define __FILE_ID__ 0x04
/**
 * Function Object Type
 *
 * Function object type operations.
 *
 * Log
 * ---
 *
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
func_new(pPyObj_t pco, pPyObj_t * r_pfunc)
{
    PyReturn_t retval = PY_RET_OK;
    pPyFunc_t pfunc = C_NULL;
    P_U8 pchunk;

    /* ensure pco pts to code obj or native obj */
    if ((pco->od.od_type != OBJ_TYPE_COB) &&
        (pco->od.od_type != OBJ_TYPE_NOB))
    {
        return PY_RET_EX_SYS;
    }

    /* allocate a func obj */
    retval = heap_getChunk(sizeof(PyFunc_t), &pchunk);
    PY_RETURN_IF_ERROR(retval);
    pfunc = (pPyFunc_t)pchunk;

    /* init func */
    pfunc->od.od_type = OBJ_TYPE_FXN;
    pfunc->f_co = (pPyCo_t)pco;
    /* create attrs dict for regular func (not native) */
    if (pco->od.od_type == OBJ_TYPE_COB)
    {
        retval = dict_new((pPyObj_t *)&pfunc->f_attrs);
        PY_RETURN_IF_ERROR(retval);
    }
    else
    {
        pfunc->f_attrs = C_NULL;
    }
    /* clear default args (will be set later, if at all) */
    pfunc->f_defaultargs = C_NULL;

    *r_pfunc = (pPyObj_t)pfunc;
    return PY_RET_OK;
}

/*
 * This function requires that all parameters have their
 * expected type.  (parm types already checked).
 *
 * Deprecated, there is no replacement.
 */
PyReturn_t
class_new(pPyObj_t pmeths,
          pPyObj_t pbases,
          pPyObj_t pname,
          pPyObj_t * r_pclass)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pkey = C_NULL;
    P_U8 btstr = (P_U8)"__bt";
    P_U8 nmstr = (P_U8)"__nm";

    /* ensure types */
    if ((pmeths->od.od_type != OBJ_TYPE_DIC) ||
        (pbases->od.od_type != OBJ_TYPE_TUP) ||
        (pname->od.od_type != OBJ_TYPE_STR))
    {
        return PY_RET_EX_TYPE;
    }

    /* allocate a class obj */
    retval = heap_getChunk(sizeof(PyFunc_t), (P_U8 *)r_pclass);
    PY_RETURN_IF_ERROR(retval);
    (*r_pclass)->od.od_type = OBJ_TYPE_CLO;
    /* class has no access to its CO */
    ((pPyFunc_t)*r_pclass)->f_co = C_NULL;
    ((pPyFunc_t)*r_pclass)->f_attrs = (pPyDict_t)pmeths;
    /* store base tuple in __bt slot */
    retval = string_new(&btstr, &pkey);
    PY_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPyObj_t)((pPyFunc_t)*r_pclass)->f_attrs,
                          pkey,
                          (pPyObj_t)pbases);
    PY_RETURN_IF_ERROR(retval);
    /* store the name of the class in the __nm slot */
    retval = string_new(&nmstr, &pkey);
    PY_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPyObj_t)((pPyFunc_t)*r_pclass)->f_attrs,
                          pkey,
                          (pPyObj_t)pname);
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
