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


#include "py.h"

extern unsigned char stdlib_img[];
extern unsigned char usrlib_img[];


int main(void)
{
    P_U8 pimg;
    PyReturn_t retval = PY_RET_OK;

    heap_init();
    retval = global_init();
    PY_RETURN_IF_ERROR(retval);

    /* Read in the stdlib modules */
    pimg = (P_U8)&stdlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    PY_ASSERT(*pimg == C_NULL);

    /* Read in the usrlib modules */
    pimg = (P_U8)&usrlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    PY_ASSERT(*pimg == C_NULL);

    return retval;
}

