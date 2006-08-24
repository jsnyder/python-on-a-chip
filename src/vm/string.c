#undef __FILE_ID__
#define __FILE_ID__ 0x12
/**
 * String Object Type
 *
 * String object type opeartions.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        string.c
 *
 * Log:
 *
 * 2002/12/15   string_isEqual() now compares against string's
 *              length, not the chunk's size.
 * 2002/04/28   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "py.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

#if USE_STRING_CACHE
/** String obj cachche: a list of all string objects. */
static pPyString_t pstrcache = C_NULL;
#endif /* USE_STRING_CACHE */

/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

/*
 * If USE_STRING_CACHE is defined nonzero, the string cache
 * will be searched for an existing String object.
 * If not found, a new object is created and inserted
 * into the cache.
 */
PyReturn_t
string_create(PyMemSpace_t memspace,
              P_S8 * paddr,
              S8 isimg,
              pPyObj_t * r_pstring)
{
    PyReturn_t retval = PY_RET_OK;
    S8 len = 0;
    pPyString_t pstr = C_NULL;
    P_S8 pdst = C_NULL;
#if USE_STRING_CACHE
    pPyString_t pcacheentry = C_NULL;
#endif /* USE_STRING_CACHE */

    /* if not loading from image */
    if (isimg == 0)
    {
        /* get length of string */
        len = mem_getNumUtf8Bytes(memspace, (P_S8 *)paddr);
        /* backup ptr to beginning of string */
        *paddr -= len + 1;
    }

    /* if loading from an img */
    else
    {
        /* get length of string */
        len = mem_getByte(memspace, (P_S8 *)paddr);
    }

    /* get space for String obj */
    retval = heap_getChunk(sizeof(PyString_t) + len,
                           (P_VOID *)&pstr);
    PY_RETURN_IF_ERROR(retval);

    /* fill the string obj */
    pstr->od.od_type = OBJ_TYPE_STR;
    pstr->length = len;
    /* copy C-string into String obj */
    pdst = (P_S8)&(pstr->val);
    mem_copy(memspace, (P_S8 *)&pdst, paddr, len);
    /* zero-pad end of string */
    for ( ; (S16)pdst < (S16)pstr + pstr->od.od_size; pdst++)
    {
        *pdst = 0;
    }

#if USE_STRING_CACHE
    /* XXX uses linear search... could improve */

    /* check for twin string in cache */
    for (pcacheentry = pstrcache;
         pcacheentry != C_NULL;
         pcacheentry = pcacheentry->next)
    {
        /* if string already exists */
        if (obj_isEqual((pPyObj_t)pcacheentry, (pPyObj_t)pstr))
        {
            /* free the string */
            heap_freeChunk((pPyObj_t)pstr);
            /* return ptr to old */
            *r_pstring = (pPyObj_t)pcacheentry;
            return PY_RET_OK;
        }
    }

    /* insert string obj into cache */
    pstr->next = pstrcache;
    pstrcache = pstr;

#endif /* USE_STRING_CACHE */

    *r_pstring = (pPyObj_t)pstr;
    return PY_RET_OK;
}


S8
string_isEqual(pPyObj_t pstr1, pPyObj_t pstr2)
{
    /* if one or both are not a string obj, return false */
    if ((obj_isType(pstr1, OBJ_TYPE_STR) == C_FALSE) ||
        (obj_isType(pstr2, OBJ_TYPE_STR) == C_FALSE))
    {
        return C_FALSE;
    }

    /* return false if lengths are not equal */
    if (((pPyString_t)pstr1)->length !=
        ((pPyString_t)pstr2)->length)
    {
        return C_FALSE;
    }

    /* compare the strings' contents */
    return sli_strncmp((const char *)
                       &(((pPyString_t)pstr1)->val),
                       (const char *)
                       &(((pPyString_t)pstr2)->val),
                       ((pPyString_t)pstr1)->length) == 0;
}


PyReturn_t
string_copy(pPyObj_t pstr, pPyObj_t * r_pstring)
{
    PyReturn_t retval = PY_RET_OK;
    pPyString_t pnew = C_NULL;

    /* ensure string obj */
    if (pstr->od.od_type != OBJ_TYPE_STR)
    {
        PY_ERR(ERR_TYPE);
    }

    /* allocate string obj */
    retval = heap_getChunk(sizeof(PyString_t)
                           + ((pPyString_t)pstr)->length,
                           (P_VOID *)&pnew);
    /* XXX handle retval */
    pnew->od.od_const = 0;
    pnew->od.od_type = OBJ_TYPE_STR;
#if USE_STRING_CACHE
    /* insert new string obj into cache */
    pnew->next = pstrcache;
    pstrcache = pnew;
#endif
    /* copy string contents (and null term) */
    mem_copy(MEMSPACE_RAM,
             (P_S8 *)&(pnew->val),
             (P_S8 *)&(((pPyString_t)pstr)->val),
             ((pPyString_t)pstr)->length + 1);
    *r_pstring = (pPyObj_t)pnew;
    return PY_RET_OK;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
