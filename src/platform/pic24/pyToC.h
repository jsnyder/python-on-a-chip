/** \file
 *  \brief This file implements Python functions defined in main.py.
 */

#include "pm.h"

/** Raise an exception unless the given expression is true.
 *  This MUST be called from the C implementation of a 
 *  Python function, becuase it assumes the existance of
 *  - PmReturn_t retval
 *  Optional arguments are a string to describe the cause of the
 *  exception, optionally containing printf-style formatting codes, 
 *  followed by arguments matching the printf codes.
 *  \param expr Expression to evaluate.
 *  \param prReturn If expression is false, exception to raise. Must
 *                  be of type \ref PmReturn_t and typically is in the
 *                  \ref PmReturn_e enum.
 */
#define EXCEPTION_UNLESS(expr, prReturn, ...) \
    do { \
        if (!(expr)) { \
            printf("Error: " __VA_ARGS__); \
            PM_RAISE(retval, prReturn); \
            return retval; \
        } \
    } while (C_FALSE)

/** Call a C function which implements a Python routine. If the
 *  return value indicates an error, return. Because this macro
 *  assumes execution within the C implementation of a Python routine,
 *  is requires the existance of the variable
 *  <code>PmReturn_t retval</code>. The C function called must
 *  return <code>PmReturn_t retval</code>.
 *  @param func Call to a C function, not just the name of the function.
 *              Its return value will be tested.
 */
#define PM_CHECK_FUNCTION(func) \
    do { \
        retval = func; \
        PM_RETURN_IF_ERROR(retval); \
    } while (C_FALSE)

/** Call a C function, then print argument-based errors on failure.
 *  @param func Call to a C function, not just the name of the function.
 *              Its return value will be tested.
 *  @param u8_ndx Zero-based index of the desired parameter to extract.
 */
#define PM_ARG_CHECK_FUNCTION(func, u8_ndx) \
    do { \
        retval = func; \
        if (retval != PM_RET_OK) \
          printf(" in argument %u.", (uint16_t) u8_ndx); \
        PM_RETURN_IF_ERROR(retval); \
    } while (C_FALSE)

/** Macro to ease calling the \ref getUint16 function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pu16_val Resulting value extracted.
 *  \return Standard Python return value.
 */
#define GET_UINT16_ARG(u8_ndx, pu16_val) \
    PM_ARG_CHECK_FUNCTION( getUint16(NATIVE_GET_LOCAL(u8_ndx), pu16_val), u8_ndx )


/** Macro to ease calling the \ref getInt16 function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pi16_val Resulting value extracted.
 *  \return Standard Python return value.
 */
#define GET_INT16_ARG(u8_ndx, pi16_val) \
    PM_ARG_CHECK_FUNCTION( getInt16(NATIVE_GET_LOCAL(u8_ndx), pi16_val), u8_ndx )

/** Macro to ease calling the \ref getInt32 function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pi32_val Resulting value extracted.
 *  \return Standard Python return value.
 */
#define GET_INT32_ARG(u8_ndx, pi32_val) \
    PM_ARG_CHECK_FUNCTION( getInt32(NATIVE_GET_LOCAL(u8_ndx), pi32_val), u8_ndx )

/** Macro to ease calling the \ref getUint32 function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pu32_val Resulting value extracted.
 *  \return Standard Python return value.
 */
#define GET_UINT32_ARG(u8_ndx, pu32_val) \
    PM_ARG_CHECK_FUNCTION( getUint32(NATIVE_GET_LOCAL(u8_ndx), pu32_val), u8_ndx )

/** Macro to ease calling the \ref getBool function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pb_bool Resulting boolean value extracted.
 *  \return Standard Python return value.
 */
#define GET_BOOL_ARG(u8_ndx, pb_bool) \
    PM_ARG_CHECK_FUNCTION( getBool(NATIVE_GET_LOCAL(u8_ndx), pb_bool), u8_ndx )

/** Macro to ease calling the \ref getFloat function. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  \param u8_ndx Zero-based index of the desired parameter to extract.
 *  \param pf_val Resulting floating-point value extracted.
 *  \return Standard Python return value.
 */
#define GET_FLOAT_ARG(u8_ndx, pf_val) \
    PM_ARG_CHECK_FUNCTION( getFloat(NATIVE_GET_LOCAL(u8_ndx), pf_val), u8_ndx )

/** Check the number of arguments passed to a Python function.
 *  Report an exception if the number is incorrect. This MUST be called from
 *  the C implementation of a Python function, becuase it assumes
 *  the existance of:
 *  - PmReturn_t retval
 *  - pPmFrame_t* ppframe
 *  @param u8_numArgs Number of arguemnts expected.
 */
#define CHECK_NUM_ARGS(u8_numArgs) \
    EXCEPTION_UNLESS(NATIVE_GET_NUM_ARGS() == (u8_numArgs), PM_RET_EX_TYPE, \
      "Expected %u arguments, but received %u.", (uint16_t) (u8_numArgs), \
      (uint16_t) NATIVE_GET_NUM_ARGS())

/** Get an integer from a Python object,
 *  requiring that the integer lie winin a minimum and minimum value.
 *  Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param i32_min Minimum allowable value.
 *  \param i32_max Maximum allowable value.
 *  \param pi32_val Pointer to resulting int32 value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getRangedInt(pPmObj_t ppo, 
  int32_t i32_min, int32_t i32_max, int32_t* pi32_val);

/** Get an unsigned, 16-bit value from a Python object. 
 *  Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pu16_val Pointer to resulting uint16 value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getUint16(pPmObj_t ppo, uint16_t* pu16_val);

/** Get an signed, 16-bit value from a Python object.
 *  Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pi16_val Pointer to resulting int16 value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getInt16(pPmObj_t ppo, int16_t* pi16_val);

/** Get a signed, 32-bit value from a Python
 *  object. Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pi32_val Pointer to resulting int32 value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getInt32(pPmObj_t ppo, int32_t* pi32_val);

/** Get an unsigned, 32-bit value from a Python
 *  object. Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pu32_val Pointer to resulting int32 value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t 
getUint32(pPmObj_t ppo, uint32_t* pu32_val);

/** Get a boolean value from a Python
 *  object. Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pb_bool Pointer to resulting boolean value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getBool(pPmObj_t ppo, bool_t* pb_bool);

/** Get a floating-point value from a Python
 *  object. Raises errors as necessary.
 *  \param ppo A Python object.
 *  \param pf_val Pointer to resulting floating-point value extracted.
 *  \return Standard Python return value.
 */
PmReturn_t
getFloat(pPmObj_t ppo, float* pf_val);
