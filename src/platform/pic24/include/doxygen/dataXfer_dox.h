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
 */

/**
 * \page dataXfer The uC/PC data transfer protocol
 * \section dataXferIntro The PC/uC data transfer protocol
 *
 *  The uC data transfer protocol is a simple protocol to exchange data between
 *  a PC and a PIC over the UART. The example given below and implemented in
 *  this library applies to the PIC24/dsPIC33 series, though porting it to other
 *  microcontrollers is straightforward.
 *
 *  \htmlonly
 *  <object width="640" height="505"><param name="movie" value="http://www.youtube.com/v/3B60xpMLoFg&hl=en_US&fs=1&"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/3B60xpMLoFg&hl=en_US&fs=1&" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="640" height="505"></embed></object>
 *  \endhtmlonly
 *
 * \section usageSketch Usage sketch
 * \code
#include "pic24_all.h"
#include "dataXfer.h"

// Indexes of all the variables to be transferred.
enum { U16_NUMCHARS_NDX, C_NDX };

// Number of characters to print on each line.
#define CHARS_PER_LINE 10

int main(void) {
  char c;
  uint16 u16_numChars = 0;

  // Initialize
  configBasic(HELLO_MSG);
  initDataXfer();

  // All variables received by the PIC must be specified.
  // Params:  Index             Variable      PC can change  Format  Description
  SPECIFY_VAR(U16_NUMCHARS_NDX, u16_numChars, TRUE,          "%hu",  "Number of characters received");
  SPECIFY_VAR(C_NDX,            c,            FALSE,         "%c",   "Character entered");

  while (1) {
    // For debug support, send the index and char received.
    sendVar(U16_NUMCHARS_NDX);
    sendVar(C_NDX);

    // Echo a character
    c = inCharXfer();
    outChar(c);

    // Add a CR every CHARS_PER_LINE
    if ((u16_numChars++ % CHARS_PER_LINE) == 0)
      outChar('\n');
  }
}
 * \endcode
 *
 * \section dataXferExamples Examples
 * The following programs use the data transfer protocol, providing working
 * examples of its usage.
 * - dataXfer_echo.c, which is given above.
 * - dataXfer_demo.c, a more complete example.
 * - ledpwm.c
 *
 * \section designGoals Design goals
 *  - Easy to use: no setup required to send variables; integrates with 
 *    ISRs seamlessly by using getch/putch rather than direct assignment 
 *    to UxRXREG/UxTXREG. Receive requires setup and returns a non-protocol 
 *    character read or a variable read.
 *  - Excellent error reporting: PIC defines the protocol, pushing most 
 *    errors onto the PC. Timeouts on the PIC and PC help spot errors. The 
 *    PIC reports errors via text messages, which flow through to the PC.
 *  - Reasonably efficient (> 100 Hz). Two bytes of overhead per variable (start, type).
 *  - Minimal PIC memory requirements: one pointer, one uint8, one bit per variable.
 *  - Can send/receive data in any order (not a fixed sequence): sendVar 
 *    in any order, receiveVar receives any var (or even a non-protocol 
 *    character, to make interaction via a menu work)
 *
 * \section errorCases Error cases
 *  - Timeout during received of a variable. In this case, the variable 
 *    is only partially assigned; the PIC is reset, while the PC reports an error.
 *  - Sending in an ISR, which could cause timing problems. Fixing this
 *    really needs a trace buffer implementation.
 *  - Index of variable not the same between PIC and PC. The PIC names 
 *    variables; the PC likewise only allows access to variables of the same 
 *    name. However, the PC code will enforce variable name to number mapping, 
 *    making this fairly uncommon (if the same name occurs twice, there's a problem).
 *
 *  \section protocol Protocol
 *  - \ref CMD_TOKEN varBits data
 *    - varBits = { v v v v v v l l} bitfield
 *      - v = variable number (0-\ref NUM_XFER_VARS, 63 = special)
 *      - l = length (1-4 bytes, encoded as 0-3)/special code. Special codes:
 *        - code = 0: escaped \ref CMD_TOKEN : this is the value \ref CMD_TOKEN,
 *          not the start of a command.
 *        - code = 1: long var
 *        - code = 2-3: Variable specification: data is size (1 byte), 
 *          format string, name, description (all
 *          zero-terminated). Code 2: send only var (PC may not modify);
 *          code 3: send/receive var.
 *          - Only the PIC can send codes 2-3.
 *        - For all but code 0, data = varNum (1 byte), length (1 byte), 
 *          data (of length bytes). varNum must be between 1 and
 *          \ref NUM_XFER_VARS.
 *    - For non-special, data is len bytes. For special:  see above. All
 *      lengths are len + 1, e.g. len = 0 is 1 byte, etc.
 *  - Sending a \ref CMD_TOKEN, whether inside a protocol packet or as a 
 *    character not in a packet, must always be escaped with a
 *    \ref CMD_TOKEN \ref ESCAPED_CMD.
 */
