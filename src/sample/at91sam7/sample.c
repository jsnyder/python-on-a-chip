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

    /* Enable PIO's clock */
    AT91F_PMC_EnablePeriphClock(AT91C_BASE_PMC, 1 << AT91C_ID_PIOA);

    /* Configure PIO lines as outputs for LEDs 1-4 */
    AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED_MASK);

    /* Clear all LED's (active low) */
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);

    /* Report results via LEDs */
    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, 0x01);


    /* Init PyMite */
    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);
    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, 0x02);
    PM_RETURN_IF_ERROR(retval);

    /* Run the sample program */
    retval = pm_run((uint8_t *)"sample");

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
