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

extern unsigned char lib_img[];


int main(void)
{
    P_U8 pimg = (P_U8)&lib_img;
    PyReturn_t retval = PY_RET_OK;

    heap_init();
    global_init();

    /* Read in the string of modules */
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    PY_ASSERT(*pimg == C_NULL);

    return retval;
}

