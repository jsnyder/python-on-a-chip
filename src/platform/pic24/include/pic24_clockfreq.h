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
 *  The clocking options for the PIC24 are chosen in this file.
 *  The resulting settings are used in pic24_clockfreq.c
 *  to configure and switch the oscillator as necessary after the chip
 *  is running.
 *
 *  To choose a clock configuration, simply
 *  select a value for \ref CLOCK_CONFIG from the table there.
 *  The default selection used by most of the PIC24H examples is FRCPLL_FCY40MHz
 *  (the internal FRC+ PLL configured for FCY = 40 MHz). Some of the examples
 *  in Chapter 12 expect an external 8 MHz crystal, and use the PRIPLL_8MHzCrystal_40MHzFCY option
 *  (external 8 MHz crystal + PLL confgured for FCY = 40 MHz). If \ref CLOCK_CONFIG is not
 *  defined, the default choice for PIC24H processors is FRCPLL_FCY40MHz, while for PIC24F 
 *  processors the default is FRCPLL_FCY16MHz (internal FRC+ PLL configured for FCY = 16 MHz).
 *
 *  This file provides several useful defines as a result of the
 *  clock selection above:
 *  - \ref CLOCK_CONFIG itself, although this is not typically
 *    directly useful. To determine which clock configuration
 *    was chosen, use the \ref CLOCK_CONFIG_INDEX for comparsion
 *    by applying the \ref IS_CLOCK_CONFIG macro.
 *  - The oscillator source as a configuration word (\ref FNOSC_SEL)
 *    and as a COSC/NOSC bitfield in the OSCCON register
 *    (\ref OSC_SEL_BITS).
 *  - The processor clock frequency \ref FCY.
 *  - The primary oscillator type \ref POSCMD_SEL.
 *  - The primary oscillator freqency \ref POSC_FREQ.
 *
 *  To define a new clock configuation:
 *  - Add a \#define to the table (see the section
 *    "#defines for CLOCK_CONFIG").
 *  - Add a configClockXxx() function which sets up
 *    and typically switches to that clock to
 *    pic24_clockfreq.c and a prototype for
 *    that function in this file.
 */

#ifndef _PIC24_CLOCKFREQ_H_
#define _PIC24_CLOCKFREQ_H_

/** Clock configuration for the PIC24 - set \ref CLOCK_CONFIG
 *  to one of the following. Naming convention is
 *  OSCTYPE_[PRIFREQ]_FCYFREQ where OSCTYPE gives the
 *  oscillator type (see \ref FNOSC_SEL for details),
 *  the optional PRIFREQ specifies primary oscillator frequency,
 *  and FCYFREQ determiens the processor clock
 *  (F<sub>CY</sub>) frequency. The "#defines for CLOCK_CONFIG"
 *  section gives the definition of the values below.
 *
 *  \code
 *  Name                            uP
 *  ---------------                 ---
 *  SIM_CLOCK (simulator)           any
 *  FRCPLL_FCY16MHz                 24F
 *  FRC_FCY4MHz                     24F
 *  PRIPLL_8MHzCrystal_16MHzFCY     24F
 *  PRI_NO_PLL_7372KHzCrystal       24F, 24H
 *  FRC_FCY3685KHz                  24H
 *  FRCPLL_FCY40MHz                 24H
 *  PRIPLL_7372KHzCrystal_40MHzFCY  24H
 *  PRIPLL_8MHzCrystal_40MHzFCY     24H
 *  \endcode
 */
#ifndef CLOCK_CONFIG
#define CLOCK_CONFIG SIM_CLOCK
#endif

