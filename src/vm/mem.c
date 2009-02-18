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


/***************************************************************
 * Functions
 **************************************************************/

uint16_t
mem_getWord(PmMemSpace_t memspace, uint8_t const **paddr)
{
    /* PyMite is little endian; get low byte first */
    uint8_t blo = mem_getByte(memspace, paddr);
    uint8_t bhi = mem_getByte(memspace, paddr);

    return (uint16_t)(blo | (bhi << (int8_t)8));
}


uint32_t
mem_getInt(PmMemSpace_t memspace, uint8_t const **paddr)
{
    /* PyMite is little endian; get low word first */
    uint16_t wlo = mem_getWord(memspace, paddr);
    uint32_t whi = mem_getWord(memspace, paddr);

    return (uint32_t)(wlo | (whi << (int8_t)16));
}


#ifdef HAVE_FLOAT
float
mem_getFloat(PmMemSpace_t memspace, uint8_t const **paddr)
{
    union
    {
        char c[4];
        float f;
    }
    v;

    /* PyMite is little endian; get low byte first */
    v.c[0] = mem_getByte(memspace, paddr);
    v.c[1] = mem_getByte(memspace, paddr);
    v.c[2] = mem_getByte(memspace, paddr);
    v.c[3] = mem_getByte(memspace, paddr);

    return v.f;
}
#endif /* HAVE_FLOAT */


void
mem_copy(PmMemSpace_t memspace,
         uint8_t **pdest, uint8_t const **psrc, uint16_t count)
{
    /* Copy memory from RAM */
    if (memspace == MEMSPACE_RAM)
    {
        sli_memcpy(*pdest, *psrc, count);
        *psrc += count;
        *pdest += count;
        return;
    }

    /* Copy memory from non-RAM to RAM */
    else
    {
        uint8_t b;

        for (; count > 0; count--)
        {
            b = mem_getByte(memspace, psrc);
            **pdest = b;
            (*pdest)++;
        }
        return;
    }
}


uint16_t
mem_getStringLength(PmMemSpace_t memspace, uint8_t const * const pstr)
{
    uint8_t const *psrc;

    /* If source is in RAM, use a possibly optimized strlen */
    if (memspace == MEMSPACE_RAM)
    {
        return sli_strlen((char const *)pstr);
    }

    /* Otherwise calculate string length */
    psrc = pstr;
    while (mem_getByte(memspace, &psrc) != (uint8_t)0);
    return psrc - pstr - 1;
}
