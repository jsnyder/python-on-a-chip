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
 * Dict Unit Tests
 * Tests the Dict implementation.
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
    CuAssertTrue(tc, OBJ_GET_TYPE(pobj) == OBJ_TYPE_DIC);
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


/* BEGIN unit tests ported from Snarf */

char *test_str1 = "zzang1";
char *test_str2 = "zzang2";
char *test_str3 = "zzang3";
char *test_strnew = "zzangnew";

char *p_test_str1;
char *p_test_str2;
char *p_test_str3;
char *p_test_strnew;

pPmObj_t p_dict;
pPmObj_t p_dict2;
pPmObj_t p_tempobj;
pPmObj_t p_tempobj2;
pPmObj_t p_list;

pPmInt_t p_firstkey;
pPmInt_t p_secondkey;
pPmInt_t p_thirdkey;
pPmInt_t p_newkey;

pPmObj_t p_firstval;
pPmObj_t p_secondval;
pPmObj_t p_thirdval;
pPmObj_t p_newval;

char sol;

/**
 * Unit Test ported from SNARF
 * This tests if it correctly creates the dictionary object
 * This also tests if dict_setItem correctly replaces the existing value
 * if the new val has the same key as the exisiting one.
 */
void
ut_dict_getItem_001(CuTest *tc)
{
    p_test_str1 = test_str1;
    p_test_str2 = test_str2;
    p_test_str3 = test_str3;
    p_test_strnew = test_strnew;
    PmReturn_t retval;
    
    retval = pm_init(MEMSPACE_RAM, C_NULL);
    
    retval = string_new((uint8_t const **)&test_str1, &p_firstval);
    retval = string_new((uint8_t const **)&test_str2, &p_secondval);
    retval = string_new((uint8_t const **)&test_str3, &p_thirdval);
    retval = string_new((uint8_t const **)&test_strnew, &p_newval);
    
    retval = int_new(1, (pPmObj_t *)&p_firstkey);
    retval = int_new(2, (pPmObj_t *)&p_secondkey);
    retval = int_new(3, (pPmObj_t *)&p_thirdkey);
    retval = int_new(2, (pPmObj_t *)&p_newkey);
    
    dict_new(&p_dict);
    
    dict_setItem(p_dict, (pPmObj_t)p_firstkey, p_firstval);
    dict_setItem(p_dict, (pPmObj_t)p_secondkey, p_secondval);
    dict_setItem(p_dict, (pPmObj_t)p_thirdkey, p_thirdval);
    dict_setItem(p_dict, (pPmObj_t)p_newkey, p_newval);
    dict_setItem(p_dict, (pPmObj_t)p_secondkey, p_secondval);
    
    dict_getItem(p_dict, (pPmObj_t)p_firstkey, &p_tempobj);
    CuAssertTrue(tc, obj_compare(p_tempobj, p_firstval) == C_SAME);
    
    dict_getItem(p_dict, (pPmObj_t)p_secondkey, &p_tempobj);
    CuAssertTrue(tc, obj_compare(p_tempobj, p_secondval) == C_SAME);
    
    dict_getItem(p_dict, (pPmObj_t)p_thirdkey, &p_tempobj);
    CuAssertTrue(tc, obj_compare(p_tempobj, p_thirdval) == C_SAME);
}


#if 0
/**
 * Unit Test ported from SNARF
 * This tests if hasKey works correctly
 */
void
ut_dict_hasKey_000(CuTest *tc)
{
  if (dict_hasKey(p_dict, (pPmObj_t)p_firstkey)==0) return 0;
  if (dict_hasKey(p_dict, (pPmObj_t)p_secondkey)==0) return 0;
  if (dict_hasKey(p_dict, (pPmObj_t)p_thirdkey)==0) return 0;
}


/* This tests if it returns the correct list of keys and vals */
U8
Dict_test2(void)
{
  dict_keys(p_dict, &p_list);

  list_getItem(p_list, 0, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_firstkey)==0) return 0 ;

  list_getItem(p_list, 1, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_secondkey)==0) return 0 ;

  list_getItem(p_list, 2, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_thirdkey)==0) return 0 ;

  //destroy_chunk(p_list); //destroys elements in p_list. Destroys contents the keys! bad

  dict_vals(p_dict, &p_list);
  list_getItem(p_list, 0, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_firstval)==0) return 0 ;

  list_getItem(p_list, 1, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_secondval)==0) return 0 ;

  list_getItem(p_list, 2, &p_tempobj);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_thirdval)==0) return 0 ;

  //NO. Destroys contents. We want to reuse for other tests.
  //destroy_chunk(p_list);
  //destroy_chunk(p_tempobj);

  return 1;
}

/* This tests if it pops correctly. */
U8
Dict_test3(void)
{
  dict_popItem(p_dict, &p_tempobj, &p_tempobj2);

  if (object_isEqual(p_tempobj,(pPmObj_t) p_firstkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2,(pPmObj_t) p_firstval)==0) return 0 ;

  dict_getItemIndex(p_dict, 0, &p_tempobj, &p_tempobj2);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_secondkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2 ,(pPmObj_t) p_secondval)==0) return 0 ;

  dict_getItemIndex(p_dict, 1, &p_tempobj, &p_tempobj2);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_thirdkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2,(pPmObj_t) p_thirdval)==0) return 0 ;

  //NO.
  //destroy_chunk(p_tempobj);
  //destroy_chunk(p_tempobj2);

  return 1;
}

/* This tests if it updates correctly.(combines 2 dicts into one)*/
U8
Dict_test4(void)
{
  dict_new(&p_dict2);
  dict_setItem(p_dict2,(pPmObj_t) p_firstkey, p_firstval);
  dict_update(&p_list, p_dict2, p_dict);

  dict_getItemIndex(p_list, 0, &p_tempobj, &p_tempobj2);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_firstkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2,(pPmObj_t) p_firstval)==0) return 0 ;

  dict_getItemIndex(p_list, 1, &p_tempobj, &p_tempobj2);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_secondkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2 ,(pPmObj_t) p_secondval)==0) return 0 ;

  dict_getItemIndex(p_list, 2, &p_tempobj, &p_tempobj2);
  if (object_isEqual(p_tempobj,(pPmObj_t) p_thirdkey)==0) return 0 ;
  if (object_isEqual(p_tempobj2 ,(pPmObj_t) p_thirdval)==0) return 0 ;

  //destroy_chunk(p_dict);
  //destroy_chunk(p_dict2);
  //destroy_chunk(p_list);
  //destroy_chunk(p_tempobj);
  //destroy_chunk(p_tempobj2);
  //Should destroy all items created above, 2 dicts, one list. All have overlapping contents

  return 1;
}
#endif
/* END unit tests ported from Snarf */


/** Make a suite from all tests in this file */
CuSuite *getSuite_testDict(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_dict_new_000);
    SUITE_ADD_TEST(suite, ut_dict_setItem_000);
    SUITE_ADD_TEST(suite, ut_dict_setItem_001);
    SUITE_ADD_TEST(suite, ut_dict_clear_000);
    SUITE_ADD_TEST(suite, ut_dict_getItem_000);

    SUITE_ADD_TEST(suite, ut_dict_getItem_001);

    return suite;
}
