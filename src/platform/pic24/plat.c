/*
# This file is Copyright 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.
*/


#undef __FILE_ID__
#define __FILE_ID__ 0x51


/** @file
 *  @brief PyMite platform-specific routines for a PIC24/dsPIC33 target 
 */


#include <stdio.h>
#include <pic24_all.h>
#include "pm.h"

/** Number of milliseconds since the system
 *  was initialized.
 */
volatile uint32_t u32_ms = 0;

/** The number of milliseconds between timer interrupts. */
#define ISR_PERIOD  1    // in ms

/** Interrupt Service Routine for Timer2.
 *  Receives one interrupts per \ref ISR_PERIOD milliseconds.
 */
void _ISR _T2Interrupt (void) {
    PmReturn_t retval;

    u32_ms++;
    _T2IF = 0;                 //clear the timer interrupt bit
    retval = pm_vmPeriodic(ISR_PERIOD * 1000);
    PM_REPORT_IF_ERROR(retval);
}

/** Configure timer 2 to produce interrupts every \ref ISR_PERIOD ms. */
void  configTimer2(void) {
  // Configure the timer
  T2CON = T2_OFF | T2_IDLE_CON | T2_GATE_OFF
          | T2_32BIT_MODE_OFF
          | T2_SOURCE_INT
          | T2_PS_1_1;
  // Subtract 1 from ticks value assigned to PR2 because period is PRx + 1
  PR2 = msToU16Ticks(ISR_PERIOD, getTimerPrescale(T2CONbits)) - 1;
  TMR2  = 0;                       //clear timer2 value
  _T2IF = 0;                       //clear interrupt flag
  _T2IP = 1;                       //choose a priority
  _T2IE = 1;                       //enable the interrupt
  T2CONbits.TON = 1;               //turn on the timer
}


PmReturn_t plat_init(void)
{
  configBasic(HELLO_MSG);
  configTimer2();
  
  return PM_RET_OK;
}


PmReturn_t
plat_deinit(void)
{
    // Disable timer interrupts
    _T2IE = 0;

    return PM_RET_OK;
}


/*
 * Gets a byte from the address in the designated memory space
 * Post-increments *paddr.
 */
