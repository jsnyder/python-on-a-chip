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


#ifndef _PIC24_UART1_H_
#define _PIC24_UART1_H_

// Only include if this UART module exists.
#if (NUM_UART_MODS >= 1)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the UARTs on the PIC. See \ref pic24_serial.h
 *  for higher-level routines, which should typically
 *  be called by the user rather than these routines.
 */


/** Chose a default baud rate for UART1, used by
 *  \ref configUART1 to set up UART1.
 */
#ifndef DEFAULT_BAUDRATE1
#define DEFAULT_BAUDRATE1  DEFAULT_BAUDRATE
#endif

/** Chose a default BRGH for UART1, used by
 *  \ref CONFIG_BAUDRATE_UART1 to set up UART1.
 */
#ifndef DEFAULT_BRGH1
#define DEFAULT_BRGH1  DEFAULT_BRGH
#endif

/** Configure UART baud rate, based on \ref FCY.
 *  NOTE: Be careful about using BRGH=1 - this uses only four clock
 *  periods to sample each bit and can be very intolerant of
 *  baud rate %error - you may see framing errors. BRGH is selected
 *  via the DEFAULT_BRGH1 define.
 *
 *  \param baudRate Desired baud rate.
 */
inline static void CONFIG_BAUDRATE_UART1(uint32 baudRate) {
#if (DEFAULT_BRGH1 == 0)
  float f_brg = (((float) FCY)/((float) baudRate)/16.0) - 1.0;
#else
  float f_brg = (((float) FCY)/((float) baudRate)/4.0) - 1.0;
#endif
  ASSERT(f_brg < 65535.5);
  U1MODEbits.BRGH = DEFAULT_BRGH1;
  U1BRG = roundFloatToUint16(f_brg);
}


/** \name Constants for the UxMODE.PDSEL bitfield
 *  Use with \ref CONFIG_PDSEL_UART1.
 *  @{
 */
#define UXMODE_PDSEL_8DATA_NOPARITY   0
#define UXMODE_PDSEL_8DATA_EVENPARITY 1
#define UXMODE_PDSEL_8DATA_ODDPARITY  2
#define UXMODE_PDSEL_9DATA_NOPARITY   3
///@}

/** Select the parity and number of data bits for the UART.
 *  Use constants UXMODE_PDSEL_8DATA_NOPARITY and following.
 *  \param u8_pdsel Parity and number of data bits.
 */
inline static void CONFIG_PDSEL_UART1(uint8 u8_pdsel) {
  ASSERT(u8_pdsel <= UXMODE_PDSEL_9DATA_NOPARITY);
  U1MODEbits.PDSEL = u8_pdsel;
}

/** Select the number of stop bits for this UART. Valid values
 *  are 1 or 2.
 *  \param u8_numStopbits Number of stop bits.
 */
inline static void CONFIG_STOPBITS_UART1(uint8 u8_numStopbits) {
  ASSERT(u8_numStopbits <= 2);
  U1MODEbits.STSEL = u8_numStopbits - 1;
}

/** Enable RX, TX for UART. */
inline static void ENABLE_UART1() {
  U1MODEbits.UEN = 0b00;                    // UxTX and UxRX pins are enabled and used; no flow control pins
  U1MODEbits.UARTEN = 1;                    // enable UART RX/TX
  U1STAbits.UTXEN = 1;                      //Enable the transmitter
}

/** Determine if a character is available in the UART's
 *  receive buffer.
 *  \return True (1) if character is available, 0 if not.
 */
#define IS_CHAR_READY_UART1() U1STAbits.URXDA

/** Determine if a the transmit buffer is full.
 *  \return True (1) if the transmit buffer if full,
 *          false (0) if not.
 */
#define IS_TRANSMIT_BUFFER_FULL_UART1() U1STAbits.UTXBF

/** Determines if all characters placed in the UART have been sent.
 *  Returns 1 if the last transmission has completed, or 0 if a transmission
 *  is in progress or queued in the transmit buffer.
 *  \return True (1) if the last transmission has completed, 0 if not.
 */
#define IS_TRANSMIT_COMPLETE_UART1() U1STAbits.TRMT

/** Waits until all characters placed in the UART have been sent. */
inline static void WAIT_UNTIL_TRANSMIT_COMPLETE_UART1() {
  while (!IS_TRANSMIT_COMPLETE_UART1())
    doHeartbeat();
}

void outChar1(uint8 u8_c);
uint8 inChar1(void);
void configUART1(uint32 u32_baudRate);
uint8 isCharReady1(void);
void checkRxErrorUART1(void);  //check for UART RX error

#endif // #if (NUM_UART_MODS >= 1)
#endif // #ifndef _PIC24_UART1_H_








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


