/*
# This file is Copyright 2007, 2009 Dean Hall.
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

/** @file
 *  @brief Initialize then run the Python VM on power-up.
 */


#include "pm.h"
#include "pic24_all.h"

extern unsigned char usrlib_img[];

int main(void)
{
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    printf("Python initialized; result was 0x%02x.\n", retval);
    PM_RETURN_IF_ERROR(retval);

    printf("Running Python...\n");
    retval = pm_run((uint8_t *)"main");

    printf("\n\nPython finished, return of 0x%02x.\nResetting...\n\n", retval);
    // Wait a bit, so reset so flash by too fast.
    DELAY_MS(1000);
    asm("reset");

    return (int)retval;
}
