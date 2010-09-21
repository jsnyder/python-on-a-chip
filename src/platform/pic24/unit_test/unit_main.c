/*
# This file is Copyright 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
# 
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.
*/

/** @file
 *  @brief Run a series of PIC-specific unit tests.
 *
 *  Note that these test routines rely on local versions of CuTest.c and
 *  CuTest.h. This is because some of the defines in CuTest.h have been
 *  modified to accomodate a limited RAM space (e.g. original max string
 *  size was 8K, etc.).
 */


#ifndef __PIC24HJ128GP504__
#error These unit tests are desgined to work only on the PIC24HJ128GP504.
#endif

#include "pm.h"
#include "pic24_all.h"
#include "CuTestSmall.h"
#include "pyFuncsInC.h"
#include <pps.h>


/* Need to declare this array since no PyMite application is linked */
pPmNativeFxn_t const usr_nat_fxn_table[];

/** A series of tests on the existance of digital IO pins.
  * @param tc Test object.
  */
void test_gpioExists(CuTest* tc)
{
    // The PIC24HJxxGP504 is a 44 pin chip with 3 IO ports
    CuAssertTrue(tc, NUM_DIGITAL_PORTS == 3);

    // It has remappable pins
#ifndef HAS_REMAPPABLE_PINS
    CuAssertTrue(tc, 0);
#endif

    // Spot check simple port / pin existance
    CuAssertTrue(tc, !digitalPinInBounds(PORT_A_INDEX, 16));
    CuAssertTrue(tc, !digitalPinInBounds(PORT_D_INDEX, 0));
    CuAssertTrue(tc,  digitalPinInBounds(PORT_C_INDEX, 15));

    // Check specific port / pin combos:
    // Port A
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 0));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 1));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 2));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 3));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 4));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 5));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 6));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 7));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 8));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 9));
    CuAssertTrue(tc,  digitalPinExists(PORT_A_INDEX, 10));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 11));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 12));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 13));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 14));
    CuAssertTrue(tc, !digitalPinExists(PORT_A_INDEX, 15));
    // Port B
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 0));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 1));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 2));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 3));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 4));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 5));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 6));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 7));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 8));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 9));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 10));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 11));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 12));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 13));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 14));
    CuAssertTrue(tc,  digitalPinExists(PORT_B_INDEX, 15));
    // Port C
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 0));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 1));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 2));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 3));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 4));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 5));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 6));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 7));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 8));
    CuAssertTrue(tc,  digitalPinExists(PORT_C_INDEX, 9));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 10));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 11));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 12));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 13));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 14));
    CuAssertTrue(tc, !digitalPinExists(PORT_C_INDEX, 15));
}

/** A series of tests on the existance of digital IO pins.
  * Note: Microchip header files define _ODCA0-4, but the data sheet
  * claims these don't exist. So, the test below fail. For now,
  * ignore this. The same is true of pins on ports B and C.
  *
  * It looks like the header files defined the ODC bits if the
  * corresponding LATx/Rx bits exist, which is incorrect.
  *
  * Therefore, these tell will always fail. Aargh.
  *
  * @param tc Test object.
  */
void test_gpioOdExists(CuTest* tc)
{
    // Test open-drain config
    // Port A
#if 0   // Test everything we can be commenting these out for now
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 0));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 1));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 2));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 3));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 4));
#endif
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 5));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 6));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_A_INDEX, 7));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_A_INDEX, 8));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_A_INDEX, 9));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_A_INDEX, 10));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 11));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 12));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 13));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 14));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 15));
    // Port B
#if 0
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 0));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 1));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 2));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 3));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 4));
#endif
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 5));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 6));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 7));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 8));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 9));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 10));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_B_INDEX, 11));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 12));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 13));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 14));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_B_INDEX, 15));
    // Port C
#if 0
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 0));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 1));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 2));
#endif
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 3));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 4));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 5));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 6));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 7));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 8));
    CuAssertTrue(tc,  digitalOpenDrainPinExists(PORT_C_INDEX, 9));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 10));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 11));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 12));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 13));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 14));
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_C_INDEX, 15));
    
    // For future testing, include one failure; fixing this should
    // allow including all the unincluded code above.
    CuAssertTrue(tc, !digitalOpenDrainPinExists(PORT_A_INDEX, 0));
}

/** A series of tests of setPinIsInput.
  * @param tc Test object.
  */
