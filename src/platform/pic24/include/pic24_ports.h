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


#ifndef _PIC24_PORTS_H_
#define _PIC24_PORTS_H_
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  This file supports configuration of IO ports on the PIC24. Support includes:
 *  - Configuring a pin for analog or digital operation by changing the
 *    corresponding _PCFGn bit. For digital
 *    operation:
 *    - Configure a pin as an input or an output by changing the
 *      corresponding _TRISxy bit.
 *    - Choose an open-drain or standard output driver by changing
 *      the corresponding _CNmPU bit.
 *    - Enable or disable pull-ups by changing the corresponding
 *      _ODCxy bit.
 *    - Enable or disable the interrupt on change mechanism by
 *      changing the corresponding _CNmIE bit.
 *  - A convenient mechanism for mapping a remappable peripheral to 
 *    input or output pins.
 * 
 *  \section portSummary Summary of port configuration macros
 *  The port configuration macros are available in two forms.
 *  <a href="#highLevelPortConfig">Higher-level</a> routines 
 *  completely configure a pin for a specific
 *  operation, while <a href="#lowLevelPortConfig">low-level</a> routines 
 *  provide a more readable name
 *  for changing the value of a single bit (_PCFGn, _TRISxy, _CNmPU, or
 *  _ODCxy).
 *
 *  To reduce the confusing variety of naming schemes for these bits,
 *  the macros refer to a pin either by its port letter \a x plus pin
 *  number \a y (for example, _TRISB3 for the TRIS bit of port B, pin 3)
 *  or by the analog input number \a n (for example, AN0 refers to 
 *  analog input 0).
 *
 *  The macros provided as "smart" - only functions applicable to that
 *  pin are contained in a given macro. For example, 
 *  CONFIG_RA1_AS_DIG_OUTPUT on the PIC24HJ32GP202 disables the pin's
 *  pullup, disables the open-drain driver, disables analog functionality,
 *  then sets the pin as an output. CONFIG_RA7_AS_DIG_OUTPUT on the
 *  PIC24HJ32GP204 only disables the open-drain driver and sets the pin
 *  as an output, because that pin supports neither analog nor pullup
 *  functionality.
 *
 *  \todo Put stub documentation for ALL port macros (doxygen only) so
 *  they hyperlink in source code
 *
 *  \todo Add a macro in for TRIS bit configuration
 *
 *  \todo Brief documentation for all remappable peripherals
 */

// Dummy macros for documentation only
#ifdef __DOXYGEN__
/** \name High-level port configuration
 *  <a name="highLevelPortConfig">These</a> macros choose 
 *  digital or analog, input or
 *  output, open-drain or standard. Use the low-level
 *  \ref ENABLE_Rxy_PULLUP() "ENABLE"/\ref DISABLE_Rxy_PULLUP() to 
 *  configure the pullup.
 */
//@{
/** This macro disables open-drain and pullups,
 *  configures port x pin y for digital (not analog) operation, and
 *  sets the pin as an output. For example, CONFIG_RA10_AS_DIG_OUTPUT()
 *  makes port A, pin 10 a digital output.
 */
static inline void CONFIG_Rxy_AS_DIG_OUTPUT() {}

/** This macro enables open-drain, disables pullups,
 *  configures port x pin y for digital (not analog) operation, and
 *  sets the pin as an output. For example, CONFIG_RA10_AS_DIG_OD_OUTPUT()
 *  makes port A, pin 10 a digital output.
 */
static inline void CONFIG_Rxy_AS_DIG_OD_OUTPUT() {}

/** This macro disables pullups and analog functionality and sets
 *  the pin as an input. For example, CONFIG_RA10_AS_DIG_OUTPUT() makes
 *  port A, pin 10 a digital input.
 */
static inline void CONFIG_Rxy_AS_DIG_INPUT() {}

/** This macro first calls \ref CONFIG_Rxy_AS_DIG_INPUT() to disable
 *  pullups on the pin then enables analog functionality on the pin.
 *  For example, CONFIG_AN1_AS_ANALOG() makes AN1 an analog input pin.
 */
static inline void CONFIG_ANx_AS_ANALOG() {}
//@}

/** \name Low-level port configuration macros
 *  <a name="lowLevelPortConfig">These</a> macros support low-level pin 
 *  configuration in the following areas:
 *  - Digital vs. analog configuration: 
 *    - ENABLE_Rxy_ANALOG() sets the corresponding _PCFGn bit,
 *      while DISABLE_Rxy_ANALOG() clears the corresponding _PCFGn bit.
 *    - CONFIG_RPy_AS_DIG_PIN() sets the corresponding _PCFGn bit.
 *  - Input vs. output configuration: none. Instead, simply assign to
 *    the _TRISxy flag directly: _TRISB1 = 1 makes port B, pin 1 an input
 *    while _TRISB1 = 0 makes it an output.
 *  - Open-drain vs. standard output driver: ENABLE_Rxy_OPENDRAIN(),
 *    DISABLE_Rxy_OPENDRAIN()
 *  - Pull-up configuration: ENABLE_Rxy_PULLUP(), DISABLE_Rxy_PULLUP()
 *  - Change notification configuration: ENABLE_Rxy_CN_INTERRUPT(),
 *    DISABLE_Rxy_CN_INTERRUPT()
 */
