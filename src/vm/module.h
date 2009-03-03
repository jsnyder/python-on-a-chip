/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __MODULE_H__
#define __MODULE_H__


/**
 * Module Object Type
 *
 * Module object type header.
 */


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
