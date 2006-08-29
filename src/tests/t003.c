/**
 * System Test 003
 *
 * Load a module image from RAM
 * using the global image info list.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        tests002.c
 *
 * Log:
 *
 * 2002/05/18   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#if defined(__AVR__)
#include <avr/pgmspace.h>
#endif

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

/* include code img */
#include "t003_img.h"

/***************************************************************
 * Main
 **************************************************************/

int main(void)
{
    /* ptr to code imgs */
    P_U8 pimg = (P_U8)lib_img;
    pPyObj_t pstring = C_NULL;
    /* ptr to module obj */
    pPyFunc_t pmod;
    /* name of module to run */
    P_U8 modstr = (P_U8)"t003";
    PyReturn_t retval = PY_RET_OK;

    /* heap pointers are a part of globals, so init globals first */
    global_init();
    heap_init();

    /* get image info into global struct */
#if defined __AVR__
    retval = img_findInMem(MEMSPACE_FLASH, &pimg);
#else
    retval = img_findInMem(MEMSPACE_RAM, &pimg);
#endif

    /* any img loading error causes early exit */
    PY_RETURN_IF_ERROR(retval);

    /* import module from global struct */
    retval = string_new(&modstr, &pstring);
    PY_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmod);
    PY_RETURN_IF_ERROR(retval);
    /* load builtins into root module */
    /* TODO: Trac #28 - Adapt native libs to used changed func calls */
    /*
    retval = global_loadBuiltins(pmod);
    PY_RETURN_IF_ERROR(retval);
    */

    /* XXX set "__name__" == "__main__" in mod's attrs here? */

    /* interpret the module's bcode */
    retval = interpret(pmod);

    return retval;
}

