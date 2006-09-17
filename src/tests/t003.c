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
 * System Test 003
 * Unrelated to issue #3.
 * Load a module image from RAM
 * using the global image info list.
 *
 * Log
 * ---
 *
 * 2006/09/01   #11: Make src/tests/ build module images as C files,
 *              not header files
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2002/05/18   First.
 */

#include "py.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PyReturn_t retval;

    retval = pm_init(MEMSPACE_FLASH, usrlib_img);
    PY_RETURN_IF_ERROR(retval);

    retval = pm_run((P_U8)"t003");
    return (int)retval;
}
