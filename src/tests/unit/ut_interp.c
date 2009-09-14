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
 * Interpreter Unit Tests
 * Tests the interpreter implementation.
 */


#include "CuTest.h"
#include "pm.h"


/* BEGIN unit tests ported from Snarf */
/**
 * The following source code was compiled to an image using pmImgCreator.py
 * from svn revision [193] using this command line:
 *
 *      ../../tools/pmImgCreator.py  -c -s -o utco.img.c utco.py
 *

def main():

    s = 0
    A = (0,1,2,3)
    B = (3,2,1,0)

    for i in A:
        s += i

    for i in B:
        s -= i

    for i in A:
        for j in B:
            s += i*j

    return s

main()

 */
extern uint8_t test_code_image0[];


/**
 * Tests interpret():
 *      retval is OK
 */
void
ut_interp_interpret_000(CuTest *tc)
{
    PmReturn_t retval;
    uint8_t const *pimg = test_code_image0;
    pPmObj_t pcodeobject;
    pPmObj_t pmodule;

    pm_init(MEMSPACE_RAM, C_NULL);

    /* Check the return value of the load function */
    retval = obj_loadFromImg(MEMSPACE_PROG, &pimg, &pcodeobject);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = mod_new(pcodeobject, &pmodule);
    CuAssertTrue(tc, retval == PM_RET_OK);
    retval = interp_addThread((pPmFunc_t)pmodule);
    CuAssertTrue(tc, retval == PM_RET_OK);

    /* Check that the module is interpreted and its return value is ok */
    retval = interpret(C_TRUE);
    CuAssertTrue(tc, retval == PM_RET_OK);
}
/* END unit tests ported from Snarf */


/** Make a suite from all tests in this file */
CuSuite *getSuite_testInterp(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, ut_interp_interpret_000);

    return suite;
}
