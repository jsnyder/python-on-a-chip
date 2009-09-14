/*
# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
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
