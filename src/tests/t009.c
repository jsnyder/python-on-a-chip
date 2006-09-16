/**
 * Regression Test for Issue #9
 *
 * Fix BINARY_SUBSCR for case stringobj[intobj]
 *
 * Log
 * ---
 *
 * 2006/09/01   #11: Make src/tests/ build module images as C files,
 *              not header files
 */

#include "py.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PyReturn_t retval;

    retval = pm_init(MEMSPACE_FLASH, usrlib_img);
    PY_RETURN_IF_ERROR(retval);

    retval = pm_run((P_U8)"t009");
    return (int)retval;
}
