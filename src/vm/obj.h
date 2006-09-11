 #ifndef __OBJ_H__
#define __OBJ_H__
/**
 * Object Type
 *
 * Object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/12/16   OD's order changed to size-first to assist GC.
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
 * Object type enum
 *
 * These values go in the od_type fields of the obj descriptor.
 * Be sure these values correspond to those in the image creator
 * tool.
 * The hashable types are grouped together for convenience.
 *
 * WARNING: od_type must be at least 5 bits!
 */
typedef enum PyType_e
{
    OBJ_TYPE_HASHABLE_MIN = 0x00,
    /** None */
    OBJ_TYPE_NON = 0x00,
    /** Signed integer */
    OBJ_TYPE_INT = 0x01,
    /** Floating point 32b */
    OBJ_TYPE_FLT = 0x02,
    /** String */
    OBJ_TYPE_STR = 0x03,
    /** Tuple (immutable sequence) */
    OBJ_TYPE_TUP = 0x04,
    /** Code obj */
    OBJ_TYPE_COB = 0x05,
    /** Module obj */
    OBJ_TYPE_MOD = 0x06,
    /** Class obj */
    OBJ_TYPE_CLO = 0x07,
    /** Function obj (callable) */
    OBJ_TYPE_FXN = 0x08,
    /** Class instance */
    OBJ_TYPE_CLI = 0x09,
    /** Code image in static memory */
    OBJ_TYPE_CIM = 0x0A,
    /** Native function image */
    OBJ_TYPE_NIM = 0x0B,
    /** Native function object */
    OBJ_TYPE_NOB = 0x0C,
    /** Exception object */
    OBJ_TYPE_EXN = 0x0E,
    OBJ_TYPE_HASHABLE_MAX = 0x0E,

    /* All types after this are not hashable */
    /** List (mutable sequence) */
    OBJ_TYPE_LST = 0x10,
    /** Dictionary (hash table) */
    OBJ_TYPE_DIC = 0x11,

    /* All types after this are not accessable to the programmer */
    /** Frame type */
    OBJ_TYPE_FRM = 0x12,
    /** Block type (for,while,try,etc) */
    OBJ_TYPE_BLK = 0x13,
    /** Segment (within a seglist) */
    OBJ_TYPE_SEG = 0x14,
    /** Seglist */
    OBJ_TYPE_SGL = 0x15
} PyType_t, *pPyType_t;


/**
 * Object Descriptor
 *
 * All Py "objects" must have this at the top of their struct.
 * (CodeObj, Frame, Dict, List, Tuple, etc.).
 *
 * ALERT: Order of fields is important to maintain bit-order.
 * In this configuration, od_const is the msb and od_type
 * occupies the lower order bytes (using avr-gcc).
 * Although, not critical to operation, it makes reading the
 * raw values easier.
 */
typedef struct PyObjDesc_s
{
    /**
     * object size in bytes
     * This is used to get/return heap space,
     * so it must be accurate for the object
     * containing this descriptor.
     */
    U8          od_size;

    /** object type */
    PyType_t    od_type:5;

    /** garbage collection mark value */
    U8          od_gcval:2;

    /** constant pool object flag */
    U8          od_const:1;

} PyObjDesc_t, *pPyObjDesc_t;


/**
 * Object
 *
 * The abstract empty object type for Py.
 */
typedef struct PyObj_s
{
    /** object descriptor */
    PyObjDesc_t od;
    /** obj value ;get rid (None doesn't need it) */
} PyObj_t, *pPyObj_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Load an object from an image in memory.
 * Return pointer to object.
 * Leave add pointing one byte past end of obj.
 *
 * The following lists the simple object types
 * and their image structures:
 * -None:
 *      -type:      S8 - OBJ_TYPE_NON
 *
 * -Int:
 *      -type:      S8 - OBJ_TYPE_INT
 *      -value:     S32 - signed integer value
 *
 * -Float:
 *      -type:      S8 - OBJ_TYPE_FLOAT
 *      -value:     F32 - 32-bit floating point value
 *
 * -Slice (is this allowed in img?):
 *      -type:      S8 - OBJ_TYPE_SLICE
 *      -index1:    S16 - first index.
 *      -index2:    S16 - second index.
 *
 * @param   memspace memory space/type
 * @param   paddr ptr to ptr to obj
 *          return by reference: paddr pts to
 *          first byte after obj
 * @param   r_pobj Return arg, the loaded object.
 * @return  Return status
 */
PyReturn_t obj_loadFromImg(PyMemSpace_t memspace,
                           P_U8 *paddr,
                           pPyObj_t * r_pobj);

/**
 * Check the object's type.  If object is null ptr
 * or not of the given type, return C_FALSE.
 * Otherwise return C_TRUE.
 *
 * @param   pobj pointer to obj to test
 * @param   type expected type of obj
 * @return  boolean if types match
 */
S8 obj_isType(pPyObj_t pobj, PyType_t type);

/**
 * Find the boolean value of the given object.
 *
 * @param   pobj Ptr to object to test.
 * @return  Nonzero value if object is False.
 */
S8 obj_isFalse(pPyObj_t pobj);

/**
 * Compare two objects for equality.
 *
 * @param   pobj1 Ptr to first object.
 * @param   pobj2 Ptr to second object.
 * @return  C_SAME if the items are equivalent, C_DIFFER otherwise.
 */
S8 obj_compare(pPyObj_t pobj1, pPyObj_t pobj2);

#endif /* __OBJ_H__ */
