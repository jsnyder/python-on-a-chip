/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2002 Dean Hall
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
