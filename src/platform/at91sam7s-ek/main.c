/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
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
