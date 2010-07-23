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
 *  Implementation of serial I/O functions prototyped in pic24_serial.h
 */

#include "pic24_all.h"
#include <libpic30.h>

/*********************************************************
 * Public functions intended to be called by other files *
 *********************************************************/

#ifdef BUILT_ON_ESOS
#define outChar			esos_PutUint8ToCommOut
#else
/** Write a character to the serial port.
 *  This function blocks until a character is
 *  written. The UART used
 *  is determined by the __C30_UART variable, which
 *  defaults to 1.
 *  \param u8_c Character to write
 */
void outChar(uint8 u8_c) {
  switch (__C30_UART) {
#if (NUM_UART_MODS >= 1)
    case 1 :
      outChar1(u8_c);
      break;
#endif
#if (NUM_UART_MODS >= 2)
    case 2 :
      outChar2(u8_c);
      break;
#endif
#if (NUM_UART_MODS >= 3)
    case 3 :
      outChar3(u8_c);
      break;
#endif
#if (NUM_UART_MODS >= 4)
    case 4 :
      outChar4(u8_c);
      break;
#endif
    default :
      REPORT_ERROR("Invalid UART");
  }
}
#endif

/** Write a null-terminated string to the serial port.
See file documentation for End-of-line behavior when passed a "\n" (newline).
\param psz_s  Pointer to null-terminated string to print.
*/
void outString(const char* psz_s) {
  while (*psz_s) {

#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR_LF)
	if (*psz_s == '\n') outChar(0x0D);
    outChar(*psz_s);    
#endif
#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR)
    if (*psz_s == '\n') outChar(0x0D);
    else outChar(*psz_s);
#endif
#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_LF)
//no translation
    outChar(*psz_s);
#endif
    psz_s++;
  }
}




static uint16 inStringInternal (char *psz_buff, uint16 u16_maxCount, uint8 echoFlag) {
  uint8 u8_c;
  uint16 u16_i;

  if (!u16_maxCount) return 0;
  u16_i = 0;
  for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
    if (echoFlag) u8_c = inCharEcho();
    else u8_c = inChar();
    if (u8_c == '\n' ||u8_c == '\r' ) break; //terminate loop
    *psz_buff = u8_c; //save character
    psz_buff++;
  }
  //stop reading, terminate, return characters read.
  *psz_buff = 0;
  return(u16_i);
}

/**
Reads a string into psz_buff, assumes psz_buff can
hold at least u16_maxCount+1 characters. String reading
halts when either a newline or carriage return is read, or u16_maxCount
characters is read. The return string is always null-terminated.
The return count does not includes the null terminator.
An input string of just '\n' returns a null string.
\param psz_buff pointer to buffer for storing string read from console
\param u16_maxCount maximum number of characters to read from console.
*/
uint16 inString (char *psz_buff, int16 u16_maxCount) {
  return inStringInternal(psz_buff,u16_maxCount,0);
}

/**
Same as inString(), except echoes characters to console as they are read.
*/
uint16 inStringEcho (char *psz_buff, int16 u16_maxCount) {
  return inStringInternal(psz_buff,u16_maxCount,1);
}


void outUint8NoLeader(uint8 u8_x) {
  uint8 u8_c;
  u8_c = (u8_x>>4)& 0xf;
  if (u8_c > 9) outChar('A'+u8_c-10);
  else outChar('0'+u8_c);
  //LSDigit
  u8_c= u8_x & 0xf;
  if (u8_c > 9) outChar('A'+u8_c-10);
  else outChar('0'+u8_c);
}

/**
Output u8_x as formatted hex value with leading "0x".
\param u8_x value to output.
*/
void outUint8(uint8 u8_x) {
  outString("0x");
  outUint8NoLeader(u8_x);
}

/**
Output u16_x as formatted hex value with leading "0x".
\param u16_x value to output.
*/
void outUint16(uint16 u16_x) {
  uint8 u8_c;

  outString("0x");
  u8_c = (u16_x >> 8);
  outUint8NoLeader(u8_c);
  u8_c = (uint8) u16_x;
  outUint8NoLeader(u8_c);
}

/**
Output u32_x as formatted hex value with leading "0x".
\param u32_x value to output.
*/
void outUint32(uint32 u32_x) {
  uint8 u8_c;
  outString("0x");
  u8_c = (u32_x >> 24);
  outUint8NoLeader(u8_c);
  u8_c = (u32_x >> 16);
  outUint8NoLeader(u8_c);
  u8_c = (u32_x >> 8);
  outUint8NoLeader(u8_c);
  u8_c = u32_x;
  outUint8NoLeader(u8_c);
}

