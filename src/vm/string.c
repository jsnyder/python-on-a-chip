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
 * 2007/04/21   #46: Finalize design of string objects
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/10   #75: Printing support (P.Adelt)
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

#include "pm.h"


/***************************************************************
 * Globals
 **************************************************************/

#if USE_STRING_CACHE
/** String obj cachche: a list of all string objects. */
static pPmString_t pstrcache = C_NULL;
#endif /* USE_STRING_CACHE */


/***************************************************************
 * Functions
 **************************************************************/

/*
 * If USE_STRING_CACHE is defined nonzero, the string cache
 * will be searched for an existing String object.
 * If not found, a new object is created and inserted
 * into the cache.
 */
PmReturn_t
string_create(PmMemSpace_t memspace,
              uint8_t const **paddr, uint8_t isimg, pPmObj_t *r_pstring)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t len = 0;
    pPmString_t pstr = C_NULL;
    uint8_t *pdst = C_NULL;

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
    retval = heap_getChunk(sizeof(PmString_t) + len, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pstr = (pPmString_t)pchunk;

    /* Fill the string obj */
    OBJ_SET_TYPE(pstr, OBJ_TYPE_STR);
    pstr->length = len;

    /* Copy C-string into String obj */
    pdst = (uint8_t *)&(pstr->val);
    mem_copy(memspace, &pdst, paddr, len);

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
    return sli_strncmp((const unsigned char *)&(pstr1->val),
                       (const unsigned char *)&(pstr2->val),
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