//@{

/** Enables analog functionality on port x of pin y by clearing the
 *  corresponding _PCFGn bit. For example, ENABLE_RA10_ANALOG() enables
 *  analog functionality on port A pin 10.
 */
#define ENABLE_Rxy_ANALOG() _PCFGn = 0

/** Disables analog functionality on port x of pin y by setting the
 *  corresponding _PCFGn bit. For example, DISABLE_RA10_ANALOG() disables
 *  analog functionality on port A pin 10.
 */
#define DISABLE_Rxy_ANALOG() _PCFGn = 1

/** Makes port P, pin y a digital pin by disabling analog functionality
 *  on that pin. This is done by setting the
 *  corresponding _PCFGn bit. For example, CONFIG_RP10_AS_DIG_PIN() makes
 *  port P, pin 10 a digital pin by disabling analog its functionality.
 */
#define CONFIG_RPy_AS_DIG_PIN() _PCFG = 1

/** Enables the open-drain driver on port x, pin y. For example, 
 *  ENABLE_Rxy_OPENDRAIN()
 */
#define ENABLE_Rxy_OPENDRAIN() _ODCxy = 1

/** Disables the open-drain driver on port x, pin y. For example, 
 *  DISABLE_Rxy_OPENDRAIN()
 */
#define DISABLE_Rxy_OPENDRAIN() _ODCxy = 0

/** Enable the pullup on port x, pin y. For example, 
 *  ENABLE_RA10_PULLUP() enables the pullup on port A, pin 10.
 */
#define ENABLE_Rxy_PULLUP() _CNmPUE = 1

/** Disable the pullup on port x, pin y. For example, 
 *  DISABLE_RA10_PULLUP() disables the pullup on port A, pin 10.
 */
#define DISABLE_Rxy_PULLUP() _CNmPUE = 1

/** Enables the change notification interrupt on port x, pin y.
 *  For example, ENABLE_RA10_CN_INTERRUPT() enables the change
 *  notification interrupt on port A, pin 10.
 */
#define ENABLE_Rxy_CN_INTERRUPT() _CNmIE = 1

/** Disables the change notification interrupt on port x, pin y.
 *  For example, DISABLE_RA10_CN_INTERRUPT() disables the change
 *  notification interrupt on port A, pin 10.
 */
#define DISABLE_Rxy_CN_INTERRUPT() _CNmIE = 0
//@}
#endif // #ifdef __DOXYGEN__

/** \name Remappable peripheral input support
 *  <a name="remappableInputs">These</a> funcions map an input internal 
 *  to the PIC to an input pin.
 *  For example, CONFIG_INT1_TO_RP(10) maps the INT1 edge-triggered
 *  interrupt to port P, pin 10.
 *
 *  Not all devices support remappable peripherals. In these cases,
 *  the macros below evalaute to nothing: \ref CONFIG_INT1_TO_RP(10) is
 *  a valid C statement which does nothing.
 */
//@{

#if defined(_INT1R) || defined(__DOXYGEN__)
/// Maps INT1 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#define CONFIG_INT1_TO_RP(pin) _INT1R = pin
#else
#define CONFIG_INT1_TO_RP(pin)
#endif

/// Maps INT2 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INT2R) || defined(__DOXYGEN__)
#define CONFIG_INT2_TO_RP(pin) _INT2R = pin
#else
#define CONFIG_INT2_TO_RP(pin)
#endif

/// Maps T2CK to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T2CKR) || defined(__DOXYGEN__)
#define CONFIG_T2CK_TO_RP(pin) _T2CKR = pin
#else
#define CONFIG_T2CK_TO_RP(pin)
#endif

/// Maps T3CK to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T3CKR) || defined(__DOXYGEN__)
#define CONFIG_T3CK_TO_RP(pin) _T3CKR = pin
#else
#define CONFIG_T3CK_TO_RP(pin)
#endif

/// Maps T4CK to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T4CKR) || defined(__DOXYGEN__)
#define CONFIG_T4CK_TO_RP(pin) _T4CKR = pin
#else
#define CONFIG_T4CK_TO_RP(pin)
#endif

/// Maps T5CK to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T5CKR) || defined(__DOXYGEN__)
#define CONFIG_T5CK_TO_RP(pin) _T5CKR = pin
#else
#define CONFIG_T5CK_TO_RP(pin)
#endif

/// Maps IC1 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC1R) || defined(__DOXYGEN__)
#define CONFIG_IC1_TO_RP(pin) _IC1R = pin
#else
#define CONFIG_IC1_TO_RP(pin)
#endif

