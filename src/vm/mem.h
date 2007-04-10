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

#ifndef __MEM_H__
#define __MEM_H__
/**
 * VM Memory
 *
 * VM memory header.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/21   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Memory Space enum.
 *
 * Defines the different addressable areas of the system.
 */
typedef enum PmMemSpace_e
{
    MEMSPACE_RAM = 0,
    MEMSPACE_PROG,
    MEMSPACE_EEPROM,
    MEMSPACE_SEEPROM,
    MEMSPACE_OTHER0,
    MEMSPACE_OTHER1,
    MEMSPACE_OTHER2,
    MEMSPACE_OTHER3
} PmMemSpace_t, *pPmMemSpace_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Returns the byte at the given address in memspace.
 *
 * Increments the address (just like getc and read(1))
 * to make image loading work (recursive).
 *
 * @param   memspace memory space/type
 * @param   paddr ptr to address
 * @return  byte from memory.
 *          paddr - points to the next byte
 */
#define mem_getByte(memspace, paddr) plat_memGetByte((memspace), (paddr))

/**
 * Return the 2-byte word at the given address in memspace.
 *
 * Word obtained in LITTLE ENDIAN order (per Python convention).
 * afterward, addr points one byte past the word.
 *
 * @param   memspace memory space
 * @param   paddr ptr to address
 * @return  word from memory.
 *          addr - points one byte past the word
 */
INLINE uint16_t mem_getWord(PmMemSpace_t memspace, uint8_t **paddr);

/**
 * Return the 4-byte int at the given address in memspace.
 *
 * Int obtained in LITTLE ENDIAN order (per Python convention).
 * afterward, addr points one byte past the int.
 *
 * @param   memspace memory space
 * @param   paddr ptr to address
 * @return  int from memory.
 *          addr - points one byte past the word
 */
INLINE uint32_t mem_getInt(PmMemSpace_t memspace, uint8_t **paddr);

/**
 * Copy count number of bytes
 * from src in memspace to dest in RAM.
 * Leave dest and src pointing one byte past end of the data.
 *
 * @param   memspace memory space/type of source
 * @param   pdest ptr to destination address
 * @param   psrc  ptr to source address
 * @param   count number of bytes to copy
 * @return  nothing.
 *          src, dest - point 1 past end of data
 * @see     sli_memcpy
 */
void mem_copy(PmMemSpace_t memspace,
              uint8_t **pdest,
              uint8_t **psrc,
              uint16_t count);

/**
 * Return the number of bytes in the UTF-8 string
 * pointed to by the contents of psrc.
 * Afterward, the contents of psrc will point one byte past
 * the null terminator of the string.
 *
 * @param   memspace memory space/type of source
 * @param   psrc  ptr to source address
 * @return  Number of bytes in UTF-8 string.
 */
uint16_t mem_getNumUtf8Bytes(PmMemSpace_t memspace, uint8_t **psrc);

#endif /* __MEM_H__ */
