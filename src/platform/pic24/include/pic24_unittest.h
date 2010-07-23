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
/**
 * \file
 * Extremely simple unit testing framework, inspired by
 * http://www.jera.com/techinfo/jtns/jtn002.html.
 */

#ifndef  _PIC24_UNITTEST_H_
#define _PIC24_UNITTEST_H_

// Circular includes: pic24_util needs this include, but
// this needs reportError. Pre-declare here.
void reportError(const char* message);

/** Macro to convert a number to a string.
 *  Typical usage: <code>TOSTRING(__LINE__)</code>
 */
#define TOSTRING(x) _TOSTRING(x)
// A helper macro used by \ref TOSTRING.
#define _TOSTRING(x) #x
///@}

/** A macro to add the file name and line at which the
 *  macro was called to the given message.
 *  \param msg Message to add file/line info to.
 */
#define ERROR_FILE_LINE(msg) "Error in " __FILE__ " line " TOSTRING(__LINE__) ": " msg

// Uncomment the following line to remove all the ASSERTs
// from the program:
//#define _NOASSERT
#ifdef _NOASSERT
#define ASSERT(placeholder) (void)0
#define _COMPILE_ASSERT_SYMBOL_INNER(line, msg)
#define _COMPILE_ASSERT_SYMBOL(line, msg)
#define COMPILE_ASSERT(test, msg)
#else
/** A useful compile-time assert macro.
 * USAGE:  COMPILE_ASSERT( condition, message_to_print_if_fails)
 *
 * Note: these macros use typedef so they can't be use in a
 *			 value assignment type macro
 * Note: message_to_print_if_fails is used as C language variable in this
 *       clever little macro, SO.... your message must adhere to C variable
 *       naming rules, i.e. no spaces or funny characters.  Use underscores
 *       or CamelCase to separate words.
 */
#define COMPILE_ASSERT(test, msg)                      \
		typedef char _COMPILE_ASSERT_SYMBOL(__LINE__, msg) [ ((test) ? 1 : -1) ]
// A helper macro used by \ref COMPILE_ASSERT.
#define _COMPILE_ASSERT_SYMBOL_INNER(line, msg) __COMPILE_ASSERT_ ## line ## _____ ## msg
// A helper macro used by \ref COMPILE_ASSERT.
#define _COMPILE_ASSERT_SYMBOL(line, msg) _COMPILE_ASSERT_SYMBOL_INNER(line, msg)

/** Assert that test is true. See \ref picAssert for
 *  details. NOTE: only test results; DO NOT include main-line
 *  code in an ASSERT, since it can be compiled out.
 *  For example, <code>ASSERT(myFunc())</code> is dangerous,
 *  since <code>myFunc()</code> will no longer be called if
 *  ASSERT is disabled by defining _NDEBUG.
 */
#define ASSERT(test) picAssert(test, ERROR_FILE_LINE("ASSERT(" #test ") failed.\n"))

/** A function to reset the chip and report a message
 *  if the test is false. Assumes \ref reportError
 *  is called at start-up to report any assertion
 *  violations.
 *
 *  \param test Boolean results of test run. If false,
 *              reset and print message.
 *  \param message Message to print if assertion fails.
 */
static inline void picAssert(uint8 test, const char* message) {
  if (!test)
    reportError(message);
}
#endif

#endif // #ifndef  _PIC24_UNITTEST_H_
