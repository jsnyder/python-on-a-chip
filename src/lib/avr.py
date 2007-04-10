# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2007 Dean Hall
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
# AVR Access Module
#
# Provides generic access to the AVR microcontroller
#
# USAGE
# -----
#
# import avr
# a = avr.portA()
# avr.portA(42)
#
# LOG
# ---
#
# 2007/03/20    First
#
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
            if (OBJ_GET_TYPE(*pa) != OBJ_TYPE_INT)
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