///@{ \name #defines for CLOCK_CONFIG
/** Create a table of vales for CLOCK_CONFIG.
 *  When adding a new entry, you must also write
 *  C code to configure the clock in \ref pic24_clockfreq.c.
 *  See that file for examples and the detailed description
 *  section at the top of this page for more information.
 *  Note that \ref FCY and
 *  \ref POSC_FREQ should be defined as a long (with a
 *  trailing L) to retain enough accuracy to store
 *  these values.
 *
 *  Table entry notes: (see actual code, not the
 *  documentation, for the table)
 *  - Use -1 for don't-care values
 *  - The "unique index" just means each clock configuration
 *    should be assigned a different number. Giving two
 *    configurations the same index will cause problems!
 *    \see CLOCK_CONFIG_INDEX.
 *  - The processor field should evaluate to a Boolean value
 *    which is true if the processor under which this file
 *    is compiled is supported. Later in this file, the
 *    values PIC24F_DEFINED and PIC24H_DEFINED are set to
 *    true (1) or false (0) based on which processor this
 *    file is compiled with. Use these values in the
 *    Boolean expression. For example:
 *    - 1 (works on any processor)
 *    - PIC24H_DEFINED (works only on the PIC24H)
 *    - PIC24F_DEFINED || PIC24H_DEFINED
 *     (works on PIC24F and PIC24H).
 *  - Valid entries for \ref FNOSC_SEL are defined documentation
 *    for that variable.
 */
//  Table entries are:
//      #define name                    Unique index  FNOSC_SEL     FCY        POSCMD_SEL   POSC_FREQ  Processor                           configClock name                           Magic number of 498
//      ------------------------------  ------------  ------------  ---------  ----------   ---------  ----------------------------------  ----------------                           -------------------
#define SIM_CLOCK                       0,            -1,            1000000L, POSCMD_NONE,       -1,  1,                                  configClockSim,                            498
#define FRCPLL_FCY16MHz                 1,            FNOSC_FRCPLL, 16000000L, POSCMD_NONE,       -1,  (PIC24F_DEFINED || PIC24FK_DEFINED),  configClockFRCPLL_FCY16MHz,                498
#define FRC_FCY4MHz                     2,            FNOSC_FRC,     4000000L, POSCMD_NONE,       -1,  (PIC24F_DEFINED || PIC24FK_DEFINED),  configClockFRC_FCY4MHz,                    498
#define PRI_NO_PLL_7372KHzCrystal       3,            FNOSC_PRI,     3686400L, POSCMD_XT,   7372800L,  (PIC24F_DEFINED || PIC24FK_DEFINED || PIC24H_DEFINED || dsPIC33F_DEFINED), configClockPRI_NO_PLL_7372KHzCrystal,      498
#define FRC_FCY3685KHz                  4,            FNOSC_FRC,     3685000L, POSCMD_NONE,       -1,  (PIC24H_DEFINED || dsPIC33F_DEFINED),                     configClockFRC_FCY3685KHz,                 498
#define FRCPLL_FCY40MHz                 5,            FNOSC_FRCPLL, 40000000L, POSCMD_NONE,       -1,  (PIC24H_DEFINED || dsPIC33F_DEFINED),                     configClockFRCPLL_FCY40MHz,                498
#define PRIPLL_7372KHzCrystal_40MHzFCY  6,            FNOSC_PRIPLL, 40000000L, POSCMD_XT,   7372800L,  (PIC24H_DEFINED || dsPIC33F_DEFINED),                     configClockPRIPLL_7372KHzCrystal_40MHzFCY, 498
#define PRIPLL_8MHzCrystal_40MHzFCY     7,            FNOSC_PRIPLL, 40000000L, POSCMD_XT,   8000000L,  (PIC24H_DEFINED || dsPIC33F_DEFINED),                     configClockPRIPLL_8MHzCrystal_40MHzFCY,    498
#define PRIPLL_8MHzCrystal_16MHzFCY     8,            FNOSC_PRIPLL, 16000000L, POSCMD_XT,   8000000L,  (PIC24F_DEFINED || PIC24FK_DEFINED),                     configClockPRIPLL_8MHzCrystal_16MHzFCY,    498
#define PRI_8MHzCrystal_4MHzFCY         9,            FNOSC_PRI,     4000000L, POSCMD_XT,   8000000L,  (PIC24F_DEFINED || PIC24FK_DEFINED || PIC24H_DEFINED || dsPIC33F_DEFINED), configClockPRI_8MHzCrystal_4MHzFCY,        498
///@}


