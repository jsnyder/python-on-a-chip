#ifndef __FUNC_H__
#define __FUNC_H__
/**
 * Function Object Type
 *
 * Function object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        func.h
 *
 * Log:
 *
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Function obj
 *
 * A function is like an instance of a code obj.
 * Contains ptr to its code obj and
 * has its own attributes dict.
 *
 * The first (__main__) module that is executed
 * has a function obj created for it to execute
 * the bytecode which builds the module.
 */
typedef struct PyFunc_s
{
    /** object descriptor */
    PyObjDesc_t od;
    /** ptr to code obj */
    pPyCo_t     f_co;
    /** ptr to attribute dict */
    pPyDict_t   f_attrs;
    /** ptr to tuple holding default args */
    pPyTuple_t  f_defaultargs;
} PyFunc_t, *pPyFunc_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a Function Obj for the given Code Obj.
 * Allocate space for a Func obj and fill the fields.
 *
 * @param   pco ptr to code obj
 * @return  ptr to new func obj
 */
PyReturn_t func_new(pPyObj_t pco, pPyObj_t * r_pframe);

/**
 * Create a new Class object from the methods dict, bases tuple,
 * and name string.
 *
 * @param   pmeths ptr to methods dict.
 * @param   pbases ptr to bases tuple.
 * @param   pname ptr to name string.
 * @param   r_pclass Return by ref, ptr to new class
 * @return  ptr to new class obj.
 */
PyReturn_t class_new(pPyObj_t pmeths,
                     pPyObj_t pbases,
                     pPyObj_t pname,
                     pPyObj_t * r_pclass);


#endif /* __TEMPLATE_H__ */