void test_gpioSetPinIsInput(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, setPinIsInput(PORT_A_INDEX, 5, C_TRUE) == PM_RET_EX_VAL);

    // Check than configuring a specific pin as an input does indeed change
    // the pin's TRIS value.
    _TRISA0 = 0;
    CuAssertTrue(tc, setPinIsInput(PORT_A_INDEX, 0, C_TRUE) == PM_RET_OK);
    CuAssertTrue(tc, _TRISA0 == 1);
    _TRISA0 = 1;
    CuAssertTrue(tc, setPinIsInput(PORT_A_INDEX, 0, C_FALSE) == PM_RET_OK);
    CuAssertTrue(tc, _TRISA0 == 0);
}

/** A series of tests of getPinIsInput.
  * @param tc Test object.
  */
void test_gpioGetPinIsInput(CuTest* tc)
{
    bool_t b_isInput;

    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, getPinIsInput(PORT_A_INDEX, 5, &b_isInput) == PM_RET_EX_VAL);

    // Check than configuring a specific pin as an input does indeed change
    // the pin's TRIS value.
    _TRISA0 = 0;
    b_isInput = C_TRUE;
    CuAssertTrue(tc, getPinIsInput(PORT_A_INDEX, 0, &b_isInput) == PM_RET_OK);
    CuAssertTrue(tc, !b_isInput);
    _TRISA0 = 1;
    b_isInput = C_FALSE;
    CuAssertTrue(tc, getPinIsInput(PORT_A_INDEX, 0, &b_isInput) == PM_RET_OK);
    CuAssertTrue(tc, b_isInput);
}

/** A series of tests of setPinIsDigital.
  * @param tc Test object.
  */
void test_gpioSetPinIsDigital(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, setPinIsDigital(PORT_A_INDEX, 5, C_TRUE) == PM_RET_EX_VAL);

    // Configuring a pin with no analog capability as digital should always
    // work (and do nothing)
    CuAssertTrue(tc, setPinIsDigital(PORT_A_INDEX, 2, C_TRUE) == PM_RET_OK);

    // Configuring a pin with no analog capability as analog should always
    // fail and report an exception
    CuAssertTrue(tc, setPinIsDigital(PORT_A_INDEX, 2, C_FALSE) == PM_RET_EX_VAL);

    // Test the PCFG bit when configuring a pin with analog capability
    _PCFG0 = 0;
    CuAssertTrue(tc, setPinIsDigital(PORT_A_INDEX, 0, C_TRUE) == PM_RET_OK);
    CuAssertTrue(tc, _PCFG0 == 1);
    _PCFG0 = 1;
    CuAssertTrue(tc, setPinIsDigital(PORT_A_INDEX, 0, C_FALSE) == PM_RET_OK);
    CuAssertTrue(tc, _PCFG0 == 0);
}

/** A series of tests of setPinIsOpenDrain.
  * @param tc Test object.
  */
void test_gpioSetPinIsOpenDrain(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, setPinIsOpenDrain(PORT_A_INDEX, 5, C_TRUE) == PM_RET_EX_VAL);

    // Configuring a pin with no open-drain capability as non-OD should always
    // work (and do nothing)
    CuAssertTrue(tc, setPinIsOpenDrain(PORT_A_INDEX, 0, C_FALSE) == PM_RET_OK);

    // Configuring a pin with no open-drain capability as OD should always
    // fail and report an exception
    CuAssertTrue(tc, setPinIsOpenDrain(PORT_A_INDEX, 0, C_TRUE) == PM_RET_EX_VAL);

    // Test the PCFG bit when configuring a pin with analog capability
    _ODCA7 = 0;
    CuAssertTrue(tc, setPinIsOpenDrain(PORT_A_INDEX, 7, C_TRUE) == PM_RET_OK);
    CuAssertTrue(tc, _ODCA7 == 1);
    _ODCA7 = 1;
    CuAssertTrue(tc, setPinIsOpenDrain(PORT_A_INDEX, 7, C_FALSE) == PM_RET_OK);
    CuAssertTrue(tc, _ODCA7 == 0);
}

/** A series of tests of setPinPullDirection.
  * @param tc Test object.
  */
void test_gpioSetPinPullDirection(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 5, 0) == PM_RET_EX_VAL);

    // Configuring a pin with no pull-up capability as non-PU should always
    // work (and do nothing)
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 8, 0) == PM_RET_OK);

    // Configuring a pin with no pull-up capability as PU should always
    // fail and report an exception
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 8, 1) == PM_RET_EX_VAL);

    // Configuring a pin with no pull-down capability as PD should always
    // fail and report an exception
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 8, -1) == PM_RET_EX_VAL);
    // Same for a pin with pull-up but not pull-down
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 0, -1) == PM_RET_EX_VAL);

    // Test the PCFG bit when configuring a pin with analog capability
    _CN2PUE = 0;
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 0, 1) == PM_RET_OK);
    CuAssertTrue(tc, _CN2PUE == 1);
    _CN2PUE = 1;
    CuAssertTrue(tc, setPinPullDirection(PORT_A_INDEX, 0, 0) == PM_RET_OK);
    CuAssertTrue(tc, _CN2PUE == 0);
}

