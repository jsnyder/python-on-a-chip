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


#ifndef _PIC24_PYPORTS_H_
#define _PIC24_PYPORTS_H_
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  \brief This file supports configuration of IO ports on the PIC24.
 *
 *  \section pinConfiguration Pin configuration
 *  The PIC24 and dsPIC33 processors support a rich and varied I/O
 *  ability. To use I/O, each pin
 *  must first be configured. The high-level functions 
 *  \ref configDigitalPin, \ref configAnalogPin simplify this
 *  process. Low-level commands, detailed below, can also be used.
 *  After configuring the pin, perform I/O by reading the value on the pin
 *  (\ref readDigitalPin) or the value last written 
 *  (\ref readDigitalLatch), or by writing the pin
 *  (\ref setDigitalPin).
 *
 *  \subsection lowLevelPinConfiguration Low-level pin configuration
 *  Low-level I/O pin configuration requires making the following
 *  choices:
 *  - First, use \ref setPinIsInput to configure a pin as either
 *    an input or an output.
 *    - For inputs, use \ref setPinIsDigital to configure the
 *      pin as an analog or digital input.
 *    - For outputs, use \ref setPinIsDigital to configure the
 *      pin as a digital input. While digital output functions
 *      correctly when the pin is configured as both an analog
 *      input and a digitial output, doing so slows the rise and
 *      fall times of the output. This occurs because analog input
 *      use a capacitor to sample and hold the analog voltage, which
 *      loads the pin, slowing its edge rates.
 *    - In either case, note that the device reset state of a pin
 *      is with analog input capability enabled; when configuring
 *      a pin for digital I/O, this must be changed for the pin to
 *      operate correctly.
 *  - Second, use \ref setPinPullDirection to
 *    select either a weak pull-up, a weak pull-down, or no pull.
 *    Note that only the PIC24F family supports pull-downs (see the
 *    24F FRM section 12.6). In addition, the availablity of pull-ups
 *    and pull-downs varies based on the chip and pin; only pins with
 *    change notification capability support pull-ups or pull-downs.
 *    Pins with this ability are labeled CNx on the pinout for the chip.
 *    - For analog inputs, the manual does not specify the
 *      required pull; however, they should be configured with no
 *      pull.
 *    - For digital outputs, the manual states that no pull should be
 *      enabled (see e.g. the PIC24HJ32GP202 manual, section 10.3,
 *      grey box beginning with "Note:"). However, if the pin is
 *      configured as an open-drain output (see next item), this
 *      is expected and should be supported.
 *  - Third, for digital outputs only, select open-drain or standard
 *    operation using \ref setPinIsOpenDrain. Recall that open-drain 
 *    (also known as open-collector) operation
 *    configures the digital output to only drive the pin low but allow
 *    it to float when high; therefore, a pull-up must be connected either
 *    externally or internally. In contrast, standard drivers (also known
 *    as push/pull or totem-pole drivers) active drive the pin either
 *    high or low.
 *  - Finally, any remappable peripherals which take control of the
 *    I/O pin must be unmapped to make use of the pin. The
 *    \ref unmapPin function does this; it can still be called for
 *    chips which do not have remappable I/O. In this case, the
 *    function does nothing.
 */

#include "pm.h"

/** @name Initialization, read/write, and high-level pin configuration functions
 *  These functions set up the I/O system, read and write to a pin, and
 *  allow configuring an I/O pin using a single function call.
 */
//@{

/** Configures a pin for digital operation. Implementation:
 *  -# Check to see if the port/pin exists.
 *  -# If the pin has analog capability, turn it off.
 *  -# Select the pin to be either an input or an output.
 *  -# Check and configure open-drain for the pin.
 *  -# Check and configure pull-ups/pull-downs for the pin.
 *  -# Remove any peripheral outputs mapped to
 *     this pin if it's a remappable pin.
 * 
 *  @param u16_port The port, consisting of one of \ref PORT_A_INDEX,
 *                  \ref PORT_B_INDEX, etc.
 *  @param u16_pin  The pin of the port to configure. Must be
 *                  a number between 0 and 15.
 *  @param b_isInput True to configure the pin as an input,
 *                   false to configure the pin as an output.
 *  @param b_isOpenDrain True to configure the pin's output
 *                   drivers to be 
 *                   <a href="http://en.wikipedia.org/wiki/Open_collector">open drain</a>,
 *                   false to configure the pin's output drivers
 *                   as a standrard
 *                   <a href="http://en.wikipedia.org/wiki/Totem_pole_output">push-pull</a>
 *                   output. <em>IMPORTANT</em>: Not all pins
 *                   have open-drain ability; therefore, the only
 *                   valid selection for this parameter may be false.
 *                   All pins have standard, push-pull drivers.
 *  @param i16_pullDir A value > 0 to enable a 
 *              <a href="http://en.wikipedia.org/wiki/Pull-up_resistor">pull-up resistor</a>
 *              on the pin, a value < 0 to enable a pull-down
 *              resistor on the pin, or 0 to disable both.
 *              <em>IMPORTANT</em>: Not all pins have pull-up
 *              or pull-down capability. Valid values for
 *              some pins are 0 (neither pull-up nor pull-down
 *              resistors are available), or >=0 (only
 *              pull-up resistors are available).
 */
