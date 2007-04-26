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

#ifndef __MISC_H__
#define __MISC_H__

/**
 * VM Misc
 *
 * VM misc header.
 *
 * Log
 * ---
 *
 * 2006/09/10   #20: Implement assert statement
 * 2002/04/23   First.
 */


/***************************************************************
 * Types
 **************************************************************/

/**
 * Class type
 *
 * This C type is used for PyMite class objects, class instances and
 * exception objects.
 */
typedef struct PmClass_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /** Attributes dict */
    pPmDict_t cl_attrs;
} PmClass_t,
 *pPmClass_t;

#endif /* __MISC_H__ */
