#ifndef __DICT_H__
#define __DICT_H__
/**
 * Dict Object Type
 *
 * Dict object type header.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        dict.h
 *
 * Log
 * ---
 *
 * 2006/09/08   #22: Implement classes
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


/**
 * Extends the desitnation dict with all of the key,val pairs of the source dict
 *
 * @param   pdictDest ptr to destination dict
 * @param   pdictSrc ptr to source dict
 * @return  Return status
 */
PyReturn_t dict_extend(pPyObj_t pdictDest, pPyObj_t pdictSrc);

#if 0
/* TBD */
U8        dict_hasKey(pPyObj_t pdict, pPyObj_t pkey);
pPyObj_t  dict_items(pPyObj_t pdict); /* list of (keys,vals) */
pPyObj_t  dict_keys(pPyObj_t pdict);
pPyObj_t  dict_popItem(pPyObj_t pdict);
void      dict_setDefault(pPyObj_t pdict, /*HERE*/);
pPyObj_t  dict_values(pPyObj_t pdict);
#endif

#endif /* __DICT_H__ */
