/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


/**
 * String Object Unit Tests
 * Tests the String Object implementation.
 */


#include "CuTest.h"
#include "pm.h"


/**
 * Tests string_new():
 *      retval is OK
 *      length is proper
 */
void
ut_string_new_000(CuTest *tc)
{
    pPmObj_t pstring;
    uint16_t length;
    uint8_t cstring[] = "forty-two";
    uint8_t const *pcstring = cstring;
    PmReturn_t retval;

    pm_init(MEMSPACE_RAM, C_NULL);

    /* Check the return value is Ok */
    retval = string_new(&pcstring, &pstring);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmString_t)pstring)->length == 9);
}


/**
 * Tests string_newFromChar():
 *      retval is OK
 *      length is proper
 */
void
ut_string_newFromChar_000(CuTest *tc)
{
    pPmObj_t pstring;
    uint16_t length;
    uint8_t cchar = 'Z';
    PmReturn_t retval;

    pm_init(MEMSPACE_RAM, C_NULL);

    /* Check the return value is Ok */
    retval = string_newFromChar(cchar, &pstring);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmString_t)pstring)->length == 1);
}


/** Make a suite from all tests in this file */
CuSuite *getSuite_testStringObj(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_string_new_000);
    SUITE_ADD_TEST(suite, ut_string_newFromChar_000);

    return suite;
}
