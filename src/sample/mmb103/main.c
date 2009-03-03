/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


/** Sample PyMite application */


#include <stdio.h>
#include <avr/io.h>

#include "libmmb103.h"
#include "pm.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PmReturn_t retval;

    /* Init board */
    mmb_init(BAUD_19200, ADC_CK_DIV_128, PWM_CK_DIV_8, 4, 20);

    /* Init and run PyMite */
    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"main");
    return (int)retval;
}
