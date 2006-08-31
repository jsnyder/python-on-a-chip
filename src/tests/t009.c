/**
 * Regression Test for Issue #9
 */

#if defined(__AVR__)
#include <avr/pgmspace.h>
#endif

#include "py.h"

#include "t009_img.h"


int main(void)
{
    /* ptr to code imgs */
    P_U8 pimg = (P_U8)&lib_img;
    pPyObj_t pstring = C_NULL;
    /* ptr to module obj */
    pPyFunc_t pmod;
    /* name of module to run */
    P_U8 modstr = (P_U8)"t009";
    PyReturn_t retval = PY_RET_OK;

    /* heap pointers are a part of globals, so init globals first */
    global_init();
    heap_init();

    /* get image info into global struct */
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* import module from global struct */
    retval = string_new(&modstr, &pstring);
    PY_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmod);
    PY_RETURN_IF_ERROR(retval);

    /* load builtins into root module */
    retval = global_loadBuiltins(pmod);
    PY_RETURN_IF_ERROR(retval);

    /* XXX set "__name__" == "__main__" in mod's attrs here? */

    /* interpret the module's bcode */
    retval = interpret(pmod);

    return retval;
}

