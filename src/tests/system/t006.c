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

#define __FILE_ID__ 0x99

/* #152 Change image terminator */
#define IMG_LIST_TERMINATOR ((uint8_t)0xFF)


extern unsigned char stdlib_img[];
extern unsigned char usrlib_img[];


int main(void)
{
    uint8_t const *pimg;
    PmReturn_t retval = PM_RET_OK;
    uint16_t size;
    uint8_t type;

    retval = heap_init();
    PM_RETURN_IF_ERROR(retval);
    retval = global_init();
    PM_RETURN_IF_ERROR(retval);

    /* Scan past stdlib images */
    pimg = (uint8_t *)&stdlib_img;
    type = (PmType_t)mem_getByte(MEMSPACE_PROG, &pimg);
    while (type == OBJ_TYPE_CIM)
    {
        size = mem_getWord(MEMSPACE_PROG, &pimg);
        pimg += (size - 3);
        type = (PmType_t)mem_getByte(MEMSPACE_PROG, &pimg);
    }
    /* The first byte after the last image should be the terminator */
    C_ASSERT(type == IMG_LIST_TERMINATOR);

    /* Scan past stdlib images */
    pimg = (uint8_t *)&usrlib_img;
    type = (PmType_t)mem_getByte(MEMSPACE_PROG, &pimg);
    while (type == OBJ_TYPE_CIM)
    {
        size = mem_getWord(MEMSPACE_PROG, &pimg);
        pimg += (size - 3);
        type = (PmType_t)mem_getByte(MEMSPACE_PROG, &pimg);
    }
    /* The first byte after the last image should be the terminator */
    C_ASSERT(type == IMG_LIST_TERMINATOR);

    return PM_RET_OK;
}

