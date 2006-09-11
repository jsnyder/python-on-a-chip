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
sli_memcpy(unsigned char *to, const unsigned char *from, unsigned int n)
{
    unsigned char *tobak;

    /* store init value of to */
    tobak = to;

#if USE_DUFFS_DEVICE
    if (n > 0)
    {
        switch (n & 0x7)
                            do {
            case 0:             *to++ = *from++;
            case 7:             *to++ = *from++;
            case 6:             *to++ = *from++;
            case 5:             *to++ = *from++;
            case 4:             *to++ = *from++;
            case 3:             *to++ = *from++;
            case 2:             *to++ = *from++;
            case 1:             *to++ = *from++;
                            } while ((n -= 8) > 0);
    }
#else
    for ( ; n > 0; n--)
    {
        *to = *from;
        from++;
        to++;
    }
#endif /* USE_DUFFS_DEVICE */
    return tobak;
}


void
sli_memset(unsigned char *dest, const char val, unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        *dest = (unsigned char)val;
        dest++;
    }
}


int
sli_strlen(char const *s)
{
    char const * si = s;
    while(*s++);
    return (unsigned int)s - (unsigned int)si;
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
sli_strncmp(const unsigned char *s1, const unsigned char *s2, unsigned int n)
{
    unsigned int i = 0;

    if (n == 0)
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
    }
    return 0;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