#ifndef _PIC24_UART2_H_
#define _PIC24_UART2_H_

// Only include if this UART module exists.
#if (NUM_UART_MODS >= 2)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the UARTs on the PIC. See \ref pic24_serial.h
 *  for higher-level routines, which should typically
 *  be called by the user rather than these routines.
 */


/** Chose a default baud rate for UART2, used by
 *  \ref configUART2 to set up UART2.
 */
#ifndef DEFAULT_BAUDRATE2
#define DEFAULT_BAUDRATE2  DEFAULT_BAUDRATE
#endif

/** Chose a default BRGH for UART2, used by
 *  \ref CONFIG_BAUDRATE_UART2 to set up UART2.
 */
#ifndef DEFAULT_BRGH2
#define DEFAULT_BRGH2  DEFAULT_BRGH
#endif

/** Configure UART baud rate, based on \ref FCY.
 *  NOTE: Be careful about using BRGH=1 - this uses only four clock
 *  periods to sample each bit and can be very intolerant of
 *  baud rate %error - you may see framing errors. BRGH is selected
 *  via the DEFAULT_BRGH1 define.
 *
 *  \param baudRate Desired baud rate.
 */
inline static void CONFIG_BAUDRATE_UART2(uint32 baudRate) {
#if (DEFAULT_BRGH2 == 0)
  float f_brg = (((float) FCY)/((float) baudRate)/16.0) - 1.0;
#else
  float f_brg = (((float) FCY)/((float) baudRate)/4.0) - 1.0;
#endif
  ASSERT(f_brg < 65535.5);
  U2MODEbits.BRGH = DEFAULT_BRGH2;
  U2BRG = roundFloatToUint16(f_brg);
}


/** \name Constants for the UxMODE.PDSEL bitfield
 *  Use with \ref CONFIG_PDSEL_UART2.
 *  @{
 */
#define UXMODE_PDSEL_8DATA_NOPARITY   0
#define UXMODE_PDSEL_8DATA_EVENPARITY 1
#define UXMODE_PDSEL_8DATA_ODDPARITY  2
#define UXMODE_PDSEL_9DATA_NOPARITY   3
///@}

/** Select the parity and number of data bits for the UART.
 *  Use constants UXMODE_PDSEL_8DATA_NOPARITY and following.
 *  \param u8_pdsel Parity and number of data bits.
 */
inline static void CONFIG_PDSEL_UART2(uint8 u8_pdsel) {
  ASSERT(u8_pdsel <= UXMODE_PDSEL_9DATA_NOPARITY);
  U2MODEbits.PDSEL = u8_pdsel;
}

/** Select the number of stop bits for this UART. Valid values
 *  are 1 or 2.
 *  \param u8_numStopbits Number of stop bits.
 */
inline static void CONFIG_STOPBITS_UART2(uint8 u8_numStopbits) {
  ASSERT(u8_numStopbits <= 2);
  U2MODEbits.STSEL = u8_numStopbits - 1;
}

/** Enable RX, TX for UART. */
inline static void ENABLE_UART2() {
  U2MODEbits.UEN = 0b00;                    // UxTX and UxRX pins are enabled and used; no flow control pins
  U2MODEbits.UARTEN = 1;                    // enable UART RX/TX
  U2STAbits.UTXEN = 1;                      //Enable the transmitter
}

/** Determine if a character is available in the UART's
 *  receive buffer.
 *  \return True (1) if character is available, 0 if not.
 */
#define IS_CHAR_READY_UART2() U2STAbits.URXDA

/** Determine if a the transmit buffer is full.
 *  \return True (1) if the transmit buffer if full,
 *          false (0) if not.
 */
#define IS_TRANSMIT_BUFFER_FULL_UART2() U2STAbits.UTXBF

/** Determines if all characters placed in the UART have been sent.
 *  Returns 1 if the last transmission has completed, or 0 if a transmission
 *  is in progress or queued in the transmit buffer.
 *  \return True (1) if the last transmission has completed, 0 if not.
 */
#define IS_TRANSMIT_COMPLETE_UART2() U2STAbits.TRMT

/** Waits until all characters placed in the UART have been sent. */
inline static void WAIT_UNTIL_TRANSMIT_COMPLETE_UART2() {
  while (!IS_TRANSMIT_COMPLETE_UART2())
    doHeartbeat();
}

void outChar2(uint8 u8_c);
uint8 inChar2(void);
void configUART2(uint32 u32_baudRate);
uint8 isCharReady2(void);
void checkRxErrorUART2(void);  //check for UART RX error

#endif // #if (NUM_UART_MODS >= 2)
#endif // #ifndef _PIC24_UART2_H_








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


