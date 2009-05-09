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
 * Seglist Unit Tests
 * Tests the Seglist implementation.
 */


#include "CuTest.h"
#include "pm.h"


/**
 * Tests seglist_new():
 *      retval is OK
 *      seglist is non-null
 */
void
ut_seglist_new_000(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;

    retval = seglist_new(&pseglist);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pseglist);
}


/**
 * Tests seglist_appendItem()
 *      retval is OK
 *      length is incremented
 */
void
ut_seglist_appendItem_000(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;

    retval = seglist_new(&pseglist);
    retval = seglist_appendItem(pseglist, PM_ZERO);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 1);
}


/**
 * Tests seglist_appendItem() nine times
 *      retval is OK
 *      length is 9
 */
void
ut_seglist_appendItem_001(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    int8_t i;

    retval = seglist_new(&pseglist);
    for (i=8; i>0; i--)
    {
        seglist_appendItem(pseglist, PM_ZERO);
    }
    retval = seglist_appendItem(pseglist, PM_ONE);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 9);
}


/**
 * Tests seglist_insertItem()
 *      retval is OK
 *      length is incremented
 */
void
ut_seglist_insertItem_000(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;

    retval = seglist_new(&pseglist);
    retval = seglist_insertItem(pseglist, PM_ZERO, 0);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 1);
}


/**
 * Tests seglist_insertItem() nine times
 *      retval is OK
 *      length is 9
 */
void
ut_seglist_insertItem_001(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    int8_t i;

    retval = seglist_new(&pseglist);
    retval = seglist_insertItem(pseglist, PM_ONE, 0);
    for (i=8; i>0; i--)
    {
        seglist_insertItem(pseglist, PM_ZERO, 0);
    }

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 9);
}


/**
 * Tests seglist_insertItem with more than one segment:
 *      retval is OK
 *      first and last items are the given objs
 */
void
ut_seglist_insertItem_002(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    pPmObj_t pobj;
    int8_t i;

    seglist_new(&pseglist);
    seglist_insertItem(pseglist, PM_ONE, 0);
    for (i=8; i>0; i--)
    {
        seglist_insertItem(pseglist, PM_ZERO, 0);
    }
    retval = seglist_getItem(pseglist, 0, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == PM_ZERO);

    retval = seglist_getItem(pseglist, 8, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == PM_ONE);
}


/**
 * Tests seglist_getItem()
 *      retval is OK
 *      obj matches the given obj
 */
void
ut_seglist_getItem_000(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    pPmObj_t pobj;

    seglist_new(&pseglist);
    seglist_appendItem(pseglist, PM_ZERO);
    retval = seglist_getItem(pseglist, 0, &pobj);

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == PM_ZERO);
}


/**
 * Tests seglist_getItem() nine times
 *      retval is OK
 *      first and last items are the given objs
 */
void
ut_seglist_getItem_001(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    pPmObj_t pobj;
    int8_t i;

    retval = seglist_new(&pseglist);
    for (i=8; i>0; i--)
    {
        seglist_appendItem(pseglist, PM_ZERO);
    }
    seglist_appendItem(pseglist, PM_ONE);
    retval = seglist_getItem(pseglist, 0, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == PM_ZERO);

    retval = seglist_getItem(pseglist, 8, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == PM_ONE);
}

/**
 * Tests seglist_removeItem() (assumption is segment size of 8)
 *      retval is OK
 *      Append 10 items, item0..9
 *          expect length == 10
 *          expect seglist[0] == item0
 *          expect seglist[7] == item7
 *          expect seglist[8] == item8
 *          expect seglist[9] == item9
 *      Remove seglist[9]
 *          expect length == 9
 *          expect seglist[8] == item8
 *      Remove seglist[9] (disabled)
 *          expect retval == PM_RET_ASSERT_FAIL
 *      Append item10
 *          expect length == 10
 *          expect seglist[9] == item10
 *      Remove seglist[7..9]
 *          expect length == 7
 *      Append item10
 *          expect length == 8
 *          expect seglist[7] == item10
 *          expect seglist[6] == item6
 *      Append item2
 *          expect seglist[8] == item2
 *      Remove seglist[0] nine times
 *          expect length == 0 
 *      Append item2
 *          expect length == 1
 *          expect seglist[0] == item2
 */
