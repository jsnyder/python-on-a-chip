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
 * Tuple Object Unit Tests
 * Tests the Tuple Object implementation.
 */


#include "CuTest.h"
#include "pm.h"


/**
 * Tests tuple_new():
 *      retval is OK
 *      length is proper
 */
void
ut_tuple_new_000(CuTest *tc)
{
    pPmObj_t ptuple;
    PmReturn_t retval;
    
    pm_init(MEMSPACE_RAM, C_NULL);
    
    /* Check the return value is Ok and length is 0 */
    retval = tuple_new(0, &ptuple);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmTuple_t)ptuple)->length == 0);
    
    /* Check the return value is Ok and length is 1 */
    retval = tuple_new(1, &ptuple);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmTuple_t)ptuple)->length == 1);
    
}


/**
 * Tests tuple_copy():
 *      retval is OK
 *      tuple and its copy are equals
 */
void
ut_tuple_copy_000(CuTest *tc)
{
    pPmObj_t ptuple;
    pPmObj_t ptuplecopy;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    PmReturn_t retval;
    
    pm_init(MEMSPACE_RAM, C_NULL);
    
    retval = tuple_new(3, &ptuple);
    retval = dict_new(&pobj0);
    retval = list_new(&pobj1);
    retval = int_new(42, &pobj2);
    ((pPmTuple_t)ptuple)->val[0] = pobj0;
    ((pPmTuple_t)ptuple)->val[1] = pobj1;
    ((pPmTuple_t)ptuple)->val[2] = pobj2;
    
    /* Check the return value is Ok */
    retval = tuple_copy(ptuple, &ptuplecopy);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, obj_compare(ptuple, ptuplecopy) == C_SAME);
}


/**
 * Tests tuple_getItem():
 *      retval is OK
 *      item at index is expected
 */
void
ut_tuple_getItem_000(CuTest *tc)
{
    pPmObj_t ptuple;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    pPmObj_t pget;
    PmReturn_t retval;
    
    pm_init(MEMSPACE_RAM, C_NULL);
    
    retval = tuple_new(3, &ptuple);
    retval = dict_new(&pobj0);
    retval = list_new(&pobj1);
    retval = int_new(42, &pobj2);
    ((pPmTuple_t)ptuple)->val[0] = pobj0;
    ((pPmTuple_t)ptuple)->val[1] = pobj1;
    ((pPmTuple_t)ptuple)->val[2] = pobj2;
    
    /* Check the return value is Ok */
    retval = tuple_getItem(ptuple, 0, &pget);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pget == pobj0);
    retval = tuple_getItem(ptuple, 1, &pget);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pget == pobj1);
    retval = tuple_getItem(ptuple, 2, &pget);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pget == pobj2);
}


/** Make a suite from all tests in this file */
CuSuite *getSuite_testTupleObj(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_tuple_new_000);
    SUITE_ADD_TEST(suite, ut_tuple_copy_000);
    SUITE_ADD_TEST(suite, ut_tuple_getItem_000);

    return suite;
}
