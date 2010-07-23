/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  FLASH memory read/write support functions. Thanks goes to David Weaver
 *  for suggestions on improving these functions.
 */

#include "pic24_all.h"
#include <stdio.h>   //for NULL definition

/**
Write table latch with address \em u16_addrhi:u16_addrlo, data: u16_wordhi:u16_wordlo
\param u16_addrhi upper word of flash memory address
\param u16_addrlo lower word of flash memory address
\param u16_wordhi upper data word (only lower 8-bits are valid, upper 8-bits should be zero)
\param u16_wordlo lower data word
*/
//doWriteLatch ;W0=TBLPAG,W1=Wn,W2=WordHi,W3=WordLo - no return values
void doWriteLatchFlash(uint16 u16_addrhi, uint16 u16_addrlo, uint16 u16_wordhi, uint16 u16_wordlo) {
  TBLPAG = u16_addrhi;
  __builtin_tblwtl(u16_addrlo,u16_wordlo); //equivalent to asm("	tblwtl W3,[W1]")
  __builtin_tblwth(u16_addrlo,u16_wordhi); //equivalent to asm("	tblwth W2,[W1]")
}

/**
Read table latch from address \em u16_addrhi:u16_addrlo
\param u16_addrhi upper word of flash memory address
\param u16_addrlo lower word of flash memory address
\return 24-bit data value returned in \em uint32 type
*/
//_ReadLatch: ;W0=TBLPAG,W1=Wn - data in W1:W0
uint32 doReadLatchFlash(uint16 u16_addrhi, uint16 u16_addrlo) {
  union32 u32_a;
  TBLPAG = u16_addrhi;
  u32_a.u16.ls16 = __builtin_tblrdl(u16_addrlo);   //equivalent to asm("	tblrdl [W1],W0")
  u32_a.u16.ms16 = __builtin_tblrdh(u16_addrlo);   //equivalent to asm("	tblrdl [W1],W1")
  return(u32_a.u32);
}


/**
Erases a flash page at \em u16_addrhi:u16_addrlo flash address
\param u16_addrhi upper word of flash memory address
\param u16_addrlo lower word of flash memory address
*/
void doErasePageFlash (uint16 u16_addrhi, uint16 u16_addrlo) {
  uint16 u16_save_SR, u16_save_TBLPAG;

// preserve the SR and TBLPAG registers
  u16_save_SR = SR;
  u16_save_TBLPAG = TBLPAG;
//disable interrupts
  SR = SR | 0xE0;
// NVCON = flash write + erase + page erase
  NVMCON = 0x4042;
  TBLPAG = u16_addrhi; // select page
//select row
//equivalant to "tblwtl W1,[W1]"
  asm("tblwtl  %0,[%0]"::"r"(u16_addrlo));
//start erase
  __builtin_write_NVM();
//reenable interrupts
  SR  = u16_save_SR;
//wait for end of erase
  while (NVMCON & 0x8000)
    doHeartbeat();
// restore TBLPAG
  TBLPAG = u16_save_TBLPAG;
}

/**
Write current flash row
*/

void doWriteRowFlash() {
  uint16 u16_save_SR;
  // save SR
  u16_save_SR = SR;
  // disable interrupts
  SR = SR | 0xE0;
  // flash write + row op
  NVMCON = 0x4001;
//start write
  __builtin_write_NVM();
//reenable interrupts
  SR = u16_save_SR;
//wait for end of write
  while (NVMCON & 0x8000)
    doHeartbeat();
}

/**
Erases a flash page at \em u32_pmemAddress, then writes \em u16_len bytes
from \em  pu8_data to program memory.
\param u32_pmemAddress  flash memory address, should be on a page boundary
\param pu8_data  pointer to byte data to write
\param u16_len number of bytes to write, this is rounded up nearest row boundary!
(should be evenly divisible by 64*3)
*/

void doWritePageFlash(union32 u32_pmemAddress, uint8* pu8_data, uint16 u16_len) {
  uint16 u16_byteCnt;
  union32 u32_a;
  uint16 u16_ICnt, u16_numInstructions;

  ASSERT(u16_len <= FLASH_PAGEBYTES);
  doErasePageFlash(u32_pmemAddress.u16.ms16, u32_pmemAddress.u16.ls16);  //erase page
  //write the bytes
  //round up to nearest row boundary
  u16_numInstructions = u16_len/3;
  if (u16_len % 3 != 0) u16_numInstructions++;
  u16_numInstructions += (u16_numInstructions%64);
  for (u16_ICnt = 0, u16_byteCnt=0;u16_ICnt<u16_numInstructions; u16_ICnt += 1,u16_byteCnt += 3) {
    u32_a.u8[0] = pu8_data[u16_byteCnt];
    u32_a.u8[1] = pu8_data[u16_byteCnt+1];
    u32_a.u8[2] = pu8_data[u16_byteCnt+2];
    u32_a.u8[3] = 0;
    doWriteLatchFlash(u32_pmemAddress.u16.ms16, u32_pmemAddress.u16.ls16,u32_a.u16.ms16,u32_a.u16.ls16);
    if ((u16_ICnt+1)%64 == 0) {
      //row boundary, write it.
      doWriteRowFlash();
    }
    u32_pmemAddress.u32 += 2;  //program memory address increments by 2
  }
}

/**
Reads a flash page at \em u32_pmemAddress, returns \em u16_len bytes
in buffer \em  pu8_data
\param u32_pmemAddress  flash memory address, should be on a page boundary
\param pu8_data  pointer to byte data to write
\param u16_len number of bytes to read
*/
void doReadPageFlash(union32 u32_pmemAddress, uint8* pu8_data, uint16 u16_len) {
  uint16 u16_byteCnt;
  union32 u32_a;

  ASSERT(u16_len <= FLASH_PAGEBYTES);
  for (u16_byteCnt=0;u16_byteCnt<u16_len;u16_byteCnt += 3) {
    u32_a = (union32) doReadLatchFlash(u32_pmemAddress.u16.ms16, u32_pmemAddress.u16.ls16);
    pu8_data[u16_byteCnt] = u32_a.u8[0];
    pu8_data[u16_byteCnt+1] = u32_a.u8[1];
    pu8_data[u16_byteCnt+2] = u32_a.u8[2];
    u32_pmemAddress.u32 += 2;
  }
}
