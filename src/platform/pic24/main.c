/*
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
*/

/** @file
 *  @brief Initialize then run the Python VM on power-up.
 */


#include "pm.h"
#include "pic24_all.h"

// Note: for unit testing, no Python heap is needed, so make it tiny.
// The unit tests need lots of heap and stack, so a small Python heap
// allows that.
#ifdef UNIT_TEST
#define HEAP_SIZE 100
#elif defined(__DEBUG)
#define HEAP_SIZE 6900
#else
#define HEAP_SIZE 6980
#endif

extern unsigned char usrlib_img[];

int main(void)
{
    uint8_t heap[HEAP_SIZE];
    PmReturn_t retval;

    retval = pm_init(heap, HEAP_SIZE, MEMSPACE_PROG, usrlib_img);
    printf("Python initialized; result was 0x%02x.\n", retval);
    PM_RETURN_IF_ERROR(retval);

    printf("Running Python...\n");
    // Uncommon one or the other to run the main code, or
    // to run sample code.
    retval = pm_run((uint8_t *)"main");
    //retval = pm_run((uint8_t *)"sample_lib");

    printf("\n\nPython finished, return of 0x%02x.\nResetting...\n\n", retval);
    // Wait a bit, so reset so flash by too fast.
    DELAY_MS(1000);
    asm("reset");

    return (int)retval;
}
