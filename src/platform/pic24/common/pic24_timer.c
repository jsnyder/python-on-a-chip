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
 *  To do.
 */

#include "pic24_all.h"

/*********************************
 * Function private to this file *
 *********************************/


/** Converts milliseconds to 16-bit timer ticks.
 *  \param u16_ms Time, in milliseconds, to convert to ticks
 *  \param u16_pre Prescale set for this timer. Note that
 *                 \ref getTimerPrescale can easily determine
 *                 this.
 *  \return Timer ticks corresponding to the given number of
 *          milliseconds.
 */
uint16 msToU16Ticks(uint16 u16_ms, uint16 u16_pre) {
// Use a float internally for precision purposes to accomodate wide range of FCY, u16_pre
  float f_ticks = FCY;
  uint16 u16_ticks;
  f_ticks = (f_ticks*u16_ms)/u16_pre/1000L;
  ASSERT(f_ticks < 65535.5);
  u16_ticks = roundFloatToUint16(f_ticks);  //back to integer
  return u16_ticks;
}

/** Converts microseconds to 16-bit timer ticks.
 *  \param u16_us Time, in microseconds, to convert to ticks
 *  \param u16_pre Prescale set for this timer. Note that
 *                 \ref getTimerPrescale can easily determine
 *                 this.
 *  \return Timer ticks corresponding to the given number of
 *          microseconds.
 */
uint16 usToU16Ticks(uint16 u16_us, uint16 u16_pre) {
  // Use a float internally for precision purposes to accomodate wide range of FCY, u16_pre
  float f_ticks = FCY;
  uint16 u16_ticks;
  f_ticks = (f_ticks*u16_us)/u16_pre/1000000L;
  ASSERT(f_ticks < 65535.5);
  u16_ticks = roundFloatToUint16(f_ticks);  //back to integer
  return u16_ticks;

}

/** Converts microseconds to 32-bit timer ticks.
 *  \param u32_us Time, in microseconds, to convert to ticks
 *  \param u16_pre Prescale set for this timer. Note that
 *                 \ref getTimerPrescale can easily determine
 *                 this.
 *  \return Timer ticks corresponding to the given number of
 *          microseconds.
 */
uint32 usToU32Ticks(uint32 u32_us, uint16 u16_pre) {
// Use a float internally for precision purposes to accomodate wide range of FCY, u16_pre
  float f_ticks = FCY;
  uint32 u32_ticks;
  f_ticks = (f_ticks*u32_us)/u16_pre/1000000L;
  u32_ticks = roundFloatToUint32(f_ticks);  //back to integer
  return u32_ticks;
}



/** Given the TCKPS bitfield, return the timer prescale encoded
 *  by these bits. Use \ref getTimerPrescale as a convenient
 *  way to extract the TCKPS bitfield from a TxCONbits SFT
 *  then call this function.
 *  \param u8_TCKPS TCKPS bitfield from the timer in question
 *  \return Prescale value.
 */
uint16 getTimerPrescaleBits(uint8 u8_TCKPS) {
  uint16 au16_prescaleValue[] = { 1, 8, 64, 256 };
  ASSERT(u8_TCKPS <= 3);
  return au16_prescaleValue[u8_TCKPS];
}

/** Converts timer ticks to milliseconds
 *  \param u32_ticks  Timer ticks
 *  \param u16_tmrPre Timer prescale value
 *  \return time in milliseconds
 */
uint32 ticksToMs (uint32 u32_ticks, uint16 u16_tmrPre) {
  //because of the wide range of the numbers, use a float for precision
  float f_ticks;
  uint32 u32_timeMs;

  f_ticks = u32_ticks;   //convert to float
  f_ticks = ((f_ticks * u16_tmrPre)/FCY) * 1000;
  u32_timeMs = roundFloatToUint32(f_ticks);  //back to int32
  return (u32_timeMs);
}


/** Converts timer ticks to microseconds
 *  \param u32_ticks  Timer ticks
 *  \param u16_tmrPre Timer prescale value
 *  \return time in microseconds
 */
uint32 ticksToUs (uint32 u32_ticks, uint16 u16_tmrPre) {
  //because of the wide range of the numbers, use a float for precision
  float f_ticks;
  uint32 u32_timeUs;

  f_ticks = u32_ticks;   //convert to float
  f_ticks = ((f_ticks * u16_tmrPre)/FCY) * 1000000L;
  u32_timeUs = roundFloatToUint32(f_ticks);  //back to int32
  return (u32_timeUs);
}

/** Converts timer ticks to nanoseconds
 *  \param u32_ticks  Timer ticks
 *  \param u16_tmrPre Timer prescale value
 *  \return time in nanoseconds
 */
uint32 ticksToNs (uint32 u32_ticks, uint16 u16_tmrPre) {
  //because of the wide range of the numbers, use a float for precision
  float f_ticks;
  uint32 u32_timeNs;

  f_ticks = u32_ticks;   //convert to float
  f_ticks = ((f_ticks * u16_tmrPre)/FCY) * 1000000000L;
  u32_timeNs = roundFloatToUint32(f_ticks);  //back to int32
  return (u32_timeNs);
}

/** Computes delta ticks between two Timer register captures
 * Assumes long time interval and thus has a parameter for tracking timer overflows
 *  \param u16_start  start tick
 *  \param u16_end    end tick
 *  \param u16_tmrPR  Timer period register
 *  \param u16_oflows number of timer overflows
 *  \return delta ticks
 */
uint32 computeDeltaTicksLong(uint16 u16_start, uint16 u16_end, uint16 u16_tmrPR, uint16 u16_oflows) {
  uint32 u32_deltaTicks;
  if (u16_oflows == 0) u32_deltaTicks = u16_end - u16_start;
  else {
    //compute ticks from start to timer overflow
    u32_deltaTicks = (u16_tmrPR + 1) - u16_start;
    //add ticks due to overflows =  (overflows -1) * ticks_per_overflow
    u32_deltaTicks += ((((uint32) u16_oflows)- 1) * (((uint32)u16_tmrPR) + 1)) ;
    //now add in the delta due to the last capture
    u32_deltaTicks += u16_end;
  }
  return (u32_deltaTicks);
}

/** Computes delta ticks between two Timer register captures
 * Assumes the delta time does not exceeds the timer period
 *  \param u16_start  start tick
 *  \param u16_end    end tick
 *  \param u16_tmrPR  Timer period register
 *  \return delta ticks
 */
uint16 computeDeltaTicks(uint16 u16_start, uint16 u16_end, uint16 u16_tmrPR) {
  uint16 u16_deltaTicks;
  if (u16_end >= u16_start) u16_deltaTicks = u16_end - u16_start;
  else {
    //compute ticks from start to timer overflow
    u16_deltaTicks = (u16_tmrPR + 1) - u16_start;
    //now add in the delta from overflow to u16_end
    u16_deltaTicks += u16_end;
  }
  return (u16_deltaTicks);
}
