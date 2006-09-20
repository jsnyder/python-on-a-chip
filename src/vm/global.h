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
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2002/04/22   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** The global root PmGlobals Dict object */
#define PM_PBUILTINS    (pPmObj_t)(gVmGlobal.builtins)

/** The global None object */
#define PM_NONE         (pPmObj_t)&(gVmGlobal.none)

/** The global False object */
#define PM_FALSE        (pPmObj_t)&(gVmGlobal.zero)

/** The global True object */
#define PM_TRUE         (pPmObj_t)&(gVmGlobal.one)

/** The global integer 0 object */
#define PM_ZERO         (pPmObj_t)&(gVmGlobal.zero)

/** The global integer 1 object */
#define PM_ONE          (pPmObj_t)&(gVmGlobal.one)

/** The global integer -1 object */
#define PM_NEGONE       (pPmObj_t)&(gVmGlobal.negone)

/** The global string "code" */
#define PM_CODE_STR     (pPmObj_t)(gVmGlobal.pcodeStr)

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * This struct contains ALL of PyMite's globals
 */
typedef struct PmVmGlobal_s
{
    /** Global none obj (none) */
    PmObj_t none;

    /** Global integer 0 obj */
    PmInt_t zero;

    /** Global integer 1 obj */
    PmInt_t one;

    /** Global integer -1 obj */
    PmInt_t negone;

    /** The string "code", used in interp.c RAISE_VARARGS */
    pPmString_t pcodeStr;

    /** Dict for builtins */
    pPmDict_t builtins;

    /** Ptr to stack of code image info. */
    pPmImgInfo_t pimglist;

    /** Ptr to current python frame */
    pPmFrame_t pframe;

    /** The single native frame */
    PmNativeFrame_t nativeframe;

    /** PyMite release value for when an error occurs */
    uint8_t errVmRelease;

    /** PyMite source file ID number for when an error occurs */
    uint8_t errFileId;

    /** Line number for when an error occurs */
    uint16_t errLineNum;

    /**
     * Interpreter loop control value
     *
     * A positive value means continue interpreting.
     * A zero value means normal interpreter exit.
     * A negative value signals an error exit.
     */
    PmInterpCtrl_t interpctrl;

    /** The PyMite heap */
    PmHeap_t heap;
    /* DO NOT PUT ANYTHING BELOW THIS */
} PmVmGlobal_t, *pPmVmGlobal_t;


/***************************************************************
 * Globals
 **************************************************************/

extern PmVmGlobal_t gVmGlobal;


/***************************************************************
 * Prototypes
 **************************************************************/

/** 
 * Initialize the global struct 
 *
 * @return Return status
 */
PmReturn_t global_init(void);

/**
 * Load the builtins dict into the given module's attrs.
 *
 * Load the "__bt" module and set the builtins dict
 * to point to __bt's attributes dict.
 * Create "None" = None entry in builtins.
 *
 * @param pmod Module whose attrs recieves builtins
 * @return  Return status
 */
PmReturn_t global_loadBuiltins(pPmFunc_t pmod);

#endif /* __GLOBAL_H__ */
