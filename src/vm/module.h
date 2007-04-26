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

#ifndef __MODULE_H__
#define __MODULE_H__

/**
 * Module Object Type
 *
 * Module object type header.
 *
 * Log:
 *
 * 2002/05/04   First.
 */


/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Creates a Module Obj for the given Code Obj.
 *
 * Use a func struct to represent the Module obj because
 * the module's construction code must execute later,
 * but set the type to OBJ_TYPE_MOD so that it is
 * not otherwise callable.
 *
 * @param   pco ptr to code obj
 * @param   return parameter; ptr to new module obj
 * @return  return status
 */
PmReturn_t mod_new(pPmObj_t pco, pPmObj_t *pmod);

/**
 * Imports a module of the given name.
 * Searches for an image with a matching name.
 * A code obj is created for the code image.
 * A module obj is created for the code obj.
 *
 * @param   pstr String obj containing name of code obj to load.
 * @param   return parameter; ptr to imported module
 * @return  return status
 */
PmReturn_t mod_import(pPmObj_t pstr, pPmObj_t *pmod);

#endif /* __MODULE_H__ */
