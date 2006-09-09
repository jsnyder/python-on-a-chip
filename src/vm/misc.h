#ifndef __VM_MISC_H__
#define __VM_MISC_H__
/**
 * VM Misc
 *
 * VM misc header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        misc.h
 *
 * Log:
 *
 * 2002/04/23   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/* do this for now, make enum later */
#define EXN_ILLEGAL_ARG 1


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Error types
 */
typedef enum PyErr_e
{
    ERR_INVALID = 1,
    ERR_UNIMPL,
    ERR_TYPE,
    ERR_ARG,
    ERR_MEM
} PyErr_t, *pPyErr_t;


/**
 * Instance
 *
 * The structure of a class instance
 */
typedef struct PyInst_s
{
    /** object descriptor */
    PyObjDesc_t od;
    
    /** dict to hold attributes */
    pPyDict_t i_attrs;
} PyInst_t, *pPyInst_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/*
void obj_checkType(pPyObj_t, PyType_t);
void exn_raise(U8 exntype);
*/

#endif /* __TEMPLATE_H__ */
