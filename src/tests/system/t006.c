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
 * Regression Test for Issue #6
 *
 * Ensure an image list is null terminated.
 *
 * Log
 * ---
 *
 * 2006/09/01   #11: Make src/tests/ build module images as C files,
 *              not header files
 */


#include "pm.h"

extern unsigned char stdlib_img[];
extern unsigned char usrlib_img[];


int main(void)
{
    uint8_t *pimg;
    PmReturn_t retval = PM_RET_OK;

    heap_init();
    retval = global_init();
    PM_RETURN_IF_ERROR(retval);

    /* Read in the stdlib modules */
    pimg = (uint8_t *)&stdlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PM_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    if (*pimg != C_NULL)
    {
        return PM_RET_EX_SYS;
    }

    /* Read in the usrlib modules */
    pimg = (uint8_t *)&usrlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PM_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    if (*pimg != C_NULL)
    {
        return PM_RET_EX_SYS;
    }

    pm_reportResult(retval);
    return retval;
}

