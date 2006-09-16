/**
 * System Test 003
 * Unrelated to issue #3.
 * Load a module image from RAM
 * using the global image info list.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
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