/// Maps IC2 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC2R) || defined(__DOXYGEN__)
#define CONFIG_IC2_TO_RP(pin) _IC2R = pin
#else
#define CONFIG_IC2_TO_RP(pin)
#endif

/// Maps IC3 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC3R) || defined(__DOXYGEN__)
#define CONFIG_IC3_TO_RP(pin) _IC3R = pin
#else
#define CONFIG_IC3_TO_RP(pin)
#endif

/// Maps IC4 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC4R) || defined(__DOXYGEN__)
#define CONFIG_IC4_TO_RP(pin) _IC4R = pin
#else
#define CONFIG_IC4_TO_RP(pin)
#endif

/// Maps IC5 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC5R) || defined(__DOXYGEN__)
#define CONFIG_IC5_TO_RP(pin) _IC5R = pin
#else
#define CONFIG_IC5_TO_RP(pin)
#endif

/// Maps IC6 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC6R) || defined(__DOXYGEN__)
#define CONFIG_IC6_TO_RP(pin) _IC6R = pin
#else
#define CONFIG_IC6_TO_RP(pin)
#endif

/// Maps IC7 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC7R) || defined(__DOXYGEN__)
#define CONFIG_IC7_TO_RP(pin) _IC7R = pin
#else
#define CONFIG_IC7_TO_RP(pin)
#endif

/// Maps IC8 to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC8R) || defined(__DOXYGEN__)
#define CONFIG_IC8_TO_RP(pin) _IC8R = pin
#else
#define CONFIG_IC8_TO_RP(pin)
#endif

/// Maps OCFA to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFAR) || defined(__DOXYGEN__)
#define CONFIG_OCFA_TO_RP(pin) _OCFAR = pin
#else
#define CONFIG_OCFA_TO_RP(pin)
#endif

/// Maps OCFB to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFBR) || defined(__DOXYGEN__)
#define CONFIG_OCFB_TO_RP(pin) _OCFBR = pin
#else
#define CONFIG_OCFB_TO_RP(pin)
#endif

/// Maps U1RX to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1RXR) || defined(__DOXYGEN__)
#define CONFIG_U1RX_TO_RP(pin) _U1RXR = pin
#else
#define CONFIG_U1RX_TO_RP(pin)
#endif

/// Maps U1CTS to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1CTSR) || defined(__DOXYGEN__)
#define CONFIG_U1CTS_TO_RP(pin) _U1CTSR = pin
#else
#define CONFIG_U1CTS_TO_RP(pin)
#endif

/// Maps U2RX to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2RXR) || defined(__DOXYGEN__)
#define CONFIG_U2RX_TO_RP(pin) _U2RXR = pin
#else
#define CONFIG_U2RX_TO_RP(pin)
#endif

/// Maps U2CTS to a remappable pin; 
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2CTSR) || defined(__DOXYGEN__)
#define CONFIG_U2CTS_TO_RP(pin) _U2CTSR = pin
#else
#define CONFIG_U2CTS_TO_RP(pin)
#endif

#if defined(_SDI1R) || defined(__DOXYGEN__)
#define CONFIG_SDI1_TO_RP(pin) _SDI1R = pin
#else
#define CONFIG_SDI1_TO_RP(pin)
#endif

#if defined(_SCK1R) || defined(__DOXYGEN__)
#define CONFIG_SCK1IN_TO_RP(pin) _SCK1R = pin
#else
#define CONFIG_SCK1IN_TO_RP(pin)
#endif

#if defined(_SS1R) || defined(__DOXYGEN__)
#define CONFIG_SS1IN_TO_RP(pin) _SS1R = pin
#else
#define CONFIG_SS1IN_TO_RP(pin)
#endif

#if defined(_SDI2R) || defined(__DOXYGEN__)
#define CONFIG_SDI2_TO_RP(pin) _SDI2R = pin
#else
#define CONFIG_SDI2_TO_RP(pin)
#endif

#if defined(_SCK2R) || defined(__DOXYGEN__)
#define CONFIG_SCK2IN_TO_RP(pin) _SCK2R = pin
#else
#define CONFIG_SCK2IN_TO_RP(pin)
#endif

#if defined(_SS2R) || defined(__DOXYGEN__)
#define CONFIG_SS2IN_TO_RP(pin) _SS2R = pin
#else
#define CONFIG_SS2IN_TO_RP(pin)
#endif

#if defined(_C1RXR) || defined(__DOXYGEN__)
#define CONFIG_C1RXR_TO_RP(pin) _C1RXR = pin
#else
#define CONFIG_C1RXR_TO_RP(pin)
#endif

#if defined(_C2RXR) || defined(__DOXYGEN__)
#define CONFIG_C2RXR_TO_RP(pin) _C2RXR = pin
#else
#define CONFIG_C2RXR_TO_RP(pin)
#endif
//@}


