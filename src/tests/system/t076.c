/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

/**
 * System Test 076
 * Prints out some objects. Tests if print operation properly escapes
 * strings and if newline works.
 */

#include "pm.h"
#include "stdio.h"


extern unsigned char usrlib_img[];


int main(void)
{
    #ifdef HAVE_PRINT
    PmReturn_t retval;
    
    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"t076");
    return (int)retval;
    #else
    printf("HAVE_PRINT is not defined. Skipping test.\n");
    return 0;
    #endif /* !HAVE_PRINT */
}
