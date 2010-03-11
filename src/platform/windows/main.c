/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 *
 * This is a special main for a Windows console application. The message loop is
 * needed to support the timers which are used to tick the main PyMite VM.
 */

/** Interactive PyMite - the desktop is the target device */


#include "pm.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "tchar.h"

// the usr modules that were converted to C from Python
// should this definition go into pm.h?
extern unsigned char usrlib_img[];


#if defined(_CONSOLE)
    int _tmain(int argc, _TCHAR* argv[])
#else
    int WinMain(HINSTANCEhInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
#endif
{
    PmReturn_t retval;

    retval = pm_init(MEMSPACE_PROG, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"main");
    return (int)retval;
}

