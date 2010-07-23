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

#ifndef __DATA_XFER_IMPL_H__
#define __DATA_XFER_IMPL_H__

/** \file
 *  \brief Routines which implement the \ref dataXfer "uC comm protocol".
 *
 *  This implements code which receives data from a uC sent
 *  either as individual characters or as data packets. For a
 *  complete specification, see the \ref dataXfer "uC comm protocol".
 *
 *  Two state machines implement this spec. The receive state
 *  machine uses the command-finding state machine in its operation,
 *  so that a user of this code will not normally need access
 *  to the command-finding machine.
 *
 *  Both machines can be reset (resetCommandFindMachine(),
 *  resetReceiveMachine()) and advanced by one state
 *  (stepCommandFindMachine(), stepReceiveMachine()). 
 *
 *  Two mechanisms provide read access to the receive 
 *  state machine. Low-level calls (getReceiveMachineOutChar(),
 *  getReceiveMachineIndex(), getReceiveMachineError(),
 *  getReceiveMachineIsSpec()) report machine
 *  state, while high-level calls (isReceiveMachineChar(), 
 *  isReceiveMachineData(), isReceiveMachineSpec()) aggreate that state into more
 *  meaningful information.
 * 
 *  Note: this is implemented in C (not C++), so that similar code can be re-used on
 *  a uC.
 *
 *  \section implementation Implementation
 *  The uC keeps state in \ref xferVar;
 *  a NULL address indicates nothing is present.
 * 
 *  On receive: implement as a state machine (see sketch below).
 *
 *  \section receiveSketch Receive state machine sketch
 *  For simplicity, "getch" really means one invocation of the receive 
 *  state machine, which is runs until the next getch. Timeouts are not 
 *  shown: if too much time passes, the state machine is reset to the
 *  top. Likewise, receiving a command at any unexpected point causes
 *  a state machine reset.
<pre>
varBits = getch
if !command:
	c = varBits  // This was just a normal char; return it
	return index = 0
	restart
// varBits is a command, not a char
if isLongVar(varBits):
	varNum, len = getch
else
	assign varNum, len from varBits
if isVarSpec and !PIC
	getch len times to buf
	parse to var spec
	report any errors, restart
else if isValid(varNum, len)
	getch len times to var
	return varIndex
else
	getch len times and discard
	report error, restart
</pre>
 *
 *  \author Bryan A. Jones, bjones AT ece DOT msstate DOT edu.
 */

#include <stdlib.h>

// Determine if we're compiling for the PIC or not.
#if defined(__PIC24H__) || defined(__PIC24F__) || defined(__dsPIC33F__) || defined(__PIC24FK__)
#define __PIC__
#include "pic24_all.h"
#endif


