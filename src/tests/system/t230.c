/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

/**
 * System Test 230
 * Fix classes during ipm
 * This test checks for a regression: __NATIVE__ __init__ method pushed None
 * on the stack causing trouble.
 */

#include "pm.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"t230");
    return (int)retval;
}