/** A series of tests of unmapPin.
  * @param tc Test object.
  */
void test_gpioUnmapPin(CuTest* tc)
{
    // This chip has remappable pins
#ifndef HAS_REMAPPABLE_PINS
    CuAssertTrue(tc, 0);
#endif
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, unmapPin(PORT_A_INDEX, 5) == PM_RET_EX_VAL);

    // Unmapping an unmappable pin should do nothing and return success
    CuAssertTrue(tc, unmapPin(PORT_A_INDEX, 0) == PM_RET_OK);

    // Map an input, then test the unmap
    _U1RXR = 0;
    CuAssertTrue(tc, unmapPin(PORT_B_INDEX, 0) == PM_RET_OK);
    CuAssertTrue(tc, _U1RXR == IN_PIN_PPS_VSS);

    // Map an output, then test the unmap
    _RP0R = 3;  // U1TX
    CuAssertTrue(tc, unmapPin(PORT_B_INDEX, 0) == PM_RET_OK);
    CuAssertTrue(tc, _RP0R == OUT_FN_PPS_NULL);
}

/** A series of tests of setDigitalPin.
  * @param tc Test object.
  */
void
test_gpioSetDigitalPin(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    CuAssertTrue(tc, setDigitalPin(PORT_A_INDEX, 5, C_TRUE) == PM_RET_EX_VAL);

    // Test setting a pin true and false
    _LATA0 = 0;
    CuAssertTrue(tc, setDigitalPin(PORT_A_INDEX, 0, C_TRUE) == PM_RET_OK);
    CuAssertTrue(tc, _LATA0 == 1);
    CuAssertTrue(tc, setDigitalPin(PORT_A_INDEX, 0, C_FALSE) == PM_RET_OK);
    CuAssertTrue(tc, _LATA0 == 0);
}

/** A series of tests of readDigitalPin.
  * @param tc Test object.
  */
void
test_gpioReadDigitalPin(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    bool_t b_pin;
    CuAssertTrue(tc, readDigitalPin(PORT_A_INDEX, 5, &b_pin) == PM_RET_EX_VAL);

    // Test setting a pin true and false
    // Make RA0 an output, then set its value and read that value back.
    configDigitalPin(PORT_A_INDEX, 0, C_FALSE, C_FALSE, 0);
    _LATA0 = 1;
    CuAssertTrue(tc, readDigitalPin(PORT_A_INDEX, 0, &b_pin) == PM_RET_OK);
    CuAssertTrue(tc, b_pin);
    _LATA0 = 0;
    CuAssertTrue(tc, readDigitalPin(PORT_A_INDEX, 0, &b_pin) == PM_RET_OK);
    CuAssertTrue(tc, !b_pin);
}

/** A series of tests of readDigitalPin.
  * @param tc Test object.
  */
void
test_gpioReadDigitalLatch(CuTest* tc)
{
    // An exception should be thrown in an invalid port / pin
    bool_t b_pin;
    CuAssertTrue(tc, readDigitalLatch(PORT_A_INDEX, 5, &b_pin) == PM_RET_EX_VAL);

    // Test setting a pin true and false
    _LATA0 = 1;
    CuAssertTrue(tc, readDigitalLatch(PORT_A_INDEX, 0, &b_pin) == PM_RET_OK);
    CuAssertTrue(tc, b_pin);
    _LATA0 = 0;
    CuAssertTrue(tc, readDigitalLatch(PORT_A_INDEX, 0, &b_pin) == PM_RET_OK);
    CuAssertTrue(tc, !b_pin);
}

/** A series of tests of configDigitalPin.
  * @param tc Test object.
  */
void
test_configDigitalPin(CuTest* tc)
{
    // Config a pin and check results
    CuAssertTrue(tc, configDigitalPin(PORT_B_INDEX, 1, C_FALSE, C_FALSE, 0) == PM_RET_OK);
    CuAssertTrue(tc, _PCFG3 == 1);
    CuAssertTrue(tc, _TRISB1 == 0);
    CuAssertTrue(tc, _ODCB1 == 0);
    CuAssertTrue(tc, _CN5PUE == 0);

    // Config with opposite params and check
    CuAssertTrue(tc, configDigitalPin(PORT_B_INDEX, 1, C_TRUE, C_TRUE, 1) == PM_RET_OK);
    CuAssertTrue(tc, _PCFG3 == 1);
    CuAssertTrue(tc, _TRISB1 == 1);
    CuAssertTrue(tc, _ODCB1 == 1);
    CuAssertTrue(tc, _CN5PUE == 1);

}
/** A series of tests of configAnalogPin.
  * @param tc Test object.
  */
