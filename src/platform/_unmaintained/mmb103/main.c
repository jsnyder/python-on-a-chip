/*
# This file is Copyright 2006, 2007, 2009 Dean Hall.
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


#include <stdio.h>
#include <avr/io.h>

#include "libmmb103.h"
#include "pm.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PmReturn_t retval;

    /* Init board (don't overwrite PyMite's AVR UART config) */
    mmb_init(0, ADC_CK_DIV_128, PWM_CK_DIV_8, 2, 16);

    /* Init and run PyMite */
    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"main");
    return (int)retval;
}
