#undef __FILE_ID__
#define __FILE_ID__ 0x92
/**
 * Unit Test 001
 *
 * Test the Dict implementation.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2003 Dean Hall.  All rights reserved.
 *
 *  List of tests and whether they are implemented (Y/N).
 *
 *      dict_new()
 *          Y return dict not C_NULL
 *          Y return od.type
 *          Y return od.const
 *          N return od.etc
 *          Y return length is 0
 *          N retval is OK
 *
 *      dict_setItem(pdict, pkey, pval)
 *          Y 000 Pass C_NULL to dict, expect a SystemError
 *          Y 001 Pass C_NULL to key, expect a SystemError
 *          Y 002 Pass C_NULL to val, expect a SystemError
 *          Y 003 Test dict_setItem() passing valid vals, return dict must not be NULL
 *          Y 004 Test dict_setItem() passing valid vals, return dict must be same addr
 *          Y 005 Test dict_setItem(), set(k,v), dict length must be 1
 *          Y 006 Test dict_setItem(), set(k,v) item at k must be same v
 *          Y 007 Test dict_setItem(), set(k,v1) set(k,v2), item at k must be v2
 *          Y 008 Test dict_setItem(), expect retval is OK
 *
 *      dict_clear(pdict)
 *          Y dict = C_NULL
 *          Y dict = non-dict
 *          Y dict = empty dict, return dict not C_NULL
 *          Y dict = empty dict, return length is 0
 *          Y dict = non-empty dict, return length is 0
 *          N retval is OK
 *
 *      dict_getItem(pdict, pkey)
 *          N dict == C_NULL
 *          N key == C_NULL
 *          N dict = non-dict
 *          N key = non-hashable
 *          N key with empty key,val lists
 *          N key (key not known)
 *          N key (kew known)
 *          N retval is OK
 *
 * Log:
 *
 * 2003/01/11   First.
 */


#include "py.h"


/**************************************************************/
/** Test dict_new() return not C_NULL */
void
ut_dict_new_000(void)
{
    pPyObj_t pobj = C_NULL;

    dict_new(&pobj);
    if (pobj == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_new() return type must be DICT */
void
ut_dict_new_001(void)
{
    pPyObj_t pobj = C_NULL;

    dict_new(&pobj);
    if (pobj->od.od_type != OBJ_TYPE_DIC)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_new() return const bit must be clear */
void
ut_dict_new_002(void)
{
    pPyObj_t pobj = C_NULL;

    dict_new(&pobj);
    if (pobj->od.od_const != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_new() return length must be 0 */
void
ut_dict_new_003(void)
{
    pPyObj_t pobj = C_NULL;

    dict_new(&pobj);
    if (((pPyDict_t)pobj)->length != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/**************************************************************/
/** Pass C_NULL to dict, expect a SystemError */
void
ut_dict_setItem_000(void)
{
    PyReturn_t retval = PY_RET_OK;
    retval = dict_setItem((pPyObj_t)C_NULL,
                          (pPyObj_t)C_NULL,
                          (pPyObj_t)C_NULL);
    if (retval != PY_RET_EX_SYS)
    {
        TEST_ERR(__LINE__);
    }
}

/** Pass C_NULL to key, expect a SystemError */
void
ut_dict_setItem_001(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    retval = dict_setItem(pdict, 
                          (pPyObj_t)C_NULL, 
                          (pPyObj_t)C_NULL);
    if (retval != PY_RET_EX_SYS)
    {
        TEST_ERR(__LINE__);
    }
}

/** Pass C_NULL to val, expect a SystemError */
void
ut_dict_setItem_002(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    retval = dict_setItem(pdict,
                          PY_ZERO,
                          (pPyObj_t)C_NULL);
    if (retval != PY_RET_EX_SYS)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem() passing valid vals, return dict must not be NULL */
void
ut_dict_setItem_003(void)
{
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_setItem(pdict, PY_ZERO, PY_ONE);
    if (pdict == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem() passing valid vals, return dict must be same addr */
void
ut_dict_setItem_004(void)
{
    pPyObj_t pdict = C_NULL;
    pPyObj_t pdictbefore = C_NULL;

    dict_new(&pdict);
    pdictbefore = pdict;
    dict_setItem(pdict, PY_ZERO, PY_ONE);
    if (pdict != pdictbefore)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem(), set(k,v), dict length must be 1 */
void
ut_dict_setItem_005(void)
{
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_setItem(pdict, PY_ZERO, PY_ONE);
    if (((pPyDict_t)pdict)->length != 1)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem(), set(k,v) item at k must be same v */
void
ut_dict_setItem_006(void)
{
    pPyObj_t pval = C_NULL;
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_setItem(pdict, PY_ZERO, PY_ONE);
    dict_getItem(pdict, PY_ZERO, &pval);
    if (pval != PY_ONE)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem(), set(k,v1) set(k,v2), item at k must be v2 */
void
ut_dict_setItem_007(void)
{
    pPyObj_t pval = C_NULL;
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_setItem(pdict, PY_ZERO, PY_ZERO);
    dict_setItem(pdict, PY_ZERO, PY_ONE);
    dict_getItem(pdict, PY_ZERO, &pval);
    if (pval != PY_ONE)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_setItem(), expect retval is OK */
void
ut_dict_setItem_008(void)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    retval = dict_setItem(pdict,
                          PY_ZERO,
                          PY_ZERO);
    if (retval != PY_RET_OK)
    {
        TEST_ERR(__LINE__);
    }
}

/**************************************************************/
/** Test dict_clear() passing C_NULL, return is void, must inspect */
void
ut_dict_clear_000(void)
{
    dict_clear((pPyObj_t)C_NULL);
}

/** Test dict_clear() passing non-dict, return is void, must inspect */
void
ut_dict_clear_001(void)
{
    pPyObj_t pint;
    PyReturn_t retval = PY_RET_OK;
    
     retval = int_new(256, &pint);
    dict_clear(pint);
}

/** Test dict_clear() passing empty dict, return dict must not be null */
void
ut_dict_clear_002(void)
{
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_clear(pdict);
    if (pdict == C_NULL)
    {
        TEST_ERR(__LINE__);
    }
 }

/** Test dict_clear() passing empty dict, return dict must have 0 length */
void
ut_dict_clear_003(void)
{
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_clear(pdict);
    if (((pPyDict_t)pdict)->length != 0)
    {
        TEST_ERR(__LINE__);
    }
}

/** Test dict_clear() passing non-empty dict, return dict must have 0 length */
void
ut_dict_clear_004(void)
{
    pPyObj_t pdict = C_NULL;

    dict_new(&pdict);
    dict_setItem(pdict, PY_ZERO, PY_ZERO);
    dict_clear(pdict);
    if (((pPyDict_t)pdict)->length != 0)
    {
        TEST_ERR(__LINE__);
    }
}


/**************************************************************/
/** Set of all dict test functions */
void
ut_dict(void)
{
    /* dict_new() tests */
    ut_dict_new_000();
    ut_dict_new_001();
    ut_dict_new_002();
    ut_dict_new_003();

    /* dict_clear() tests */
    ut_dict_clear_000();
    ut_dict_clear_001();
    ut_dict_clear_002();
    ut_dict_clear_003();
    ut_dict_clear_004();

    /* dict_setItem() tests */
    ut_dict_setItem_000();
    ut_dict_setItem_001();
    ut_dict_setItem_002();
    ut_dict_setItem_003();
    ut_dict_setItem_004();
    ut_dict_setItem_005();
    ut_dict_setItem_006();
    ut_dict_setItem_007();
    ut_dict_setItem_008();
}
