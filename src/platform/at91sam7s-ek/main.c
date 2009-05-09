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


#include "Board.h"
#include "pm.h"


extern unsigned char usrlib_img[];


int
main(void)
{
    PmReturn_t retval;

    /* Init PyMite */
    retval = pm_init(MEMSPACE_PROG, usrlib_img);

    /* Configure PIOA for LEDs and clear them */
    AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED_MASK);
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);

    PM_RETURN_IF_ERROR(retval);

    /* Run the sample program */
    retval = pm_run((uint8_t *)"main");

    /* Report results via LEDs */
    if (retval == PM_RET_OK)
    {
        AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);
        AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, 0x03);
    }
    else
    {
        AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);
        AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, 0x04);
    }
    return (int)retval;
}
