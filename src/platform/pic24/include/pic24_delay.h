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
 *  Provides simple software delays. They are not cycle-accurate, however.
 *  These routines are integrated with a \ref doHeartbeat "heartbeat LED",
 *  so the heartbeat count is updated during a delay.
 */

#ifndef _PIC24_DELAY_H_
#define _PIC24_DELAY_H_

/** Define a debounce delay for use in reading pushbutton
 *  switches. The value is specified in milliseconds.
 */
#ifndef DEBOUNCE_DLY
#define DEBOUNCE_DLY  15   //in milliseconds
#endif

/** A constant which gives the number of processor
 *  clock cycles in 1 millisecond. This value
 *  is cast to a uint32.
 */
#define CYCLES_PER_MS ((uint32)(FCY * 0.001))

/** A constant which gives the number of processor
 *  clock cycles in 1 microsecond. This value
 *  is cast to a uint32.
 */
#define CYCLES_PER_US ((uint32)(FCY * 0.000001))

#include "pic24_util.h"  // Need u32_heartbeatCount
#include <libpic30.h>    // Has __delay32

/** Delay the given number of processor clock cycles,
 *  then notify the heartbeat that time passed.
 *  Scale the time added to the heartbeat because
 *  we are not incurring the same
 *  overhead as if we repeatedly called
 *  <code>doHeartbeat()</code>.
 *  \param u32_cyc Number of processor clock cycles
 *                 to delay.
 */
inline static void delayAndUpdateHeartbeatCount(uint32 u32_cyc) {
  __delay32(u32_cyc);
#if USE_HEARTBEAT
  u32_heartbeatCount += (u32_cyc >> 4);
#endif
}


/** A macro to delay the given number of milliseconds.
 *  The maximum delay is ~ 100+
 *  seconds when FCY = 40 MHz, because the underlying
 *  function \ref delayAndUpdateHeartbeatCount uses
 *  a uint32 value for the number of processor clocks
 *  to delay.
 * \param ms The number of milliseconds to delay.
 */
#define DELAY_MS(ms)  delayAndUpdateHeartbeatCount(CYCLES_PER_MS * ((uint32) ms));

/** A macro to delay the given number of microseconds.
 *  \see \ref DELAY_MS for additional information.
 * \param us The number of microseconds to delay.
 */
#define DELAY_US(us)  delayAndUpdateHeartbeatCount(CYCLES_PER_US * ((uint32) us));


#endif