#ifndef __DOXYGEN__ // The following non-standard #if confuses Doxygen
// Check to make sure the CLOCK_CONFIG choice selected
// exists and is valid. Otherwise, the compiler emits some very
// confusing errors. Cute hack: the last value in the #define
// above (the magic number) is what the #if tests in gcc.
#if (CLOCK_CONFIG != 498)
#error ***********************************************************************
#error * Value chosen for CLOCK_CONFIG does not exist or is not valid!       *
#error * This produces very confusing compiler errors below.                 *
#error ***********************************************************************
#endif
#endif

// For some reason, primary oscillator selections are named
// POSCMD_xx in the PIC24H and POSCMOD_xx in the PIC24F.
// Work around this.
// Hopefully, this will be defined in PIC24F headers at some point
/// \cond nodoxygen
#ifndef POSCMD_EC
#define POSCMD_EC   POSCMOD_EC
#define POSCMD_XT   POSCMOD_XT
#define POSCMD_HS   POSCMOD_HS
#define POSCMD_NONE POSCMOD_NONE
#endif
/// \endcond

// Turn clock config type info the right #defines, using
// a three step process:
// Step 1. Just use another macro to turn params (viewied as one argument here)
//         to multiple arguments to the underscore version of the macro
/// \cond nodoxygen
#define GET_CLOCK_CONFIG_INDEX(params)    _GET_CLOCK_CONFIG_INDEX(params)
#define GET_FNOSC_SEL(params)             _GET_FNOSC_SEL(params)
#define GET_FCY(params)                   _GET_FCY(params)
#define GET_POSCMD_SEL(params)            _GET_POSCMD_SEL(params)
#define GET_POSC_FREQ(params)             _GET_POSC_FREQ(params)
#define GET_IS_SUPPORTED(params)          _GET_IS_SUPPORTED(params)
#define GET_CONFIG_DEFAULT_CLOCK(params)  _GET_CONFIG_DEFAULT_CLOCK(params)

// Step 2. Return the desired parameter, now that params are seen as
//         individual arguments.
#define _GET_CLOCK_CONFIG_INDEX(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClock, magic)        ndx
#define _GET_FNOSC_SEL(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)             oscSel
#define _GET_FCY(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)                   Fcy
#define _GET_POSCMD_SEL(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)            posCmdSel
#define _GET_POSC_FREQ(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)             poscFreq
#define _GET_IS_SUPPORTED(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)          isSupported
#define _GET_CONFIG_DEFAULT_CLOCK(ndx, oscSel, Fcy, posCmdSel, poscFreq, isSupported, configClockFunc, magic)  configClockFunc
// Step 3. Call the macros above to set constants based on the
//         clock config selected.
/// \endcond
#define CLOCK_CONFIG_INDEX      GET_CLOCK_CONFIG_INDEX(CLOCK_CONFIG)
#define FNOSC_SEL               GET_FNOSC_SEL(CLOCK_CONFIG)
#define FCY                     GET_FCY(CLOCK_CONFIG)
#define POSCMD_SEL              GET_POSCMD_SEL(CLOCK_CONFIG)
#define POSC_FREQ               GET_POSC_FREQ(CLOCK_CONFIG)
#define CONFIG_DEFAULT_CLOCK()  GET_CONFIG_DEFAULT_CLOCK(CLOCK_CONFIG)()

// Verify that the current processor is supported by the clock
// configuration chosen.
// 1. Set up some #defines as booleans which tell which processor
//    is selected for this compile.
/// \cond nodoxygen
#ifdef __PIC24F__
#define PIC24F_DEFINED 1
#else
#define PIC24F_DEFINED 0
#endif
#ifdef __PIC24H__
#define PIC24H_DEFINED 1
#else
#define PIC24H_DEFINED 0
#endif
#ifdef __dsPIC33F__
#define dsPIC33F_DEFINED 1
#else
#define dsPIC33F_DEFINED 0
#endif
#ifdef __PIC24FK__
#define PIC24FK_DEFINED 1
#else
#define PIC24FK_DEFINED 0
#endif

