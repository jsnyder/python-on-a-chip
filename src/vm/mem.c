#undef __FILE_ID__
#define __FILE_ID__ 0x0D
/**
 * VM Memory
 *
 * VM memory operations.
 * Implementations and stubs for getByte and memCopy functions.
 * Functions to load object images from static memory.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        mem.c
 *
 * Log
 * ---
 *
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/27   Added access to Flash and EEPROM.
 * 2002/04/21   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "py.h"

#ifdef TARGET_ATMEGA103
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#endif /* atmega103 */


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

U8
mem_getByte(PyMemSpace_t memspace, P_U8 *paddr)
{
    U8 b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_FLASH:
#ifdef TARGET_ATMEGA103
            b = pgm_read_byte(*paddr);
#elif defined(TARGET_DESKTOP)
            b = **paddr;
#else
#error Undefined TARGET
#endif /* TARGET_ATMEGA103 */
            *paddr += 1;
            return b;

        case MEMSPACE_EEPROM:
#ifdef TARGET_ATMEGA103
            b = eeprom_read_byte((U16)*paddr);
            *paddr += 1;
#endif /* TARGET_ATMEGA103 */
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
U16
mem_getWord(PyMemSpace_t memspace, P_U8 *paddr)
{
    /* PyMite is little endien; get lo byte first */
    U8 blo = mem_getByte(memspace, paddr);
    U8 bhi = mem_getByte(memspace, paddr);
    return (U16)(blo | (bhi << 8));
}


void
mem_copy(PyMemSpace_t memspace,
         P_U8 *pdest,
         P_U8 *psrc,
         U16 count)
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
        U8 b;

        for ( ; count > 0; count--)
        {
            b = mem_getByte(memspace, psrc);
            **pdest = b;
            (*pdest)++;
        }
        return;
    }
}


U16
mem_getNumUtf8Bytes(PyMemSpace_t memspace, P_U8 *psrc)
{
    P_U8 pbase = *psrc;
    while(mem_getByte(memspace, psrc) != 0);
    return *psrc - pbase - 1;
}


void
mem_reverseWord(P_U32 pword)
{
    P_U8 pbyte = (P_U8)pword;
    U8 temp = 0;
    
    temp = pbyte[3];
    pbyte[3] = pbyte[0];
    pbyte[0] = temp;
    temp = pbyte[2];
    pbyte[2] = pbyte[1];
    pbyte[1] = temp;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
