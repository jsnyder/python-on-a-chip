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

#ifndef _PIC24_I2C1_H_
#define _PIC24_I2C1_H_

// Only include if this I2C Module exists.
#if (NUM_I2C_MODS >= 1)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  I<sup>2</sup>C support functions - these are split into two classes: primitive operations (start, stop,
 *  rstart, put, get) and transactions, which use the primitive operations to read/write
 *  multiple bytes.
 *
 *  \note For simplicity, only functions supporting the first
 *  I<sup>2</sup>C module are listed. Chips with more than one
 *  module have similar functions defined for each module.
 */




#ifndef I2C_ACK
#define I2C_ACK 0
#endif
#ifndef I2C_NAK
#define I2C_NAK 1
#endif

#define I2C_WADDR(x) (x & 0xFE) //clear R/W bit of I2C addr
#define I2C_RADDR(x) (x | 0x01) //set R/W bit of I2C addr


//I2C Operations
void configI2C1(uint16 u16_FkHZ);
void startI2C1(void);
void rstartI2C1(void);
void stopI2C1(void);
void putI2C1(uint8 u8_val);
uint8 putNoAckCheckI2C1(uint8 u8_val);
uint8 getI2C1(uint8 u8_ack2Send);

//I2C Transactions
void write1I2C1(uint8 u8_addr,uint8 u8_d1);
void write2I2C1(uint8 u8_addr,uint8 u8_d1, uint8 u8_d2);
void writeNI2C1(uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt);
void read1I2C1 (uint8 u8_addr,uint8* pu8_d1);
void read2I2C1 (uint8 u8_addr,uint8* pu8_d1, uint8* pu8_d2);
void readNI2C1 (uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt);

#endif // #if (NUM_I2C_MODS >= 1)
#endif // #ifndef _PIC24_I2C1_H_





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

#ifndef _PIC24_I2C2_H_
#define _PIC24_I2C2_H_

// Only include if this I2C Module exists.
#if (NUM_I2C_MODS >= 2)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  I<sup>2</sup>C support functions - these are split into two classes: primitive operations (start, stop,
 *  rstart, put, get) and transactions, which use the primitive operations to read/write
 *  multiple bytes.
 *
 *  \note For simplicity, only functions supporting the first
 *  I<sup>2</sup>C module are listed. Chips with more than one
 *  module have similar functions defined for each module.
 */




#ifndef I2C_ACK
#define I2C_ACK 0
#endif
#ifndef I2C_NAK
#define I2C_NAK 1
#endif

#define I2C_WADDR(x) (x & 0xFE) //clear R/W bit of I2C addr
#define I2C_RADDR(x) (x | 0x01) //set R/W bit of I2C addr


//I2C Operations
void configI2C2(uint16 u16_FkHZ);
void startI2C2(void);
void rstartI2C2(void);
void stopI2C2(void);
void putI2C2(uint8 u8_val);
uint8 putNoAckCheckI2C2(uint8 u8_val);
uint8 getI2C2(uint8 u8_ack2Send);

//I2C Transactions
void write1I2C2(uint8 u8_addr,uint8 u8_d1);
void write2I2C2(uint8 u8_addr,uint8 u8_d1, uint8 u8_d2);
void writeNI2C2(uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt);
void read1I2C2 (uint8 u8_addr,uint8* pu8_d1);
void read2I2C2 (uint8 u8_addr,uint8* pu8_d1, uint8* pu8_d2);
void readNI2C2 (uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt);

#endif // #if (NUM_I2C_MODS >= 2)
#endif // #ifndef _PIC24_I2C2_H_





