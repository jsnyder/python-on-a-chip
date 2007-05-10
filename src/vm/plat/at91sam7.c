/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2007 Dean Hall
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
#define __FILE_ID__ 0x52

/**
 * PyMite platform-specific routines for ARM7 target
 *
 * Log
 * ---
 *
 * 2007/04/29   #114: Create platform file for ARM
 */

#include "../pm.h"

#include "AT91SAM7S64.h"
#include "lib_AT91SAM7S64.h"


/***************************************************************
 * Constants
 **************************************************************/

#define RTTC_INTERRUPT_LEVEL 0

/** 200 ms for 48 MHz */
#define PIV_200_MS 600000  


/***************************************************************
 * Functions
 **************************************************************/

static void
at91sam7_pit_handler(void)
{
    PmReturn_t retval;

    retval = pm_vmPeriodic(200);
    PM_REPORT_IF_ERROR(retval);
}


PmReturn_t
plat_init(void)
{
    /* Configure PIT interrupt */
    AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,
                          AT91C_ID_SYS,
                          RTTC_INTERRUPT_LEVEL,
                          AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE,
                          (void*)at91sam7_pit_handler);

    /* Enable PIT interrupt */
    AT91C_BASE_PITC->PITC_PIMR = AT91C_PITC_PITEN
                                 | AT91C_PITC_PITIEN
                                 | PIV_200_MS;
    AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

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


/* ARM7 target shall use stdio for I/O routines */
PmReturn_t
plat_getByte(uint8_t *b)
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


/* ARM7 target shall use stdio for I/O routines */
PmReturn_t
plat_putByte(uint8_t b)
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


PmReturn_t
plat_getMsTicks(uint32_t *r_ticks)
{
    /* TODO: make access atomic */
    *r_ticks = pm_timerMsTicks;
    
    return PM_RET_OK;
}


void 
plat_reportError(PmReturn_t result)
{
}