// 2. Check to see if this clock configuration supports that processor.
#if !GET_IS_SUPPORTED(CLOCK_CONFIG)
#error The clock configuration chosen is not supported by this processor.
#endif
// 3. Check that the primary oscillator type chosen works for the
//    oscilallator frequency selected. If the primary
#if (POSCMD_SEL == POSCMD_XT) && ( (POSC_FREQ < 3500000L) || (POSC_FREQ > 10000000L) )
#error The XT oscialltor chosen in POSCMD_SEL does not support this frequency!
#error Valid ranges are from 3.5 MHz to 10 MHz.
#endif
#if (POSCMD_SEL == POSCMD_HS) && ( (POSC_FREQ < 10000000L) || (POSC_FREQ > 32000000L) )
#error The HS oscialltor chosen in POSCMD_SEL does not support this frequency!
#error Valid ranges are from 10 MHz to 32 MHz.
#endif
/// \endcond

/// @{
/// \name Some of the #defines produced by CLOCK_CONFIG choice

/** \def CLOCK_CONFIG_INDEX
 *  A unique number is assigned to each clock configuration,
 *  in order to allow comparsions between configurations.
 *  CLOCK_CONFIG_INDEX gives the number assigned to the
 *  selected clock configuration. The macro
 *  \ref IS_CLOCK_CONFIG uses this number for its comparsisons.
 *
 *  \see SIM_CLOCK
 */

/** \def FNOSC_SEL
 *  Oscillator source selection for the PIC24. FNOSC_SEL
 *  is set to one of the following based on
 *  \ref CLOCK_CONFIG :
 *  \code
 *      Name                 Description                                    PIC24F  PIC24H
 *      -------------        --------------------------------------------   ------  ------
 *      FNOSC_FRC            Fast RC oscillator                                X      X
 *      FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL              X      X
 *      FNOSC_PRI            Primary oscillator (XT, HS, EC)                   X      X
 *      FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL            X      X
 *      FNOSC_SOSC           Secondary oscillator                              X      X
 *      FNOSC_LPRC           Low power RC oscillator                           X      X
 *      FNOSC_FRCDIV         Fast RC oscillator with divide                    X
 *      FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16                       X
 *      FNOSC_LPRCDIVN       Low power Fast RC oscillator w/divide by N               X
 \endcode
 */

/** \def FCY
 *  FCY specifies the resulting processor clock frequency after
 *  all PLL/divide operations take the inital clock and produce
 *  a processor clock. The units of this value are Hz, so the
 *  value 40000000L is 40 MHz.
 *
 *  NOTE: This should be defined as a long (with a trailing L
 *  after the number) to allocate enough space to correctly
 *  store the processor clock frequency.
 */

/** \def POSCMD_SEL
 *  Specifies the primary oscillator type. Valid values:
 *  \code
 *      POSCMD_EC            External clock
 *      POSCMD_XT            XT oscillator (for crystals from 3.5 MHz to 10 MHz)
 *      POSCMD_HS            HS oscillator (for crystals from 10 MHz to 32 MHz)
 *      POSCMD_NONE          Primary oscillator disabled
 *  \endcode
 */

/** \def POSC_FREQ
 *  This values gives the primary osciallator frequency (if used).
 *  The units of this value are Hz, so the value 40000000L is 40 MHz.
 *
 *  NOTE: This should be defined as a long (with a trailing L
 *  after the number) to allocate enough space to correctly
 *  store the processor clock frequency.
*/

/** \def OSC_SEL_BITS
 *  A macro giving the NOSC/COSC bits
 *  for the OSCCON register
 *  which correspond to \ref FNOSC_SEL,
 *  the configuration word which contains
 *  the FNOSC bits.
 */

/** \def CONFIG_DEFAULT_CLOCK
 *  Calls one of the configClock() functions defined
 *  in pic24_clockfreq.c based on the \ref CLOCK_CONFIG
 *  chosen.
 */
///@}


///@{ \name Helper macros for clock configuration
/** A helper macro to check if the given clock configuration
 *  was selected. Example usage is given in
 *  \ref pic24_clockfreq.c. A shorter example:
 *  \code
 *  #if IS_CLOCK_CONFIG(FRCPLL_FCY40MHz)
 *  ... code only included if CLOCK_CONFIG is FRCPLL_FCY40MHz ...
 *  #endif
 *  \endcode
 *  \param clockConfig Clock configuration to compare the current
 *         clock configuation against.
 */
