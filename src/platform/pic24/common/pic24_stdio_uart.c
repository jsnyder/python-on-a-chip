/*
 * "Copyright (c) 2009 David Weaver ("AUTHORS")"
 * All rights reserved.
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
 * STDIO UART support functions
 *\par
 * This file provided courtesy of David Weaver who has given permission for it
 * to be included in the code archive.
 *\par
 * Provides standard I/O functions compatible with our single character library functions.
 * See chap10/reverse_string_stdio.c or chap10/stdio_test.c for examples using \em scanf().
 *\par
 * See libc documentation for definitions of open(), close(), read(), write(), and lseek().
 * Exceptions and limitations imposed by this implementation are documented here.
 *\par
 * Use of stdio functions is memory intensive especially for floating point!
 *\par
 *\em fopen() access specifiers work as docummented in libc.
 * Translation mode may be set seperately for reading
 * and writing as in example 1. If using read+write access, remember to seek during 
 * transitions from write to read and read to write. Use \em fseek() or \em rewind(). See example 2.
 *\par Example 1:
 *\code
 *     file1 = fopen("uart1", "r"); // uart1 open for reading text using file1
 *     file2 = fopen("uart1", "wb"); // uart1 open for writing binary using file2
 *     fprintf(file2, "Enter string:\n"); // binary - no "\n" substituion allowed - see open()
 *     fscanf(file1, "%s", buffer);\endcode
 *\par Example 2:
 *\code
 *     file3 = fopen("uart1", "r+"); // uart1 open for reading and writing text using file3
 *     fseek(file3, 0, SEEK_END);  // move to end of file for output - or use rewind()
 *     fprintf(file3, "Enter string:\n"); // text - may substitute for "\n" - see open()
 *     fseek(file3, 0, SEEK_SET);  // move to start of file for input - or use rewind()
 *     fscanf(file3, "%s", buffer);\endcode
 */

#include "pic24_all.h"
#include <stdio.h>

// These definitions for translation mode
// Also see SERIAL_EOL_DEFAULT setting in pic_24libconfig.h for output translation 
#define SERIAL_BREAK_CR // Break input stream on CR if specified
#define SERIAL_BREAK_NL // Break input stream on NL if specified

// These definitions are for libc placement and compatibility
#define _LIBC_FUNCTION __attribute__((__weak__, __section__(".libc")))
#define SUCCESS 0
#define FAIL -1
#define CHAR_ACCESS 0x4000
#define DATA_ACCESS 0x8000  //this flag assumed if CHAR_ACCESS not set
#define READ_ACCESS 0x0
#define WRITE_ACCESS 0x1
#define READ_WRITE_ACCESS 0x2
#define ACCESS_RW_MASK 0x3 // bits set to 0 or 2 for read and 1 or 2 for write
#define ACCESS_SET_OPEN DATA_ACCESS // expedient - reuse bit position to indicate open

//set default baudrate as needed for each of four UARTs
#ifndef DEFAULT_BAUDRATE1
#define DEFAULT_BAUDRATE1 DEFAULT_BAUDRATE
#endif
#ifndef DEFAULT_BAUDRATE2
#define DEFAULT_BAUDRATE2 DEFAULT_BAUDRATE
#endif
#ifndef DEFAULT_BAUDRATE3
#define DEFAULT_BAUDRATE3 DEFAULT_BAUDRATE
#endif
#ifndef DEFAULT_BAUDRATE4
#define DEFAULT_BAUDRATE4 DEFAULT_BAUDRATE
#endif

#define MAX_ALLOWED_HANDLES (NUM_UART_MODS+3) // number of handles allowed
#define RANGECK_HANDLE(xxhandlexx) ((xxhandlexx >= 0) && (xxhandlexx < MAX_ALLOWED_HANDLES))
enum ALLOWED_HANDLES {
	HANDLE_STDIN=0,
	HANDLE_STDOUT=1,
	HANDLE_STDERR=2,
	HANDLE_UART1,
	HANDLE_UART2,
	HANDLE_UART3,
	HANDLE_UART4
};

struct {
	void (*pfnv_outChar)(); // pointers to functions returning void need casts when set (why?)
	uint8 (*pfn_inChar)();
	uint16 u16_read_access;
	uint16 u16_write_access;
} FILES[MAX_ALLOWED_HANDLES] = {
	{ 0, 0 }, //stdin
	{ 0, 0 }, //stdout
	{ 0, 0 }, //stderr
#if (NUM_UART_MODS >= 1)
	{ (void *)&outChar1, &inChar1 },
#if (NUM_UART_MODS >= 2)
	{ (void *)&outChar2, &inChar2 },
#if (NUM_UART_MODS >= 3)
	{ (void *)&outChar3, &inChar3 },
#if (NUM_UART_MODS >= 4)
	{ (void *)&outChar4, &inChar4 }
#endif
#endif
#endif
#endif
};

