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

#ifndef __PY_H__
#define __PY_H__
/**
 * Py Header
 *
 * Include things that are needed by nearly everything.
 *
 * Log
 * ---
 *
 * 2006/09/16   #16: Create pm_init() that does the initial housekeeping
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/30   #6: Have pmImgCreator append a null terminator to image list
 * 2002/05/04   Merged most of contents to respective files.
 *              Started doxygen comments.
 * 2002/04/15   Merging object descriptor into tops of objects.
 * 2002/02/06   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "dwh_types.h"

/***************************************************************
 * Configurables
 **************************************************************/

/**
 * Value indicating the release of PyMite
 *
 * This value should be incremented for every public release.
 * It helps locate a defect when used in conjunction with a fileID
 * and line number.
 */
#define PY_RELEASE  3


/***************************************************************
 * Constants
 **************************************************************/

/* System global defs */
#ifdef NULL
/** null for C code */
#define C_NULL          NULL
#else
/** null for C code */
#define C_NULL          0
#endif

/** false for C code */
#define C_FALSE         0

/** true for C code */
#define C_TRUE          (!C_FALSE)

/** Comparison result is that items are the same */
#define C_SAME 0

/** Comparison result is that items differ */
#define C_DIFFER -1

/** PORT inline for C code */
#define INLINE          __inline__


/***************************************************************
 * Macros
 **************************************************************/

/** puts debug info in registers, halts interpreter */
#if __DEBUG__
#define PY_ERR(line)                        \
        gVmGlobal.errFileId = __FILE_ID__;  \
        gVmGlobal.errLineNum = (U16)(line); \
        retval = PY_RET_ERR;                \
        for(;;)
#else
#define PY_ERR(line)                        \
        gVmGlobal.errFileId = __FILE_ID__;  \
        gVmGlobal.errLineNum = (U16)(line); \
        retval = PY_RET_ERR;                \
        return PY_RET_ERR
#endif

/** error macro for unit tests */
#define TEST_ERR(arg)   for(;;)

/** return an error code if it is not PY_RET_OK */
#define PY_RETURN_IF_ERROR(retval)  if((retval) != PY_RET_OK) \
                                        return (retval)

/** If the boolean expression fails, return the ASSERT error code */
#define PY_ASSERT(boolexpr) if (!(boolexpr)) return PY_RET_ASSERT_FAIL

/***************************************************************
 * Enums
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Return values for system functions
 * to report status, errors, exceptions, etc.
 * Normally, functions which use these values
 * should propagate the same return value
 * up the call tree to the interpreter.
 */
typedef enum PyReturn_e
{
    /* general status return values */
    PY_RET_OK         = 0,      /**< everything is ok */
    PY_RET_NO         = 0xFF,   /**< general "no result" */
    PY_RET_ERR        = 0xFE,   /**< general failure */
    PY_RET_STUB       = 0xFD,   /**< return val for stub fxn */
    PY_RET_ASSERT_FAIL= 0xFC,   /**< assertion failure */

    /* return vals that indicate an exception occured */
    PY_RET_EX         = 0xE0,   /**< general exception */
    PY_RET_EX_EXIT    = 0xE1,   /**< system exit */
    PY_RET_EX_FLOAT   = 0xE2,   /**< floating point error */
    PY_RET_EX_ZDIV    = 0xE3,   /**< zero division error */
    PY_RET_EX_ASSRT   = 0xE4,   /**< assertion error */
    PY_RET_EX_ATTR    = 0xE5,   /**< attribute error */
    PY_RET_EX_IMPRT   = 0xE6,   /**< import error */
    PY_RET_EX_INDX    = 0xE7,   /**< index error */
    PY_RET_EX_KEY     = 0xE8,   /**< key error */
    PY_RET_EX_MEM     = 0xE9,   /**< memory error */
    PY_RET_EX_NAME    = 0xEA,   /**< name error */
    PY_RET_EX_SYNTAX  = 0xEB,   /**< syntax error */
    PY_RET_EX_SYS     = 0xEC,   /**< system error */
    PY_RET_EX_TYPE    = 0xED,   /**< type error */
    PY_RET_EX_VAL     = 0xEE,   /**< value error */
    PY_RET_EX_WARN    = 0xEF,   /**< warning */
} PyReturn_t;


/***************************************************************
 * Global Declarations
 **************************************************************/

/***************************************************************
 * Includes (order is critical)
 **************************************************************/

#include "sli.h"
#include "mem.h"
#include "obj.h"
#include "heap.h"
#include "int.h"
#include "string.h"
#include "tuple.h"
#include "seglist.h"
#include "list.h"
#include "dict.h"
#include "codeobj.h"
#include "func.h"
#include "module.h"
#include "frame.h"
#include "interp.h"
#include "img.h"
#include "global.h"
#include "misc.h"

/***************************************************************
 * Function Protos
 **************************************************************/

/**
 * Initializes the PyMite virtual machine and  indexes the user's application 
 * image.  The VM heap and globals are reset.  The argument, pusrimg, may be
 * null for interactive sessions.
 *
 * @param memspace      Memory space in which the user image is located
 * @param pusrimg       Address of the user image in the memory space
 * @return Return status
 */
PyReturn_t pm_init(PyMemSpace_t memspace, P_U8 pusrimg);

/**
 * Executes the named module
 *
 * @param modstr        Name of module to run
 * @return Return status
 */
PyReturn_t pm_run(P_U8 modstr);


#endif /* __PY_H__ */