#define IS_CLOCK_CONFIG(clockConfig) _GET_CLOCK_CONFIG_INDEX(clockConfig) == CLOCK_CONFIG_INDEX

/** A macro to determine the NOSC/COSC bits
 *  for the OSCCON register given bits taken
 *  from the PIC24's configuration FNOSC word.
 */
#define GET_OSC_SEL_BITS(bits) _GET_OSC_SEL_BITS(bits)
/// \cond nodoxygen
#if defined(__PIC24H__) || defined (__PIC24FK__) || defined(__dsPIC33F__) || defined(__DOXYGEN__)
#define _GET_OSC_SEL_BITS(bits) ((bits >> 0) & 0x07)
#elif defined (__PIC24F__) 
#define _GET_OSC_SEL_BITS(bits) ((bits >> 8) & 0x07)
#else
#error Unknown processor
#endif
// Note: putting the \ endcond here causes Doxygen 1.5.6
// to complain. ???
///@}
/// \endcond
#define OSC_SEL_BITS GET_OSC_SEL_BITS(FNOSC_SEL)

// Double check to make sure the oscillator selection above is valid.
#if ( (OSC_SEL_BITS < 0) || (OSC_SEL_BITS > 7) )
#error Invalid oscillator selection FNOSC_SEL.
#endif

/** @{
 *  \name configClock() functions for various clock setups
 */


#if GET_IS_SUPPORTED(SIM_CLOCK)
/** Nothing to do! Simulator clock not set by OSCCON,
 *  but instead in the Debugger | Settings, Osc/Trace
 *  dialog box. It should be 2 MHz there, since that's
 *  Fosc = 2*Fcy. At 1 MHz, simulation speed seems fast
 *  enough to execute a reasonable amount of code. Also,
 *  at a 64K line trace buffer, we can see 64 ms of
 *  execution, which is plenty to see 20 ms servo pulses.
 */
void configClockSim(void);
#endif

#if GET_IS_SUPPORTED(FRCPLL_FCY16MHz)
void configClockFRCPLL_FCY16MHz(void);
#endif

#if GET_IS_SUPPORTED(FRC_FCY4MHz)
void configClockFRC_FCY4MHz(void);
#endif

#if GET_IS_SUPPORTED(PRI_NO_PLL_7372KHzCrystal)
void configClockPRI_NO_PLL_7372KHzCrystal(void);
#endif

#if GET_IS_SUPPORTED(FRC_FCY3685KHz)
void configClockFRC_FCY3685KHz(void);
#endif

#if GET_IS_SUPPORTED(FRCPLL_FCY40MHz)
void configClockFRCPLL_FCY40MHz(void);
#endif

#if GET_IS_SUPPORTED(PRI_NO_PLL_7372KHzCrystal)
void configClockPRIPLL_7372KHzCrystal_40MHzFCY(void);
#endif

#if GET_IS_SUPPORTED(PRIPLL_8MHzCrystal_40MHzFCY)
void configClockPRIPLL_8MHzCrystal_40MHzFCY(void);
#endif

#if GET_IS_SUPPORTED(PRIPLL_8MHzCrystal_16MHzFCY)
void configClockPRIPLL_8MHzCrystal_16MHzFCY(void);
#endif

#if GET_IS_SUPPORTED(PRI_8MHzCrystal_4MHzFCY)
void configClockPRI_8MHzCrystal_4MHzFCY(void);
#endif


/// @}

/** Configure the default clock by calling the
 *  \ref CONFIG_DEFAULT_CLOCK() macro.
 */
static inline void configClock() {
  CONFIG_DEFAULT_CLOCK();
}


/** Switch the clock to the source specified. The source
 *  given will be assigned to NOSC in the OSCCON register,
 *  the a switch clock performed.
 *
 *  Note: <b>DO NOT</b> use \ref FNOSC_SEL as the source;
 *  instead, use \ref OSC_SEL_BITS. FNOSC_SEL is for
 *  configuration bits while switchClock
 *  expects a NOSC value to write to the
 *  OSCCON register.
 *
 * \param u8_source The clock source to switch to.
 */
void switchClock(uint8 u8_source);

#endif