/**********************************
 * Functions private to this file *
 **********************************/

/**
* Check __C30_UART for the UART to use. If set to 1, for example, then 
* set up \em stdin, \em stdout, and \em stderr for UART1 and
* call \em configUART1() if not currently enabled.
*\return \em SUCCESS or \em FAIL.
*
*/
static int16 stdioOpen(void)
{
#if (NUM_UART_MODS >= 1)
	if (__C30_UART == 1) {
		FILES[HANDLE_STDERR].pfnv_outChar = (void *)&outChar1;
		FILES[HANDLE_STDOUT].pfnv_outChar = (void *)&outChar1;
		FILES[HANDLE_STDIN].pfn_inChar = &inChar1;
		if (!U1MODEbits.UARTEN) {
			configUART1(DEFAULT_BAUDRATE1);
		}
		return SUCCESS;
	}
#if (NUM_UART_MODS >= 2)
	if (__C30_UART == 2) {
		FILES[HANDLE_STDERR].pfnv_outChar = (void *)&outChar2;
		FILES[HANDLE_STDOUT].pfnv_outChar = (void *)&outChar2;
		FILES[HANDLE_STDIN].pfn_inChar = &inChar2;
		if (!U2MODEbits.UARTEN) {
			configUART2(DEFAULT_BAUDRATE2);
		}
		return SUCCESS;
	}
#if (NUM_UART_MODS >= 3)
	if (__C30_UART == 3) {
		FILES[HANDLE_STDERR].pfv_outChar = (void *)&outChar3;
		FILES[HANDLE_STDOUT].pfv_outChar = (void *)&outChar3;
		FILES[HANDLE_STDIN].pfui8_inChar = &inChar3;
		if (!U3MODEbits.UARTEN) {
			configUART3(DEFAULT_BAUDRATE3);
		}
		return SUCCESS;
	}
#if (NUM_UART_MODS >= 4)
	if (__C30_UART == 4) {
		FILES[HANDLE_STDERR].pfv_outChar = (void *)&outChar4;
		FILES[HANDLE_STDOUT].pfv_outChar = (void *)&outChar4;
		FILES[HANDLE_STDIN].pfui8_inChar = &inChar4;
		if (!U4MODEbits.UARTEN) {
			configUART4(DEFAULT_BAUDRATE4);
		}
		return SUCCESS;
	}
#endif
#endif
#endif
#endif
	return FAIL;
}

/*********************************************************
 * Public functions intended to be called by other files *
 *********************************************************/

/**
* Initiate I/O on UART specified by \em name
*\param name of file (UART) to open.
*Limited to "stdin", "stdout", "stderr", "uart1", "uart2", "uart3", and "uart4".
*\n
*UART number specified by \em __C30_UART is reserved and can only be opened
*as \em stdin, \em stdout, and \em stderr.
*\param access is a bit field. Default, 0x0, is for binary read.
*Set it to include \em 0x4000 for character translation mode:
*\n
*input - possible break on '\\r' and '\\n' - See \em SERIAL_BREAK_NL and \em SERIAL_BREAK_CR.
*\n
*output - possible substitutions for '\\n' - See \em SERIAL_EOL_CR and \em SERIAL_EOL_CR_LF.
*\n
*If desired, OR it with 0x1 for write, or 0x2 for read and write.
*\param mode not used
*\return \em handle or \em FAIL.
*
*/
int _LIBC_FUNCTION
open(const char *name, int access, int mode)
{
	enum ALLOWED_HANDLES ie_handle;
	uint16 u16_masked_access;
	uint16 u16_set_access;

	switch (name[4]) { // Expedient - name[4] is unique for the allowed file names
	case 'n': //stdin
		if (stdioOpen()) return FAIL;
		ie_handle = HANDLE_STDIN;
		break;
	case 'u': //stdout
		if (stdioOpen()) return FAIL;
		ie_handle = HANDLE_STDOUT;
		break;
	case 'r': //stderr
		if (stdioOpen()) return FAIL;
		ie_handle = HANDLE_STDERR;
		break;
    #if (NUM_UART_MODS >= 1)
	case '1': //uart1
        if (__C30_UART == 1) return FAIL;
		if (!U1MODEbits.UARTEN) {
			configUART1(DEFAULT_BAUDRATE1);
		}
		ie_handle = HANDLE_UART1;
		break;
    #endif
	#if (NUM_UART_MODS >= 2)
	case '2': //uart2
        if (__C30_UART == 2) return FAIL;
		if (!U2MODEbits.UARTEN) {
			configUART2(DEFAULT_BAUDRATE2);
		}
		ie_handle = HANDLE_UART2;
		break;
	#endif
	#if (NUM_UART_MODS >= 3)
	case '3': //uart3
        if (__C30_UART == 3) return FAIL;
		if (!U3MODEbits.UARTEN) {
			configUART3(DEFAULT_BAUDRATE3);
		}
		ie_handle = HANDLE_UART3;
		break;
    #endif
    #if (NUM_UART_MODS >= 4)
	case '4': //uart4
        if (__C30_UART == 4) return FAIL;
		if (!U4MODEbits.UARTEN) {
			configUART4(DEFAULT_BAUDRATE4);
		}
		ie_handle = HANDLE_UART4;
		break;
	 #endif
	default:
		return FAIL; // name not recognized
	}

	u16_masked_access = access & ACCESS_RW_MASK;
	u16_set_access = ACCESS_SET_OPEN | access;
	if ((u16_masked_access == READ_ACCESS) || (u16_masked_access == READ_WRITE_ACCESS)) {
		FILES[ie_handle].u16_read_access = u16_set_access;
	}
	if ((u16_masked_access == WRITE_ACCESS) || (u16_masked_access == READ_WRITE_ACCESS)) {
		FILES[ie_handle].u16_write_access = u16_set_access;
	}
	return ie_handle;
}