PmReturn_t configDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t b_isInput,
    bool_t b_isOpenDrain, int16_t i16_pullDir);

/** Configure a pin for analog operation.
 *  @param u16_analogPin Pin x (named ANxx on the data sheet) to 
 *     configure as an analog pin
 */
PmReturn_t
configAnalogPin(uint16_t u16_analogPin);

/** Write to an I/O pin. If the pin is configured as an input, the value
 *  will be stored but only appear on the pin when it is changed to an output.
 *  @param u16_port The port, consisting of one of \ref PORT_A_INDEX,
 *                  \ref PORT_B_INDEX, etc.
 *  @param u16_pin  The pin of the port to configure. Must be
 *                  a number between 0 and 15.
 *  @param b_isHigh True to set the pin high, false to set it low.
 */
PmReturn_t
setDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t b_isHigh);


/** Read the digital value sensed on an I/O pin. The pin should be
 *  configured as a digital input. If it's a digital output, then
 *  then this function simple read what's being written.
 *  @param u16_port  The port, consisting of one of \ref PORT_A_INDEX,
 *                   \ref PORT_B_INDEX, etc.
 *  @param u16_pin   The pin of the port to configure. Must be
 *                   a number between 0 and 15.
 *  @param pb_isHigh True if the pin is high, false if low.
 */
PmReturn_t
readDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isHigh);


/** Read the last value written to an I/O pin. Therefore, this returns
 *  not the current value on the pin, but the last value written to
 *  the pin.
 *  @param u16_port  The port, consisting of one of \ref PORT_A_INDEX,
 *                   \ref PORT_B_INDEX, etc.
 *  @param u16_pin   The pin of the port to configure. Must be
 *                   a number between 0 and 15.
 *  @param pb_isHigh True if the last write was high, false if low.
 */
PmReturn_t
readDigitalLatch(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isHigh);
//@}


/** @name low-level pin configuration functions
 *  These functions allow low-level configuration of I/O pins.
 *  See the \ref lowLevelPinConfiguration "low-level pin configuration"
 *  section for usage.
 */
//@{

/** Determine if the given digitial I/O pin exists.
 *  @param u16_port Port, where 0 = A, 1 = B, etc.
 *  @param u16_pin  Pin of the given port; from 0 to 15.
 *  @return Returns C_TRUE if the pin exists, C_FALSE otherwise.
 *          Nonexistant ports or pins simply return C_FALSE.
 */
bool_t digitalPinExists(uint16_t u16_port, uint16_t u16_pin);

/** Set an I/O pin to be either an input or an output. Setting this
 *  pin as an output implies that it is a digital output. In contrast,
 *  configuring this pint to be an input allows it to be used as either
 *  a digital input or an analog input.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 *  \param b_isInput True to select the pin as an input, false as an output.
 */
PmReturn_t setPinIsInput(uint16_t u16_port, uint16_t u16_pin, bool_t b_isInput);

/** Determine if an I/O pin is an input or an output.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 *  \param pb_isInput True if the pin is an input, false if it's an output.
 */
PmReturn_t
getPinIsInput(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isInput);

/** Configure an I/O pin as either a digital I/O or an 
 *  analog input. To use an an analog input, this pin
 *  must already be configured as an input using
 *  \ref setPinIsInput. For use as a digital pin (either as
 *  an input or an output), configure this pin in digital mode.
 *  See the \ref lowLevelPinConfiguration "low-level pin 
 *  configuration" section for more details.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 *  \param b_isDigital True to configure the pin as a digital input, 
 *           false to configure the pin as an analog input.
 */
PmReturn_t setPinIsDigital(uint16_t u16_port, uint16_t u16_pin, 
  bool_t b_isDigital);


/** Specify the direction (input or output) for an I/O pin.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 *  \param b_isOpenDrain True to select an open-drain driver for the
 *                       pin, false to select a standard push-pull (totem-pole) driver.
 */
PmReturn_t setPinIsOpenDrain(uint16_t u16_port, uint16_t u16_pin, bool_t b_isOpenDrain);

