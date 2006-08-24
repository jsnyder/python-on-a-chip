#ifndef __MODULE_H__
#define __MODULE_H__
/**
 * Module Object Type
 *
 * Module object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        module.h
 *
 * Log:
 *
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

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

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Create a Module Obj for the given Code Obj.
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
PyReturn_t mod_new(pPyCo_t pco, pPyFunc_t * pmod);

/**
 * Import a module of the given name.
 * Search for an image with a matching name.
 * A code obj is created for the code image.
 * A module obj is created for the code obj.
 *
 * @param   pstr String obj containing name of code obj to load.
 * @param   return parameter; ptr to imported module
 * @return  return status
 */
PyReturn_t mod_import(pPyObj_t pstr, pPyFunc_t * pmod);

#endif /* __MODULE_H__ */
