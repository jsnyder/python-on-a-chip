/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#include "pm.h"


#ifdef __cplusplus
extern
#endif
unsigned char const usrlib_img[];


int
main(void)
{
    PmReturn_t retval;

    /* Init PyMite */
    retval = pm_init(MEMSPACE_PROG, (uint8_t *)usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    /* Run the sample program */
    retval = pm_run((uint8_t *)"main");

    return (int)retval;
}
