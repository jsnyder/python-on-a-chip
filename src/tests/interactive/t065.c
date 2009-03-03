/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

/**
 * Interactive Test 065
 * Tests plat module's putb and getb functions
 */

#include "pm.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    puts("DIRECTIONS: Type one char input and <return> when prompted.");
    puts("EXPECT: To see `Echo: `, the char you typed, the next two chars in the alphabet.");
    puts("EXAMPLE:\n\tType a letter: x\n\tEcho: xyz");

    retval = pm_run((uint8_t *)"t065");
    return (int)retval;
}
