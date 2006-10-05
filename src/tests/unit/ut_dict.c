/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2002 Dean Hall
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
 * Dict Unit Tests
 *
 * Tests the Dict implementation.
 *
 * Log
 * ---
 *
 * 2006/10/03   #48: Organize and deploy unit tests
 * 2003/01/11   First.
 */


#include "CuTest.h"
#include "pm.h"


/**
 * Test dict_new():
 *      retval is OK
 *      obj pointer is not C_NULL
 *      obj type must be DICT
 *      obj const bit must be clear
 *      dict length must be 0
 */
void
ut_dict_new_000(CuTest* tc)
{
    pPmObj_t pobj = C_NULL;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = dict_new(&pobj);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pobj);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pobj) == OBJ_TYPE_DIC);
    CuAssertTrue(tc, !OBJ_IS_CONST(*pobj));
    CuAssertTrue(tc, ((pPmDict_t)pobj)->length == 0);
}


/**
 * Test dict_setItem():
 *      Pass valid vals; expect retval is OK
 *      Pass valid vals, return dict must not be NULL
 *      Pass valid vals, return dict must be same addr
 */
void
ut_dict_setItem_000(CuTest* tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pobj_orig;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = dict_new(&pobj);
    pobj_orig = pobj;

    retval = dict_setItem(pobj, PM_ZERO, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pobj);
    CuAssertPtrEquals(tc, pobj_orig, pobj);
}

/**
 * Test dict_setItem():
 *      Pass valid vals, set(k,v); dict length must be 1
 *      Pass valid vals, set(k,v); item at k must be same v
 *      Pass valid vals, set(k,v1); set(k,v2), item at k must be v2
 */
void
ut_dict_setItem_001(CuTest* tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = dict_new(&pobj);

    retval = dict_setItem(pobj, PM_ZERO, PM_ONE);
    CuAssertTrue(tc, ((pPmDict_t)pobj)->length == 1);
    retval = dict_getItem(pobj, PM_ZERO, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrEquals(tc, PM_ONE, pval);
    retval = dict_setItem(pobj, PM_ZERO, PM_NEGONE);
    retval = dict_getItem(pobj, PM_ZERO, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrEquals(tc, PM_NEGONE, pval);
}


/**
 * Test dict_clear():
 *      Pass non-dict object; expect TypeError
 *      Pass empty dict; expect retval is OK
 *      Pass empty dict; expect dict is not C_NULL
 *      Pass empty dict; expect length is 0
 *      Pass non-empty dict; expect length is 0
 */
void
ut_dict_clear_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = dict_new(&pobj);

    retval = dict_clear(PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = dict_clear(pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pobj);
    CuAssertTrue(tc, ((pPmDict_t)pobj)->length == 0);
    retval = dict_setItem(pobj, PM_ZERO, PM_ONE);
    retval = dict_clear(pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmDict_t)pobj)->length == 0);
}


/**
 * Test dict_getItem():
 *      Pass non-dict object; expect TypeError
 *      Pass non-hashable key; expect KeyError
 *      Pass empty dict, any key; expect KeyError
 *      Pass non-empty list, non-present key; expect KeyError
 *      Pass non-empty dict, present key; expect OK and value
 */
void
ut_dict_getItem_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = dict_new(&pobj);

    retval = dict_getItem(PM_ONE, PM_ONE, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = dict_new(&pobj);
    retval = dict_getItem(pobj, pobj, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_KEY);
    retval = dict_new(&pobj);
    retval = dict_getItem(pobj, PM_ONE, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_KEY);
    retval = dict_new(&pobj);
    retval = dict_setItem(pobj, PM_ONE, PM_ZERO);
    retval = dict_getItem(pobj, PM_NEGONE, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_KEY);
    retval = dict_new(&pobj);
    retval = dict_setItem(pobj, PM_ONE, PM_ZERO);
    retval = dict_getItem(pobj, PM_ONE, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pval == PM_ZERO);
}


/** Make a suite from all tests in this file */
CuSuite *getSuite_testDict(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, ut_dict_new_000);
	SUITE_ADD_TEST(suite, ut_dict_setItem_000);
	SUITE_ADD_TEST(suite, ut_dict_setItem_001);
	SUITE_ADD_TEST(suite, ut_dict_clear_000);
	SUITE_ADD_TEST(suite, ut_dict_getItem_000);

    return suite;
}