#ifndef _PIC24_UART3_H_
#define _PIC24_UART3_H_

// Only include if this UART module exists.
#if (NUM_UART_MODS >= 3)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the UARTs on the PIC. See \ref pic24_serial.h
 *  for higher-level routines, which should typically
 *  be called by the user rather than these routines.
 */


/** Chose a default baud rate for UART3, used by
 *  \ref configUART3 to set up UART3.
 */
#ifndef DEFAULT_BAUDRATE3
#define DEFAULT_BAUDRATE3  DEFAULT_BAUDRATE
#endif

/** Chose a default BRGH for UART3, used by
 *  \ref CONFIG_BAUDRATE_UART3 to set up UART3.
 */
#ifndef DEFAULT_BRGH3
#define DEFAULT_BRGH3  DEFAULT_BRGH
#endif

/** Configure UART baud rate, based on \ref FCY.
 *  NOTE: Be careful about using BRGH=1 - this uses only four clock
 *  periods to sample each bit and can be very intolerant of
 *  baud rate %error - you may see framing errors. BRGH is selected
 *  via the DEFAULT_BRGH1 define.
 *
 *  \param baudRate Desired baud rate.
 */
inline static void CONFIG_BAUDRATE_UART3(uint32 baudRate) {
#if (DEFAULT_BRGH3 == 0)
  float f_brg = (((float) FCY)/((float) baudRate)/16.0) - 1.0;
#else
  float f_brg = (((float) FCY)/((float) baudRate)/4.0) - 1.0;
#endif
  ASSERT(f_brg < 65535.5);
  U3MODEbits.BRGH = DEFAULT_BRGH3;
  U3BRG = roundFloatToUint16(f_brg);
}


/** \name Constants for the UxMODE.PDSEL bitfield
 *  Use with \ref CONFIG_PDSEL_UART3.
 *  @{
 */
#define UXMODE_PDSEL_8DATA_NOPARITY   0
#define UXMODE_PDSEL_8DATA_EVENPARITY 1
#define UXMODE_PDSEL_8DATA_ODDPARITY  2
#define UXMODE_PDSEL_9DATA_NOPARITY   3
///@}

/** Select the parity and number of data bits for the UART.
 *  Use constants UXMODE_PDSEL_8DATA_NOPARITY and following.
 *  \param u8_pdsel Parity and number of data bits.
 */
inline static void CONFIG_PDSEL_UART3(uint8 u8_pdsel) {
  ASSERT(u8_pdsel <= UXMODE_PDSEL_9DATA_NOPARITY);
  U3MODEbits.PDSEL = u8_pdsel;
}

/** Select the number of stop bits for this UART. Valid values
 *  are 1 or 2.
 *  \param u8_numStopbits Number of stop bits.
 */
inline static void CONFIG_STOPBITS_UART3(uint8 u8_numStopbits) {
  ASSERT(u8_numStopbits <= 2);
  U3MODEbits.STSEL = u8_numStopbits - 1;
}

/** Enable RX, TX for UART. */
inline static void ENABLE_UART3() {
  U3MODEbits.UEN = 0b00;                    // UxTX and UxRX pins are enabled and used; no flow control pins
  U3MODEbits.UARTEN = 1;                    // enable UART RX/TX
  U3STAbits.UTXEN = 1;                      //Enable the transmitter
}

/** Determine if a character is available in the UART's
 *  receive buffer.
 *  \return True (1) if character is available, 0 if not.
 */
#define IS_CHAR_READY_UART3() U3STAbits.URXDA

/** Determine if a the transmit buffer is full.
 *  \return True (1) if the transmit buffer if full,
 *          false (0) if not.
 */
#define IS_TRANSMIT_BUFFER_FULL_UART3() U3STAbits.UTXBF

/** Determines if all characters placed in the UART have been sent.
 *  Returns 1 if the last transmission has completed, or 0 if a transmission
 *  is in progress or queued in the transmit buffer.
 *  \return True (1) if the last transmission has completed, 0 if not.
 */
#define IS_TRANSMIT_COMPLETE_UART3() U3STAbits.TRMT

/** Waits until all characters placed in the UART have been sent. */
inline static void WAIT_UNTIL_TRANSMIT_COMPLETE_UART3() {
  while (!IS_TRANSMIT_COMPLETE_UART3())
    doHeartbeat();
}

void outChar3(uint8 u8_c);
uint8 inChar3(void);
void configUART3(uint32 u32_baudRate);
uint8 isCharReady3(void);
void checkRxErrorUART3(void);  //check for UART RX error

#endif // #if (NUM_UART_MODS >= 3)
#endif // #ifndef _PIC24_UART3_H_








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


