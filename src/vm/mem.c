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
#define __FILE_ID__ 0x0D
/**
 * VM Memory
 *
 * VM memory operations.
 * Implementations and stubs for getByte and memCopy functions.
 * Functions to load object images from static memory.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/27   Added access to Flash and EEPROM.
 * 2002/04/21   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "pm.h"

#ifdef TARGET_AVR
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#endif /* AVR */


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

uint8_t
mem_getByte(PmMemSpace_t memspace, uint8_t **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_FLASH:
#ifdef TARGET_AVR
            b = pgm_read_byte(*paddr);
#elif defined(TARGET_DESKTOP) || defined(TARGET_ARM)
            b = **paddr;
#else
#error Undefined TARGET
#endif /* TARGET_AVR */
            *paddr += 1;
            return b;

        case MEMSPACE_EEPROM:
#ifdef TARGET_AVR
            b = eeprom_read_byte(*paddr);
            *paddr += 1;
#endif /* TARGET_AVR */
            return b;

        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


INLINE
uint16_t
mem_getWord(PmMemSpace_t memspace, uint8_t **paddr)
{
    /* PyMite is little endian; get lo byte first */
    uint8_t blo = mem_getByte(memspace, paddr);
    uint8_t bhi = mem_getByte(memspace, paddr);
    return (uint16_t)(blo | (bhi << 8));
}


INLINE
uint32_t
mem_getInt(PmMemSpace_t memspace, uint8_t **paddr)
{
    /* PyMite is little endian; get low word first */
    uint16_t wlo = mem_getWord(memspace, paddr);
    uint32_t whi = mem_getWord(memspace, paddr);
    return (uint32_t)(wlo | (whi << 16));
}


void
mem_copy(PmMemSpace_t memspace,
         uint8_t **pdest,
         uint8_t **psrc,
         uint16_t count)
{

    /* copy memory from RAM */
    if (memspace == MEMSPACE_RAM)
    {
        sli_memcpy(*pdest, *psrc, count);
        *psrc += count;
        *pdest += count;
        return;
    }

    /* copy memory from non-RAM to RAM */
    else
    {
        uint8_t b;

        for ( ; count > 0; count--)
        {
            b = mem_getByte(memspace, psrc);
            **pdest = b;
            (*pdest)++;
        }
        return;
    }
}


uint16_t
mem_getNumUtf8Bytes(PmMemSpace_t memspace, uint8_t **psrc)
{
    uint8_t *pbase = *psrc;
    while(mem_getByte(memspace, psrc) != 0);
    return *psrc - pbase - 1;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
