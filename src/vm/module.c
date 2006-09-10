#undef __FILE_ID__
#define __FILE_ID__ 0x0E
/**
 * Module Object Type
 *
 * Module object type operations.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        module.c
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
