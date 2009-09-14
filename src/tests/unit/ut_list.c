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
 * List Unit Tests
 * Tests the List implementation.
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
    CuAssertTrue(tc, OBJ_GET_TYPE(pobj) == OBJ_TYPE_LST);
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
 * Test list_removeItem():
 *      Remove from non-list object, expect a TypeError
 *      New list, append item0..4
 *          expect list length == 5
 *      Remove item0 (first),
 *          expect list length == 4,
 *          expect list[0] == item1,
 *          expect list[-1] == item4
 *      Remove item5,
 *          expect ValueError
 *      Remove item4 (last),
 *          expect list length == 3,
 *          expect list[-1] == item3,
 *      Remove item4
 *          expect ValueError
 *      Remove item2 (middle),
 *          expect list length == 2,
 *          expect list[0] == item1,
 *          expect list[1] == item3
 *      Remove item1, item3 (rest),
 *          expect list length == 0
 *      Append item5,
 *          expect list length == 1
 *          expect list[0] == item5
 */
void
ut_list_removeItem_000(CuTest *tc)
{
    pPmObj_t pobj = C_NULL;
    pPmObj_t pval;
    pPmObj_t pitem0, pitem1, pitem2, pitem3, pitem4, pitem5;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&pobj);

    retval = int_new(0, &pitem0);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = int_new(1, &pitem1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = int_new(2, &pitem2);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = int_new(3, &pitem3);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = int_new(4, &pitem4);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = int_new(5, &pitem5);
    CuAssertTrue(tc, retval == PM_RET_OK);

    retval = list_append(pobj, pitem0);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_append(pobj, pitem1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_append(pobj, pitem2);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_append(pobj, pitem3);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_append(pobj, pitem4);
    CuAssertTrue(tc, retval == PM_RET_OK);


    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 5);

    retval = list_remove(pobj, pitem0);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 4);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, pval == pitem1);
    retval = list_getItem(pobj, -1, &pval);
    CuAssertTrue(tc, pval == pitem4);

    retval = list_remove(pobj, pitem5);
    CuAssertTrue(tc, retval == PM_RET_EX_VAL);

    retval = list_remove(pobj, pitem4);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 3);
    retval = list_getItem(pobj, -1, &pval);
    CuAssertTrue(tc, pval == pitem3);

    retval = list_remove(pobj, pitem4);
    CuAssertTrue(tc, retval == PM_RET_EX_VAL);

    retval = list_remove(pobj, pitem2);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 2);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, pval == pitem1);
    retval = list_getItem(pobj, 1, &pval);
    CuAssertTrue(tc, pval == pitem3);

    retval = list_remove(pobj, pitem1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_remove(pobj, pitem3);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 0);

    retval = list_append(pobj, pitem5);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)pobj)->length == 1);
    retval = list_getItem(pobj, 0, &pval);
    CuAssertTrue(tc, pval == pitem5);

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
 * Test list_getItem():
 *      Append 3 items and check that each can be retrieved
 */
void
ut_list_getItem_001(CuTest *tc)
{
    pPmObj_t plist;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    pPmObj_t pget;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);

    retval = list_new(&plist);
    retval = dict_new(&pobj0);
    retval = tuple_new(0, &pobj1);
    retval = int_new(42, &pobj2);

    retval = list_append(plist, pobj0);
    retval = list_append(plist, pobj1);
    retval = list_append(plist, pobj2);

    retval = list_getItem(plist, 0, &pget);
    CuAssertTrue(tc, pget == pobj0);
    retval = list_getItem(plist, 1, &pget);
    CuAssertTrue(tc, pget == pobj1);
    retval = list_getItem(plist, 2, &pget);
    CuAssertTrue(tc, pget == pobj2);
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
    CuAssertTrue(tc, retval == PM_RET_OK);
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
 * Test list_setItem():
 *      Create list with 3 None objects in it
 *      Set each index to a new object
 *      Check that each object is at its proper index
 */
