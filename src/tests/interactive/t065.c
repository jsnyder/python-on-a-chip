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

/**
 * Interactive Test 065
 * Tests plat module's putb and getb functions
 *
 * Log
 * ---
 *
 * 2006/12/26   #65: Create plat module with put and get routines
 */

#include "pm.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    puts("DIRECTIONS: Type one char input and <return> when prompted.");
    puts("EXPECT: To see `Echo: `, the char you typed, the next two chars in the alphabet.");
    puts("EXAMPLE:\n\tType a letter: x\n\tEcho: xyz");

    retval = pm_run((uint8_t *)"t065");
    return (int)retval;
}
