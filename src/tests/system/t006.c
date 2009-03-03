/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */

/**
 * Regression Test for Issue #6
 * Ensure an image list is null terminated.
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

