/** \file
 *  \brief This file implements Python functions defined in main.py.
 * 
 */

#include "pm.h"


/** @name Read/write and high-level digital pin configuration functions
 *  These functions set up the I/O system, read and write to a pin, and
 *  allow configuring an I/O pin using a single function call. They wrap a
 *  series of C functions from pic24_pyports.h into the
 *  pic24_dspic33::digital_io Python class. 
 */
//@{
/** Implements the Python \ref pic24_dspic33::digital_io::__init__ function. 
 *  The \ref configDigitalPin function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
configDigitalPinPy(pPmFrame_t *ppframe);

/** Implements the Python \ref pic24_dspic33::digital_io::set function.
 *  The \ref setDigitalPin function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
setDigitalPinPy(pPmFrame_t *ppframe);

/** Implements the Python \ref pic24_dspic33::digital_io::get function.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
readDigitalValuePy(pPmFrame_t *ppframe);

/** Implements the Python \ref pic24_dspic33::digital_io::getPin function.
 *  The \ref readDigitalPin function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t readDigitalPinPy(pPmFrame_t *ppframe);

/** Implements the Python \ref pic24_dspic33::digital_io::getLatch function.
 *  The \ref readDigitalLatch function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t readDigitalLatchPy(pPmFrame_t *ppframe);
//@}

/** @name Analog pin configuration and ADC read routines.
 */
//@{
/** Implements the Python \ref pic24_dspic33::analog_input::__init__ function. 
 *  The \ref configAnalogPin function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
configAnalogPinPy(pPmFrame_t *ppframe);


/** Implements the Python \ref pic24_dspic33::analog_input::getCode function. 
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
readAnalogCodePy(pPmFrame_t *ppframe);

/** Implements the Python \ref pic24_dspic33::analog_input::getVoltage function.
 *  @param ppframe Python stack frame containing arguments to the function.
 *  @param f_scale Scale factor to multiply the code by before returning a value.
 */
PmReturn_t
readAnalogFloatPy(pPmFrame_t *ppframe, float f_scale);
//@}

/// @name PWM configuration and use
//@{

/** Implements the Python \ref pic24_dspic33::pwm::__init__ function.
 *  The \ref configPwm function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
configPwmPy(pPmFrame_t *ppframe);

/** Configure an output compare module for PWM operation.
 *  @param u32_freq Frequency at which the PWM will operate, in Hz.
 *  @param b_isTimer2 True to use timer2, false to use timer3 for
 *      PWM.
 *  @param u16_oc Output compare module to use.
 *  @param i16_ocPin For remappable devices, the port P pin on
 *      which to map the PWM output. For non-remappable devices,
 *      this value must be < 0.
 */
PmReturn_t
configPwm(uint32_t u32_freq, bool_t b_isTimer2, uint16_t u16_oc, 
  int16_t i16_ocPin);

/** Implements the Python \ref pic24_dspic33::pwm::setCounts function.
 *  The \ref setPwmCounts function does the work.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
setPwmCountsPy(pPmFrame_t *ppframe);

/** Set the duty cycle of the PWM peripheral.
 *  @param u16_counts A number of PR2/3 counts which gives the on
 *      time of the PWM wave to generate. Must be less than the
 *      PR2/3 value.
 *  @param u16_oc Output compare module to use.
 */
PmReturn_t
setPwmCounts(uint16_t u16_counts, uint16_t u16_oc);

/** Implements the Python \ref pic24_dspic33::pwm::set function.
 *  @param ppframe Python stack frame containing arguments to the function.
 */
PmReturn_t
setPwmRatioPy(pPmFrame_t *ppframe);

/** Determine the number of Output Compare modules available on
 *  this processor.
 */
#if   defined(_OC9IF)
#define NUM_OC_MODS 9
#elif defined(_OC8IF)
#define NUM_OC_MODS 8
#elif defined(_OC7IF)
#define NUM_OC_MODS 7
#elif defined(_OC6IF)
#define NUM_OC_MODS 6
#elif defined(_OC5IF)
#define NUM_OC_MODS 5
#elif defined(_OC4IF)
#define NUM_OC_MODS 4
#elif defined(_OC3IF)
#define NUM_OC_MODS 3
#elif defined(_OC2IF)
#define NUM_OC_MODS 2
#elif defined(_OC1IF)
#define NUM_OC_MODS 1
#else
#error No OC modules found!
#endif
//@}
