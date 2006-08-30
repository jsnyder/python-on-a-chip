#ifndef __GLOBAL_H__
#define __GLOBAL_H__
/**
 * VM Globals
 *
 * VM globals header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        global.h
 *
 * Log
 * ---
 *
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2002/04/22   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** The global root PyGlobals Dict object */
#define PY_PBUILTINS    (pPyObj_t)(gVmGlobal.builtins)

/** The global None object */
#define PY_NONE         (pPyObj_t)&(gVmGlobal.none)

/** The global False object */
#define PY_FALSE        (pPyObj_t)&(gVmGlobal.zero)

/** The global True object */
#define PY_TRUE         (pPyObj_t)&(gVmGlobal.one)

/** The global integer 0 object */
#define PY_ZERO         (pPyObj_t)&(gVmGlobal.zero)

/** The global integer 1 object */
#define PY_ONE          (pPyObj_t)&(gVmGlobal.one)

/** The global integer -1 object */
#define PY_NEGONE       (pPyObj_t)&(gVmGlobal.negone)


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * This struct contains ALL of Py's globals
 */
typedef struct PyVmGlobal_s
{
    /** Global none obj (none) */
    PyObj_t         none;

    /** Global integer 0 obj */
    PyInt_t         zero;

    /** Global integer 1 obj */
    PyInt_t         one;

    /** Global integer -1 obj */
    PyInt_t         negone;

    /** Dict for builtins */
    pPyDict_t       builtins;

    /** Ptr to stack of code image info. */
    pPyImgInfo_t    pimglist;

    /** Ptr to current python frame */
    pPyFrame_t      pframe;

    /** The single native frame */
    PyNativeFrame_t nativeframe;

    /** PyMite release value for when an error occurs */
    U8              errVmRelease;
    
    /** PyMite source file ID number for when an error occurs */
    U8              errFileId;
    
    /** Line number for when an error occurs */
    U8              errLineNum;
    
    /**
     * Interpreter loop control value
     *
     * A positive value means continue interpreting.
     * A zero value means normal interpreter exit.
     * A negative value signals an error exit.
     */
    PyInterpCtrl_t  interpctrl;
    
    /** the amount of heap space available */
    U16             heapavail;

    /* leave this at the bottom of the global struct */
    /** Global declaration of heap. */
    S8              heapbase[HEAP_SIZE];
    /* DO NOT PUT ANYTHING BELOW THIS */
} PyVmGlobal_t, *pPyVmGlobal_t;


/***************************************************************
 * Globals
 **************************************************************/

extern PyVmGlobal_t gVmGlobal;


/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Initial the global struct.
 *
 * @return  nothing
 */
void global_init(void);

/**
 * Load the builtins dict into the given module's attrs.
 *
 * Load the "__bt" module and set the builtins dict
 * to point to __bt's attributes dict.
 * Create "None" = None entry in builtins.
 *
 * @param pmod Module whose attrs recieves builtins
 * @return  nothing
 */
PyReturn_t global_loadBuiltins(pPyFunc_t pmod);

#endif /* __GLOBAL_H__ */
