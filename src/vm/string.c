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

#undef __FILE_ID__
#define __FILE_ID__ 0x12
/**
 * String Object Type
 *
 * String object type opeartions.
 *
 * Log
 * ---
 *
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
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
              P_U8 * paddr,
              U8 isimg,
              pPyObj_t * r_pstring)
{
    PyReturn_t retval = PY_RET_OK;
    U8 len = 0;
    pPyString_t pstr = C_NULL;
    P_U8 pdst = C_NULL;
#if USE_STRING_CACHE
    pPyString_t pcacheentry = C_NULL;
#endif /* USE_STRING_CACHE */
    P_U8 pchunk;

    /* if not loading from image */
    if (isimg == 0)
    {
        /* get length of string */
        len = mem_getNumUtf8Bytes(memspace, paddr);
        /* backup ptr to beginning of string */
        *paddr -= len + 1;
    }

    /* if loading from an img */
    else
    {
        /* get length of string */
        len = mem_getByte(memspace, paddr);
    }

    /* get space for String obj */
    retval = heap_getChunk(sizeof(PyString_t) + len, &pchunk);
    PY_RETURN_IF_ERROR(retval);
    pstr = (pPyString_t)pchunk;

    /* fill the string obj */
    pstr->od.od_type = OBJ_TYPE_STR;
    pstr->length = len;
    /* copy C-string into String obj */
    pdst = (P_U8)&(pstr->val);
    mem_copy(memspace, &pdst, paddr, len);
    /* zero-pad end of string */
    for ( ; pdst < (P_U8)pstr + pstr->od.od_size; pdst++)
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
        if (string_compare(pcacheentry, pstr) == C_SAME)
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


PyReturn_t
string_newFromChar(U8 c, pPyObj_t *r_pstring)
{
    PyReturn_t retval;
    pPyString_t pstr;
#if USE_STRING_CACHE
    pPyString_t pcacheentry = C_NULL;
#endif /* USE_STRING_CACHE */
    P_U8 pchunk;

    /* Get space for String obj */
    retval = heap_getChunk(sizeof(PyString_t) + 1, &pchunk);
    PY_RETURN_IF_ERROR(retval);
    pstr = (pPyString_t)pchunk;

    /* Fill the string obj */
    pstr->od.od_type = OBJ_TYPE_STR;
    pstr->length = 1;
    pstr->val[0] = c;
    pstr->val[1] = '\0';

#if USE_STRING_CACHE
    /* XXX uses linear search... could improve */

    /* check for twin string in cache */
    for (pcacheentry = pstrcache;
         pcacheentry != C_NULL;
         pcacheentry = pcacheentry->next)
    {
        /* if string already exists */
        if (string_compare(pcacheentry, pstr) == C_SAME)
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
    return retval;
}


S8
string_compare(pPyString_t pstr1, pPyString_t pstr2)
{
    /* Return false if lengths are not equal */
    if (pstr1->length != pstr2->length)
    {
        return C_DIFFER;
    }

    /* Compare the strings' contents */
    return sli_strncmp((const unsigned char *)&(pstr1->val),
                       (const unsigned char *)&(pstr2->val),
                       pstr1->length
                      ) == 0 ? C_SAME : C_DIFFER;
}


PyReturn_t
string_copy(pPyObj_t pstr, pPyObj_t * r_pstring)
{
    PyReturn_t retval = PY_RET_OK;
    pPyString_t pnew = C_NULL;
    P_U8 pchunk;

    /* ensure string obj */
    if (pstr->od.od_type != OBJ_TYPE_STR)
    {
        return PY_RET_EX_TYPE;
    }

    /* allocate string obj */
    retval = heap_getChunk(sizeof(PyString_t) + ((pPyString_t)pstr)->length,
                           &pchunk
                          );
    PY_RETURN_IF_ERROR(retval);
    pnew = (pPyString_t)pchunk;
    pnew->od.od_const = 0;
    pnew->od.od_type = OBJ_TYPE_STR;
#if USE_STRING_CACHE
    /* insert new string obj into cache */
    pnew->next = pstrcache;
    pstrcache = pnew;
#endif
    /* copy string contents (and null term) */
    mem_copy(MEMSPACE_RAM,
             (P_U8 *)&(pnew->val),
             (P_U8 *)&(((pPyString_t)pstr)->val),
             ((pPyString_t)pstr)->length + 1
            );
    *r_pstring = (pPyObj_t)pnew;
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
