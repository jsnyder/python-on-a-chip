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
# is seen in the file COPYING up one directory from this.

#
# This is a sample application that calls functions in the AVR module.
#

"""__NATIVE__
#include <avr/io.h>
"""


print "Hello world."


#
# Initialize the AVR's port A pin direction
#
def init():
    """__NATIVE__
    /* Set port A pins as all outputs */
    DDRA = 0xFF;
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass

init()
import avr
avr.portA(0xaa)


print "Expect a NameError (0xEA) after this."
foo()
