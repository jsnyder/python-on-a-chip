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
 *  Configure and possibly switch the processor clock to the
 *  desired frequency, based on selections made in
 *  pic24_clockfreq.h. Each entry in the \ref CLOCK_CONFIG
 *  table should have a corresponding block of code in this
 *  file to configure the clock. Typical code structure is:
 *
 *  \code
#if IS_CLOCK_CONFIG(FRCPLL_FCY16MHz)
#warning Clock configured for FRCPLL, FCY = 16 MHz
#endif
#if GET_IS_SUPPORTED(FRCPLL_FCY16MHz)
void configClockFRCPLL_FCY16MHz(void) {
  ... code to configure this clock ...
  // Typically, after setup code above, swtich to
  // the newly configured oscillator.
  switchClock(OSC_SEL_BITS);
}
#endif
 * \endcode
 *
 * Notes: is some modes, the configuration bit settings suggest
 * that a clock switch unnecessary. For example, FNOSC_PRI
 * or FNOSC_FRC should require no clock switching. However, if
 * this was run from a bootloader, it may switch the clock away
 * from the settings determined by the configuration bits,
 * so a switch is still performed.
 * Likewise, in the PIC24F/H modes that use the PLL, the bootloader
 * could be using the PLL. In this can, PLL settings can't be
 * changed. So, the code switches to the FRC, changes PLL bits
 * (when it's guaranteed to be safe), then switch back to the PLL.
 */

#include "pic24_all.h"

#if !USE_CLOCK_TIMEOUT
//empty functions
void checkClockTimeout(void) {
}
#else
/* 
The purpose of the clock timeout functions is
output a meaningful error in case the clock switch
does not occur.  

*/
#define CLOCKTIMEOUT_MAX 200000L
#if  ( defined(__PIC24H__) || defined(__dsPIC33F__) )
#define FRC_FCY 40000000L
#elif ( defined(__PIC24F__) || defined(__PIC24FK__) )
#define FRC_FCY 16000000L
#else
#error Unknown processor.
#endif
#define FRC_BRGH 0


static void configFrcUART(void) {
  float f_brg;
  uint16 UxBRG;
  // First, switch to a known-good clock
#if ( defined(__PIC24H__) || defined(__dsPIC33F__) )
  configClockFRCPLL_FCY40MHz();
#elif ( defined(__PIC24F__) || defined(__PIC24FK__) )
  //safe choice: FCY=16 MHz, FRC+PLL
  configClockFRCPLL_FCY16MHz();
#else
#error Unknown processor
#endif

  // Second, get UART I/O pins mapped and general config done.
  configDefaultUART(DEFAULT_BAUDRATE);
  // BRG register is probably wrong since not using defined FCY. Fix it.
#if (FRC_BRGH == 0)
  f_brg = (((float) FRC_FCY)/((float) DEFAULT_BAUDRATE)/16.0) - 1.0;
#else
  f_brg = (((float) FRC_FCY)/((float) DEFAULT_BAUDRATE)/4.0) - 1.0;
#endif
  UxBRG = roundFloatToUint16(f_brg);
  switch (DEFAULT_UART) {
#if (NUM_UART_MODS >= 1)
    case 1 :
      U1BRG = UxBRG;
      U1MODEbits.BRGH = FRC_BRGH;
      break;
#endif
#if (NUM_UART_MODS >= 2)
    case 2 :
      U2BRG = UxBRG;
      U2MODEbits.BRGH = FRC_BRGH;
      break;
#endif
#if (NUM_UART_MODS >= 3)
    case 3 :
      U3BRG = UxBRG;
      U3MODEbits.BRGH = FRC_BRGH;
      break;
#endif
#if (NUM_UART_MODS >= 4)
    case 4 :
      U4BRG = UxBRG;
      U4MODEbits.BRGH = FRC_BRGH;
      break;
#endif
    default : ASSERT(0);
 }
}

static void checkClockTimeout(void) {
  static uint32 u32_timeoutCount = 0;
  
  // See if the clock has already failed. If so, return to allow
  // diagnostic code to perform (hopefully safe) clock switches
  // in order to report errors.
  if (u32_timeoutCount == 0xFFFFFFFF) return;

  // Otherwise, update timeout. If we the switch hasn't failed,
  // simple return to wait for the switch a bit more.
  u32_timeoutCount++;
  if (u32_timeoutCount < CLOCKTIMEOUT_MAX) return;

  // Clock switch failed. Mark this in the timeout.
  u32_timeoutCount = 0xFFFFFFFF;

  configFrcUART();
  outString("\n\n"
            "Your clock choice failed to initialize, have switched to internal Fast RC oscillator +PLL.\n"
            "Check your setting for the 'CLOCK_CONFIG' macro.\n"
            "Watch the compiler output window when pic24_clockfreq.c is compiled, a warning message\n"
            "will tell you the selected value for 'CLOCK_CONFIG'.\n"
            "In MPLAB, use Project->Build Options->Project, then click on MPLAB C30 tab to see if \n"
            "the macro is defined there. If the macro is selecting an external crystal (the primary oscillator),\n"
            "and your board does not have a crystal, you will get this message.\n"
            "Delete the macro definition from the MPLAB project if you want to use the default \n"
            "clock choice of FRC + PLL.\n"
            "You must recompile and reprogram with an appropriate CLOCK_CONFIG choice for this code to execute.\n");

  while(1) {
    doHeartbeat();  // never return.
  }
}
#endif


void switchClock(uint8 u8_source) {
  // Create a union that mirrors the OSCCON structure
  // with all its bit names but is also byte-accessable.
  OSCCONBITS OSCCONBITS_copy;

  // Switch clock to use new choice specified by u8_choice.
  // Valid values are 0-7.
  // Throw an error if the source isn't in the list above.
  ASSERT(u8_source < 8);
  // 1. Disable interrupts per 7.11.2 FRM rev B under
  //    "A recommended code sequence for a clock switch
  //     includes the following:" heading.
  //    Assumes there are no priority 7 interrupts enabled.
  asm("DISI #0x3FFF"); // Disable interrupts for a long time
  // 2. Switch to the PLL. Use compiler built-ins to unlock
  //    clock switch registers. See 7.11.1 of the FRM rev B.
  OSCCONBITS_copy = OSCCONbits;      // Copy OSCCON bits
  OSCCONBITS_copy.NOSC = u8_source;  // Select new clock source
  OSCCONBITS_copy.OSWEN = 1;         // Request clock switch
  // First write high byte, containing new clock source NOSC
  __builtin_write_OSCCONH(BITS2BYTEH(OSCCONBITS_copy));
  // Then write low byte, requesting clock switch with OSWEN
  __builtin_write_OSCCONL(BITS2BYTEL(OSCCONBITS_copy));
  asm("DISI #0");     // Re-enable them at the next instruction

#ifndef SIM
  // 3. Wait for switch to complete.
  //    Note that oscillator switching is not supported by
  //    the simulator, causing the statements below to
  //    run forever.
  while (_OSWEN == 1) {
    checkClockTimeout();
  }

  // 4. Wait for the PLL to lock if using the PLL.
  // (Is this really necessary? It certainly can't hurt.)
  if ( (u8_source == GET_OSC_SEL_BITS(FNOSC_FRCPLL)) ||
       (u8_source == GET_OSC_SEL_BITS(FNOSC_PRIPLL)) ) {
    while (_LOCK == 0) {
      checkClockTimeout();
    }
  }

  // 5. Make sure clock switch worked
  while (_COSC != u8_source) checkClockTimeout();
#endif
}

#if IS_CLOCK_CONFIG(SIM_CLOCK)
#warning Clock configured for simulation, FCY = 1 Mhz
#endif
#if GET_IS_SUPPORTED(SIM_CLOCK)
void configClockSim(void) { }
#endif


#if IS_CLOCK_CONFIG(FRCPLL_FCY16MHz)
#warning Clock configured for FRCPLL, FCY = 16 MHz
#endif
#if GET_IS_SUPPORTED(FRCPLL_FCY16MHz)
void configClockFRCPLL_FCY16MHz(void) {
  // To be safe: if this was run by a bootloader that chose FRCPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to FRCPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  // Two cases:
  //   1. Non-USB parts just have a FRC postscaler that feeds
  //      the 4x PLL block. Set this postscaler to 1 since the
  //      FRC runs at 8 MHz to get a 32 MHz FOSC = 16 MHz FCY.
  _RCDIV = 0;
#ifdef _CPDIV
  //      The PLL multiplies this 4 MHz input to 96 MHz then
  //      divides it by 3 to 32 MHz. A second PLL prescaler
  //      then selects the final FOSC. Choose a prescale of
  //      1 so FOSC = 32 MHz, giving FCY = 16 MHz.
  _CPDIV = 0;  // 0 means a prescale of 1
#endif
#ifdef _PLLDIV
  //   2. USB parts have a more complex clocking scheme. The
  //      FRC postscaler feeds a PLL prescaler rather than
  //      directly determining FOSC. The
  //      PLL input must be 4 MHz, so choose a PLL prescaler
  //      of 2 since the FRC runs at 8 MHz.
  _PLLDIV = 1;  // 1 means a prescale of 2
#elif defined(PLLDIV_NODIV)
#warning Ensure that the PLLDIV value is set to divide by 2 in the configuration bits for FRCPLL_FCY16MHz clock option!!
#endif
#ifdef _PLLEN
  _PLLEN = 1;
#warning PLL Enabled
#endif
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRCPLL));
}
#endif


