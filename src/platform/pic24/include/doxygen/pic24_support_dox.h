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

// Documentation placed on the PIC24 support library page. This file only
// include comments for Doxygen; it does not contain any
// code.
/**
 * \page PIC24_support PIC24 support library
 * The PIC24 support library is divided into
 * \ref external "external components", \ref internal "internal components",
 * and \ref codeTools "tools" used in creating the library.
 * External components should be called by
 * the typical user to set up the PIC, communicate over the UART,
 * I<sup>2</sup>C bus, etc. Internal components include both
 * implementation details and information on adding support for
 * PIC24 processors not currently supported by this library.
 * Following these three sections is
 * a \ref libraryFunctionSummary "library function summary", 
 * listing all functions available in the library.
 *
 * A simple example which echos characters via the UART:
\code
#include "pic24_all.h"
int main(void) {
  // Set up clock, heartbeat, UART, print welcome message
  configBasic(HELLO_MSG);
  while (1) {
    // Echo characters
    outChar(inChar());
  }
  return 0;
}
\endcode
 *
 * \section libraryComponents Library components
 *
 * \subsection external External library components
 * - Development support
 *   - A single header file to include all the files below,
 *     in pic24_all.h
 *   - \ref delayRoutines "Delay routines" in pic24_delay.h
 *   - Definition of \ref dataTypes "generic data types" in pic24_generic.h
 *   - \ref portConfig "Setup of IO ports" in pic24_ports.h
 *   - Unit testing / assertions, in pic24_unittest.h
 *   - \ref utils "Miscellanous utilities" in pic24_util.h
 *   - \ref dataXfer "Debug/data tranfer" abilities in dataXfer.h
 * - Peripheral support
 *   - Analog to digital converter routines, in pic24_adc.h
 *   - Direct memory access (DMA) routines, in pic24_dma.h
 *   - Enhanced controller area network (ECAN) routines, in pic24_ecan.h
 *   - Read/write of FLASH, in pic24_flash.h
 *   - Setup of timers, in pic24_timer.h
 *   - Serial communication support, in pic24_serial.h
 *   - I<sup>2</sup>C support, in pic24_i2c.h
 *   - SPI support, in pic24_spi.h
 *
 * \subsection internal Internal library components
 * - User-configurable library settings, in pic24_libconfig.h
 * - Clock configuration, in pic24_clockfreq.h and
 *   pic24_clockfreq.c
 * - Configuration bit settings, in pic24_configbits.c
 * - UART support in pic24_uart.h and pic24_uart.c, which
 *   is typically called by routines in pic24_serial.h.
 *
 * \subsection codeTools Tools used to create the code
 * <a href="http://www.scons.org/">SCons</a> provides automated
 * library building and testing. See SConstruct.py for
 * documentation of this process. Capabilities include:
 * - Automated build of all example code in the textbook
 * - Support for multiple copies of a device, such as the UART,
 *   I<sup>2</sup>C, and SPI, is auto-generated from templates
 *   which contain a single copy of the code. The templates/
 *   directory contains the templates from which these files
 *   are built.
 *
 * To maintain a consistent style, a batch file which runs
 * the <a href="http://astyle.sourceforge.net/">Artistic Style</a>
 * code formatter is available as runAStyle.bat.
 *
 * \section libraryFunctionSummary Library function summary
 * This section lists all the commands available in the various sections
 * of the library, providing a quick overview of the library's
 * capabilities.
 *
 * \subsection delayRoutines Delay routines
 * The file pic24_delay.h defines:
 * - \ref DEBOUNCE_DLY, DELAY_MS(ms), DELAY_US(us), \ref CYCLES_PER_MS, 
 *   \ref CYCLES_PER_US, \ref delayAndUpdateHeartbeatCount(uint32 u32_cyc)
 *
 * \subsection dataTypes Generic data types
 * The file in pic24_generic.h defines:
 * - Signed integers: \ref int8, \ref int16, \ref int32, \ref int64
 * - Unsigned integers: \ref uint8, \ref uint16, \ref uint32, \ref uint64
 * - Unions: \ref union16, \ref union32, \ref union64
 *
 * \subsection portConfig Setup of IO ports
 * The file pic24_ports.h includes files which define:
 * - High-level port configuration: CONFIG_Rxy_AS_DIG_OUTPUT(),
 *   CONFIG_Rxy_AS_DIG_OD_OUTPUT(), CONFIG_Rxy_AS_DIG_INPUT(),
 *   CONFIG_ANx_AS_ANALOG()
 * - Low-level port configuration: ENABLE_Rxy_ANALOG(), 
 *   DISABLE_Rxy_ANALOG(), CONFIG_RPy_AS_DIG_PIN(), ENABLE_Rxy_OPENDRAIN(),
 *   DISABLE_Rxy_OPENDRAIN(), ENABLE_Rxy_PULLUP(), DISABLE_Rxy_PULLUP(),
 *   ENABLE_Rxy_CN_INTERRUPT(), DISABLE_Rxy_CN_INTERRUPT()
 * - <a href="pic24_ports.h#remappableInputs">Remappable peripheral input support</a>
 * - <a href="#remappableOutputs">Remappable peripheral output support</a>
 * \todo The relative anchor links above don't work across files.
 * 
 * \subsection utils Miscellaneous utility functions
 * The file pic24_utils.h includes files which define:
 * - The number of various peripherals on the chip: \ref NUM_UART_MODS,
 *   \ref NUM_I2C_MODS, \ref NUM_SPI_MODS, \ref NUM_ECAN_MODS
 * - Chip identification support, through DEV_ID_LOCATION, REVISION_LOCATION,
 *   \ref DEV_ID, \ref DEV_ID_STR, \ref EXPECTED_REVISION1,
 *   \ref EXPECTED_REVISION1_STR
 * - <a href="#bitfieldMacros">Bitfield struct to word/byte conversion</a>,
 *   in \ref BITS2WORD, \ref BITS2BYTEL, \ref BITS2BYTEH.
 * - More to do...
 */