/** \name Remappable peripheral output support
 *  <a name="remappableOutputs">These</a> functions maps an output
 *  internal to the PIC to an output pin.
 *  For example, CONFIG_C1OUT_TO_RP(10) maps the C1OUT comparator
 *  output to port P, pin 10.
 *
 *  Not all devices support remappable peripherals. In these cases,
 *  the macros below evalaute to nothing: CONFIG_C1OUT_TO_RP(10) is
 *  a valid C statement which does nothing.
 *
 *  CONFIG_NULL_TO_RP(n) will return RPn to an 'unmapped' state
 *  (i.e, the reset condition).
 */
//@{

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_NULL_TO_RP(pin) _RP##pin##R = 0
#else
#define CONFIG_NULL_TO_RP(pin)
#endif

/// Maps C1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_C1OUT_TO_RP(pin) _RP##pin##R = 1
#else
#define CONFIG_C1OUT_TO_RP(pin)
#endif

/// Maps C2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_C2OUT_TO_RP(pin) _RP##pin##R = 2
#else
#define CONFIG_C2OUT_TO_RP(pin)
#endif

/// Maps U1TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_U1TX_TO_RP(pin) _RP##pin##R = 3
#else
#define CONFIG_U1TX_TO_RP(pin)
#endif

/// Maps U1RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_U1RTS_TO_RP(pin) _RP##pin##R = 4
#else
#define CONFIG_U1RTS_TO_RP(pin)
#endif

/// Maps U2TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_U2TX_TO_RP(pin) _RP##pin##R = 5
#else
#define CONFIG_U2TX_TO_RP(pin)
#endif

/// Maps U2RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_U2RTS_TO_RP(pin) _RP##pin##R = 6
#else
#define CONFIG_U2RTS_TO_RP(pin)
#endif

/// Maps SDO1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SDO1_TO_RP(pin) _RP##pin##R = 7
#else
#define CONFIG_SDO1_TO_RP(pin)
#endif

/// Maps SCK1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SCK1OUT_TO_RP(pin) _RP##pin##R = 8
#else
#define CONFIG_SCK1OUT_TO_RP(pin)
#endif

/// Maps SS11OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SS1OUT_TO_RP(pin) _RP##pin##R = 9
#else
#define CONFIG_SS1OUT_TO_RP(pin)
#endif

/// Maps SDO2 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SDO2_TO_RP(pin) _RP##pin##R = 10
#else
#define CONFIG_SDO2_TO_RP(pin)
#endif

/// Maps SCK2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SCK2OUT_TO_RP(pin) _RP##pin##R = 11
#else
#define CONFIG_SCK2OUT_TO_RP(pin)
#endif

/// Maps SS2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a> 
/// for more information.
#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_SS2OUT_TO_RP(pin) _RP##pin##R = 12
#else
#define CONFIG_SS2OUT_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_C1TX_TO_RP(pin) _RP##pin##R = 16
#else
#define CONFIG_C1TX_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_OC1_TO_RP(pin) _RP##pin##R = 18
#else
#define CONFIG_OC1_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_OC2_TO_RP(pin) _RP##pin##R = 19
#else
#define CONFIG_OC2_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_OC3_TO_RP(pin) _RP##pin##R = 20
#else
#define CONFIG_OC3_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_OC4_TO_RP(pin) _RP##pin##R = 21
#else
#define CONFIG_OC4_TO_RP(pin)
#endif

#if defined(_RP0R) || defined(__DOXYGEN__)
#define CONFIG_OC5_TO_RP(pin) _RP##pin##R = 22
#else
#define CONFIG_OC5_TO_RP(pin)
#endif
//@}


// Include appropriate ports file for the device in use.
#if defined(__PIC24HJ128GP202__)

#include "devices/pic24hj128gp202_ports.h"

#elif defined(__PIC24HJ128GP204__)

#include "devices/pic24hj128gp204_ports.h"

#elif defined(__PIC24HJ128GP206__)

#include "devices/pic24hj128gp206_ports.h"

#elif defined(__PIC24HJ128GP210__)

#include "devices/pic24hj128gp210_ports.h"

#elif defined(__PIC24HJ128GP306__)

#include "devices/pic24hj128gp306_ports.h"

#elif defined(__PIC24HJ128GP310__)

#include "devices/pic24hj128gp310_ports.h"

#elif defined(__PIC24HJ128GP502__)

#include "devices/pic24hj128gp502_ports.h"

#elif defined(__PIC24HJ128GP504__)

#include "devices/pic24hj128gp504_ports.h"

#elif defined(__PIC24HJ128GP506__)

#include "devices/pic24hj128gp506_ports.h"

#elif defined(__PIC24HJ128GP510__)

#include "devices/pic24hj128gp510_ports.h"

#elif defined(__PIC24HJ12GP201__)

#include "devices/pic24hj12gp201_ports.h"

#elif defined(__PIC24HJ12GP202__)

#include "devices/pic24hj12gp202_ports.h"

