/**
 * Test Issue #006
 *
 * Ensure an image list is null terminated.
 */


#include "py.h"

#include "t006_img.h"


int main(void)
{
    P_U8 pimg = (P_U8)&lib_img;
    PyReturn_t retval = PY_RET_OK;

    global_init();
    heap_init();

    /* Read in the string of modules */
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* The module image list terminator must be a null */
    pimg -= 1;
    PY_ASSERT(*pimg == C_NULL);

    return retval;
}

