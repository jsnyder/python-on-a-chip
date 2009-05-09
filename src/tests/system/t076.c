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
