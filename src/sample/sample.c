/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2002 Dean Hall
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * Sample PyMite application
 *
 * Log
 * ---
 *
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2006/08/22   Creation
 */


#include "py.h"

extern unsigned char stdlib_img[];
extern unsigned char usrlib_img[];


int main(void)
{
    /* ptr to code imgs */
    P_U8 pimg;
    pPyObj_t pstring = C_NULL;
    /* ptr to module obj */
    pPyObj_t pmod;
    /* name of module to run */
    P_U8 modstr = (P_U8)"sample";
    PyReturn_t retval = PY_RET_OK;

    /* heap pointers are a part of globals, so init globals first */
    global_init();
    heap_init();

    /* load std image info */
    pimg = (P_U8)&stdlib_img;
    retval = img_findInMem(MEMSPACE_RAM, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* load usr image info */
    pimg = (P_U8)&usrlib_img;
    retval = img_findInMem(MEMSPACE_RAM, &pimg);
    PY_RETURN_IF_ERROR(retval);

    /* import module from global struct */
    retval = string_new(&modstr, &pstring);
    PY_RETURN_IF_ERROR(retval);
    retval = mod_import(pstring, &pmod);
    PY_RETURN_IF_ERROR(retval);
    /* load builtins into root module */
    retval = global_loadBuiltins((pPyFunc_t)pmod);
    PY_RETURN_IF_ERROR(retval);

    /* XXX set "__name__" == "__main__" in mod's attrs here? */

    /* interpret the module's bcode */
    retval = interpret((pPyFunc_t)pmod);

    return retval;
}
