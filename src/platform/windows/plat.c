/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 *
 * Win32 host version, tweaked from original 'desktop' version
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x50

//  determine how we handle time in Windows
//#define USE_SETTIMER 1   /* this requires an active message loop*/
#define USE_TIMESETEVENT 1 /* (Older) Windows multi-media function */
//#define USE_CREATETIMERQUEUETIMER 0 /* CreateTimerQueueTimer function */

/** PyMite platform-specific routines for Desktop target */

#include <stdio.h>
#include <string.h>

#include "pm.h"

//#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if defined(USE_SETTIMER)
    /* local prototypes */
    VOID CALLBACK on_timer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
#endif

#if defined(USE_TIMESETEVENT)
    // shortcut so we do not need an explicit addition to the linker command line
    #pragma comment(lib, "winmm")

    void CALLBACK on_mm_timer(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
#endif


/* local variables*/
static UINT_PTR idEvent = 0;
static DWORD dwLastTime = 0;
static const UINT uTimeOut = 200;  /* # of ms for each timer tick */


/* Desktop target shall use stdio for I/O routines. */
PmReturn_t plat_init(void)
{
    /*
     * The *nix version used the sigalrm to generate a timer. On Windows, we
     * use a standard Windows timer. Note we do not use an HWND so we do not
     * need to actually create any windows. But we do need a Windows event loop
     * to allow the timer callback to be called properly.
     */
    dwLastTime = GetTickCount();
    
#if defined(USE_SETTIMER)
    idEvent = SetTimer(NULL, 0, uTimeOut, on_timer);
    // use the return value in a KillTimer function. But we need a plat_uninit() call...
#endif

#if defined(USE_TIMESETEVENT)
    idEvent = timeSetEvent(uTimeOut, 0 /*change later, if system load too high*/, on_mm_timer, 0, TIME_PERIODIC|TIME_CALLBACK_FUNCTION);
#endif

    return PM_RET_OK;
}

#if defined(USE_SETTIMER)
/* Called from Windows every X ms */
VOID CALLBACK on_timer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    PmReturn_t retval = PM_RET_OK;
    DWORD delta = dwTime - dwLastTime;
    //printf("diff = %ld\n", delta);

    // update our system time
    pm_timerMsTicks = dwTime;

    retval = pm_vmPeriodic((uint16_t)delta);
    dwLastTime = dwTime;

    PM_REPORT_IF_ERROR(retval);
}
#endif

#if defined(USE_TIMESETEVENT)
void CALLBACK on_mm_timer(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    PmReturn_t retval = PM_RET_OK;
    DWORD dwTime = GetTickCount();
    DWORD delta =  dwTime - dwLastTime;
    //printf("diff = %ld\n", delta);

    // update our system time
    pm_timerMsTicks = dwTime;

    retval = pm_vmPeriodic((uint16_t)delta);
    dwLastTime = dwTime;

    PM_REPORT_IF_ERROR(retval);
}
#endif

/*
 * Undo anything we may have done in the plat_init function
 */
void plat_uninit(void)
{
#if defined(USE_SETTIMER)
    KillTimer(idEvent);
    idEvent = 0;
#endif

#if defined(USE_TIMESETEVENT)
    timeKillEvent(idEvent);
    idEvent = 0;
#endif
}

/*
 * Gives us time to update our clock, etc.
 */
void plat_tick(void)
{
    BOOL bRet;
    MSG msg;

    //if ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/*
 * Gets a byte from the address in the designated memory space
 * Post-increments *paddr.
 */
uint8_t plat_memGetByte(PmMemSpace_t memspace, uint8_t const **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
        case MEMSPACE_PROG:
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_EEPROM:
        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


/* Desktop target shall use stdio for I/O routines */
PmReturn_t plat_getByte(uint8_t *b)
{
    int c;
    PmReturn_t retval = PM_RET_OK;

    c = getchar();
    *b = c & 0xFF;

    if (c == EOF)
    {
        PM_RAISE(retval, PM_RET_EX_IO);
    }

    return retval;
}


/* Desktop target shall use stdio for I/O routines */
PmReturn_t plat_putByte(uint8_t b)
{
    int i;
    PmReturn_t retval = PM_RET_OK;

    i = putchar(b);
    fflush(stdout);

    if ((i != b) || (i == EOF))
    {
        PM_RAISE(retval, PM_RET_EX_IO);
    }

    return retval;
}


PmReturn_t plat_getMsTicks(uint32_t *r_ticks)
{
    *r_ticks = pm_timerMsTicks;

    return PM_RET_OK;
}


void plat_reportError(PmReturn_t result)
{
    /* Print error */
    printf("Error:     0x%02X\n", result);
    printf("  Release: 0x%02X\n", gVmGlobal.errVmRelease);
    printf("  FileId:  0x%02X\n", gVmGlobal.errFileId);
    printf("  LineNum: %d\n", gVmGlobal.errLineNum);

    /* Print traceback */
    {
        pPmObj_t pframe;
        pPmObj_t pstr;
        PmReturn_t retval;

        printf("Traceback (top first):\n");

        /* Get the top frame */
        pframe = (pPmObj_t)gVmGlobal.pthread->pframe;

        /* If it's the native frame, print the native function name */
        if (pframe == (pPmObj_t)&(gVmGlobal.nativeframe))
        {

            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)gVmGlobal.nativeframe.nf_func->
                                   f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK)
            {
                printf("  Unable to get native func name.\n");
                return;
            }
            else
            {
                printf("  %s() __NATIVE__\n", ((pPmString_t)pstr)->val);
            }

            /* Get the frame that called the native frame */
            pframe = (pPmObj_t)gVmGlobal.nativeframe.nf_back;
        }

        /* Print the remaining frame stack */
        for (;
             pframe != C_NULL;
             pframe = (pPmObj_t)((pPmFrame_t)pframe)->fo_back)
        {
            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)((pPmFrame_t)pframe)->
                                   fo_func->f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK) break;

            printf("  %s()\n", ((pPmString_t)pstr)->val);
        }
        printf("  <module>.\n");
    }
}
