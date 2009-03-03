/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#undef __FILE_ID__
#define __FILE_ID__ 0x12


/**
 * String Object Type
 *
 * String object type opeartions.
 */

#include "pm.h"


#if USE_STRING_CACHE
/** String obj cachche: a list of all string objects. */
static pPmString_t pstrcache = C_NULL;
#endif /* USE_STRING_CACHE */


/*
 * If USE_STRING_CACHE is defined nonzero, the string cache
 * will be searched for an existing String object.
 * If not found, a new object is created and inserted
 * into the cache.
 */
PmReturn_t
string_create(PmMemSpace_t memspace, uint8_t const **paddr, uint8_t isimg,
              int16_t n, pPmObj_t *r_pstring)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t len = 0;
    pPmString_t pstr = C_NULL;
    uint8_t *pdst = C_NULL;
    uint8_t const *psrc = C_NULL;

#if USE_STRING_CACHE
    pPmString_t pcacheentry = C_NULL;
#endif /* USE_STRING_CACHE */
    uint8_t *pchunk;

    /* If not loading from image */
    if (isimg == (uint8_t)0)
    {
        /* Get length of string */
        len = mem_getStringLength(memspace, *paddr);
    }

    /* If loading from an img */
    else
    {
        /* Get length of string */
        len = mem_getWord(memspace, paddr);
    }

    /* Get space for String obj */
    retval = heap_getChunk(sizeof(PmString_t) + len * n, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pstr = (pPmString_t)pchunk;

    /* Fill the string obj */
    OBJ_SET_TYPE(pstr, OBJ_TYPE_STR);
    pstr->length = len * n;

    /* Copy C-string into String obj */
    pdst = (uint8_t *)&(pstr->val);
    while (--n >= 0)
    {
        psrc = *paddr;
        mem_copy(memspace, &pdst, &psrc, len);
    }

    /* Be sure paddr points to one byte past the end of the source string */
    *paddr = psrc;

    /* Zero-pad end of string */
    for (; pdst < (uint8_t *)pstr + OBJ_GET_SIZE(pstr); pdst++)
    {
        *pdst = 0;
    }

#if USE_STRING_CACHE
    /* Check for twin string in cache */
    for (pcacheentry = pstrcache;
         pcacheentry != C_NULL; pcacheentry = pcacheentry->next)
    {
        /* If string already exists */
        if (string_compare(pcacheentry, pstr) == C_SAME)
        {
            /* Free the string */
            retval = heap_freeChunk((pPmObj_t)pstr);

            /* Return ptr to old */
            *r_pstring = (pPmObj_t)pcacheentry;
            return retval;
        }
    }

    /* Insert string obj into cache */
    pstr->next = pstrcache;
    pstrcache = pstr;

#endif /* USE_STRING_CACHE */

    *r_pstring = (pPmObj_t)pstr;
    return PM_RET_OK;
}


PmReturn_t
string_newFromChar(uint8_t const c, pPmObj_t *r_pstring)
{
    PmReturn_t retval;
    uint8_t cstr[2];
    uint8_t const *pcstr;

    cstr[0] = c;
    cstr[1] = '\0';
    pcstr = cstr;

    retval = string_new(&pcstr, r_pstring);

    /* If c was a null character, force the length to 1 */
    if (c == '\0')
    {
        ((pPmString_t)*r_pstring)->length = 1;
    }

    return retval;
}


int8_t
string_compare(pPmString_t pstr1, pPmString_t pstr2)
{
    /* Return false if lengths are not equal */
    if (pstr1->length != pstr2->length)
    {
        return C_DIFFER;
    }

    /* Compare the strings' contents */
    return sli_strncmp((char const *)&(pstr1->val),
                       (char const *)&(pstr2->val),
                       pstr1->length) == 0 ? C_SAME : C_DIFFER;
}


#ifdef HAVE_PRINT
PmReturn_t
string_print(pPmObj_t pstr, uint8_t marshall)
{
    uint16_t i;
    uint8_t ch;
    uint8_t nibble;
    PmReturn_t retval = PM_RET_OK;

    C_ASSERT(pstr != C_NULL);

    /* Ensure string obj */
    if (OBJ_GET_TYPE(pstr) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    if (marshall)
    {
        retval = plat_putByte('\'');
        PM_RETURN_IF_ERROR(retval);
    }

    for (i = 0; i < (((pPmString_t)pstr)->length); i++)
    {
        ch = ((pPmString_t)pstr)->val[i];
        if (ch == '\\')
        {
            /* Output an additional backslash to escape it. */
            retval = plat_putByte('\\');
            PM_RETURN_IF_ERROR(retval);
        }

        /* If the marshalled char is not printable, print its hex escape code */
        if (marshall && (ch < (uint8_t)32 || ch >= (uint8_t)128))
        {
            plat_putByte('\\');
            plat_putByte('x');

            nibble = (ch >> (uint8_t)4) + '0';
            if (nibble > '9')
                nibble += ('a' - '0' - (uint8_t)10);
            plat_putByte(nibble);

            nibble = (ch & (uint8_t)0x0F) + '0';
            if (nibble > '9')
                nibble += ('a' - '0' - (uint8_t)10);
            plat_putByte(nibble);
        }
        else
        {
            /* Simply output character */
            retval = plat_putByte(ch);
            PM_RETURN_IF_ERROR(retval);
        }
    }
    if (marshall)
    {
        retval = plat_putByte('\'');
    }

    return retval;
}
#endif /* HAVE_PRINT */


PmReturn_t
string_cacheInit(void)
{
#if USE_STRING_CACHE
    pstrcache = C_NULL;
#endif
    return PM_RET_OK;
}


PmReturn_t
string_getCache(pPmString_t **r_ppstrcache)
{
#if USE_STRING_CACHE
    *r_ppstrcache = &pstrcache;
#else
    *r_ppstrcache = C_NULL;
#endif
    return PM_RET_OK;
}
