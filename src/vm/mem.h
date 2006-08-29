#ifndef __MEM_H__
#define __MEM_H__
/**
 * VM Memory
 *
 * VM memory header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        mem.h
 *
 * Log
 * ---
 *
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
 * If the number of memspaces changes,
 * you must modify NUM_MEMSPACES to match.
 */
typedef enum PyMemSpace_e
{
    MEMSPACE_RAM = 0,
    MEMSPACE_FLASH,
    MEMSPACE_EEPROM,
    MEMSPACE_SEEPROM,
    MEMSPACE_OTHER0,
    MEMSPACE_OTHER1,
    MEMSPACE_OTHER2,
    MEMSPACE_OTHER3
} PyMemSpace_t, *pPyMemSpace_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Return the byte at the given address in memspace.
 *
 * Increment the address (just like getc and read(1))
 * to make image loading work (recursive).
 *
 * PORT:    fill in getByte for each memspace in the system;
 *          call sys_error for invalid memspaces.
 *
 * @param   memspace memory space/type
 * @param   paddr ptr to address
 * @return  byte from memory.
 *          paddr - points to the next byte
 */
U8 mem_getByte(PyMemSpace_t memspace, P_U8 *paddr);

/**
 * Return the word at the given address in memspace.
 *
 * Word obtained in LITTLE ENDIAN order (per Python convention).
 * afterward, addr points one byte past the word.
 *
 * @param   memspace memory space
 * @param   paddr ptr to address
 * @return  word from memory.
 *          addr - points one byte past the word
 */
INLINE U16 mem_getWord(PyMemSpace_t memspace, P_U8 *paddr);

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
void mem_copy(PyMemSpace_t memspace,
              P_U8 *pdest,
              P_U8 *psrc,
              U16 count);

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
U16 mem_getNumUtf8Bytes(PyMemSpace_t memspace, P_U8 *psrc);

/**
 * Performs byte reversal with the word
 *
 * Changes the endienness of the word
 *
 * @param   pword ptr to word to change
 * @return  nothing; work is done in-place
 */
void mem_reverseWord(P_U32 pword);

#endif /* __MEM_H__ */
