#ifndef __CODEOBJ_H__
#define __CODEOBJ_H__
/**
 * CodeObj Type
 *
 * CodeObj type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        codeobj.h
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/06/04   making co_names a tuple,
 *              removing nameoff and codeoff from img.
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** code image field offset consts */
#define CI_TYPE_FIELD       0
#define CI_SIZE_FIELD       1
#define CI_ARGCOUNT_FIELD   3
#define CI_STACKSIZE_FIELD  4
#define CI_NLOCALS_FIELD    5
#define CI_NAMES_FIELD      6

/** native code image size */
#define NATIVE_IMAGE_SIZE   4


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Code Object
 *
 * An extended object that holds only
 * the most frequently used parts
 * of the static code image.
 * Other parts can be obtained by
 * inspecting the code image itself.
 */
typedef struct PyCo_s
{
    /** object descriptor */
    PyObjDesc_t     od;
    /** memory space selector */
    PyMemSpace_t    co_memspace:8;
    /** address in memspace of code image */
    P_U8            co_codeimgaddr;
    /** address in RAM of names tuple */
    pPyTuple_t      co_names;
    /** address in RAM of constants tuple */
    pPyTuple_t      co_consts;
    /** address in memspace of bytecode (or native function) */
    P_U8            co_codeaddr;
} PyCo_t, *pPyCo_t;

/**
 * Native Code Object
 *
 * An extended object that holds only
 * the most frequently used parts
 * of the static native image.
 * Other parts can be obtained by
 * inspecting the native image itself.
 */
typedef struct PyNo_s
{
    /** object descriptor */
    PyObjDesc_t     od;
    /** expected num args to the func */
    S8              no_argcount;
    /** index into native function table */
    S16             no_funcindx;
} PyNo_t, *pPyNo_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a CodeObj by loading info from a code image in memory.
 *
 * An image is a static representation of a Python object.
 * The process of converting an object to and from an image
 * is also called marshalling.
 * In PyMite, code images are the equivalent of .pyc files.
 * Code images can only contain a select subset of object types
 * (None, Int, Float, String, Slice?, Tuple, and CodeImg).
 * All other types (Lists, Dicts, CodeObjs, Modules, Classes,
 * Functions, ClassInstances) are built at runtime.
 *
 * All multibyte values (S16, S32) are in Little Endian order
 * (least significant byte comes first in the byte stream).
 *
 * memspace and *paddr determine the start of the code image.
 * Load the code object with values from the code image,
 * including the names and consts tuples.
 * Leave contents of paddr pointing one byte past end of
 * code img.
 *
 * The code image has the following structure:
 *      -type:      S8 - OBJ_TYPE_CIM
 *      -size:      S16 - number of bytes
 *                  the code image occupies.
 *      -argcount:  S8 - number of arguments to this code obj.
 *      -stacksz:   S8 - the maximum arg-stack size needed.
 *      -nlocals:   S8 - number of local vars in the code obj.
 *      -names:     Tuple - tuple of string objs.
 *      -consts:    Tuple - tuple of objs.
 *      -code:      U8[] - bytecode array.
 *
 * @param   memspace memory space containing image
 * @param   paddr ptr to ptr to code img in memspace
 *          return by reference: paddr points one byte
 *          past end of code img
 * @param   r_pco Return arg.  New code object with fields
 *          filled in.
 * @return  Return status
 */
PyReturn_t
co_loadFromImg(PyMemSpace_t memspace,
               P_U8 *paddr,
               pPyObj_t * r_pco);

/**
 * Create a Native code object by loading a native image.
 *
 * An image is a static representation of a Python object.
 * A native image is much smaller than a regular image
 * because only two items of data are needed after the type:
 * the number of args the func expects and the index into
 * the native function table.
 * A reference to the image is not needed since it is
 * just as efficient to store the info in RAM as it is to
 * store a pointer and memspace value.
 *
 * memspace and *paddr determine the start of the native image.
 * Loads the argcount and the func index from the native object.
 * Leaves contents of paddr pointing one byte past end of
 * code img.
 *
 * The native image has the following structure:
 *      -type:      S8 - OBJ_TYPE_CIM
 *      -argcount:  S8 - number of arguments to this code obj.
 *      -code:      S16 - index into native function table.
 *
 * @param   memspace memory space containing image
 * @param   paddr ptr to ptr to code img in memspace (return)
 * @return  new code object with fields filled in.
 *          return by reference: paddr points one byte
 *          past end of code img
 */
PyReturn_t no_loadFromImg(PyMemSpace_t memspace,
                          P_U8 * paddr,
                          pPyObj_t * r_pno);


#endif /* __CODEOBJ_H__ */