void
ut_list_setItem_001(CuTest *tc)
{
    pPmObj_t plist;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    pPmObj_t pget;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);

    retval = list_new(&plist);
    retval = dict_new(&pobj0);
    retval = tuple_new(0, &pobj1);
    retval = int_new(42, &pobj2);

    retval = list_append(plist, PM_NONE);
    retval = list_append(plist, PM_NONE);
    retval = list_append(plist, PM_NONE);

    retval = list_setItem(plist, 0, pobj0);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_setItem(plist, 1, pobj1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = list_setItem(plist, 2, pobj2);
    CuAssertTrue(tc, retval == PM_RET_OK);

    retval = list_getItem(plist, 0, &pget);
    CuAssertTrue(tc, pget == pobj0);
    retval = list_getItem(plist, 1, &pget);
    CuAssertTrue(tc, pget == pobj1);
    retval = list_getItem(plist, 2, &pget);
    CuAssertTrue(tc, pget == pobj2);
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
    CuAssertTrue(tc, OBJ_GET_TYPE(pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == 0);

    retval = list_append(pobj, PM_ONE);
    retval = list_copy(pobj, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, obj_compare(pval, pobj) == C_SAME);
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
    CuAssertTrue(tc, OBJ_GET_TYPE(pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == 0);

    retval = list_append(pobj, PM_ONE);
    retval = list_replicate(pobj, 1, &pval);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj != pval);
    CuAssertTrue(tc, OBJ_GET_TYPE(pval) == OBJ_TYPE_LST);
    CuAssertTrue(tc, ((pPmList_t)pval)->length == ((pPmList_t)pobj)->length);
}


/**
 * Test list_replicate():
 *      Replicate a list and see that it exists as expected
 */
void
ut_list_replicate_001(CuTest *tc)
{
    pPmObj_t plist;
    pPmObj_t preplicated;
    pPmObj_t pexpected;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);

    /* Build the original list */
    retval = list_new(&plist);
    retval = dict_new(&pobj0);
    retval = tuple_new(0, &pobj1);
    retval = int_new(42, &pobj2);

    retval = list_append(plist, pobj0);
    retval = list_append(plist, pobj1);
    retval = list_append(plist, pobj2);

    /* Build the expected list */
    retval = list_new(&pexpected);
    retval = list_append(pexpected, pobj0);
    retval = list_append(pexpected, pobj1);
    retval = list_append(pexpected, pobj2);
    retval = list_append(pexpected, pobj0);
    retval = list_append(pexpected, pobj1);
    retval = list_append(pexpected, pobj2);

    /* Create the replicated list */
    retval = list_replicate(plist, 2, &preplicated);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, obj_compare(preplicated, pexpected) == C_SAME);
}


/**
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
void
ut_list_insert_000(CuTest *tc)
{
    pPmObj_t plist;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pget;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&plist);
    retval = tuple_new(0, &pobj0);
    retval = dict_new(&pobj1);

    /* Call on non-list, expect a TypeError */
    retval = list_insert(pobj0, 0, pobj0);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);

    /* Call on empty list */
    retval = list_insert(plist, 0, pobj0);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)plist)->length == 1);
    retval = list_getItem(plist, 0, &pget);
    CuAssertTrue(tc, pobj0 == pget);

    /* Call on list of length 1 with index 0 */
    retval = list_insert(plist, 0, pobj1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)plist)->length == 2);
    retval = list_getItem(plist, 0, &pget);
    CuAssertTrue(tc, pobj1 == pget);

    /* Call on list of length 1 with index 1 */
    retval = list_new(&plist);
    retval = list_insert(plist, 0, pobj0);
    retval = list_insert(plist, 1, pobj1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)plist)->length == 2);
    retval = list_getItem(plist, 1, &pget);
    CuAssertTrue(tc, pobj1 == pget);

    /* Call on list of length 1 with index >1 */
    retval = list_new(&plist);
    retval = list_insert(plist, 0, pobj0);
    retval = list_insert(plist, 10, pobj1);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, ((pPmList_t)plist)->length == 2);
    retval = list_getItem(plist, 1, &pget);
    CuAssertTrue(tc, pobj1 == pget);
}


/**
 * Test list_index()
 *      Call on non-list, expect TypeError
 *      Call on empty list, expect retval is ValueError,
 *      Call on list of non-zero length
 *          expect retval is OK,
 *          expect index matches item's location
 */
void
ut_list_index_000(CuTest *tc)
{
    pPmObj_t plist;
    pPmObj_t pobj0;
    pPmObj_t pobj1;
    pPmObj_t pobj2;
    uint16_t index;
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_RAM, C_NULL);
    retval = list_new(&plist);
    retval = tuple_new(0, &pobj0);
    retval = dict_new(&pobj1);
    retval = int_new(42, &pobj2);

    /* Call on non-list, expect a TypeError */
    retval = list_index(pobj0, 0, &index);
    CuAssertTrue(tc, retval == PM_RET_EX_TYPE);
    
    /* Call on empty list, expect a ValueError */
    retval = list_index(plist, pobj1, &index);
    CuAssertTrue(tc, retval == PM_RET_EX_VAL);
    
    retval = list_append(plist, pobj0);
    retval = list_append(plist, pobj1);
    retval = list_append(plist, pobj2);
    
    /* Call on non-empty list, expect proper indices */
    retval = list_index(plist, pobj0, &index);
    CuAssertTrue(tc, index == 0);
    retval = list_index(plist, pobj1, &index);
    CuAssertTrue(tc, index == 1);
    retval = list_index(plist, pobj2, &index);
    CuAssertTrue(tc, index == 2);
}


/** Make a suite from all tests in this file */
CuSuite *getSuite_testList(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_list_new_000);
    SUITE_ADD_TEST(suite, ut_list_append_000);
    SUITE_ADD_TEST(suite, ut_list_getItem_000);
    SUITE_ADD_TEST(suite, ut_list_getItem_001);
    SUITE_ADD_TEST(suite, ut_list_setItem_000);
    SUITE_ADD_TEST(suite, ut_list_setItem_001);
    SUITE_ADD_TEST(suite, ut_list_copy_000);
    SUITE_ADD_TEST(suite, ut_list_replicate_000);
    SUITE_ADD_TEST(suite, ut_list_replicate_001);
    SUITE_ADD_TEST(suite, ut_list_removeItem_000);
    SUITE_ADD_TEST(suite, ut_list_insert_000);
    SUITE_ADD_TEST(suite, ut_list_index_000);

    return suite;
}
