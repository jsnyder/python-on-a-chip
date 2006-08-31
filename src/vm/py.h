#ifndef __PY_H__
#define __PY_H__
/**
 * Py Header
 *
 * Include things that are needed by nearly everything.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 *
 * Log
 * ---
 *
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
 * It helps locate a bug when used in conjunction with a fileID
 * and line number.
 *
 * Release  Description
 * -------  -----------
 * 1        First release of zip on SourceForge
 * 2        Second release on SourceForge
 */
#define PY_RELEASE  2


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

/** PORT inline for C code */
#define INLINE          __inline__


/***************************************************************
 * Macros
 **************************************************************/

/** puts debug info in registers, halts interpreter */
#if __DEBUG__
#define PY_ERR(line)                        \
        gVmGlobal.errFileId = __FILE_ID__;  \
        gVmGlobal.errLineNum = (U8)(line);  \
        retval = PY_RET_ERR;                \
        for(;;)
#else
#define PY_ERR(line)                        \
        gVmGlobal.errFileId = __FILE_ID__;  \
        gVmGlobal.errLineNum = (U8)(line);  \
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
    PY_RET_EX_RUNTIME = 0xEB,   /**< runtime error */
    PY_RET_EX_SYNTAX  = 0xEC,   /**< syntax error */
    PY_RET_EX_SYS     = 0xED,   /**< system error */
    PY_RET_EX_TYPE    = 0xEE,   /**< type error */
    PY_RET_EX_VAL     = 0xEF,   /**< value error */
    PY_RET_EX_WARN    = 0xD0,   /**< warning */
} PyReturn_t;


/***************************************************************
 * Global Declarations
 **************************************************************/

/***************************************************************
 * Function Protos
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

#endif /* __PY_H__ */
