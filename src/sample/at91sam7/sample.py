# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

#
# Sample program for ARM target (Atmel AT91SAM7S64 chip on a AT91SAM7S-EK board)
#
"""__NATIVE__
#include "Board.h"
"""


def getButtons(n):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    uint32_t val = 0;
    pPmObj_t pn;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* If arg is not an int, raise TypeError */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & SW1_MASK) == 0)
    {
        val |= 0x01;
    }
    if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & SW2_MASK) == 0)
    {
        val |= 0x02;
    }
    if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & SW3_MASK) == 0)
    {
        val |= 0x04;
    }
    if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & SW4_MASK) == 0)
    {
        val |= 0x08;
    }

    /* WARNING: in-place integer modification!  Bad if int objs are ever cached. */
    ((pPmInt_t)pn)->val = val;
    NATIVE_SET_TOS(pn);
    return retval;
    """
    pass


def setLeds(n):
    """__NATIVE__
    pPmObj_t pn;
    int32_t n;
    PmReturn_t retval;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* If arg is not an int, raise TypeError */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get int value from the arg */
    n = ((pPmInt_t)pn)->val;

    /* Clear all and set the desired LEDs (active low) */
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_MASK);
    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, n);
    NATIVE_SET_TOS(PM_NONE);
    return PM_RET_OK;
    """
    pass


n = 0
while 1:
    getButtons(n)
    setLeds(n)


# :mode=c:
