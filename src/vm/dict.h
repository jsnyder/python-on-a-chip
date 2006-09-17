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

#ifndef __DICT_H__
#define __DICT_H__
/**
 * Dict Object Type
 *
 * Dict object type header.
 *
 * Log:
 *
 * 2002/04/30   First.
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

/**
 * Dict
 *
 * Contains ptr to two seglists; 
 * one for keys, the other for values
 */
typedef struct PyDict_s
{
    /** object descriptor */
    PyObjDesc_t     od;
    /** number of key,value pairs in the dict */
    S16             length;
    /** ptr to seglist containing keys */
    pSeglist_t      d_keys;
    /** ptr to seglist containing values */
    pSeglist_t      d_vals;
} PyDict_t, *pPyDict_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Clears the contents of a dict.
 * after this operation, the dict should in the same state
 * as if it were just created using dict_new().
 *
 * @param   pdict ptr to dict to clear.
 * @return  nothing
 */
PyReturn_t dict_clear(pPyObj_t pdict);


/**
 * Get the value in the dict using the given key.
 *
 * @param   pdict ptr to dict to search
 * @param   pkey ptr to key obj
 * @param   r_pobj Return; addr of ptr to obj
 * @return  Return status
 */
PyReturn_t dict_getItem(pPyObj_t pdict,
                        pPyObj_t pkey,
						pPyObj_t * r_pobj);


/**
 * Allocate space for a new Dict.
 * Return a pointer to the dict by reference.
 *
 * @param   r_pdict Return; Addr of ptr to dict
 * @return  Return status
 */
PyReturn_t dict_new(pPyObj_t * r_pdict);


/**
 * Set a value in the dict using the given key.
 *
 * If the dict already contains a matching key, the value is
 * replaced; otherwise the new key,val pair is inserted
 * at the front of the dict (for fast lookup).
 * In the later case, the length of the dict is incremented.
 *
 * @param   pdict ptr to dict in which (key,val) will go
 * @param   pkey ptr to key obj
 * @param   pval ptr to val obj
 * @return  Return status
 */
PyReturn_t dict_setItem(pPyObj_t pdict,
                        pPyObj_t pkey,
						pPyObj_t pval);


#if 0
/* TBD */
pPyObj_t  dict_copy(pPyObj_t pdict);
U8        dict_hasKey(pPyObj_t pdict, pPyObj_t pkey);
pPyObj_t  dict_items(pPyObj_t pdict); /* list of (keys,vals) */
pPyObj_t  dict_keys(pPyObj_t pdict);
pPyObj_t  dict_popItem(pPyObj_t pdict);
void      dict_setDefault(pPyObj_t pdict, /*HERE*/);
void      dict_update(pPyObj_t pdict, pPyObj_t pdictb);
pPyObj_t  dict_values(pPyObj_t pdict);
#endif

#endif /* __DICT_H__ */