// Specify that this is C code for proper C++ linking
#ifdef __cplusplus
extern "C" {
#endif

/** \name Constants
 *  These values are \#defined as necessary so that the work under:
 *  - Pre-C99 (no bool, true, or false); this is MSVC++ in C mode
 *    and GCC for the PIC24.
 *  - C++ (bool, true, and false built in)
 *  - C++/CLI (NULL not defined)
 */
// @{
#if defined(__cplusplus)
#ifndef NULL
/// Define NULL under C++/CLI for portability
#define NULL nullptr
#endif

#ifndef FALSE
/// The boolean value false.
#define FALSE false
#endif

#ifndef TRUE
/// The boolean value true.
#define TRUE true
#endif

/// A boolean data type, which can take on values of
/// \ref TRUE and \ref FALSE.
#define BOOL bool

/// On MSVC under C++, use a throw for an assert. This
/// is defined already for the PIC.
#ifndef ASSERT
	#ifdef _NOASSERT
        #define ASSERT(placeholder) (void)0
	#else
		#define ASSERT(x) if (!(x)) throw #x
	#endif
#endif

/// An assert with message macro
#ifndef ASSERTM
	#ifdef _NOASSERT
        #define ASSERT(msg, expr) (void)0
	#else
		#define ASSERTM(msg, expr) if (! (expr)) throw msg ": " #expr
	#endif
#endif


#else

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef ASSERT
	#ifdef _NOASSERT
        #define ASSERT(placeholder) (void)0
	#else
		#include <assert.h>
		#define ASSERT(x) assert(x)
	#endif
#endif

/// An assert with message macro; the msg isn't used in C
#ifndef ASSERTM
#define ASSERTM(msg, expr) ASSERT(expr)
#endif

#define BOOL unsigned char
#endif
// @}

/// An abbreviation for an unsigned integer.
typedef unsigned int uint;

#ifndef __PIC__
/// An abbreviation for an 8-bit unsigned integer.
typedef unsigned char uint8;
#endif


// Unit testing: uncomment the following line to run PIC tests on PC.
//#define __PIC__

/// \name Command-finding state machine
//@{

/// The character used to begin a command. If this is not a command,
/// then use the two-character sequence \ref CMD_TOKEN 
/// \ref ESCAPED_CMD; a \ref CMD_TOKEN followed
/// by any other value is a command.
#define CMD_TOKEN ((char) 0xAA)

/// After a \ref CMD_TOKEN "command token", this value specifies that
/// the character \ref CMD_TOKEN was sent.
#define ESCAPED_CMD  ((char) 0xFC)

/// After a \ref CMD_TOKEN "command token", this value specifies that
/// the command is a long variable.
#define CMD_LONG_VAR  ((char) 0xFD)

/// After a \ref CMD_TOKEN "command token", this value specifies that
/// the command is a send-only var.
#define CMD_SEND_ONLY ((char) 0xFE)

/// After a \ref CMD_TOKEN "command token", this value specifies that
/// the command is a send/receive var.
#define CMD_SEND_RECEIVE_VAR ((char) 0xFF)

/// The number of bits in the variable size field of the varBits field, following a
/// command token.
#define VAR_SIZE_BITS 2

/// A mask which removes all but the variable size bits in the varBits field.
#define VAR_SIZE_MASK ((1 << VAR_SIZE_BITS) - 1)

/// The maximum size of a short variable (which must fit in \ref VAR_SIZE_BITS number
/// of bits).
#define SHORT_VAR_MAX_LEN (1 << VAR_SIZE_BITS)

/// State of the command-finding state machine. See \ref stepCommandFindMachine
/// for more information.
typedef enum { 
	/// The machine is in its starting state.
	STATE_CMD_START,
	/// The machine is waiting for another character; c_outChar is not valid.
	STATE_CMD_WAIT1,
	/// The machine is waiting for an additional character; c_outChar is not valid.
	STATE_CMD_WAIT2
} CMD_STATE;

/// The output of the command-finding state machine. See \ref stepCommandFindMachine
/// for more information.
typedef enum {
	/// The state machine produced no output, but is waiting for additional input.
	OUTPUT_CMD_NONE,
	/// A character was received; c_outChar contains the character.
	OUTPUT_CMD_CHAR,
	/// A command was received; c_outChar contains the command.
	OUTPUT_CMD_CMD,
	/// A repeated command was received; c_outChar contains the command.
	OUTPUT_CMD_REPEATED_CMD,
	/// The machine received a \ref CMD_TOKEN \ref CMD_TOKEN \ref CMD_TOKEN,
	/// so report a repeated command and wait for the next character to
	/// finish decoding.
	OUTPUT_CMD_REPEATED_WAIT
} CMD_OUTPUT;

void resetCommandFindMachine();
CMD_OUTPUT stepCommandFindMachine(char c_inChar, char* c_outChar);
//@}



/// \name Data structures to store received variables
//@{

/// Struct to hold send/receive data. An array of these entries holds all the
/// necessary state.
typedef struct {
  /// Pointer to the data to be exchanged. NULL means this entry is not
  /// defined.
  uint8* pu8_data;
  /// Size of data in bytes – 1: 0 = 1 byte, etc.
  uint8 u8_size;
#if !defined(__PIC__) || defined(__DOXYGEN__)
  /// printf format string to use in displaying the variable. <b>PC only.</b>
  char* psz_format;
  /// Name of this variable, typically the same as used
  /// in the code. <b>PC only.</b>
  char* psz_name;
  /// Description of this variable. <b>PC only.</b>
  char* psz_desc;
#endif
} XFER_VAR;

/// Maximum number of transfer variables supported
#define MAX_NUM_XFER_VARS ((1 << (8 - VAR_SIZE_BITS)) - 1)

/// Number of transfer variables supported. Must be less than
/// the \ref MAX_NUM_XFER_VARS.
#define NUM_XFER_VARS 62
#if NUM_XFER_VARS > MAX_NUM_XFER_VARS
#error Too many transfer variables; there must be MAX_NUM_XFER_VARS or fewer.
#endif

/// A table to hold the state of transfer variables.
extern XFER_VAR xferVar[NUM_XFER_VARS];

/// An array of isWriteable bits for each var. Each bit is true if the PC is
/// allowed to change this variable; false otherwise. This does *NOT*
/// restrict the PIC to read-only access to this variable.
extern uint8 au8_xferVarWriteable[NUM_XFER_VARS/8 + ((NUM_XFER_VARS % 8) > 0)];

//@}



/// \name Receive state machine
//@{

/// This value retured for the index from the receive state
/// machine (see, e.g., \ref isReceiveMachineData) indicates
/// that a character, not a command, was received.
#define CHAR_RECEIVED_INDEX 0xFF

/// States of the receive state machine. See
/// \ref stepReceiveMachine for more information.
typedef enum {
		/// At the start of the machine
		STATE_RECV_START,
		/// Waiting for a command or escaped \ref CMD_TOKEN
		STATE_RECV_CMD_WAIT,
		/// Reading data bytes in from a command
		STATE_RECV_READ_BYTES,
		/// Reading the variable index for a long var command
		STATE_RECV_LONG_INDEX,
		/// Reading the variable length for a long/specification command
		STATE_RECV_LONG_LENGTH,
		/// Reading the variable index for a specification command
		STATE_RECV_SPEC_INDEX,
} RECEIVE_STATE;


/// Protocol errors produced by the receive state machine.
/// Internal errors (invalid state transitions, etc.) are
/// detected via ASSERTs.
typedef enum {
	/// No error; all state machine outputs are valid
	/// when the state is \ref STATE_RECV_START after execution of
	/// \ref stepReceiveMachine.
	ERR_NONE = 0,
	/// A repeated command (the sequence \ref CMD_TOKEN
	/// \ref CMD_TOKEN c, where c != \ref ESCAPED_CMD),
	/// was received.
	ERR_REPEATED_CMD,
	/// A timeout occurred in the middle of receiving a
	/// command.
	ERR_TIMEOUT,
	/// A command occurred in the middle of receiving
	/// data belonging to an earlier command.
	ERR_INTERRUPTED_CMD,
	/// Data was sent to a variable that has not been
	/// specified: the pointer to its data is NULL.
	ERR_UNSPECIFIED_INDEX,
	/// Data was sent to a variable which exceeds the
	/// \ref NUM_XFER_VARS.
	ERR_INDEX_TOO_HIGH,
	/// The size of data sent to a variable does not
	/// match the size specified earlier.
	ERR_VAR_SIZE_MISMATCH,
	/// The destination variable is read-only.
	ERR_READ_ONLY_VAR,
	/// The PIC is sent a variable specification
	ERR_PIC_VAR_SPEC
} RECEIVE_ERROR;

/// Number of error codes in the \ref RECEIVE_ERROR enum.
#define NUM_ERROR_CODES (ERR_PIC_VAR_SPEC + 1)

RECEIVE_STATE getReceiveMachineState();
char getReceiveMachineOutChar();
uint getReceiveMachineIndex();
RECEIVE_ERROR getReceiveMachineError();
#if !defined(__PIC__) || defined(__DOXYGEN__)
BOOL getReceiveMachineIsSpec();
#endif
void resetReceiveMachine();
void clearReceiveMachineError();
void clearReceiveStruct();
BOOL isReceiveMachineChar(char* c_receivedChar);
BOOL isReceiveMachineData(uint* u_receivedIndex);
#if !defined(__PIC__) || defined(__DOXYGEN__)
BOOL isReceiveMachineSpec(uint* u_receivedIndex);
#endif
uint getVarIndex(char c_cmd);
uint getVarLength(char c_cmd);
void assignBit(uint u_index, BOOL b_bitVal);
BOOL isVarWriteable(uint u_index);
RECEIVE_ERROR stepReceiveMachine(char c_inChar, BOOL b_isTimeout);
const char* getReceiveErrorString();

#ifdef __cplusplus
}
#endif

#endif
