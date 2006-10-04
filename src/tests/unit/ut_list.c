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
 * List Unit Tests
 *
 * Tests the List implementation.
 *
 * Log
 * ---
 *
 * 2006/10/04   #48: Organize and deploy unit tests
 * 2003/01/12   First.
 */


#include "CuTest.h"
#include "pm.h"


/**
 * Test list_new():
 *      Pass valid vals,
 *          expect retval is OK,
 *          expect return list is not NULL,
 *          expect return type be of LIST type,
 *          expect return object is not const,
 *          expect list length be 0.
 */
void
ut_list_new_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pobj);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pobj) == OBJ_TYPE_LST);
    CuAssertTrue(tc, !OBJ_IS_CONST(*pobj));
    CuAssertTrue(tc, ((pPmDict_t)pobj)->length == 0);
}


/**
 * Test list_append():
 *      Append to non-list object, expect a TypeError
 *      New list, append 1 item,
 *          expect list length == 1,
 *          expect list[0] == item,
 *          expect list[-1] == item
 */
void
ut_list_append_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = list_append(PM_ONE, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = list_append(pobj, PM_ONE);
    CuAssertPtrNotNull(tc, pobj);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 1);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, pval == PM_ONE);
    retval = list_getItem(pobj, -1, &pval);
    CuAssertTrue(tc, pval == PM_ONE);
}


/**
 * Test list_getItem():
 *      Call on non-list object, expect a TypeError
 *      Call on empty list with index < 0, expect IndexError
 *      Call on empty list with index > 0, expect IndexError
 *      Call on empty list with index = 0, expect IndexError
 *      Call on non-empty list with index < -length, expect IndexError
 *      Call on non-empty list with index == length, expect IndexError
 *      Call on non-empty list with index > length, expect IndexError
 *      Call on non-empty list with index == 0,
 *          expect retval is OK,
 *          expect length = 1
 *          expect proper val
 */
void
ut_list_getItem_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = list_getItem(PM_ONE, 0, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = list_getItem(pobj, -1, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_getItem(pobj, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);

    retval = list_append(pobj, PM_ONE);
    retval = list_getItem(pobj, -2, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_getItem(pobj, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_getItem(pobj, 10, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 1);
    CuAssertTrue(tc, pval == PM_ONE);
}


/**
 * Test list_setItem():
 *      Call on non-list object, expect a TypeError
 *      Call on empty list with index < 0, expect IndexError
 *      Call on empty list with index > 0, expect IndexError
 *      Call on empty list with index = 0, expect IndexError
 *      Call on non-empty list with index < -length, expect IndexError
 *      Call on non-empty list with index == length, expect IndexError
 *      Call on non-empty list with index > length, expect IndexError
 *      Call on non-empty list with index == 0,
 *          expect retval is OK,
 *          expect length = 1
 *          expect proper val
 */
void
ut_list_setItem_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = list_setItem(PM_ONE, 0, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = list_setItem(pobj, -1, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_setItem(pobj, 1, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_setItem(pobj, 0, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);

    retval = list_append(pobj, PM_ONE);
    retval = list_setItem(pobj, -1, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_setItem(pobj, 1, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_setItem(pobj, 10, PM_ONE);
    CuAssertTrue(tc, retval == PM_RET_EX_INDX);
    retval = list_setItem(pobj, 0, PM_ZERO);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 1);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, pval == PM_ZERO);
}


/**
 * Test list_copy()
 *      Call on non-list, expect TypeError
 *      Call on empty list,
 *          expect retval is OK,
 *          expect obj is different (ptrs differ)
 *          expect return obj is a list
 *          expect return list length is 0
 *      Call on non-empty list,
 *          expect retval is OK,
 *          expect obj is different
 *          expect return obj is a list
 *          expect return length is same as original
 *          expect lists have identical contents
 */
void
ut_list_copy_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = list_copy(PM_ONE, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = list_copy(pobj, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == 0);

    retval = list_append(pobj, PM_ONE);
    retval = list_copy(pobj, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == ((pPmList_t)pobj)->length);
}


/**
 * Test list_replicate()
 *      Call on non-list, expect TypeError
 *      Call on empty list,
 *          expect retval is OK,
 *          expect obj is different (ptrs differ)
 *          expect return length is 0
 *      Call on non-empty list,
 *          expect retval is OK,
 *          expect obj is different
 *          expect return length is N x the original
 *          expect list has identical contents repeated
 */
void
ut_list_replicate_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = list_replicate(PM_ONE, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    retval = list_replicate(pobj, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == 0);

    retval = list_append(pobj, PM_ONE);
    retval = list_replicate(pobj, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(*pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == ((pPmList_t)pobj)->length);
}


/*
 * Todo when list_insert is implemented:
 *
 * Test list_insert()
 *      Call on non-list, expect TypeError
 *      Call on empty list,
 *          expect retval is OK,
 *          expect return length is 1
 *          expect obj[0] is same as given
 *      Call on list of length 1 with index 0,
 *          expect retval is OK,
 *          expect return length is 2
 *          expect obj[0] is same as given
 *      Call on list of length 1 with index 1
 *          expect retval is OK,
 *          expect return length is 2
 *          expect obj[1] is same as given
 *      Call on list of length 1 with index >1
 *          expect retval is OK,
 *          expect return length is 2
 *          expect obj[1] is same as given
 */


/** Make a suite from all tests in this file */
CuSuite *getSuite_testList(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_list_new_000);
    SUITE_ADD_TEST(suite, ut_list_append_000);
    SUITE_ADD_TEST(suite, ut_list_getItem_000);
    SUITE_ADD_TEST(suite, ut_list_copy_000);
    SUITE_ADD_TEST(suite, ut_list_replicate_000);

/* Uncomment below when list_setItem() is implemented */
/*  SUITE_ADD_TEST(suite, ut_list_setItem_000);*/

    return suite;
}
