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

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/**
 * VM Globals
 *
 * VM globals header.
 *
 * Log
 * ---
 *
 * 2007/01/09   #75: Restructured for green threads (P.Adelt)
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2002/04/22   First.
 */


/***************************************************************
 * Constants
 **************************************************************/

/** The global root PmGlobals Dict object */
#define PM_PBUILTINS    (pPmObj_t)(gVmGlobal.builtins)

/** The global None object */
#define PM_NONE         (pPmObj_t)(gVmGlobal.pnone)

/** The global False object */
#define PM_FALSE        (pPmObj_t)(gVmGlobal.pzero)

/** The global True object */
#define PM_TRUE         (pPmObj_t)(gVmGlobal.pone)

/** The global integer 0 object */
#define PM_ZERO         (pPmObj_t)(gVmGlobal.pzero)

/** The global integer 1 object */
#define PM_ONE          (pPmObj_t)(gVmGlobal.pone)

/** The global integer -1 object */
#define PM_NEGONE       (pPmObj_t)(gVmGlobal.pnegone)

/** The global string "code" */
#define PM_CODE_STR     (pPmObj_t)(gVmGlobal.pcodeStr)


/***************************************************************
 * Types
 **************************************************************/

/**
 * This struct contains ALL of PyMite's globals
 */
typedef struct PmVmGlobal_s
{
    /** Global none obj (none) */
    pPmObj_t pnone;

    /** Global integer 0 obj */
    pPmInt_t pzero;

    /** Global integer 1 obj */
    pPmInt_t pone;

    /** Global integer -1 obj */
    pPmInt_t pnegone;

    /** The string "code", used in interp.c RAISE_VARARGS */
    pPmString_t pcodeStr;

    /** Dict for builtins */
    pPmDict_t builtins;

    /** Ptr to stack of code image info. */
    pPmImgInfo_t pimglist;

    /** The single native frame.  Static alloc so it won't be GC'd */
    PmNativeFrame_t nativeframe;

    /** PyMite release value for when an error occurs */
    uint8_t errVmRelease;

    /** PyMite source file ID number for when an error occurs */
    uint8_t errFileId;

    /** Line number for when an error occurs */
    uint16_t errLineNum;

    /** Thread list */
    pPmList_t threadList;

    /** Ptr to current thread */
    pPmThread_t pthread;

    /** Flag to trigger rescheduling */
    uint8_t reschedule;
} PmVmGlobal_t,
 *pPmVmGlobal_t;


/***************************************************************
 * Globals
 **************************************************************/

extern volatile PmVmGlobal_t gVmGlobal;


/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Initializes the global struct
 *
 * @return Return status
 */
PmReturn_t global_init(void);

/**
 * Sets the builtins dict into the given module's attrs.
 *
 * If not yet done, loads the "__bt" module via global_loadBuiltins().
 * Restrictions described in that functions documentation apply.
 *
 * @param pmod Module whose attrs receive builtins
 * @return Return status
 */
PmReturn_t global_setBuiltins(pPmFunc_t pmod);

/**
 * Loads the "__bt" module and sets the builtins dict (PM_PBUILTINS)
 * to point to __bt's attributes dict.
 * Creates "None" = None entry in builtins.
 *
 * When run, there should not be any other threads in the interpreter
 * thread list yet.
 *
 * @return  Return status
 */
PmReturn_t global_loadBuiltins(void);

#endif /* __GLOBAL_H__ */
