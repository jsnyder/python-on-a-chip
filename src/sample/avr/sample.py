#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# This is a sample application that calls functions in the AVR module.
#

"""__NATIVE__
#include <avr/io.h>
"""


import avr


#
# Initialize the port A pin direction
#
def init():
    """__NATIVE__
    /* Set port A pins as all outputs */
    DDRA = 0xFF;
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def main():
    init()
    avr.portA(0xaa)


main()