#elif defined(__PIC24HJ16GP304__)

#include "devices/pic24hj16gp304_ports.h"

#elif defined(__PIC24HJ256GP206__)

#include "devices/pic24hj256gp206_ports.h"

#elif defined(__PIC24HJ256GP210__)

#include "devices/pic24hj256gp210_ports.h"

#elif defined(__PIC24HJ256GP610__)

#include "devices/pic24hj256gp610_ports.h"

#elif defined(__PIC24HJ32GP202__)

#include "devices/pic24hj32gp202_ports.h"

#elif defined(__PIC24HJ32GP204__)

#include "devices/pic24hj32gp204_ports.h"

#elif defined(__PIC24HJ32GP302__)

#include "devices/pic24hj32gp302_ports.h"

#elif defined(__PIC24HJ32GP304__)

#include "devices/pic24hj32gp304_ports.h"

#elif defined(__PIC24HJ64GP202__)

#include "devices/pic24hj64gp202_ports.h"

#elif defined(__PIC24HJ64GP204__)

#include "devices/pic24hj64gp204_ports.h"

#elif defined(__PIC24HJ64GP206__)

#include "devices/pic24hj64gp206_ports.h"

#elif defined(__PIC24HJ64GP210__)

#include "devices/pic24hj64gp210_ports.h"

#elif defined(__PIC24HJ64GP502__)

#include "devices/pic24hj64gp502_ports.h"

#elif defined(__PIC24HJ64GP504__)

#include "devices/pic24hj64gp504_ports.h"

#elif defined(__PIC24HJ64GP506__)

#include "devices/pic24hj64gp506_ports.h"

#elif defined(__PIC24HJ64GP510__)

#include "devices/pic24hj64gp510_ports.h"

#elif defined(__PIC24F04KA200__)

#include "devices/pic24f04ka200_ports.h"

#elif defined(__PIC24F04KA201__)

#include "devices/pic24f04ka201_ports.h"

#elif defined(__PIC24F08KA101__)

#include "devices/pic24f08ka101_ports.h"

#elif defined(__PIC24F08KA102__)

#include "devices/pic24f08ka102_ports.h"

#elif defined(__PIC24F16KA101__)

#include "devices/pic24f16ka101_ports.h"

#elif defined(__PIC24F16KA102__)

#include "devices/pic24f16ka102_ports.h"

#elif defined(__PIC24F32KA101__)

#include "devices/pic24f32ka101_ports.h"

#elif defined(__PIC24F32KA102__)

#include "devices/pic24f32ka102_ports.h"

#elif defined(__PIC24FJ128GA006__)

#include "devices/pic24fj128ga006_ports.h"

#elif defined(__PIC24FJ128GA008__)

#include "devices/pic24fj128ga008_ports.h"

#elif defined(__PIC24FJ128GA010__)

#include "devices/pic24fj128ga010_ports.h"

#elif defined(__PIC24FJ128GA106__)

#include "devices/pic24fj128ga106_ports.h"

#elif defined(__PIC24FJ128GA108__)

#include "devices/pic24fj128ga108_ports.h"

#elif defined(__PIC24FJ128GA110__)

#include "devices/pic24fj128ga110_ports.h"

#elif defined(__PIC24FJ128GB106__)

#include "devices/pic24fj128gb106_ports.h"

#elif defined(__PIC24FJ128GB108__)

#include "devices/pic24fj128gb108_ports.h"

#elif defined(__PIC24FJ128GB110__)

#include "devices/pic24fj128gb110_ports.h"

#elif defined(__PIC24FJ16GA002__)

#include "devices/pic24fj16ga002_ports.h"

#elif defined(__PIC24FJ16GA004__)

#include "devices/pic24fj16ga004_ports.h"

#elif defined(__PIC24FJ192GA106__)

#include "devices/pic24fj192ga106_ports.h"

#elif defined(__PIC24FJ192GA108__)

#include "devices/pic24fj192ga108_ports.h"

#elif defined(__PIC24FJ192GA110__)

#include "devices/pic24fj192ga110_ports.h"

#elif defined(__PIC24FJ32GB002__)

#include "devices/pic24fj32gb002_ports.h"

#elif defined(__PIC24FJ64GB002__)

#include "devices/pic24fj64gb002_ports.h"

#elif defined(__PIC24FJ32GB004__)

#include "devices/pic24fj32gb004_ports.h"

#elif defined(__PIC24FJ64GB004__)

#include "devices/pic24fj64gb004_ports.h"

#elif defined(__PIC24FJ192GB106__)

#include "devices/pic24fj192gb106_ports.h"

#elif defined(__PIC24FJ192GB108__)

#include "devices/pic24fj192gb108_ports.h"

#elif defined(__PIC24FJ192GB110__)

#include "devices/pic24fj192gb110_ports.h"

#elif defined(__PIC24FJ256GA106__)

#include "devices/pic24fj256ga106_ports.h"

