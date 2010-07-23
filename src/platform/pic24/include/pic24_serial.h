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
 *  This file defines routines to send and receive data
 *  over the serial port. All hardware-specific routines
 *  are contained elsewhere.
 *  These are lightweight character I/O functions and are
 *  intended for use when \em printf overhead is too costly.
 */

#ifndef _PIC24_SERIAL_H_
#define _PIC24_SERIAL_H_

/** \name outString() end-of-line behavior
 *  @{
 */

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a CR with every LF in outString.
 *  PuTTY uses this, expects "\n\r".
 */
#define SERIAL_EOL_CR_LF 0

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a carriage return only ("\r") to end a line.
 */
#define SERIAL_EOL_CR   1

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  sends a new line only ("\n"). This
 *  works for Bully Bootloader, MPLAB SIM, TeraTerm,
 *  RealTerm.
 */
#define SERIAL_EOL_LF   2

/** This macro defines end-of-line output behavior
 *  when the \ref outString() function is passed a new line ("\n").
 *  Set this to either \ref SERIAL_EOL_CR_LF, \ref SERIAL_EOL_CR, or
 *  \ref SERIAL_EOL_LF.
 */
#ifndef SERIAL_EOL_DEFAULT   //can be overridden in project file
#define SERIAL_EOL_DEFAULT SERIAL_EOL_LF
#endif

#if (SERIAL_EOL_DEFAULT != SERIAL_EOL_CR_LF) && \
	(SERIAL_EOL_DEFAULT != SERIAL_EOL_CR)    && \
    (SERIAL_EOL_DEFAULT != SERIAL_EOL_LF)
#error Invalid choice for SERIAL_EOF_DEFAULT
#endif

/// @}

/** Defines the default UART which the configUART() function
 *  initializes and which serial I/O is directed to
 *  until the
 */
#ifndef DEFAULT_UART
#define DEFAULT_UART 1
#endif
#if (DEFAULT_UART > NUM_UART_MODS) || (DEFAULT_UART < 1)
#error Invalid choice of DEFAULT_UART
#endif


uint8 inChar(void);  //blocking single character input
void outString(const char* psz_s);
uint16 inString (char *psz_buff, int16 u16_maxCount);
uint16 inStringEcho (char *psz_buff, int16 u16_maxCount);
void outChar(uint8 u8_c);
void outUint8NoLeader (uint8 u8_x);
void outUint8 (uint8 u8_x);
void outUint16(uint16 u16_x);
void outUint32(uint32 u32_x);
void outUint8Decimal(uint8 u8_x);
void outUint16Decimal(uint16 u16_x);
uint8 isCharReady(void); //determine if character is available to be read

uint8 inCharEcho(void);
void configDefaultUART(uint32 u32_baudRate);

#endif
