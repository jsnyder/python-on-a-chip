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

#undef __FILE_ID__
#define __FILE_ID__ 0x15
/**
 * PyMite User API
 *
 * High-level functions to initialize and run PyMite
 *
 * Log
 * ---
 *
 * 2007/01/09   #75: Refactored for green thread support (P.Adelt)
 * 2006/09/16   #16: Create pm_init() that does the initial housekeeping
 */

#include "pm.h"


/** Number of millisecond-ticks to pass before scheduler is run */
#define PM_THREAD_TIMESLICE_MS  10

extern unsigned char stdlib_img[];

/* Stores the timer millisecond-ticks since system start */
volatile uint32_t pm_timerMsTicks = 0;
/* Stores tick timestamp of last scheduler run */
volatile uint32_t pm_lastRescheduleTimestamp = 0;

PmReturn_t pm_init(PmMemSpace_t memspace, uint8_t *pusrimg)
{
    PmReturn_t retval;
    uint8_t *pimg;

    /* Initialize the hardware platform */
    retval = plat_init();
    PM_RETURN_IF_ERROR(retval);

    /* Initialize the heap and the globals */
    retval = heap_init();
    PM_RETURN_IF_ERROR(retval);

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

    /* Load builtins into thread */
    retval = global_setBuiltins((pPmFunc_t)pmod);
    PM_RETURN_IF_ERROR(retval);

    /* Interpret the module's bcode */
    retval = interp_addThread((pPmFunc_t)pmod);
    PM_RETURN_IF_ERROR(retval);
    retval = interpret(INTERP_RETURN_ON_NO_THREADS);

    return retval;
}

void pm_printError(PmReturn_t result)
{
#ifdef TARGET_DESKTOP
        printf("Error:     0x%02X\n", result);
        printf("  Release: 0x%02X\n", gVmGlobal.errVmRelease);
#if __DEBUG__
        printf("  FileId:  0x%02X\n", gVmGlobal.errFileId);
        printf("  LineNum: %d\n", gVmGlobal.errLineNum);
#endif
#endif
}

/* Warning: Can be called in interrupt context! */
PmReturn_t
pm_vmPeriodic(uint16_t usecsSinceLastCall)
{
    /* Add the full milliseconds to pm_timerMsTicks and store additional
     * microseconds for the next run. Thus, usecsSinceLastCall must be
     * less than 2^16-1000 so it will not overflow usecResidual.
     */
    static uint16_t usecResidual = 0;
    C_ASSERT(usecsSinceLastCall < 64536);
    /* TODO Potential for optimization: Division is calculated twice. */
    usecResidual += usecsSinceLastCall;
    pm_timerMsTicks += usecResidual/1000;
    usecResidual %= 1000;

    /* check if enough time has passed for a scheduler run */
    if ((pm_timerMsTicks - pm_lastRescheduleTimestamp)
        >= PM_THREAD_TIMESLICE_MS)
    {
        interp_setRescheduleFlag(1);
        pm_lastRescheduleTimestamp = pm_timerMsTicks;
    }
    return PM_RET_OK;
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
        pm_printError(result);
    }
}
#endif /* TARGET_DESKTOP */