#elif defined(__PIC24FJ256GA108__)

#include "devices/pic24fj256ga108_ports.h"

#elif defined(__PIC24FJ256GA110__)

#include "devices/pic24fj256ga110_ports.h"

#elif defined(__PIC24FJ256GB106__)

#include "devices/pic24fj256gb106_ports.h"

#elif defined(__PIC24FJ256GB108__)

#include "devices/pic24fj256gb108_ports.h"

#elif defined(__PIC24FJ256GB110__)

#include "devices/pic24fj256gb110_ports.h"


#elif defined(__PIC24FJ32GA102__)

#include "devices/pic24fj32ga102_ports.h"

#elif defined(__PIC24FJ32GA104__)

#include "devices/pic24fj32ga104_ports.h"

#elif defined(__PIC24FJ64GA102__)

#include "devices/pic24fj64ga102_ports.h"

#elif defined(__PIC24FJ64GA104__)

#include "devices/pic24fj64ga104_ports.h"

#elif defined(__PIC24FJ32GA002__)

#include "devices/pic24fj32ga002_ports.h"

#elif defined(__PIC24FJ32GA004__)

#include "devices/pic24fj32ga004_ports.h"

#elif defined(__PIC24FJ48GA002__)

#include "devices/pic24fj48ga002_ports.h"

#elif defined(__PIC24FJ48GA004__)

#include "devices/pic24fj48ga004_ports.h"

#elif defined(__PIC24FJ64GA002__)

#include "devices/pic24fj64ga002_ports.h"

#elif defined(__PIC24FJ64GA004__)

#include "devices/pic24fj64ga004_ports.h"

#elif defined(__PIC24FJ64GA006__)

#include "devices/pic24fj64ga006_ports.h"

#elif defined(__PIC24FJ64GA008__)

#include "devices/pic24fj64ga008_ports.h"

#elif defined(__PIC24FJ64GA010__)

#include "devices/pic24fj64ga010_ports.h"

#elif defined(__PIC24FJ64GA106__)

#include "devices/pic24fj64ga106_ports.h"

#elif defined(__PIC24FJ64GA108__)

#include "devices/pic24fj64ga108_ports.h"

#elif defined(__PIC24FJ64GA110__)

#include "devices/pic24fj64ga110_ports.h"

#elif defined(__PIC24FJ64GB106__)

#include "devices/pic24fj64gb106_ports.h"

#elif defined(__PIC24FJ64GB108__)

#include "devices/pic24fj64gb108_ports.h"

#elif defined(__PIC24FJ64GB110__)

#include "devices/pic24fj64gb110_ports.h"

#elif defined(__PIC24FJ96GA006__)

#include "devices/pic24fj96ga006_ports.h"

#elif defined(__PIC24FJ96GA008__)

#include "devices/pic24fj96ga008_ports.h"

#elif defined(__PIC24FJ96GA010__)

#include "devices/pic24fj96ga010_ports.h"

#elif defined(__dsPIC33FJ06GS101__)

#include "devices/dspic33fj06gs101_ports.h"

#elif defined(__dsPIC33FJ06GS102__)

#include "devices/dspic33fj06gs102_ports.h"

#elif defined(__dsPIC33FJ06GS202__)

#include "devices/dspic33fj06gs202_ports.h"

#elif defined(__dsPIC33FJ128GP202__)

#include "devices/dspic33fj128gp202_ports.h"

#elif defined(__dsPIC33FJ128GP204__)

#include "devices/dspic33fj128gp204_ports.h"

#elif defined(__dsPIC33FJ128GP206A__)

#include "devices/dspic33fj128gp206a_ports.h"

#elif defined(__dsPIC33FJ128GP206__)

#include "devices/dspic33fj128gp206_ports.h"

#elif defined(__dsPIC33FJ128GP306A__)

#include "devices/dspic33fj128gp306a_ports.h"

#elif defined(__dsPIC33FJ128GP306__)

#include "devices/dspic33fj128gp306_ports.h"

#elif defined(__dsPIC33FJ128GP310A__)

#include "devices/dspic33fj128gp310a_ports.h"

#elif defined(__dsPIC33FJ128GP310__)

#include "devices/dspic33fj128gp310_ports.h"

#elif defined(__dsPIC33FJ128GP706A__)

#include "devices/dspic33fj128gp706a_ports.h"

#elif defined(__dsPIC33FJ128GP706__)

#include "devices/dspic33fj128gp706_ports.h"

#elif defined(__dsPIC33FJ128GP708A__)

#include "devices/dspic33fj128gp708a_ports.h"

#elif defined(__dsPIC33FJ128GP708__)

#include "devices/dspic33fj128gp708_ports.h"

#elif defined(__dsPIC33FJ128GP710A__)

#include "devices/dspic33fj128gp710a_ports.h"

#elif defined(__dsPIC33FJ128GP710__)

#include "devices/dspic33fj128gp710_ports.h"

