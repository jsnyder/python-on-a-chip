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
 * 2007/01/09   #75: Restructured for green threads (P.Adelt)
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

uint8_t *global_bistr = (uint8_t *)"__bi";

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
volatile PmVmGlobal_t gVmGlobal;


/***************************************************************
 * Functions
 **************************************************************/

PmReturn_t
global_init(void)
{
    PmReturn_t retval;
    uint8_t *codestr = (uint8_t *)"code";
    pPmObj_t pobj;

    /* clear the global struct */
    sli_memset((uint8_t *)&gVmGlobal, '\0', sizeof(PmVmGlobal_t));

    /* set the PyMite release num (for debug and post mortem) */
    gVmGlobal.errVmRelease = PM_RELEASE;

    /* init zero */
    OBJ_SET_TYPE(gVmGlobal.zero, OBJ_TYPE_INT);
    OBJ_SET_SIZE(gVmGlobal.zero, sizeof(PmInt_t));
    gVmGlobal.zero.val = (int32_t)0;

    /* init one */
    OBJ_SET_TYPE(gVmGlobal.one, OBJ_TYPE_INT);
    OBJ_SET_SIZE(gVmGlobal.one, sizeof(PmInt_t));
    gVmGlobal.one.val = (int32_t)1;

    /* init negone */
    OBJ_SET_TYPE(gVmGlobal.negone, OBJ_TYPE_INT);
    OBJ_SET_SIZE(gVmGlobal.negone, sizeof(PmInt_t));
    gVmGlobal.negone.val = (int32_t)-1;

    /* init None */
    OBJ_SET_TYPE(gVmGlobal.none, OBJ_TYPE_NON);
    OBJ_SET_SIZE(gVmGlobal.none, sizeof(PmObj_t));

    /* Init "code" string obj */
    retval = string_new((uint8_t **)&codestr, &pobj);
    gVmGlobal.pcodeStr = (pPmString_t)pobj;

    /* init empty builtins */
    gVmGlobal.builtins = C_NULL;

    /* empty img info list */
    gVmGlobal.pimglist = C_NULL;

    /* clear ptrs */
    /*FP = C_NULL;*//* fp is local to interp, until thread struct is made */
    
    /* create empty threadList */
    list_new((pPmObj_t*)&(gVmGlobal.threadList));

    return retval;
}

PmReturn_t
global_setBuiltins(pPmFunc_t pmod)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    
    if (PM_PBUILTINS == C_NULL)
    {
        /* need to load builtins first */
        global_loadBuiltins();
    }
    /* put builtins module in the module's attrs dict */
    retval = string_new(&global_bistr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    return dict_setItem((pPmObj_t)pmod->f_attrs, pkey, PM_PBUILTINS);
}


PmReturn_t
global_loadBuiltins(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    uint8_t *nonestr = (uint8_t *)"None";
    pPmObj_t pstr = C_NULL;
    pPmObj_t pbimod;

    /* import the builtins */
    retval = string_new(&global_bistr, &pstr);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstr, &pbimod);
    PM_RETURN_IF_ERROR(retval);

    /* must interpret builtins' root code to set the attrs */
    C_ASSERT(gVmGlobal.threadList->length == 0);
    interp_addThread((pPmFunc_t)pbimod);
    retval = interpret(INTERP_RETURN_ON_NO_THREADS);
    PM_RETURN_IF_ERROR(retval);

    /* builtins points to the builtins module's attrs dict */
    gVmGlobal.builtins = ((pPmFunc_t)pbimod)->f_attrs;

    /* set None manually */
    retval = string_new(&nonestr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem(PM_PBUILTINS, pkey, PM_NONE);
    PM_RETURN_IF_ERROR(retval);

    /* deallocate builtins module */
    retval = heap_freeChunk((pPmObj_t)pbimod);

    return retval;
}

/***************************************************************
 * Main
 **************************************************************/

/***************************************************************
 * Test
 **************************************************************/
