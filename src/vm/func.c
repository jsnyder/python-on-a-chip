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
func_new(pPmObj_t pco, pPmObj_t * r_pfunc)
{
    PmReturn_t retval = PM_RET_OK;
    pPmFunc_t pfunc = C_NULL;
    P_U8 pchunk;

    /* ensure pco pts to code obj or native obj */
    if ((pco->od.od_type != OBJ_TYPE_COB) &&
        (pco->od.od_type != OBJ_TYPE_NOB))
    {
        return PM_RET_EX_SYS;
    }

    /* allocate a func obj */
    retval = heap_getChunk(sizeof(PmFunc_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pfunc = (pPmFunc_t)pchunk;

    /* init func */
    pfunc->od.od_type = OBJ_TYPE_FXN;
    pfunc->f_co = (pPmCo_t)pco;
    /* create attrs dict for regular func (not native) */
    if (pco->od.od_type == OBJ_TYPE_COB)
    {
        retval = dict_new((pPmObj_t *)&pfunc->f_attrs);
        PM_RETURN_IF_ERROR(retval);
    }
    else
    {
        pfunc->f_attrs = C_NULL;
    }
    /* clear default args (will be set later, if at all) */
    pfunc->f_defaultargs = C_NULL;

    *r_pfunc = (pPmObj_t)pfunc;
    return PM_RET_OK;
}

/*
 * This function requires that all parameters have their
 * expected type.  (parm types already checked).
 *
 * Deprecated, there is no replacement.
 */
PmReturn_t
class_new(pPmObj_t pmeths,
          pPmObj_t pbases,
          pPmObj_t pname,
          pPmObj_t * r_pclass)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    P_U8 btstr = (P_U8)"__bt";
    P_U8 nmstr = (P_U8)"__nm";

    /* ensure types */
    if ((pmeths->od.od_type != OBJ_TYPE_DIC) ||
        (pbases->od.od_type != OBJ_TYPE_TUP) ||
        (pname->od.od_type != OBJ_TYPE_STR))
    {
        return PM_RET_EX_TYPE;
    }

    /* allocate a class obj */
    retval = heap_getChunk(sizeof(PmFunc_t), (P_U8 *)r_pclass);
    PM_RETURN_IF_ERROR(retval);
    (*r_pclass)->od.od_type = OBJ_TYPE_CLO;
    /* class has no access to its CO */
    ((pPmFunc_t)*r_pclass)->f_co = C_NULL;
    ((pPmFunc_t)*r_pclass)->f_attrs = (pPmDict_t)pmeths;
    /* store base tuple in __bt slot */
    retval = string_new(&btstr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPmObj_t)((pPmFunc_t)*r_pclass)->f_attrs,
                          pkey,
                          (pPmObj_t)pbases);
    PM_RETURN_IF_ERROR(retval);
    /* store the name of the class in the __nm slot */
    retval = string_new(&nmstr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPmObj_t)((pPmFunc_t)*r_pclass)->f_attrs,
                          pkey,
                          (pPmObj_t)pname);
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
