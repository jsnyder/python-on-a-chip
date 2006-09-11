#undef __FILE_ID__
#define __FILE_ID__ 0x04
/**
 * Function Object Type
 *
 * Function object type operations.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        func.c
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

    /* ensure pco pts to code obj or native obj */
    if ((pco->od.od_type != OBJ_TYPE_COB) &&
        (pco->od.od_type != OBJ_TYPE_NOB))
    {
        return PY_RET_EX_SYS;
    }

    /* allocate a func obj */
    retval = heap_getChunk(sizeof(PyFunc_t), (P_U8 *)&pfunc);
    PY_RETURN_IF_ERROR(retval);

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
