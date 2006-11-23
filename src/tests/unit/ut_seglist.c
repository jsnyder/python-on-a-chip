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
 * Seglist Unit Tests
 *
 * Tests the Seglist implementation.
 *
 * Log
 * ---
 *
 * 2006/11/22   First.
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

    return suite;
}