/** Specify the pull direction (up, down, or none) for an I/O pin.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 *  \param i16_dir  Pull direction: 0 = none, negative = pull down, 
 *                    positive = pull up.
 */
PmReturn_t setPinPullDirection(uint16_t u16_port, uint16_t u16_pin, 
  int16_t i16_dir);

/** For chip that support remappable peripherals, unmap any
 *  peripherals which take full control of pin from the given
 *  pin, freeing the pin for use with general-purpose I/O. if
 *  the chip in use does not support remappable I/O, this routine
 *  does nothing.
 *  \param u16_port I/O port (A = 0, B = 1, etc.)
 *  \param u16_pin  Pin on the I/O port (from 0 to 15)
 */
PmReturn_t unmapPin(uint16_t u16_port, uint16_t u16_pin);
//@}


/** Map ports to an index. */
enum { PORT_A_INDEX = 0, ///< Index of port A
       PORT_B_INDEX,     ///< Index of port B
       PORT_C_INDEX,     ///< Index of port C
       PORT_D_INDEX,     ///< Index of port D
       PORT_E_INDEX,     ///< Index of port E
       PORT_F_INDEX,     ///< Index of port F
       PORT_G_INDEX,     ///< Index of port G
};

/** @name Bit manipulation functions
 */
//@{

/** Look up a specific bit in a bitfield.
 *  @param u16_bitfield Bitfield to access.
 *  @param u16_bit Bit in bitfield to access. Must be from
 *               0 to 15.
 *  @return True if the bit is a 1, false otherwise.
 */
bool_t getBit(uint16_t u16_bitfield, uint16_t u16_bit);

/** Look up a specific bit in an extended (> 16 bit) bitfield.
 *  @param u_bitfield Bitfield to access.
 *  @param u16_bit Bit in bitfield to access
 *  @return True if the bit is a 1, false otherwise.
 */
#define GET_EXTENDED_BIT(u_bitfield, u16_bit) \
    getBit(*(((uint16_t*) &(u_bitfield)) + ((u16_bit) >> 4)), (u16_bit) & 0x000F)

/** Set a specific bit in a bitfield.
 *  @param pu16_bitfield Pointer to bitfield to modify.
 *  @param u16_bit Bit in bitfield to access. Must be from
 *               0 to 15.
 *  @param b_val True to set the bit, false to clear it.
 */
void setBit(volatile uint16_t* pu16_bitfield, uint16_t u16_bit, bool_t b_val);

/** Set a specific bit in an extended (> 16 bit) bitfield.
 *  @param p_bitfield Pointer to bitfield to modify.
 *  @param u16_bit Bit in bitfield to access.
 *  @param b_val True to set the bit, false to clear it.
 */
#define SET_EXTENDED_BIT(p_bitfield, u16_bit, b_val) \
    setBit(((uint16_t*) (p_bitfield)) + ((u16_bit) >> 4), (u16_bit) & 0x000F, b_val)
//@}


/** This macro tells how many digital I/O ports exist on the selected processor. */
#if   defined(_RG0)  || defined(_RG1)  || defined(_RG2)  || defined(_RG3)  || \
      defined(_RG4)  || defined(_RG5)  || defined(_RG6)  || defined(_RG7)  || \
      defined(_RG8)  || defined(_RG9)  || defined(_RG10) || defined(_RG11) || \
      defined(_RG12) || defined(_RG13) || defined(_RG14) || defined(_RG15)
  #define NUM_DIGITAL_PORTS 7
#elif defined(_RF0)  || defined(_RF1)  || defined(_RF2)  || defined(_RF3)  || \
      defined(_RF4)  || defined(_RF5)  || defined(_RF6)  || defined(_RF7)  || \
      defined(_RF8)  || defined(_RF9)  || defined(_RF10) || defined(_RF11) || \
      defined(_RF12) || defined(_RF13) || defined(_RF14) || defined(_RF15)
  #define NUM_DIGITAL_PORTS 6
#elif defined(_RE0)  || defined(_RE1)  || defined(_RE2)  || defined(_RE3)  || \
      defined(_RE4)  || defined(_RE5)  || defined(_RE6)  || defined(_RE7)  || \
      defined(_RE8)  || defined(_RE9)  || defined(_RE10) || defined(_RE11) || \
      defined(_RE12) || defined(_RE13) || defined(_RE14) || defined(_RE15)
  #define NUM_DIGITAL_PORTS 5
#elif defined(_RD0)  || defined(_RD1)  || defined(_RD2)  || defined(_RD3)  || \
      defined(_RD4)  || defined(_RD5)  || defined(_RD6)  || defined(_RD7)  || \
      defined(_RD8)  || defined(_RD9)  || defined(_RD10) || defined(_RD11) || \
      defined(_RD12) || defined(_RD13) || defined(_RD14) || defined(_RD15)
  #define NUM_DIGITAL_PORTS 4
