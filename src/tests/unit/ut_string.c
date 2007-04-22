/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2007 Dean Hall
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


/**
 * String Object Unit Tests
 *
 * Tests the String Object implementation.
 *
 * Log
 * ---
 *
 * 2007/03/12   First.
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
