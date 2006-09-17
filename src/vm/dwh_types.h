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

#ifndef __DWH_TYPES_H__
#define __DWH_TYPES_H__
/**
 * Data type definitions as prefered by the author.
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