#elif defined(_RC0)  || defined(_RC1)  || defined(_RC2)  || defined(_RC3)  || \
      defined(_RC4)  || defined(_RC5)  || defined(_RC6)  || defined(_RC7)  || \
      defined(_RC8)  || defined(_RC9)  || defined(_RC10) || defined(_RC11) || \
      defined(_RC12) || defined(_RC13) || defined(_RC14) || defined(_RC15)
  #define NUM_DIGITAL_PORTS 3
#elif defined(_RB0)  || defined(_RB1)  || defined(_RB2)  || defined(_RB3)  || \
      defined(_RB4)  || defined(_RB5)  || defined(_RB6)  || defined(_RB7)  || \
      defined(_RB8)  || defined(_RB9)  || defined(_RB10) || defined(_RB11) || \
      defined(_RB12) || defined(_RB13) || defined(_RB14) || defined(_RB15)
  #define NUM_DIGITAL_PORTS 2
#elif defined(_RA0)  || defined(_RA1)  || defined(_RA2)  || defined(_RA3)  || \
      defined(_RA4)  || defined(_RA5)  || defined(_RA6)  || defined(_RA7)  || \
      defined(_RA8)  || defined(_RA9)  || defined(_RA10) || defined(_RA11) || \
      defined(_RA12) || defined(_RA13) || defined(_RA14) || defined(_RA15) || \
      defined(__DOXYGEN__)
  #define NUM_DIGITAL_PORTS 1
#else
  #error No digital I/O ports were found on the current microprocessor.
  #error Something is very confused.
#endif

// Define HAS_PULL_DOWNS if this chip has pull-down ability.
#if defined(_CN0PDE)  || defined(_CN1PDE)  || \
    defined(_CN2PDE)  || defined(_CN3PDE)  || \
    defined(_CN4PDE)  || defined(_CN5PDE)  || \
    defined(_CN6PDE)  || defined(_CN7PDE)  || \
    defined(_CN8PDE)  || defined(_CN9PDE)  || \
    defined(_CN10PDE) || defined(_CN11PDE) || \
    defined(_CN12PDE) || defined(_CN13PDE) || \
    defined(_CN14PDE) || defined(_CN15PDE) || \
    defined(_CN15PDE) || defined(_CN17PDE) || \
    defined(_CN18PDE) || defined(_CN19PDE) || \
    defined(_CN20PDE) || defined(_CN21PDE) || \
    defined(_CN22PDE) || defined(_CN23PDE) || \
    defined(_CN24PDE) || defined(_CN25PDE) || \
    defined(_CN26PDE) || defined(_CN27PDE) || \
    defined(_CN28PDE) || defined(_CN29PDE) || \
    defined(_CN30PDE) || defined(_CN31PDE)
#define HAS_PULL_DOWNS
#endif

#if defined(__DOXYGEN__) || \
    defined(_RP0R)  || defined(_RP1R)  || defined(_RP2R)  || defined(_RP3R)  || \
    defined(_RP4R)  || defined(_RP5R)  || defined(_RP6R)  || defined(_RP7R)  || \
    defined(_RP8R)  || defined(_RP9R)  || defined(_RP10R) || defined(_RP11R) || \
    defined(_RP12R) || defined(_RP13R) || defined(_RP14R) || defined(_RP15R) || \
    defined(_RP16R) || defined(_RP17R) || defined(_RP18R) || defined(_RP19R) || \
    defined(_RP20R) || defined(_RP21R) || defined(_RP22R) || defined(_RP23R) || \
    defined(_RP24R) || defined(_RP25R) || defined(_RP26R) || defined(_RP27R) || \
    defined(_RP28R) || defined(_RP29R) || defined(_RP30R) // Note: RP31 cannot exist
/** When defined, indicates that this device has remappable pins. */
#define HAS_REMAPPABLE_PINS
#endif

/** For unit testing, make some of the static functions visible;
 *  otherwise, leave them static. This macro's definition provides
 *  this capability. */
#ifdef UNIT_TEST
#define __STATIC__
// Prototype static functions that are otherwise hidden from the
// user of the library and exposed here only for testing.
inline __STATIC__ bool_t digitalPinInBounds(uint16_t u16_port, uint16_t u16_pin);
__STATIC__ bool_t digitalOpenDrainPinExists(uint16_t u16_port, uint16_t u16_pin);
#else
#define __STATIC__ static
#endif



#endif  // #define _PIC24_PYPORTS_H_
