/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2007 Dean Hall
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
 * Interpreter Unit Tests
 *
 * Tests the interpreter implementation.
 *
 * Log
 * ---
 *
 * 2007/03/12   First.
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
    uint8_t *pimg = test_code_image0;
    pPmObj_t pcodeobject;
    pPmObj_t pmodule;
    uint16_t size;
    
    pm_init(MEMSPACE_RAM, C_NULL);

    /* Check the return value of the load function */
    retval = obj_loadFromImg(MEMSPACE_FLASH, &pimg, &pcodeobject);
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
