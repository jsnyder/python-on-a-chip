#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Sample program for ARM target (Atmel AT91SAM7S64 chip on a AT91SAM7S-EK board)
#
"""__NATIVE__
#include "Board.h"
"""


def getButtons():
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    uint32_t val = 0;
    pPmObj_t pint;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Collect the button input as bits in an int */
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

    retval = int_new(val, &pint);
    PM_RETURN_IF_ERROR(retval);

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
    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
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


while 1:
    setLeds(getButtons())


# :mode=c:
