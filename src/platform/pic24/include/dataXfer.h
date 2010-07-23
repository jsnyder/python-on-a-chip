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

#ifndef __DATA_XFER_H__
#define __DATA_XFER_H__

/** \file
 *  \brief Routines which implement the \ref dataXfer "uC comm protocol".
 */

#include "dataXferImpl.h"

// Specify that this is C code for proper C++ linking
#ifdef __cplusplus
extern "C" {
#endif

/// Number of for loop iterations which equal a timeout for the PIC.
///     # loops   =      instructions/sec * loops/instruction * seconds
#define RECEIVE_TIMEOUT (FCY              * 1/20              * 0.1)

/// Send one character to the uC, escaping if necessary.
/// \param c Character to send.
void xferOutChar(char c);


/// A system-dependent macro to output one character.
#ifndef OUT_CHAR
#ifdef __PIC__
void outChar(uint8 c);
#define OUT_CHAR(c) outChar(c);
#else
void outChar(uint8 c);
#define OUT_CHAR(c) outChar(c);
#endif
#else
// Hack: a command line of -DOUT_CHAR(c)=testOutChar(c) doesn't work. Just -DOUT_CHAR then
// redefine it here.
#undef OUT_CHAR
void testOutChar(uint8 c);
#define OUT_CHAR(c) testOutChar(c)
#endif

/// Initialize the data transfer system. This must be called before calling
/// any of the data transfer functions in the library.
void initDataXfer();

/** Specify a variable to be sent or received.
 *  \param u_varIndex       A value from 0-\ref NUM_XFER_VARS, unique for each var
 *  \param pv_data          A pointer to the data to be sent
 *  \param u_size           Size of the data in bytes; must be from 1 to 256.
 *  \param b_isWriteable    True if the PC is allowed to change this
                              variable; false otherwise. This does *NOT*
                              restrict the PIC to read-only access to this
                              variable.
 *  \param psz_format       printf format string to use in displaying the
                              Variable.
 *  \param psz_name         Name of this variable, typically the same as used
                              in the code
 *  \param psz_desc         Description of this variable.
 */
void specifyVar(uint u_varIndex, void* pv_data, uint u_size, 
                BOOL b_isWriteable, char* psz_format, char* psz_name,
                char* psz_desc);

/** For simplicity, define a macro that specifies a variable with
 *  default names. For example, SEND_VAR(1, u8_c);
 *  \param u_varIndex    A value from 0-\ref NUM_XFER_VARS, unique for each var
 *  \param data          A pointer to the data to be sent
 *  \param isWriteable   True if the PC is allowed to change this
                          variable; false otherwise. This does *NOT*
                          restrict the PIC to read-only access to this
                          variable.
 *  \param format        printf format string to use in displaying the
                          variable
 *  \param desc          Description of this variable.
 */
#define SPECIFY_VAR(u_varIndex, data, isWriteable, format, desc) \
  specifyVar(u_varIndex, &data, sizeof(data), isWriteable, format, #data, desc)

/// Send an already-specified variable; \see specifyVar.
/// \param u_varIndex The index of the variable to send; must be from 0 to
///                    \ref NUM_XFER_VARS.
void sendVar(uint u_varIndex);

#if !defined(__PIC__) || defined(__DOXYGEN__)
/** Return a string with the data stored in the given variable formatted using
 *  the format string contained in the variable. Limitation: current, use of
 *  a string (%s format) will probably crash the program. <b>PC only.</b>
 *  \param u_varIndex The index of the variable to send; must be from 0 to
 *                    \ref NUM_XFER_VARS.
 *  \param psz_buf Buffer large enough to contain the formatted string.
 *  \return On success, the total number of characters written is returned. 
 *          This count does not include the additional null-character 
 *          automatically appended at the end of the string.
 *          On failure, a negative number is returned.
 */
int formatVar(uint u_varIndex, char* psz_buf);
#endif


#if defined(__PIC__) || defined(__DOXYGEN__)
/** Receive a character or a variable. Any errors that occur are
*  reported via outString. <b>uC only.</b>
 *  \param c Pointer to space for storing the received character, if
 *             a character was received (see return value).
 *  \return  An index to the variable, if a variable was received, or
 *             \ref CHAR_RECEIVED_INDEX if a character was received.
 */
uint receiveVar(char* c);

/** Receive a character, while transparently processing any
 *  variables sent by the PC. Variables are assigned, but
 *  this simple interface does not report these assignments
 *  to its caller. This provides a simple wrapper around \ref receiveVar,
 *  which also reports on received variables.  <b>uC only.</b>
 *  \return The character received.
 */
char inCharXfer();
#endif


#ifdef __cplusplus
}
#endif

#endif