#if IS_CLOCK_CONFIG(FRC_FCY4MHz)
#warning Clock configured for FRC, FCY = 4 MHz.
#warning Baud rates of 19200 or lower recommended for this clock choice.
#endif
#if GET_IS_SUPPORTED(FRC_FCY4MHz)
void configClockFRC_FCY4MHz(void) {
  // Ensure that the FRC postscaler is at '1' and not its reset default of '2' (PIC24F family)
  _RCDIV = 0;
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
}
#endif


#if IS_CLOCK_CONFIG(PRI_NO_PLL_7372KHzCrystal)
#warning Clock configured for a 7.372 MHz crystal primary oscillator, no PLL
#endif
#if GET_IS_SUPPORTED(PRI_NO_PLL_7372KHzCrystal)
void configClockPRI_NO_PLL_7372KHzCrystal(void) {
  switchClock(GET_OSC_SEL_BITS(FNOSC_PRI));
}
#endif


#if IS_CLOCK_CONFIG(FRC_FCY3685KHz)
#warning Clock configured for FRC, FCY = 3.685 MHz
#warning Baud rates of 9600 or lower recommended for this clock choice.
#endif
#if GET_IS_SUPPORTED(FRC_FCY3685KHz)
void configClockFRC_FCY3685KHz(void) {
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  // Choose no tuning on FRC to get 7.37 MHz nominal FOSC.
  // Do after clock switch in case FRCPLL was in use, since
  // that would alter PLL input frequency. (Might be OK, but
  // this is perhaps safer.)
  _TUN = 0;
}
#endif


