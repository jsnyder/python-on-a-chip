#undef __FILE_ID__
#define __FILE_ID__ 0x11
/**
 * Standard Library Interface
 *
 * Py requires a few functions from a few different
 * standard C libraries (memory, string, etc).
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        sli.c
 *
 * Log:
 *
 * 2002/05/16   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "py.h"


/***************************************************************
 * Constants
 **************************************************************/

/** use Duff's Device or simple for-loop for memcpy. */
#define USE_DUFFS_DEVICE    0


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/

void *
sli_memcpy(void *to, const void *from, size_t n)
{
    void *tobak;

    /* store init value of to */
    tobak = to;

#if USE_DUFFS_DEVICE
    if (n > 0)
    {
        switch (n & 0x7)
                            do {
            case 0:             *(P_U8)to++ = *(P_U8)from++;
            case 7:             *(P_U8)to++ = *(P_U8)from++;
            case 6:             *(P_U8)to++ = *(P_U8)from++;
            case 5:             *(P_U8)to++ = *(P_U8)from++;
            case 4:             *(P_U8)to++ = *(P_U8)from++;
            case 3:             *(P_U8)to++ = *(P_U8)from++;
            case 2:             *(P_U8)to++ = *(P_U8)from++;
            case 1:             *(P_U8)to++ = *(P_U8)from++;
                            } while ((n -= 8) > 0);
    }
#else
    for ( ; n > 0; n--)
    {
        *(P_S8)to = *(P_S8)from;
        from++;
        to++;
    }
#endif /* USE_DUFFS_DEVICE */
    return tobak;
}


void
sli_memset(void *dest, const char val, size_t n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        *((char *)dest) = val;
        dest++;
    }
}


size_t
sli_strlen(char const *s)
{
    char const * si = s;
    while(*s++);
    return (size_t)((U16)s - (U16)si);
}


int
sli_strcmp(const char *s1, const char *s2)
{
    /* while not at either strings' end and they're same */
    while ((*s1 != C_NULL) && (*s2 != C_NULL) && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    /* return string difference */
    return *s1 - *s2;
}


int
sli_strncmp(const char *s1, const char *s2, S16 n)
{
    S16 i = 0;

    if (n <= 0)
    {
        return 0;
    }

    /* scan n bytes in string */
    for (i = 0; i < n; i++)
    {
        /* if bytes differ, return difference */
        if (s1[i] != s2[i])
        {
            return s1[i] - s2[i];
        }
        /* XXX if one (or both) is null and i<n */
    }
    return 0;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
