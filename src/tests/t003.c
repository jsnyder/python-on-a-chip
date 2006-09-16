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

/***************************************************************
 * Includes
 **************************************************************/


 #include "py.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

extern unsigned char stdlib_img[];
extern unsigned char usrlib_img[];

/***************************************************************
 * Main
 **************************************************************/

int main(void)
{
    /* ptr to code imgs */
    P_U8 pimg;
    pPyObj_t pstring = C_NULL;
    /* ptr to module obj */
    pPyFunc_t pmod;
    /* name of module to run */
    P_U8 modstr = (P_U8)"t003";
    PyReturn_t retval = PY_RET_OK;

    heap_init();
    retval = global_init();
    PY_RETURN_IF_ERROR(retval);

    /* load std image info */
    pimg = (P_U8)&stdlib_img;
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* load usr image info */
    pimg = (P_U8)&usrlib_img;
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

