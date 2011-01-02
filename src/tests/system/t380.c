/*
# This file is Copyright 2011 Dean Hall.
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
*/

/**
 * System Test 380
 */

#include <stdlib.h>

#include "pm.h"


extern unsigned char usrlib_img[];

int formerly_bad_heapsizes[] = {0x10000, 0x20008, 0x30004, 0x4000C};


int main(void)
{
    uint8_t *heap;
    PmReturn_t retval;
    int32_t hs;
    int8_t i;

    for (i = 0; i < 4; i++)
    {
        hs = formerly_bad_heapsizes[i];
        heap = malloc(hs);
        retval = pm_init(heap, hs, MEMSPACE_PROG, usrlib_img);
        if (retval != PM_RET_OK)
        {
            free(heap);
            break;
        }

        retval = pm_run((uint8_t *)"t380");
        free(heap);
        PM_BREAK_IF_ERROR(retval);
    }
    return retval;
}
