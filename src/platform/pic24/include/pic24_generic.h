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
 *  Typedefs and structures to allow for generic 8-, 16-, 32-, and 64-bit
 *  variables.
 */

#ifndef _PIC24_GENERIC_H_
#define _PIC24_GENERIC_H_
/** unsigned 8-bit integers
 * \note Prefix for all uint8s is <em>u8_</em>
 */
typedef unsigned char       uint8;   //8 bits
/** unsigned 16-bit integers
 * \note Prefix for all uint16s is <em>u16_</em>
 */
typedef unsigned int      uint16;  //16 bits
/** unsigned 32-bit integers
 * \note Prefix for all uint32s is <em>u32_</em>
 */
typedef unsigned long       uint32;  //32 bits
/** unsigned 64-bit integers
 * \note Prefix for all uint64s is <em>u64_</em>
 */
typedef unsigned long long  uint64;  //64 bits

/** signed 8-bit integers
 * \note Prefix for all int8s is <em>i8_</em>
 */
typedef signed char         int8;    //8 bits
/** signed 16-bit integers
 * \note Prefix for all int16s is <em>i16_</em>
 */
typedef signed int        int16;   //16 bits
/** signed 32-bit integers
 * \note Prefix for all int32s is <em>i32_</em>
 */
typedef signed long         int32;   //32 bits
/** signed 64-bit integers
 * \note Prefix for all int64s is <em>i64_</em>
 */
typedef signed long long    int64;   //64 bits

/// A union type for byte or word access for 16 bit values.
typedef union _union16 {
  uint16 u16;
  uint8 u8[2];
} union16;

/// A union type for byte, word, or dword access for 32 bit values.
typedef union _union32 {
  uint32 u32;

  struct {
    uint16 ls16;
    uint16 ms16;
  } u16;

  uint8 u8[4];
} union32;

/// A union type for byte, word, or dword access for 64 bit values.
typedef union _union64 {
  uint32 u32[2];
  uint16 u16[4];
  uint8 u8[8];
} union64;


#endif
