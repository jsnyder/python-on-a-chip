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
# is seen in the file COPYING in this directory.

## @file
#  @copybrief avr

## @package avr
#  @brief AVR Access Module
#
# Provides generic access to the AVR microcontroller
#
# <b>USAGE</b>
#
# \code
# import avr
# a = avr.portA()
# avr.portA(42)
# \endcode


"""__NATIVE__
#include <avr/io.h>
"""


def portA(a):
    """__NATIVE__
    pPmObj_t pa;
    uint8_t ddra;
    PmReturn_t retval = PM_RET_OK;

    /* Store port A data direction register */
    ddra = DDRA;

    switch (NATIVE_GET_NUM_ARGS())
    {
        /* If no argument is present, return PORTA */
        case 0:

            /* Set port A as all inputs so it can be read */
            DDRA = 0x00;

            /* Read port A and create a Python integer from its value */
            retval = int_new((int32_t)PORTA, &pa);

            /* Return the integer on the stack */
            NATIVE_SET_TOS(pa);
            break;

        /* If one argument is present, set port A to that value */
        case 1:
            pa = NATIVE_GET_LOCAL(0);

            /* If the arg is not an integer, raise TypeError */
            if (OBJ_GET_TYPE(pa) != OBJ_TYPE_INT)
            {
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;
            }

            /* Otherwise set PORTA to the low byte of the integer value */
            PORTA = ((pPmInt_t)pa)->val;
            break;

        /* If an invalid number of args are present, raise TypeError */
        default:
            PM_RAISE(retval, PM_RET_EX_TYPE);
            break;
    }

    /* Restore port A data direction register */
    DDRA = ddra;
    return retval;
    """
    pass


# :mode=c:
