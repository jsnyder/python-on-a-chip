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
 * Heap Unit Tests
 *
 * Tests the Heap implementation.
 *
 * Log
 * ---
 *
 * 2006/11/21   First.
 */


#include "CuTest.h"
#include "pm.h"

/* Max chunk size for 32-bit desktop target */
#define HEAP_MAX_CHUNK_SIZE 2044

/* Min chunk size for 32-bit desktop target */
#define HEAP_CHUNK_MIN_SIZE 12

/**
 * Tests heap_init():
 *      retval is OK
 *      avail size is greater than zero
 */
void
ut_heap_init_000(CuTest *tc)
{
    PmReturn_t retval;

    retval = heap_init();

    CuAssertTrue(tc, retval == PM_RET_OK);

    CuAssertTrue(tc, heap_getAvail() > 0);
}


/**
 * Tests heap_getChunk():
 *      retval is OK
 *      return arg pointer is non-null
 *      return chunk is of requested size (rounded up to next multiple of four)
 */
void
ut_heap_getChunk_000(CuTest *tc)
{
    uint8_t *pchunk;
    PmReturn_t retval;
    pPmObj_t pobj;

    retval = heap_init();
    retval = heap_getChunk(8, &pchunk);
    pobj = (pPmObj_t)pchunk;

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pchunk);
    CuAssertTrue(tc, OBJ_GET_SIZE(pobj) == HEAP_CHUNK_MIN_SIZE);
}


/**
 * Tests heap_getChunk():
 *      checks that MAX_CHUNK_SIZE can be allocated
 */
void
ut_heap_getChunk_001(CuTest *tc)
{
    uint8_t *pchunk;
    PmReturn_t retval;
    pPmObj_t pobj;

    retval = heap_init();
    retval = heap_getChunk(HEAP_MAX_CHUNK_SIZE, &pchunk);
    pobj = (pPmObj_t)pchunk;

    CuAssertTrue(tc, retval == PM_RET_OK);
    CuAssertPtrNotNull(tc, pchunk);
    CuAssertTrue(tc, OBJ_GET_SIZE(pobj) >= HEAP_MAX_CHUNK_SIZE);
}


/**
 * Tests heap_getAvail():
 *      retval is OK
 *      avail is reduced by amount obtained in getChunk
 */
void
ut_heap_getAvail_000(CuTest *tc)
{
    uint16_t avail1;
    uint16_t avail2;
    uint16_t actualsize;
    uint8_t *pchunk;
    PmReturn_t retval;

    retval = heap_init();
    avail1 = heap_getAvail();

    retval = heap_getChunk(16, &pchunk);
    actualsize = OBJ_GET_SIZE(pchunk);
    
    avail2 = heap_getAvail();
    CuAssertTrue(tc, (avail1 - avail2) == actualsize);
}


/**
 * Tests heap_freeChunk():
 *      retval is OK
 *      avail is increased by amount obtained in freeChunk
 */
void
ut_heap_freeChunk_000(CuTest *tc)
{
    uint16_t avail1;
    uint16_t avail2;
    uint16_t actualsize;
    uint8_t *pchunk;
    PmReturn_t retval;

    retval = heap_init();
    retval = heap_getChunk(16, &pchunk);
    actualsize = OBJ_GET_SIZE(pchunk);
    avail1 = heap_getAvail();
    retval = heap_freeChunk((pPmObj_t)pchunk);
    CuAssertTrue(tc, retval == PM_RET_OK);

    avail2 = heap_getAvail();
    CuAssertTrue(tc, (avail2 - avail1) == actualsize);
}


/**
 * Tests heap_freeChunk():
 *      avail returns to pre-allocated value after free
 */
void
ut_heap_freeChunk_001(CuTest *tc)
{
    uint16_t avail1;
    uint16_t avail2;
    uint8_t *pchunk1;
    uint8_t *pchunk2;
    uint8_t *pchunk3;
    PmReturn_t retval;

    retval = heap_init();
    avail1 = heap_getAvail();
    retval = heap_getChunk(19, &pchunk1);
    retval = heap_getChunk(33, &pchunk2);
    retval = heap_getChunk(88, &pchunk3);
    avail2 = heap_getAvail();
    CuAssertTrue(tc, avail1 - avail2 >= (19+33+88));

    retval = heap_freeChunk((pPmObj_t)pchunk1);
    retval = heap_freeChunk((pPmObj_t)pchunk2);
    retval = heap_freeChunk((pPmObj_t)pchunk3);
    CuAssertTrue(tc, retval == PM_RET_OK);

    avail2 = heap_getAvail();
    CuAssertTrue(tc, avail2 == avail1);
}


/** Make a suite from all tests in this file */
CuSuite *getSuite_testHeap(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_heap_init_000);
    SUITE_ADD_TEST(suite, ut_heap_getChunk_000);
    SUITE_ADD_TEST(suite, ut_heap_getChunk_001);
    SUITE_ADD_TEST(suite, ut_heap_getAvail_000);
    SUITE_ADD_TEST(suite, ut_heap_freeChunk_000);
    SUITE_ADD_TEST(suite, ut_heap_freeChunk_001);

    return suite;
}
