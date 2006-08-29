#undef __FILE_ID__
#define __FILE_ID__ 0x0B
/**
 * List Object Type
 *
 * List object type operations.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        list.c
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/04/22   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "py.h"


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

/***************************************************************
 * Functions
 **************************************************************/

PyReturn_t
list_append(pPyObj_t plist, pPyObj_t pobj)
{
    PyReturn_t retval = PY_RET_STUB;

    /* if either obj is null, raise ValueError exception */
    if ((plist == C_NULL) || (pobj == C_NULL))
    {
        return PY_RET_EX_VAL;
    }

    /* if pobj1 is not a list, raise a ValueError exception */
    if (plist->od.od_type != OBJ_TYPE_LST)
    {
        return PY_RET_EX_VAL;
    }

    /* append object to list */
    retval = seglist_appendItem(((pPyList_t)plist)->val, pobj);
    PY_RETURN_IF_ERROR(retval);

    /* incr list length */
    ((pPyList_t)plist)->length++;
    /* XXX test for max length? */

    return retval;
}


PyReturn_t
list_copy(pPyObj_t pobj, pPyObj_t * r_pobj)
{
    PyReturn_t retval = PY_RET_STUB;
    return retval;
}


PyReturn_t
list_getItem(pPyObj_t plist, S16 index, pPyObj_t * r_pobj)
{
    PyReturn_t retval = PY_RET_STUB;
    S16 segnum = 0;
    S16 segindx = 0;

    /*
     * no need to check type, since it's already done by:
     * the bytecodes: BINARY_SUBSCR, UNPACK_SEQUENCE, FOR_LOOP.
     * BUT
     * if someone else calls, we'll need to check.
     */
    /*
    if (plist->od.od_type != OBJ_TYPE_LIST)
    {
        return PY_RET_EX_TYPE;
    }
    */

    /* convert list index into seglist index */
    segnum = index / SEGLIST_OBJS_PER_SEG;
    segindx = index % SEGLIST_OBJS_PER_SEG;

    /* get item from seglist */
    retval = seglist_getItem(((pPyList_t)plist)->val,
                             segnum,
                             segindx,
                             r_pobj);
    return retval;
}


PyReturn_t
list_insert(pPyObj_t plist, pPyObj_t pobj, S8 index)
{
    PyReturn_t retval = PY_RET_STUB;
    return retval;
}


PyReturn_t
list_new(pPyObj_t *r_pobj)
{
    PyReturn_t retval = PY_RET_OK;
    pPyList_t plist = C_NULL;

    /* allocate a list */
    retval = heap_getChunk(sizeof(PyList_t), (P_U8 *)r_pobj);
    PY_RETURN_IF_ERROR(retval);

    /* set list type, empty the contents */
    plist = (pPyList_t)*r_pobj;
    plist->od.od_type = OBJ_TYPE_LST;
    plist->length = 0;
    /* create empty seglist */
    retval = seglist_new(&plist->val);
    return retval;
}


PyReturn_t
list_replicate(pPyObj_t psrclist,
               pPyObj_t pint,
               pPyObj_t * r_pnewlist)
{
    PyReturn_t retval = PY_RET_OK;
    S8 i = 0;
    S8 j = 0;
    S8 length = 0;
    pPyObj_t pitem = C_NULL;

    /* exception if any args are null */
    if ((psrclist == C_NULL)
        || (pint == C_NULL)
        || (r_pnewlist == C_NULL))
    {
        return PY_RET_EX_VAL;
    }

    /* exception if first arg is not a list */
    if (psrclist->od.od_type != OBJ_TYPE_LST)
    {
        return PY_RET_EX_VAL;
    }
    length = ((pPyList_t)psrclist)->length;

    /* exception if second arg is not an int */
    if (pint->od.od_type != OBJ_TYPE_INT)
    {
        return PY_RET_EX_VAL;
    }
    /* XXX limit size of int? */

    /* allocate new list */
    retval = list_new(r_pnewlist);
    PY_RETURN_IF_ERROR(retval);

    /* copy srclist the designated number of times */
    for (i = ((pPyInt_t)pint)->val; i > 0; i--)
    {
        /* iterate over the length of srclist */
        for (j = 0; j < length; j++)
        {
            retval = list_getItem(psrclist, j, &pitem);
            retval = list_append(*r_pnewlist, pitem);
            PY_RETURN_IF_ERROR(retval);
        }
    }
    return retval;
}


PyReturn_t
list_setItem(pPyObj_t pobj1, S16 index, pPyObj_t pobj2)
{
    PyReturn_t retval = PY_RET_STUB;
    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