uint8_t
plat_memGetByte(PmMemSpace_t memspace, uint8_t const **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
            b = **paddr;
            *paddr += 1;
            return b;

        /* For now, assume a large memory model, so all program memory
         * can be mapped into the PSV space. */
        case MEMSPACE_PROG:
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_EEPROM:  // Not yet implemented.
        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


/*
 * UART receive char routine MUST return exactly and only the received char;
 * it should not translate \n to \r\n.
 * This is because the interactive interface uses binary transfers.
 */
PmReturn_t
plat_getByte(uint8_t *b)
{
  PmReturn_t retval = PM_RET_OK;

  /* Wait for character */
  while (!isCharReady1()) doHeartbeat();

  /* Return errors for Framing error or Overrun */
  if (U1STAbits.PERR || U1STAbits.FERR || U1STAbits.OERR) {
    PM_RAISE(retval, PM_RET_EX_IO);
    return retval;
  }
  *b = U1RXREG;

  return retval;
}


/*
 * UART send char routine MUST send exactly and only the given char;
 * it should not translate \n to \r\n.
 * This is because the interactive interface uses binary transfers.
 */
PmReturn_t
plat_putByte(uint8_t b)
{
  outChar1(b);
  return PM_RET_OK;
}


/** Return the number of milliseconds since the system
 *  was initialized.
 */
PmReturn_t
plat_getMsTicks(uint32_t *r_ticks)
{
    *r_ticks = u32_ms;
    return PM_RET_OK;
}

void
plat_reportError(PmReturn_t result)
{

#ifdef HAVE_DEBUG_INFO
#define LEN_FNLOOKUP 26
#define LEN_EXNLOOKUP 17

    uint8_t res;
    pPmFrame_t pframe;
    pPmObj_t pstr;
    PmReturn_t retval;
    uint8_t bcindex;
    uint16_t bcsum;
    uint16_t linesum;
    uint16_t len_lnotab;
    uint8_t const *plnotab;
    uint16_t i;

    /* This table should match src/vm/fileid.txt */
    char const * const fnlookup[LEN_FNLOOKUP] = {
        "<no file>",
        "codeobj.c",
        "dict.c",
        "frame.c",
        "func.c",
        "global.c",
        "heap.c",
        "img.c",
        "int.c",
        "interp.c",
        "pmstdlib_nat.c",
        "list.c",
        "main.c",
        "mem.c",
        "module.c",
        "obj.c",
        "seglist.c",
        "sli.c",
        "strobj.c",
        "tuple.c",
        "seq.c",
        "pm.c",
        "thread.c",
        "float.c",
        "class.c",
        "bytearray.c",
    };

    /* This table should match src/vm/pm.h PmReturn_t */
    char const * const exnlookup[LEN_EXNLOOKUP] = {
        "Exception",
        "SystemExit",
        "IoError",
        "ZeroDivisionError",
        "AssertionError",
        "AttributeError",
        "ImportError",
        "IndexError",
        "KeyError",
        "MemoryError",
        "NameError",
        "SyntaxError",
        "SystemError",
        "TypeError",
        "ValueError",
        "StopIteration",
        "Warning",
    };

    /* Print traceback */
    printf("Traceback (most recent call first):\n");

    /* Get the top frame */
    pframe = gVmGlobal.pthread->pframe;

    /* If it's the native frame, print the native function name */
    if (pframe == (pPmFrame_t)&(gVmGlobal.nativeframe))
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
        pframe = (pPmFrame_t)gVmGlobal.nativeframe.nf_back;
    }

    /* Print the remaining frame stack */
    for (; pframe != C_NULL; pframe = pframe->fo_back)
    {
        /* The last name in the names tuple of the code obj is the name */
        retval = tuple_getItem((pPmObj_t)pframe->fo_func->f_co->co_names,
                               -1,
                               &pstr);
        if ((retval) != PM_RET_OK) break;

        /*
         * Get the line number of the current bytecode. Algorithm comes from:
         * http://svn.python.org/view/python/trunk/Objects/lnotab_notes.txt?view=markup
         */
        bcindex = pframe->fo_ip - pframe->fo_func->f_co->co_codeaddr;
        plnotab = pframe->fo_func->f_co->co_lnotab;
        len_lnotab = mem_getWord(MEMSPACE_PROG, &plnotab);
        bcsum = 0;
        linesum = pframe->fo_func->f_co->co_firstlineno;
        for (i = 0; i < len_lnotab; i += 2)
        {
            bcsum += mem_getByte(MEMSPACE_PROG, &plnotab);
            if (bcsum > bcindex) break;
            linesum += mem_getByte(MEMSPACE_PROG, &plnotab);
        }
        printf("  File \"%s\", line %d, in %s\n",
               ((pPmFrame_t)pframe)->fo_func->f_co->co_filename,
               linesum,
               ((pPmString_t)pstr)->val);
    }

    /* Print error */
    res = (uint8_t)result;
    if ((res > 0) && ((res - PM_RET_EX) < LEN_EXNLOOKUP))
    {
        printf("%s", exnlookup[res - PM_RET_EX]);
    }
    else
    {
        printf("Error code 0x%02X", result);
    }
    printf(" detected by ");

    if ((gVmGlobal.errFileId > 0) && (gVmGlobal.errFileId < LEN_FNLOOKUP))
    {
        printf("%s:", fnlookup[gVmGlobal.errFileId]);
    }
    else
    {
        printf("FileId 0x%02X line ", gVmGlobal.errFileId);
    }
    printf("%d\n", gVmGlobal.errLineNum);

#else /* HAVE_DEBUG_INFO */

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
#endif /* HAVE_DEBUG_INFO */
}
