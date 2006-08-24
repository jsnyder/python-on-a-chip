#undef __FILE_ID__
#define __FILE_ID__ 0x05
/**
 * VM Globals
 *
 * VM globals operations.
 * Py's global struct def and initial values.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        global.c
 *
 * Log:
 *
 * 2002/04/22   First.
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

/**
 * Py VM configuration.
 * Static declarations declared here.
 * Dynamic changes to this struct are set in HERE.
 */
PyVmGlobal_t gVmGlobal;


/***************************************************************
 * Functions
 **************************************************************/

void
global_init(void)
{
    /* clear the entire global struct */
    sli_memset(&gVmGlobal, '\0', sizeof(PyVmGlobal_t));

    /* set the PyMite release num (for debug and post mortem) */
    gVmGlobal.errVmRelease = PY_RELEASE;

    /* init zero */
    gVmGlobal.zero.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.zero.od.od_size = sizeof(PyInt_t);
    gVmGlobal.zero.od.od_const = 1;
    gVmGlobal.zero.val = 0;

    /* init one */
    gVmGlobal.one.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.one.od.od_size = sizeof(PyInt_t);
    gVmGlobal.one.od.od_const = 1;
    gVmGlobal.one.val = 1;

    /* init negone */
    gVmGlobal.negone.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.negone.od.od_size = sizeof(PyInt_t);
    gVmGlobal.negone.od.od_const = 1;
    gVmGlobal.negone.val = (S32)-1;

    /* init None */
    gVmGlobal.none.od.od_type = OBJ_TYPE_NON;
    gVmGlobal.none.od.od_size = sizeof(PyObj_t);
    gVmGlobal.none.od.od_const = 1;

    /* init empty builtins */
    gVmGlobal.builtins = C_NULL;

    /* empty img info list */
    gVmGlobal.pimglist = C_NULL;

    /* clear ptrs */
    /*FP = C_NULL;*//* fp is local to interp, until thread struct is made */

    /* interpreter loop return value */
    gVmGlobal.interpctrl = INTERP_CTRL_CONT;

    return;
}


PyReturn_t
global_loadBuiltins(pPyFunc_t pmod)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pkey = C_NULL;
    P_S8 bistr = (P_S8)"__bi";
    P_S8 nonestr = (P_S8)"None";
    pPyObj_t pstr = C_NULL;
    pPyFunc_t pbimod = C_NULL;

    /* import the builtins */
    retval = string_new(&bistr, &pstr);
    PY_RETURN_IF_ERROR(retval);
    retval = mod_import(pstr, &pbimod);
    PY_RETURN_IF_ERROR(retval);

    /* must interpret builtins' root code to set the attrs */
    retval = interpret(pbimod);
    PY_RETURN_IF_ERROR(retval);

    /* reset interpreter to run */
    gVmGlobal.interpctrl = INTERP_CTRL_CONT;

    /* builtins points to the builtins module's attrs dict */
    gVmGlobal.builtins = pbimod->f_attrs;

    /* set None manually */
    retval = string_new(&nonestr, &pkey);
    PY_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPyObj_t)PY_PBUILTINS,
                          pkey,
                          PY_NONE);
    PY_RETURN_IF_ERROR(retval);

    /* put builtins module in the module's attrs dict */
    retval = string_new(&bistr, &pkey);
    PY_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPyObj_t)pmod->f_attrs,
                          pkey,
                          (pPyObj_t)PY_PBUILTINS);
    PY_RETURN_IF_ERROR(retval);

    /* deallocate builtins module */
    heap_freeChunk((pPyObj_t)pbimod);

    return PY_RET_OK;
}

/***************************************************************
 * Main
 **************************************************************/

/***************************************************************
 * Test
 **************************************************************/
