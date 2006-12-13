/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2006 Dean Hall
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

/**
 * PyMite User API
 *
 * High-level functions to initialize and run PyMite
 *
 * Log
 * ---
 *
 * 2006/09/16   #16: Create pm_init() that does the initial housekeeping
 */

#include "pm.h"


extern unsigned char stdlib_img[];


PmReturn_t pm_init(PmMemSpace_t memspace, uint8_t *pusrimg)
{
    PmReturn_t retval;
    uint8_t *pimg;

    /* Initialize the heap and the globals */
    heap_init();
    retval = global_init();
    PM_RETURN_IF_ERROR(retval);

    /* Load std image info */
    pimg = (uint8_t *)&stdlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PM_RETURN_IF_ERROR(retval);

    /* Load usr image info if given */
    if (pusrimg != C_NULL)
    {
        pimg = pusrimg;
        retval = img_findInMem(memspace, &pimg);
    }

    return retval;
}


PmReturn_t pm_run(uint8_t *modstr)
{
    PmReturn_t retval;
    pPmObj_t pmod;
    pPmObj_t pstring;
    uint8_t *pmodstr = modstr;

    /* Import module from global struct */
    retval = string_new(&pmodstr, &pstring);
    PM_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmod);
    PM_RETURN_IF_ERROR(retval);

    /* Load builtins into root module */
    retval = global_loadBuiltins((pPmFunc_t)pmod);
    PM_RETURN_IF_ERROR(retval);

    /* Interpret the module's bcode */
    retval = interpret((pPmFunc_t)pmod);

    return retval;
}


#ifdef TARGET_DESKTOP

void pm_reportResult(PmReturn_t result)
{
    if (result == PM_RET_OK)
    {
        puts("Ok.");
    }
    else
    {
        printf("Error:     0x%02X\n", result);
        printf("  Release: 0x%02X\n", gVmGlobal.errVmRelease);
#if __DEBUG__
        printf("  FileId:  0x%02X\n", gVmGlobal.errFileId);
        printf("  LineNum: %d\n", gVmGlobal.errLineNum);
#endif
    }
}
#endif /* TARGET_DESKTOP */