#elif defined(__dsPIC33FJ128GP802__)

#include "devices/dspic33fj128gp802_ports.h"

#elif defined(__dsPIC33FJ128GP804__)

#include "devices/dspic33fj128gp804_ports.h"

#elif defined(__dsPIC33FJ128MC202__)

#include "devices/dspic33fj128mc202_ports.h"

#elif defined(__dsPIC33FJ128MC204__)

#include "devices/dspic33fj128mc204_ports.h"

#elif defined(__dsPIC33FJ128MC506A__)

#include "devices/dspic33fj128mc506a_ports.h"

#elif defined(__dsPIC33FJ128MC506__)

#include "devices/dspic33fj128mc506_ports.h"

#elif defined(__dsPIC33FJ128MC510A__)

#include "devices/dspic33fj128mc510a_ports.h"

#elif defined(__dsPIC33FJ128MC510__)

#include "devices/dspic33fj128mc510_ports.h"

#elif defined(__dsPIC33FJ128MC706A__)

#include "devices/dspic33fj128mc706a_ports.h"

#elif defined(__dsPIC33FJ128MC706__)

#include "devices/dspic33fj128mc706_ports.h"

#elif defined(__dsPIC33FJ128MC708A__)

#include "devices/dspic33fj128mc708a_ports.h"

#elif defined(__dsPIC33FJ128MC708__)

#include "devices/dspic33fj128mc708_ports.h"

#elif defined(__dsPIC33FJ128MC710A__)

#include "devices/dspic33fj128mc710a_ports.h"

#elif defined(__dsPIC33FJ128MC710__)

#include "devices/dspic33fj128mc710_ports.h"

#elif defined(__dsPIC33FJ128MC802__)

#include "devices/dspic33fj128mc802_ports.h"

#elif defined(__dsPIC33FJ128MC804__)

#include "devices/dspic33fj128mc804_ports.h"

#elif defined(__dsPIC33FJ12GP201__)

#include "devices/dspic33fj12gp201_ports.h"

#elif defined(__dsPIC33FJ12GP202__)

#include "devices/dspic33fj12gp202_ports.h"

#elif defined(__dsPIC33FJ12MC201__)

#include "devices/dspic33fj12mc201_ports.h"

#elif defined(__dsPIC33FJ12MC202__)

#include "devices/dspic33fj12mc202_ports.h"

#elif defined(__dsPIC33FJ16GP304__)

#include "devices/dspic33fj16gp304_ports.h"

#elif defined(__dsPIC33FJ16GS402__)

#include "devices/dspic33fj16gs402_ports.h"

#elif defined(__dsPIC33FJ16GS404__)

#include "devices/dspic33fj16gs404_ports.h"

#elif defined(__dsPIC33FJ16GS502__)

#include "devices/dspic33fj16gs502_ports.h"

#elif defined(__dsPIC33FJ16GS504__)

#include "devices/dspic33fj16gs504_ports.h"

#elif defined(__dsPIC33FJ16MC304__)

#include "devices/dspic33fj16mc304_ports.h"

#elif defined(__dsPIC33FJ256GP506A__)

#include "devices/dspic33fj256gp506a_ports.h"

#elif defined(__dsPIC33FJ256GP506__)

#include "devices/dspic33fj256gp506_ports.h"

#elif defined(__dsPIC33FJ256GP510A__)

#include "devices/dspic33fj256gp510a_ports.h"

#elif defined(__dsPIC33FJ256GP510__)

#include "devices/dspic33fj256gp510_ports.h"

#elif defined(__dsPIC33FJ256GP710A__)

#include "devices/dspic33fj256gp710a_ports.h"

#elif defined(__dsPIC33FJ256GP710__)

#include "devices/dspic33fj256gp710_ports.h"

#elif defined(__dsPIC33FJ256MC510A__)

#include "devices/dspic33fj256mc510a_ports.h"

#elif defined(__dsPIC33FJ256MC510__)

#include "devices/dspic33fj256mc510_ports.h"

#elif defined(__dsPIC33FJ256MC710A__)

#include "devices/dspic33fj256mc710a_ports.h"

#elif defined(__dsPIC33FJ256MC710__)

#include "devices/dspic33fj256mc710_ports.h"

#elif defined(__dsPIC33FJ32GP202__)

#include "devices/dspic33fj32gp202_ports.h"

#elif defined(__dsPIC33FJ32GP204__)

#include "devices/dspic33fj32gp204_ports.h"

#elif defined(__dsPIC33FJ32GP302__)

#include "devices/dspic33fj32gp302_ports.h"

#elif defined(__dsPIC33FJ32GP304__)

#include "devices/dspic33fj32gp304_ports.h"

#elif defined(__dsPIC33FJ32GS406__)

#include "devices/dspic33fj32gs406_ports.h"

#elif defined(__dsPIC33FJ32GS606__)

#include "devices/dspic33fj32gs606_ports.h"

