#ifndef __DWH_TYPES_H__
#define __DWH_TYPES_H__
/**
 * Data type definitions as prefered by the author.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        dwh_types.h
 *
 * 2006/09/14   #27: Fix S16/U16 are 32-bits on DESKTOP
 * 2001/11/19   Added pointer to void.
 * 2001/10/21   First lick.
 */

#ifdef TARGET_DESKTOP
typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned short  U16;
typedef signed short    S16;
typedef unsigned long   U32;
typedef signed long     S32;
typedef float           F32;
typedef double          F64;

#elif defined(TARGET_AVR)
typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned int    U16;
typedef signed int      S16;
typedef unsigned long   U32;
typedef signed long     S32;
typedef float           F32;
typedef double          F64;
#endif

/* pointers to basic types */
typedef void*           P_VOID;
typedef U8*             P_U8;
typedef S8*             P_S8;
typedef U16*            P_U16;
typedef S16*            P_S16;
typedef U32*            P_U32;
typedef S32*            P_S32;
typedef F32*            P_F32;
typedef F64*            P_F64;


#endif /* __DWH_TYPES_H__ */