#if IS_CLOCK_CONFIG(FRCPLL_FCY40MHz)
#warning Clock configured for FRCPLL, FCY = 40 MHz
#endif
#if GET_IS_SUPPORTED(FRCPLL_FCY40MHz)
void configClockFRCPLL_FCY40MHz(void) {
  // To be safe: if this was run by a bootloader that chose FRCPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to FRCPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  //settings for Cycle time = 40 MHz, internal oscillator with PLL
  // Tune the internal oscialltor to 6.85 MHz. Each unit
  // in the register below = 0.375% of the 7.37 MHz
  // nominal frequency in 2's complement per register 7-6
  // in section 7.4 of the FRM rev B. So:
  // Sanity check: -32*0.375% = -12% -> 6.4856 MHz per data sheet.
  //               +30*0.375% = 11.25% -> 8.1991 Mhz not 8.23 MHz
  //                                      given in the data sheet!
  //      However, +31*0.375% = 11.625% -> 8.2268 MHz, so the above
  //      is a typo. This error has been reported to Microchip and
  //      confirmed. It should be fixed in next rev of data sheet.
  // Another concern: since the clock is +/- 2%, we could end
  // up with a > 8.0 MHz processor clock! At 8 MHz, this would
  // be 8.16 MHz, so the processor would run at 81.6 MHz.
  // Ignore this for now; probably, the chip will still run.

  _TUN = -19;  // Correct setting assuming the RC oscillator is exactly 7.37MHz.
  // It may need to be tweaked however. Use the echo.c program, and a baud rate
  // of 115,200 and increase/decrease TUN until you get no framing errors

  // Choose PLL factors: Fref after first prescale must be
  // between 0.8 and 8.0 MHz. Choose a prescale of 8
  // for Fref of 0.856 MHz.
  _PLLPRE = 6; // Prescale = PLLPRE + 2
  // Fvco after multiply must be between 100 and 200 MHz.
  // Pick 160 MHz, so multiply by 187.
  _PLLDIV = 185; // Multiply = PLLDIV + 2
  // Final desired Fosc = 80 MHz for an Fcy = 40 MHz.
  // (See 7.7 of the FRM rev B). Pick 80 MHz, so postscale by 2.
  _PLLPOST = 0; // Postscale = 2 * (PLLPOST + 1)
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRCPLL));
}
#endif

