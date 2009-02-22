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


extern unsigned char stdlib_img[];

/***************************************************************
 * Constants
 **************************************************************/

static uint8_t const *bistr = (uint8_t const *)"__bi";


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
    uint8_t *pchunk;
    pPmObj_t pobj;

    /* Clear the global struct */
    sli_memset((uint8_t *)&gVmGlobal, '\0', sizeof(PmVmGlobal_t));

    /* Set the PyMite release num (for debug and post mortem) */
    gVmGlobal.errVmRelease = PM_RELEASE;

    /* Init zero */
    retval = heap_getChunk(sizeof(PmInt_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_INT);
    ((pPmInt_t)pobj)->val = (int32_t)0;
    gVmGlobal.pzero = (pPmInt_t)pobj;

    /* Init one */
    retval = heap_getChunk(sizeof(PmInt_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_INT);
    ((pPmInt_t)pobj)->val = (int32_t)1;
    gVmGlobal.pone = (pPmInt_t)pobj;

    /* Init negone */
    retval = heap_getChunk(sizeof(PmInt_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_INT);
    ((pPmInt_t)pobj)->val = (int32_t)-1;
    gVmGlobal.pnegone = (pPmInt_t)pobj;

    /* Init False */
    retval = heap_getChunk(sizeof(PmBoolean_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_BOOL);
    ((pPmBoolean_t)pobj)->val = (int32_t)C_FALSE;
    gVmGlobal.pfalse = (pPmInt_t)pobj;

    /* Init True */
    retval = heap_getChunk(sizeof(PmBoolean_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_BOOL);
    ((pPmBoolean_t)pobj)->val = (int32_t)C_TRUE;
    gVmGlobal.ptrue = (pPmInt_t)pobj;

    /* Init None */
    retval = heap_getChunk(sizeof(PmObj_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pobj = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(pobj, OBJ_TYPE_NON);
    gVmGlobal.pnone = pobj;

    /* Init "code" string obj */
    retval = string_new((uint8_t const **)&codestr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    gVmGlobal.pcodeStr = (pPmString_t)pobj;

    /* Init empty builtins */
    gVmGlobal.builtins = C_NULL;

    /* Init native frame */
    OBJ_SET_SIZE(&gVmGlobal.nativeframe, sizeof(PmNativeFrame_t));
    OBJ_SET_TYPE(&gVmGlobal.nativeframe, OBJ_TYPE_NFM);

    /* Create empty threadList */
    retval = list_new(&pobj);
    gVmGlobal.threadList = (pPmList_t)pobj;

    /* Init the PmImgPaths with std image info */
    gVmGlobal.imgPaths.memspace[0] = MEMSPACE_PROG;
    gVmGlobal.imgPaths.pimg[0] = (uint8_t *)&stdlib_img;
    gVmGlobal.imgPaths.pathcount = 1;

    return retval;
}


PmReturn_t
global_setBuiltins(pPmFunc_t pmod)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    uint8_t const *pbistr = bistr;

    if (PM_PBUILTINS == C_NULL)
    {
        /* Need to load builtins first */
printf("before: (%d, %d)\n", heap_getAvail(), 8*1024);
        global_loadBuiltins();
printf("after:  (%d, %d)\n", heap_getAvail(), 8*1024);
    }

    /* Put builtins module in the module's attrs dict */
    retval = string_new(&pbistr, &pkey);
    PM_RETURN_IF_ERROR(retval);

    return dict_setItem((pPmObj_t)pmod->f_attrs, pkey, PM_PBUILTINS);
}


PmReturn_t
global_loadBuiltins(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pkey = C_NULL;
    uint8_t const *nonestr = (uint8_t const *)"None";
    uint8_t const *falsestr = (uint8_t const *)"False";
    uint8_t const *truestr = (uint8_t const *)"True";
    pPmObj_t pstr = C_NULL;
    pPmObj_t pbimod;
    uint8_t const *pbistr = bistr;

    /* Import the builtins */
    retval = string_new(&pbistr, &pstr);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstr, &pbimod);
    PM_RETURN_IF_ERROR(retval);

    /* Must interpret builtins' root code to set the attrs */
    C_ASSERT(gVmGlobal.threadList->length == 0);
    interp_addThread((pPmFunc_t)pbimod);
    retval = interpret(INTERP_RETURN_ON_NO_THREADS);
    PM_RETURN_IF_ERROR(retval);

    /* Builtins points to the builtins module's attrs dict */
    gVmGlobal.builtins = ((pPmFunc_t)pbimod)->f_attrs;

    /* Set None manually */
    retval = string_new(&nonestr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem(PM_PBUILTINS, pkey, PM_NONE);
    PM_RETURN_IF_ERROR(retval);

    /* Set False manually */
    retval = string_new(&falsestr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem(PM_PBUILTINS, pkey, PM_FALSE);
    PM_RETURN_IF_ERROR(retval);

    /* Set True manually */
    retval = string_new(&truestr, &pkey);
    PM_RETURN_IF_ERROR(retval);
    retval = dict_setItem(PM_PBUILTINS, pkey, PM_TRUE);
    PM_RETURN_IF_ERROR(retval);

    /* Deallocate builtins module */
    retval = heap_freeChunk((pPmObj_t)pbimod);

    return retval;
}


/***************************************************************
 * Main
 **************************************************************/

/***************************************************************
 * Test
 **************************************************************/
