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

#ifndef __OBJ_H__
#define __OBJ_H__
/**
 * Object Type
 *
 * Object type header.
 *
 * Log
 * ---
 *
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/09   #75: OBJ_TYPE_THR for thread objects (P.Adelt)
 * 2007/01/09   #75: Printing support (P.Adelt)
 * 2006/09/20   #35: Macroize all operations on object descriptors
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

#define OBJ_GET_GCVAL(obj) ((obj).od.od_gcval)
#define OBJ_SET_GCVAL(obj, gcval) (obj).od.od_gcval = (gcval)
#define OBJ_GET_GCFREE(obj) ((obj).od.od_gcfree)
#define OBJ_SET_GCFREE(obj, free) ((obj).od.od_gcfree = (uint8_t)free)
/* 
 * od_size bits are shifted because size is a scaled value 
 * True size is always a multiple of 4, so the lower two bits are ignored
 * and two more significant bits are gained.
 */
#define OBJ_GET_SIZE(obj) ((obj).od.od_size << 2)
#define OBJ_SET_SIZE(obj, size) (obj).od.od_size = (uint8_t)((size) >> 2)
#define OBJ_GET_TYPE(obj) ((obj).od.od_type)
#define OBJ_SET_TYPE(obj, type) (obj).od.od_type = (type)

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
 * WARNING: od_type must be at most 5 bits! (must be < 0x20)
 */
typedef enum PmType_e
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
    OBJ_TYPE_SGL = 0x15,
    /** Sequence iterator */
    OBJ_TYPE_SQI = 0x16,
    /** Thread */
    OBJ_TYPE_THR = 0x17,
} PmType_t, *pPmType_t;


/**
 * Object Descriptor
 *
 * All PyMite "objects" must have this at the top of their struct.
 * (CodeObj, Frame, Dict, List, Tuple, etc.).
 *
 * ALERT: Order of fields is important to maintain bit-order.
 * In this configuration, od_const is the msb and od_type
 * occupies the lower order bytes (using avr-gcc).
 * Although, not critical to operation, it makes reading the
 * raw values easier.
 */
typedef struct PmObjDesc_s
{
    /**
     * object size in bytes
     * This is used to get/return heap space,
     * so it must be accurate for the object
     * containing this descriptor.
     */
    uint8_t od_size;

    /** object type */
    PmType_t    od_type:5;

    /** garbage collection mark value */
    uint8_t od_gcval:1;

    /** Garbage collection free flag */
    uint8_t od_gcfree:1;

    /** #100: Remove od_const bit from object descriptor */
    uint8_t od_unused:1;

} PmObjDesc_t, *pPmObjDesc_t;


/**
 * Object
 *
 * The abstract empty object type for PyMite.
 */
typedef struct PmObj_s
{
    /** object descriptor */
    PmObjDesc_t od;
    /** obj value ;get rid (None doesn't need it) */
} PmObj_t, *pPmObj_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Loads an object from an image in memory.
 * Return pointer to object.
 * Leave add pointing one byte past end of obj.
 *
 * The following lists the simple object types
 * and their image structures:
 * -None:
 *      -type:      int8_t - OBJ_TYPE_NON
 *
 * -Int:
 *      -type:      int8_t - OBJ_TYPE_INT
 *      -value:     int32_t - signed integer value
 *
 * -Float:
 *      -type:      int8_t - OBJ_TYPE_FLOAT
 *      -value:     float32_t - 32-bit floating point value
 *
 * -Slice (is this allowed in img?):
 *      -type:      int8_t - OBJ_TYPE_SLICE
 *      -index1:    int16_t - first index.
 *      -index2:    int16_t - second index.
 *
 * @param   memspace memory space/type
 * @param   paddr ptr to ptr to obj
 *          return by reference: paddr pts to
 *          first byte after obj
 * @param   r_pobj Return arg, the loaded object.
 * @return  Return status
 */
PmReturn_t obj_loadFromImg(PmMemSpace_t memspace,
                           uint8_t **paddr,
                           pPmObj_t * r_pobj);

/**
 * Finds the boolean value of the given object.
 *
 * @param   pobj Ptr to object to test.
 * @return  Nonzero value if object is False.
 */
int8_t obj_isFalse(pPmObj_t pobj);

/**
 * Returns the boolean true if the item is in the object
 *
 * @param   pobj Ptr to container object
 * @param   pitem Ptr to item
 */
PmReturn_t obj_isIn(pPmObj_t pobj, pPmObj_t pitem);

/**
 * Compares two objects for equality.
 *
 * @param   pobj1 Ptr to first object.
 * @param   pobj2 Ptr to second object.
 * @return  C_SAME if the items are equivalent, C_DIFFER otherwise.
 */
int8_t obj_compare(pPmObj_t pobj1, pPmObj_t pobj2);

/**
 * Print an object, thereby using objects helpers.
 * 
 * @param   pobj Ptr to object for printing.
 * @param   marshallString Only has influence on the way strings are printed.
 *                         If 0, just output the string bytewise. Otherwise,
 *                         surround with single quotes and escape unprintable
 *                         characters.
 * @return  Return status
 */
PmReturn_t obj_print(pPmObj_t pobj, uint8_t marshallString);

#endif /* __OBJ_H__ */