/**
Output u8_x as decimal value.
\param u8_x value to output.
*/
void outUint8Decimal( uint8 u8_x ) {
  static uint8  u8_d[]={50, 30, 20, 10, 5, 3, 2, 1 };
  static uint8  u8_f[]={5, 3, 2, 1, 5, 3, 2, 1 };

  char      psz_out[5];
  uint8     u8_i, u8_destroy;

  u8_i = 0;
  u8_destroy = u8_x;
  psz_out[0] = '0';
  psz_out[1] = '0';
  psz_out[2] = '0';
  psz_out[3] = 0;
  if (u8_destroy >= 200) {
    psz_out[0] += 200;
    u8_destroy -= 200;
  } // end if()
  if (u8_destroy >= 100) {
    psz_out[0] += 100;
    u8_destroy -= 100;
  } // end if()
  for (u8_i=0; u8_i<8; u8_i++) {
    if (u8_destroy >= u8_d[u8_i]) {
      psz_out[1+(u8_i/4)] += u8_f[u8_i];
      u8_destroy -= u8_d[u8_i];
    }
  } //end for()
  psz_out[3] = 0;
  outString( psz_out );
}

/**
Output u16_x as decimal value.
\param u16_x value to output.
*/
void outUint16Decimal( uint16 u16_x ) {
  static uint16  u16_d[]={50000, 30000, 20000, 10000, 5000, 3000, 2000, 1000, \
                          500, 300, 200, 100, 50, 30, 20, 10, 5, 3, 2, 1
                         };
  static uint8   u8_f[]={5, 3, 2, 1 };

  uint8     u8_i;
  uint16    u16_destroy;
  char      psz_out[5];

  u8_i = 0;
  u16_destroy = u16_x;
  psz_out[0] = '0';
  psz_out[1] = '0';
  psz_out[2] = '0';
  psz_out[3] = '0';
  psz_out[4] = '0';

  for (u8_i=0; u8_i<20; u8_i++) {
    if (u16_destroy >= u16_d[u8_i]) {
      psz_out[u8_i/4] += u8_f[u8_i % 4];
      u16_destroy -= u16_d[u8_i];
    }
  } //end for()
  psz_out[5] = 0;
  outString( psz_out );
}

/** Read a character from the serial port.
 *  This function blocks until a character is
 *  read.
 *  The serial port used is selected by the
 *  __C30_UART variable, which defaults to 1.
 *  \return Character read from the serial port.
 */
uint8 inChar(void) {
  switch (__C30_UART) {
#if (NUM_UART_MODS >= 1)
    case 1 :
      return inChar1();
#endif
#if (NUM_UART_MODS >= 2)
    case 2 :
      return inChar2();
#endif
#if (NUM_UART_MODS >= 3)
    case 3 :
      return inChar3();
#endif
#if (NUM_UART_MODS >= 4)
    case 4 :
      return inChar4();
#endif
    default :
      REPORT_ERROR("Invalid UART");
      return 0;
  }
}

/**
Same as inChar(), except echo character that is back to console
*/

uint8 inCharEcho(void) {
  uint8 u8_c;
  u8_c = inChar(); //get character
  outChar(u8_c);   //echo
  return u8_c;
}

/** Determine if a character is ready to be read
 *  from the serial port.
 *  \return non-zero value if character is ready, zero otherwise..
 */
uint8 isCharReady(void) {
  switch (__C30_UART) {
#if (NUM_UART_MODS >= 1)
    case 1 :
      return isCharReady1();
#endif
#if (NUM_UART_MODS >= 2)
    case 2 :
      return isCharReady2();
#endif
#if (NUM_UART_MODS >= 3)
    case 3 :
      return isCharReady3();
#endif
#if (NUM_UART_MODS >= 4)
    case 4 :
      return isCharReady4();
#endif
    default :
      REPORT_ERROR("Invalid UART");
      return 0;
  }
}



/** Configures a UART based compiler setting of DEFAULT_UART
 *  and sets __C30_UART to the default UART.
 *  If you want to configure a different UART, then call the configUARTx function explicitly.
 *  \param u32_baudRate The baud rate to use.
 */
void configDefaultUART(uint32 u32_baudRate) {
  switch (DEFAULT_UART) {
#if (NUM_UART_MODS >= 1)
    case 1 :
      __C30_UART = 1;   //this is the default UART
      configUART1(u32_baudRate);
      break;
#endif
#if (NUM_UART_MODS >= 2)
    case 2 :
      __C30_UART = 2;   //this is the default UART
      configUART2(u32_baudRate);
      break;
#endif
#if (NUM_UART_MODS >= 3)
    case 3 :
      __C30_UART = 3;   //this is the default UART
      configUART3(u32_baudRate);
      break;
#endif
#if (NUM_UART_MODS >= 4)
    case 4 :
      __C30_UART = 4;   //this is the default UART
      configUART4(u32_baudRate);
      break;
#endif
    default :
      REPORT_ERROR("Invalid UART");
  }
}

