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
 * Integer Object Unit Tests
 *
 * Tests the Integer Object implementation.
 *
 * Log
 * ---
 *
 * 2007/03/10   First.
 */


#include "CuTest.h"
#include "pm.h"


/* BEGIN unit tests ported from Snarf */
/**
 * Tests int_new():
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 */
void
ut_int_new_000(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(42, &pint);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pint) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)pint)->val == 42);
}
/* END unit tests ported from Snarf */


/**
 * Tests int_dup():
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 *      comparison of the two yields a true result
 */
void
ut_int_dup_000(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t pdup;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(42, &pint);
    retval = int_dup(pint, &pdup);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pdup) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)pdup)->val == 42);
    
    /* Check that comparing the two objects yields true */
    CuAssertTrue(tc, obj_compare(pint, pdup) == C_SAME);
}


/**
 * Tests int_positive():
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 *      comparison of the two yields a true result
 */
void
ut_int_positive_000(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t ppos;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(42, &pint);
    retval = int_positive(pint, &ppos);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*ppos) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)ppos)->val == 42);
    
    /* Check that comparing the two objects yields true */
    CuAssertTrue(tc, obj_compare(pint, ppos) == C_SAME);
}


/**
 * Tests int_positive() when given value is negative:
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 *      comparison of the two yields a true result
 */
void
ut_int_positive_001(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t ppos;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(-42, &pint);
    retval = int_positive(pint, &ppos);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*ppos) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)ppos)->val == -42);
    
    /* Check that comparing the two objects yields true */
    CuAssertTrue(tc, obj_compare(pint, ppos) == C_SAME);
}


/**
 * Tests int_positive() when given value is zero:
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 *      comparison of the two yields a true result
 */
void
ut_int_positive_002(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t ppos;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(0, &pint);
    retval = int_positive(pint, &ppos);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*ppos) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)ppos)->val == 0);
    
    /* Check that comparing the two objects yields true */
    CuAssertTrue(tc, obj_compare(pint, ppos) == C_SAME);
}


/**
 * Tests int_negative():
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the negative of the original
 *      comparison of the two yields a false result
 */
void
ut_int_negative_000(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t pneg;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(42, &pint);
    retval = int_negative(pint, &pneg);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pneg) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)pneg)->val == -42);
    
    /* Check that comparing the two objects yields false */
    CuAssertTrue(tc, obj_compare(pint, pneg) == C_DIFFER);
}


/**
 * Tests int_negative() when given value is negative:
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the negative of the original
 *      comparison of the two yields a false result
 */
void
ut_int_negative_001(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t pneg;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(-42, &pint);
    retval = int_negative(pint, &pneg);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pneg) == OBJ_TYPE_INT);
    
    /* Check that the value is 42 */
    CuAssertTrue(tc, ((pPmInt_t)pneg)->val == 42);
    
    /* Check that comparing the two objects yields false */
    CuAssertTrue(tc, obj_compare(pint, pneg) == C_DIFFER);
}


/**
 * Tests int_negative() when given value is zero:
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the original
 *      comparison of the two yields a false result
 */
void
ut_int_negative_002(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t pneg;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(0, &pint);
    retval = int_negative(pint, &pneg);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pneg) == OBJ_TYPE_INT);
    
    /* Check that the value is 0 */
    CuAssertTrue(tc, ((pPmInt_t)pneg)->val == 0);
    
    /* Check that comparing the two objects yields true */
    CuAssertTrue(tc, obj_compare(pint, pneg) == C_SAME);
}


/**
 * Tests int_bitInvert()
 *      retval is OK
 *      object type is INT
 *      integer value is equal to the bitwise complement of the original
 *      comparison of the two yields a false result
 */
void
ut_int_bitInvert_000(CuTest *tc)
{
    PmReturn_t retval;
    pPmObj_t pint;
    pPmObj_t pinv;

    pm_init(MEMSPACE_RAM, C_NULL);
    retval = int_new(42, &pint);
    retval = int_bitInvert(pint, &pinv);
    
    /* Check the return value of the load function */
    CuAssertTrue(tc, retval == PM_RET_OK);
    
    /* Check that the type is INT */
    CuAssertTrue(tc, OBJ_GET_TYPE(*pinv) == OBJ_TYPE_INT);
    
    /* Check that the value is -43 */
    CuAssertTrue(tc, ((pPmInt_t)pinv)->val == -43);
    
    /* Check that comparing the two objects yields false */
    CuAssertTrue(tc, obj_compare(pint, pinv) == C_DIFFER);
}
/* BEGIN unit tests ported from Snarf */


/** Make a suite from all tests in this file */
CuSuite *getSuite_testIntObj(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_int_new_000);
    SUITE_ADD_TEST(suite, ut_int_dup_000);
    SUITE_ADD_TEST(suite, ut_int_positive_000);
    SUITE_ADD_TEST(suite, ut_int_positive_001);
    SUITE_ADD_TEST(suite, ut_int_positive_002);
    SUITE_ADD_TEST(suite, ut_int_negative_000);
    SUITE_ADD_TEST(suite, ut_int_negative_001);
    SUITE_ADD_TEST(suite, ut_int_negative_002);
    SUITE_ADD_TEST(suite, ut_int_bitInvert_000);

    return suite;
}
