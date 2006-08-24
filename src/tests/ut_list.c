#undef __FILE_ID__
#define __FILE_ID__ 0x9B
/**
 * List Unit Tests
 *
 * Unit tests for the List implementation.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2003 Dean Hall.  All rights reserved.
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


#include "py.h"


/**************************************************************/

/** new list, expect retval is OK and plist != C_NULL */
void
ut_list_new_000(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (retval != PY_RET_OK)
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
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (pobj->od.od_type != OBJ_TYPE_LST)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect clear const bit */
void
ut_list_new_002(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (pobj->od.od_const != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect length == 0 */
void
ut_list_new_003(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pobj = C_NULL;

    retval = list_new(&pobj);
    if (((pPyList_t)pobj)->length != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, expect list->val != C_NULL */
void
ut_list_new_004(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t plist = C_NULL;

    retval = list_new(&plist);
    if (((pPyList_t)plist)->val == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
}


/**************************************************************/

/** call with list == C_NULL, expect a ValueError */
void
ut_list_append_000(void)
{
    PyReturn_t retval = PY_RET_OK;

    retval = list_append((pPyObj_t)C_NULL, (pPyObj_t)C_NULL);
    if (retval != PY_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** call with item == C_NULL, expect a ValueError */
void
ut_list_append_001(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t plist = C_NULL;

    retval = list_new(&plist);
    retval = list_append(plist, (pPyObj_t)C_NULL);
    if (retval != PY_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** call with non-list argument, expect a ValueError */
void
ut_list_append_002(void)
{
    PyReturn_t retval = PY_RET_OK;

    retval = list_append(PY_ZERO, PY_ONE);
    if (retval != PY_RET_EX_VAL)
    {
        TEST_ERR(__LINE__);
    }
}

/** new list, append 1 item, expect list length == 1 */
void
ut_list_append_003(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t plist = C_NULL;

    retval = list_new(&plist);
    retval = list_append(plist, PY_ZERO);
    if (((pPyList_t)plist)->length != 1)
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