#ifndef _PIC24_UART4_H_
#define _PIC24_UART4_H_

// Only include if this UART module exists.
#if (NUM_UART_MODS >= 4)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the UARTs on the PIC. See \ref pic24_serial.h
 *  for higher-level routines, which should typically
 *  be called by the user rather than these routines.
 */


/** Chose a default baud rate for UART4, used by
 *  \ref configUART4 to set up UART4.
 */
#ifndef DEFAULT_BAUDRATE4
#define DEFAULT_BAUDRATE4  DEFAULT_BAUDRATE
#endif

/** Chose a default BRGH for UART4, used by
 *  \ref CONFIG_BAUDRATE_UART4 to set up UART4.
 */
#ifndef DEFAULT_BRGH4
#define DEFAULT_BRGH4  DEFAULT_BRGH
#endif

/** Configure UART baud rate, based on \ref FCY.
 *  NOTE: Be careful about using BRGH=1 - this uses only four clock
 *  periods to sample each bit and can be very intolerant of
 *  baud rate %error - you may see framing errors. BRGH is selected
 *  via the DEFAULT_BRGH1 define.
 *
 *  \param baudRate Desired baud rate.
 */
inline static void CONFIG_BAUDRATE_UART4(uint32 baudRate) {
#if (DEFAULT_BRGH4 == 0)
  float f_brg = (((float) FCY)/((float) baudRate)/16.0) - 1.0;
#else
  float f_brg = (((float) FCY)/((float) baudRate)/4.0) - 1.0;
#endif
  ASSERT(f_brg < 65535.5);
  U4MODEbits.BRGH = DEFAULT_BRGH4;
  U4BRG = roundFloatToUint16(f_brg);
}


/** \name Constants for the UxMODE.PDSEL bitfield
 *  Use with \ref CONFIG_PDSEL_UART4.
 *  @{
 */
#define UXMODE_PDSEL_8DATA_NOPARITY   0
#define UXMODE_PDSEL_8DATA_EVENPARITY 1
#define UXMODE_PDSEL_8DATA_ODDPARITY  2
#define UXMODE_PDSEL_9DATA_NOPARITY   3
///@}

/** Select the parity and number of data bits for the UART.
 *  Use constants UXMODE_PDSEL_8DATA_NOPARITY and following.
 *  \param u8_pdsel Parity and number of data bits.
 */
inline static void CONFIG_PDSEL_UART4(uint8 u8_pdsel) {
  ASSERT(u8_pdsel <= UXMODE_PDSEL_9DATA_NOPARITY);
  U4MODEbits.PDSEL = u8_pdsel;
}

/** Select the number of stop bits for this UART. Valid values
 *  are 1 or 2.
 *  \param u8_numStopbits Number of stop bits.
 */
inline static void CONFIG_STOPBITS_UART4(uint8 u8_numStopbits) {
  ASSERT(u8_numStopbits <= 2);
  U4MODEbits.STSEL = u8_numStopbits - 1;
}

/** Enable RX, TX for UART. */
inline static void ENABLE_UART4() {
  U4MODEbits.UEN = 0b00;                    // UxTX and UxRX pins are enabled and used; no flow control pins
  U4MODEbits.UARTEN = 1;                    // enable UART RX/TX
  U4STAbits.UTXEN = 1;                      //Enable the transmitter
}

/** Determine if a character is available in the UART's
 *  receive buffer.
 *  \return True (1) if character is available, 0 if not.
 */
#define IS_CHAR_READY_UART4() U4STAbits.URXDA

/** Determine if a the transmit buffer is full.
 *  \return True (1) if the transmit buffer if full,
 *          false (0) if not.
 */
#define IS_TRANSMIT_BUFFER_FULL_UART4() U4STAbits.UTXBF

/** Determines if all characters placed in the UART have been sent.
 *  Returns 1 if the last transmission has completed, or 0 if a transmission
 *  is in progress or queued in the transmit buffer.
 *  \return True (1) if the last transmission has completed, 0 if not.
 */
#define IS_TRANSMIT_COMPLETE_UART4() U4STAbits.TRMT

/** Waits until all characters placed in the UART have been sent. */
inline static void WAIT_UNTIL_TRANSMIT_COMPLETE_UART4() {
  while (!IS_TRANSMIT_COMPLETE_UART4())
    doHeartbeat();
}

void outChar4(uint8 u8_c);
uint8 inChar4(void);
void configUART4(uint32 u32_baudRate);
uint8 isCharReady4(void);
void checkRxErrorUART4(void);  //check for UART RX error

#endif // #if (NUM_UART_MODS >= 4)
#endif // #ifndef _PIC24_UART4_H_








