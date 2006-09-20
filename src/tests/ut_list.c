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

#undef __FILE_ID__
#define __FILE_ID__ 0x9B
/**
 * List Unit Tests
 *
 * Unit tests for the List implementation.
 *
 *  Tests and whether they are implemented (Y/N).
 *
 *      list_new()
 *          Y 000 new list, expect retval is OK and plist != C_NULL
 *          Y 001 new list, expect list type
 *          Y 002 new list, expect clear const bit
 *          Y 003 new list, expect length == 0
 *          Y 004 new list, expect list->val != C_NULL (IMPL)
 *          N od.etc?
 *
 *      list_append(plist, pitem)
 *          Y 000 append with list == C_NULL, expect a ValueError
 *          Y 001 append with item == C_NULL, expect a ValueError
 *          Y 002 append with non-list argument, expect a ValueError
 *          Y 003 new list, append 1 item, expect list length == 1
 *          N new list, append item, expect list[-1] == item
 *
 *      list_setItem(plist, indx, pval)
 *          N list = C_NULL
 *          N indx < 0
 *          N val = C_NULL
 *          N indx >= len
 *          N return list is same
 *          N return val is same
 *          N return length is same
 *          N return list[indx] == val
 *
 *      list_getItem(plist, indx)
 *          N list = C_NULL
 *          N list = non-list
 *          N indx < 0
 *          N indx > len
 *          N indx == len
 *          N indx = 0 on empty list
 *          N indx = 0 on nonempty list
 *          N indx = N on list of length > N
 *          N return obj != C_NULL
 *
 *      list_copy(plist)
 *          N list = C_NULL
 *          N list = non-list
 *          N return list != C_NULL
 *          N return list ptr != list ptr
 *          N return list length == list.length
 *          N return list objs == list objs
 *
 *      list_replicate(psrclist, n)
 *
 * Log:
 *
 * 2003/01/12   First.
 */


#include "pm.h"


/**************************************************************/

/** new list, expect retval is OK and plist != C_NULL */
void
ut_list_new_000(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (retval != PM_RET_OK)
    {
        TEST_ERR(__LINE__);
    }
    if (pobj == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect list type */
void
ut_list_new_001(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (OBJ_GET_TYPE(*pobj) != OBJ_TYPE_LST)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect clear const bit */
void
ut_list_new_002(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (OBJ_IS_CONST(pobj))
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect length == 0 */
void
ut_list_new_003(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (((pPmList_t)pobj)->length != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect list->val != C_NULL */
void
ut_list_new_004(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t plist = C_NULL;

    retval = list_new(&plist);
    if (((pPmList_t)plist)->val == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
}


/**************************************************************/

/** call with list == C_NULL, expect a ValueError */
void
ut_list_append_000(void)
{
    PmReturn_t retval = PM_RET_OK;

    retval = list_append((pPmObj_t)C_NULL, (pPmObj_t)C_NULL);
    if (retval != PM_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** call with item == C_NULL, expect a ValueError */
void
ut_list_append_001(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t plist = C_NULL;

    retval = list_new(&plist);
    retval = list_append(plist, (pPmObj_t)C_NULL);
    if (retval != PM_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** call with non-list argument, expect a ValueError */
void
ut_list_append_002(void)
{
    PmReturn_t retval = PM_RET_OK;

    retval = list_append(PM_ZERO, PM_ONE);
    if (retval != PM_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, append 1 item, expect list length == 1 */
void
ut_list_append_003(void)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t plist = C_NULL;

    retval = list_new(&plist);
    retval = list_append(plist, PM_ZERO);
    if (((pPmList_t)plist)->length != 1)
    {
        TEST_ERR(__LINE__);
    }
}

/**************************************************************/
/** Set of all list test functions */
void
ut_list(void)
{
    /* list_new() tests */
    ut_list_new_000();
    ut_list_new_001();
    ut_list_new_002();
    ut_list_new_003();
    ut_list_new_004();

    /* list_append() tests */
    ut_list_append_000();
    ut_list_append_001();
    ut_list_append_002();
    ut_list_append_003();
}