#if IS_CLOCK_CONFIG(PRIPLL_7372KHzCrystal_40MHzFCY)
#warning Clock configured for PRIPLL using a 7.3727 Mhz primary oscillator, FCY = 40 MHz
#endif
#if GET_IS_SUPPORTED(PRIPLL_7372KHzCrystal_40MHzFCY)
void configClockPRIPLL_7372KHzCrystal_40MHzFCY(void) {
  // To be safe: if this was run by a bootloader that chose PRIPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to PRIPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  //settings for Cycle time = 40 MHz, primary oscillator with PLL
  _PLLPRE = 4; // Prescale = PLLPRE + 2
  _PLLDIV = 128; // Multiply = PLLDIV + 2
  _PLLPOST = 0; // Postscale = 2 * (PLLPOST + 1)
  switchClock(GET_OSC_SEL_BITS(FNOSC_PRIPLL));
}
#endif

#if IS_CLOCK_CONFIG(PRIPLL_8MHzCrystal_40MHzFCY)
#warning Clock configured for PRIPLL using an 8.0 Mhz primary oscillator, FCY = 40 MHz
#endif
#if GET_IS_SUPPORTED(PRIPLL_8MHzCrystal_40MHzFCY)
void configClockPRIPLL_8MHzCrystal_40MHzFCY(void) {
  //settings for Cycle time = 40 MHz, primary oscillator with PLL
  //These PLL settings will give an FCY == Crystal Freq * 10/2, or FOSC = Crystal Freq * 10
  /*
  This settings assumes the external crystal on is 8.0MHz
  */
  // To be safe: if this was run by a bootloader that chose PRIPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to PRIPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  _PLLPRE = 0; // Prescale = PLLPRE + 2
  _PLLDIV = 38; // Multiply = PLLDIV + 2
  _PLLPOST = 0; // Postscale = 2 * (PLLPOST + 1)
  switchClock(GET_OSC_SEL_BITS(FNOSC_PRIPLL));
}
#endif

#if IS_CLOCK_CONFIG(PRIPLL_8MHzCrystal_16MHzFCY)
#warning Clock configured for PRIPLL using a 8.0 Mhz primary oscillator, FCY = 16 MHz
#endif
#if GET_IS_SUPPORTED(PRIPLL_8MHzCrystal_16MHzFCY)
void configClockPRIPLL_8MHzCrystal_16MHzFCY(void) {
  // To be safe: if this was run by a bootloader that chose FRCPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to FRCPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_FRC));
  // Two cases:
  //   1. Non-USB parts just have a FRC postscaler that feeds
  //      the 4x PLL block. Set this postscaler to 1 since the
  //      FRC runs at 8 MHz to get a 32 MHz FOSC = 16 MHz FCY.
  _RCDIV = 0;
#ifdef _CPDIV
  //      The PLL multiplies this 4 MHz input to 96 MHz then
  //      divides it by 3 to 32 MHz. A second PLL prescaler
  //      then selects the final FOSC. Choose a prescale of
  //      1 so FOSC = 32 MHz, giving FCY = 16 MHz.
  _CPDIV = 0;  // 0 means a prescale of 1
#endif
#ifdef _PLLDIV
  //   2. USB parts have a more complex clocking scheme. The
  //      FRC postscaler feeds a PLL prescaler rather than
  //      directly determining FOSC. The
  //      PLL input must be 4 MHz, so choose a PLL prescaler
  //      of 2 since the FRC runs at 8 MHz.
  _PLLDIV = 1;  // 1 means a prescale of 2
#elif defined(PLLDIV_NODIV)
#warning Ensure that the PLLDIV value is set to divide by 2 in the configuration bits for PRIPLL_8MHzCrystal_16MHzFCY clock option!!
#endif
#ifdef _PLLEN
  _PLLEN = 1;
#warning PLL Enabled
#endif

  switchClock(GET_OSC_SEL_BITS(FNOSC_PRIPLL));
}
#endif

#if IS_CLOCK_CONFIG(PRI_8MHzCrystal_4MHzFCY)
#warning Clock configured for PRI using a 8.0 Mhz primary oscillator, FCY = 4 MHz
#endif
#if GET_IS_SUPPORTED(PRI_8MHzCrystal_4MHzFCY)
void configClockPRI_8MHzCrystal_4MHzFCY(void) {
  // To be safe: if this was run by a bootloader that chose FRCPLL mode,
  // then we can't change the bits below. To do so, first switch to FRC,
  // change bits, then switch back to FRCPLL.
  switchClock(GET_OSC_SEL_BITS(FNOSC_PRI));
}
#endif
