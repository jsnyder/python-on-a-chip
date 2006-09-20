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
#define __FILE_ID__ 0x05
/**
 * VM Globals
 *
 * VM globals operations.
 * PyMite's global struct def and initial values.
 *
 * Log
 * ---
 *
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/22   First.
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

/** Most PyMite globals all in one convenient place */
PmVmGlobal_t gVmGlobal;


/***************************************************************
 * Functions
 **************************************************************/

PmReturn_t
global_init(void)
{
    PmReturn_t retval;
    uint8_t *codestr = (uint8_t *)"code";

    /* clear the global struct less the heap */
    sli_memset((uint8_t *)&gVmGlobal, '\0', sizeof(PmVmGlobal_t) -
                                            sizeof(PmHeap_t));

    /* set the PyMite release num (for debug and post mortem) */
    gVmGlobal.errVmRelease = PM_RELEASE;

    /* init zero */
    gVmGlobal.zero.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.zero.od.od_size = sizeof(PmInt_t);
    gVmGlobal.zero.od.od_const = 1;
    gVmGlobal.zero.val = 0;

    /* init one */
    gVmGlobal.one.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.one.od.od_size = sizeof(PmInt_t);
    gVmGlobal.one.od.od_const = 1;
    gVmGlobal.one.val = 1;

    /* init negone */
    gVmGlobal.negone.od.od_type = OBJ_TYPE_INT;
    gVmGlobal.negone.od.od_size = sizeof(PmInt_t);
    gVmGlobal.negone.od.od_const = 1;
    gVmGlobal.negone.val = (uint32_t)-1;

    /* init None */
    gVmGlobal.none.od.od_type = OBJ_TYPE_NON;
    gVmGlobal.none.od.od_size = sizeof(PmObj_t);
    gVmGlobal.none.od.od_const = 1;

    /* Init "code" string obj */
    retval = string_new((uint8_t **)&codestr, (pPmObj_t *)&gVmGlobal.pcodeStr);

    /* init empty builtins */
    gVmGlobal.builtins = C_NULL;

    /* empty img info list */
    gVmGlobal.pimglist = C_NULL;

    /* clear ptrs */
    /*FP = C_NULL;*//* fp is local to interp, until thread struct is made */

    /* interpreter loop return value */
    gVmGlobal.interpctrl = INTERP_CTRL_CONT;

    return retval;
}


PmReturn_t
global_loadBuiltins(pPmFunc_t pmod)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    uint8_t *bistr = (uint8_t *)"__bi";
    uint8_t *nonestr = (uint8_t *)"None";
    pPmObj_t pstr = C_NULL;
    pPmObj_t pbimod;

    /* import the builtins */
    retval = string_new(&bistr, &pstr);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstr, &pbimod);
    PM_RETURN_IF_ERROR(retval);

    /* must interpret builtins' root code to set the attrs */
    retval = interpret((pPmFunc_t)pbimod);
    PM_RETURN_IF_ERROR(retval);

    /* reset interpreter to run */
    gVmGlobal.interpctrl = INTERP_CTRL_CONT;

    /* builtins points to the builtins module's attrs dict */
    gVmGlobal.builtins = ((pPmFunc_t)pbimod)->f_attrs;

    /* set None manually */
    retval = string_new(&nonestr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem(PM_PBUILTINS, pkey, PM_NONE);
    PM_RETURN_IF_ERROR(retval);

    /* put builtins module in the module's attrs dict */
    retval = string_new(&bistr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem((pPmObj_t)pmod->f_attrs, pkey, PM_PBUILTINS);
    PM_RETURN_IF_ERROR(retval);

    /* deallocate builtins module */
    heap_freeChunk((pPmObj_t)pbimod);

    return PM_RET_OK;
}

/***************************************************************
 * Main
 **************************************************************/

/***************************************************************
 * Test
 **************************************************************/
