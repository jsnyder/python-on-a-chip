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
