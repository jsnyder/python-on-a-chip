/**
 * Feature Test for Issue #20
 *
 * Implement assert statement
 *
 */

#include "py.h"


extern unsigned char usrlib_img[];


int main(void)
{
    PyReturn_t retval;

    retval = pm_init(MEMSPACE_FLASH, usrlib_img);
    PY_RETURN_IF_ERROR(retval);

    retval = pm_run((P_U8)"t020");
    return (int)retval;
}