void
ut_seglist_removeItem_000(CuTest *tc)
{
    PmReturn_t retval;
    pSeglist_t pseglist;
    pPmObj_t pobj;
    int8_t i;
    pPmObj_t item[11];

    retval = seglist_new(&pseglist);
    for (i=0; i<11; i++)
    {
        retval = int_new(i, &item[i]);
        CuAssertTrue(tc, retval == PM_RET_OK);
    }
    
    for (i=0; i<10; i++)
    {
        retval = seglist_appendItem(pseglist, (pPmObj_t)item[i]);
        CuAssertTrue(tc, retval == PM_RET_OK);
    }

    CuAssertTrue(tc, pseglist->sl_length == 10);
    
        
    for (i=0; i<10; i++)
    {
        retval = seglist_getItem(pseglist, i, &pobj);
        CuAssertTrue(tc, retval == PM_RET_OK);
        CuAssertTrue(tc, pobj == item[i]);
    }
    
    retval = seglist_removeItem(pseglist, 9);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 9);
    retval = seglist_getItem(pseglist, 8, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[8]);

    /* Testing seglist_removeItem(pseglist, 9) for a PM_RET_ASSERT_FAIL
     * return code is only valid if the VM is compiled with DEBUG. This can
     * not be determined here, so the test is deactivated as it will wreak
     * havoc inside the seglist if executed without C_ASSERT stopping the
     * operation.
     */
    /*
    retval = seglist_removeItem(pseglist, 9);
    CuAssertTrue(tc, retval == PM_RET_ASSERT_FAIL);
    */
    
    /* TODO check if number of segments has actually decreased if item 8 is
     * removed; also check heap usage after GC
     */

    retval = seglist_appendItem(pseglist, (pPmObj_t)item[10]);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 10);
    retval = seglist_getItem(pseglist, 9, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[10]);

    retval = seglist_removeItem(pseglist, 9);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = seglist_removeItem(pseglist, 8);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = seglist_removeItem(pseglist, 7);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 7);

    retval = seglist_appendItem(pseglist, (pPmObj_t)item[10]);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 8);
    retval = seglist_getItem(pseglist, 7, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[10]);
    retval = seglist_getItem(pseglist, 6, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[6]);

    retval = seglist_appendItem(pseglist, (pPmObj_t)item[2]);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = seglist_getItem(pseglist, 8, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[2]);

    for (i=0; i<9; i++)
    {
        retval = seglist_removeItem(pseglist, 0);
        CuAssertTrue(tc, retval == PM_RET_OK);
    }
    CuAssertTrue(tc, pseglist->sl_length == 0);
    retval = seglist_appendItem(pseglist, (pPmObj_t)item[2]);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pseglist->sl_length == 1);
    retval = seglist_getItem(pseglist, 0, &pobj);
    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertTrue(tc, pobj == item[2]);
}

/** Make a suite from all tests in this file */
CuSuite *getSuite_testSeglist(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_seglist_new_000);
    SUITE_ADD_TEST(suite, ut_seglist_appendItem_000);
    SUITE_ADD_TEST(suite, ut_seglist_appendItem_001);
    SUITE_ADD_TEST(suite, ut_seglist_insertItem_000);
    SUITE_ADD_TEST(suite, ut_seglist_insertItem_001);
    SUITE_ADD_TEST(suite, ut_seglist_insertItem_002);
    SUITE_ADD_TEST(suite, ut_seglist_getItem_000);
    SUITE_ADD_TEST(suite, ut_seglist_getItem_001);
    SUITE_ADD_TEST(suite, ut_seglist_removeItem_000);

    return suite;
}