#elif defined(__dsPIC33FJ32GS608__)

#include "devices/dspic33fj32gs608_ports.h"

#elif defined(__dsPIC33FJ32GS610__)

#include "devices/dspic33fj32gs610_ports.h"

#elif defined(__dsPIC33FJ32MC202__)

#include "devices/dspic33fj32mc202_ports.h"

#elif defined(__dsPIC33FJ32MC204__)

#include "devices/dspic33fj32mc204_ports.h"

#elif defined(__dsPIC33FJ32MC302__)

#include "devices/dspic33fj32mc302_ports.h"

#elif defined(__dsPIC33FJ32MC304__)

#include "devices/dspic33fj32mc304_ports.h"

#elif defined(__dsPIC33FJ64GP202__)

#include "devices/dspic33fj64gp202_ports.h"

#elif defined(__dsPIC33FJ64GP204__)

#include "devices/dspic33fj64gp204_ports.h"

#elif defined(__dsPIC33FJ64GP206A__)

#include "devices/dspic33fj64gp206a_ports.h"

#elif defined(__dsPIC33FJ64GP206__)

#include "devices/dspic33fj64gp206_ports.h"

#elif defined(__dsPIC33FJ64GP306A__)

#include "devices/dspic33fj64gp306a_ports.h"

#elif defined(__dsPIC33FJ64GP306__)

#include "devices/dspic33fj64gp306_ports.h"

#elif defined(__dsPIC33FJ64GP310A__)

#include "devices/dspic33fj64gp310a_ports.h"

#elif defined(__dsPIC33FJ64GP310__)

#include "devices/dspic33fj64gp310_ports.h"

#elif defined(__dsPIC33FJ64GP706A__)

#include "devices/dspic33fj64gp706a_ports.h"

#elif defined(__dsPIC33FJ64GP706__)

#include "devices/dspic33fj64gp706_ports.h"

#elif defined(__dsPIC33FJ64GP708A__)

#include "devices/dspic33fj64gp708a_ports.h"

#elif defined(__dsPIC33FJ64GP708__)

#include "devices/dspic33fj64gp708_ports.h"

#elif defined(__dsPIC33FJ64GP710A__)

#include "devices/dspic33fj64gp710a_ports.h"

#elif defined(__dsPIC33FJ64GP710__)

#include "devices/dspic33fj64gp710_ports.h"

#elif defined(__dsPIC33FJ64GP802__)

#include "devices/dspic33fj64gp802_ports.h"

#elif defined(__dsPIC33FJ64GP804__)

#include "devices/dspic33fj64gp804_ports.h"

#elif defined(__dsPIC33FJ64GS406__)

#include "devices/dspic33fj64gs406_ports.h"

#elif defined(__dsPIC33FJ64GS606__)

#include "devices/dspic33fj64gs606_ports.h"

#elif defined(__dsPIC33FJ64GS608__)

#include "devices/dspic33fj64gs608_ports.h"

#elif defined(__dsPIC33FJ64GS610__)

#include "devices/dspic33fj64gs610_ports.h"

#elif defined(__dsPIC33FJ64MC202__)

#include "devices/dspic33fj64mc202_ports.h"

#elif defined(__dsPIC33FJ64MC204__)

#include "devices/dspic33fj64mc204_ports.h"

#elif defined(__dsPIC33FJ64MC506A__)

#include "devices/dspic33fj64mc506a_ports.h"

#elif defined(__dsPIC33FJ64MC506__)

#include "devices/dspic33fj64mc506_ports.h"

#elif defined(__dsPIC33FJ64MC508A__)

#include "devices/dspic33fj64mc508a_ports.h"

#elif defined(__dsPIC33FJ64MC508__)

#include "devices/dspic33fj64mc508_ports.h"

#elif defined(__dsPIC33FJ64MC510A__)

#include "devices/dspic33fj64mc510a_ports.h"

#elif defined(__dsPIC33FJ64MC510__)

#include "devices/dspic33fj64mc510_ports.h"

#elif defined(__dsPIC33FJ64MC706A__)

#include "devices/dspic33fj64mc706a_ports.h"

#elif defined(__dsPIC33FJ64MC706__)

#include "devices/dspic33fj64mc706_ports.h"

#elif defined(__dsPIC33FJ64MC710A__)

#include "devices/dspic33fj64mc710a_ports.h"

#elif defined(__dsPIC33FJ64MC710__)

#include "devices/dspic33fj64mc710_ports.h"

#elif defined(__dsPIC33FJ64MC802__)

#include "devices/dspic33fj64mc802_ports.h"

#elif defined(__dsPIC33FJ64MC804__)

#include "devices/dspic33fj64mc804_ports.h"

#else

#error -- processor ID not specified in pic24_ports.h

#endif


#ifndef _PIC24_DIGIO_DEFINED
#warning Digital IO macros not defined for this device!
#warning Edit common\pic24_ports.h file!
#endif

#endif