/**
*Input \em len characters from UART specified for \em handle to \em buffer.
*Uses \em mode specified via \em open().
*If \em handle is for \em stdin, calls \em open() with character translation read \em access as needed. 
*\param handle specifies UART to read from.
*\param buffer storage for read characters.
*\param len maximum number of characters to read.
*\return number of charaters in \em buffer or \em FAIL.
*
*/
int _LIBC_FUNCTION
read(int handle, void *buffer, unsigned int len)
{
	uint16 u16_char_count;

	if(!RANGECK_HANDLE(handle)) return FAIL; // invalid handle
	if ((handle == HANDLE_STDIN) && !(FILES[HANDLE_STDIN].u16_read_access & ACCESS_SET_OPEN)) {
		open("stdin", (CHAR_ACCESS | READ_ACCESS), 0);
	}
	if (!FILES[handle].u16_read_access) return FAIL; // not open
	for (u16_char_count = 0; u16_char_count < len; u16_char_count++) {
		((unsigned char *)buffer)[u16_char_count] = (*FILES[handle].pfn_inChar)();
		#ifdef SERIAL_BREAK_NL
		if ((FILES[handle].u16_read_access & CHAR_ACCESS) && (((unsigned char *)buffer)[u16_char_count] == '\n')) {
			++u16_char_count;
			break;
		}
		#endif
		#ifdef SERIAL_BREAK_CR
		if ((FILES[handle].u16_read_access & CHAR_ACCESS) && (((unsigned char *)buffer)[u16_char_count] == '\r')) {
			++u16_char_count;
			break;
		}
		#endif
	}

	return u16_char_count;
}

/**
*Output \em len characters from \em buffer to UART specified for \em handle.
*Uses \em mode specified via \em open().
* If \em handle is for \em stdout or \em stderr, calls \em open() with character translation write \em access as needed.
*\param handle specifies UART to write to.
*\param buffer contains characters to write.
*\param len number of characters to write.
*\return number of charaters written from buffer or \em FAIL.
*
*/
int _LIBC_FUNCTION
write(int handle, void *buffer, unsigned int len)
{
	uint16 u16_char_count;

	if(!RANGECK_HANDLE(handle)) return FAIL; // invalid handle
	if ((handle == HANDLE_STDOUT) && !(FILES[HANDLE_STDOUT].u16_write_access & ACCESS_SET_OPEN)) {
		open("stdout", (CHAR_ACCESS | WRITE_ACCESS), 0);
	}
	if ((handle == HANDLE_STDERR) && !(FILES[HANDLE_STDERR].u16_write_access & ACCESS_SET_OPEN)) {
		open("stderr", (CHAR_ACCESS | WRITE_ACCESS), 0);
	}
	if (!FILES[handle].u16_write_access) return FAIL; // not open
	for (u16_char_count = 0; u16_char_count < len; u16_char_count++) {
		if ((FILES[handle].u16_write_access & CHAR_ACCESS) && (((unsigned char *)buffer)[u16_char_count] == '\n')) {
           #if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR)
		    (*FILES[handle].pfv_outChar)('\r');
			continue;
           #endif
           #if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR_LF)
		     (*FILES[handle].pfv_outChar)('\r');
           #endif
		    (*FILES[handle].pfnv_outChar)('\n');
			continue;
		}
		(*FILES[handle].pfnv_outChar)(((unsigned char *)buffer)[u16_char_count]);
	}

	return u16_char_count;
}

/**
*Stub required by \em fclose().
*\param handle not used.
*\return \em SUCCESS.
*
*/
int _LIBC_FUNCTION
close(int handle) {
	return SUCCESS;
}

/**
*Stub required by \em rewind() and \em fseek().
*\param handle not used.
*\param offset not used.
*\param origin not used.
*\return \em SUCCESS.
*
*/
long _LIBC_FUNCTION
lseek(int handle, long offset, int origin) {
	return SUCCESS;
}