void
test_configAnalogPin(CuTest* tc)
{
    // An exception should bethrown for an invalid analog pin
    CuAssertTrue(tc, configAnalogPin(13) == PM_RET_EX_VAL);

    // Config RA0 / AN0 as a digital output
    CuAssertTrue(tc, configDigitalPin(PORT_A_INDEX, 0, C_FALSE, C_FALSE, 1) == PM_RET_OK);
    // Now make it an analog input
    CuAssertTrue(tc, configAnalogPin(0) == PM_RET_OK);
    CuAssertTrue(tc, _PCFG0 == 0);
    CuAssertTrue(tc, _CN2PUE == 0);
    CuAssertTrue(tc, _TRISA0 == 1);
}

/** A series of tests of configPwm.
  * @param tc Test object.
  */
void
test_configPwm(CuTest* tc)
{
    // An exception should be thrown for an invalid OC pin
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     1,      -1) == PM_RET_EX_VAL);
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     1,      26) == PM_RET_EX_VAL);

    // An exception should be thrown for an invalid OC peripheral
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     -1,     0) == PM_RET_EX_VAL);
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     0,      0) == PM_RET_EX_VAL);
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     5,      0) == PM_RET_EX_VAL);

    // An exception should be thrown for an invalid frequency
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(0,        C_TRUE,     1,      0) == PM_RET_EX_VAL);
#if (FCY > 34000000L)
    // A min FCY given above gives a min frequnecy of 2 Hz, so we can test 1 Hz for failure.
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(FCY/256L/65536L - 1L, C_TRUE,     1,      0) == PM_RET_EX_VAL);
#endif
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(FCY + 1L, C_TRUE,     1,      0) == PM_RET_EX_VAL);    

    // Configure and check bits
    //                         u32_freq, b_isTimer2, u16_oc, i16_ocPin)
    CuAssertTrue(tc, configPwm(1000,     C_TRUE,     2,      0) == PM_RET_OK);
    CuAssertTrue(tc, OC2CON == (OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE));
#if (FCY == 1000000L)
    CuAssertTrue(tc, T2CON == (T2_ON | T2_IDLE_CON | T2_GATE_OFF
          | T2_32BIT_MODE_OFF | T2_SOURCE_INT | T2_PS_1_1));
    CuAssertTrue(tc, PR2 == 999);
#endif
    CuAssertTrue(tc, _RP0R == OUT_FN_PPS_OC2);
    CuAssertTrue(tc, OC2RS == 0);
    CuAssertTrue(tc, _TRISB0 == 0);
    CuAssertTrue(tc, _PCFG2 == 1);
    CuAssertTrue(tc, _CN4PUE == 0);
}

/** A series of tests of setPwm.
  * @param tc Test object.
  */
void
test_setPwm(CuTest* tc)
{
    //                            OCnRS OC
    CuAssertTrue(tc, setPwmCounts(600,  2) == PM_RET_OK);
    CuAssertTrue(tc, OC2RS == 600);
}

/** Run a series of tests on general-purpose I/O functions.
    @return A suite of tests.
 */
CuSuite*
getSuite_testGpio() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_gpioExists);
    SUITE_ADD_TEST(suite, test_gpioOdExists);
    SUITE_ADD_TEST(suite, test_gpioSetPinIsInput);
    SUITE_ADD_TEST(suite, test_gpioGetPinIsInput);
    SUITE_ADD_TEST(suite, test_gpioSetPinIsDigital);
    SUITE_ADD_TEST(suite, test_gpioSetPinIsOpenDrain);
    SUITE_ADD_TEST(suite, test_gpioSetPinPullDirection);
    SUITE_ADD_TEST(suite, test_gpioUnmapPin);
    SUITE_ADD_TEST(suite, test_gpioSetDigitalPin);
    SUITE_ADD_TEST(suite, test_gpioReadDigitalPin);
    SUITE_ADD_TEST(suite, test_gpioReadDigitalLatch);
    SUITE_ADD_TEST(suite, test_configDigitalPin);
    SUITE_ADD_TEST(suite, test_configAnalogPin);
    SUITE_ADD_TEST(suite, test_configPwm);
    SUITE_ADD_TEST(suite, test_setPwm);
    return suite;
}


int main(void)
{
    CuString* output = CuStringNew();
    CuSuite*  suite = CuSuiteNew();

    // Add all suites to be tested
    CuSuiteAddSuite(suite, getSuite_testGpio());

    // Run the tests and report the results
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    puts(output->buffer);

    /*
     * Zero failures indicates an all-good exit code.
     * Any errors gives a non-zero exit code that should stop the build
     * when this is called by the Makefile
     */
    return suite->failCount;
}
