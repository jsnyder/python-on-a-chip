/** \file
 *  \brief This file provides a set of functions to ease calling
 *         C functions from Python.
 */

#include "pyToC.h"
#include <limits.h>

#undef __FILE_ID__
#define __FILE_ID__ 0x71

PmReturn_t
getInt32(pPmObj_t ppo, int32_t* pi32_val)
{
    PmReturn_t retval = PM_RET_OK;

    // Raise TypeError if Python object isn't an int
    EXCEPTION_UNLESS(OBJ_GET_TYPE(ppo) == OBJ_TYPE_INT, PM_RET_EX_TYPE, 
      "Object must be an int");

    // Get the value, now that we know it's an int
    *pi32_val = ((pPmInt_t) ppo)->val;

    return retval;
}

PmReturn_t
getFloat(pPmObj_t ppo, float* pf_val)
{
    PmReturn_t retval = PM_RET_OK;

    // Raise TypeError if Python object isn't an int
    EXCEPTION_UNLESS(OBJ_GET_TYPE(ppo) == OBJ_TYPE_FLT, PM_RET_EX_TYPE, 
      "Object must be a float");

    // Get the value, now that we know it's an int
    *pf_val = ((pPmFloat_t) ppo)->val;

    return retval;
}

PmReturn_t 
getUint32(pPmObj_t ppo, uint32_t* pu32_val)
{
    PmReturn_t retval = PM_RET_OK;
    int32_t i32_val;

    // Get the int32 from the Python arguments passed to this function
    PM_CHECK_FUNCTION( getInt32(ppo, &i32_val) );

    // Raise a ValueError if address is < min or > max
    EXCEPTION_UNLESS(i32_val >= 0, PM_RET_EX_VAL, 
        "Object value must be non-negative");
    *pu32_val = i32_val;

    return retval;
}

PmReturn_t
getRangedInt(pPmObj_t ppo,
  int32_t i32_min, int32_t i32_max, int32_t* pi32_val)
{
    PmReturn_t retval = PM_RET_OK;

    // Get the int32 from the Python arguments passed to this function
    PM_CHECK_FUNCTION( getInt32(ppo, pi32_val) );

    // Raise a ValueError if address is < min or > max
    EXCEPTION_UNLESS((*pi32_val >= i32_min) && 
      (*pi32_val <= i32_max), PM_RET_EX_VAL, 
        "Object value must be between %ld and %ld.", 
        i32_min, i32_max);

    return retval;
}

PmReturn_t
getUint16(pPmObj_t ppo, uint16_t* pu16_val)
{
    PmReturn_t retval = PM_RET_OK;
    int32_t i32;

    PM_CHECK_FUNCTION( getRangedInt(ppo, 0, 65535, &i32) );
    *pu16_val = (uint16_t) i32;
    return retval;
}

PmReturn_t
getInt16(pPmObj_t ppo, int16_t* pi16_val)
{
    PmReturn_t retval = PM_RET_OK;
    int32_t i32;

    PM_CHECK_FUNCTION( getRangedInt(ppo, -32768, 32767, &i32) );
    *pi16_val = (int16_t) i32;
    return retval;
}

PmReturn_t
getBool(pPmObj_t ppo, bool_t* pb_bool)
{
    PmReturn_t retval = PM_RET_OK;

    // Raise TypeError if Python object isn't a bool
    EXCEPTION_UNLESS(OBJ_GET_TYPE(ppo) == OBJ_TYPE_BOOL, PM_RET_EX_TYPE, 
      "Object must be a bool");
    
    *pb_bool = ((pPmBoolean_t) ppo)->val;

    return retval;
}
