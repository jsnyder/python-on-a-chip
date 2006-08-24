#undef __FILE_ID__
#define __FILE_ID__ 0x13
/**
 * Tuple Object Type
 *
 * Tuple object type operations.
 *
 * @author      Dean Hall
 * @file        tuple.c
 *
 * Log:
 *
 * 2002/04/28   First.
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
tuple_loadFromImg(PyMemSpace_t memspace, 
                  P_VOID * paddr, 
                  pPyObj_t * r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    S8 i = 0;
    S8 n = 0;
    
    /* get num objs in tuple */
    n = mem_getByte(memspace, (P_S8 *)paddr);

    /* create empty tuple */
    retval = tuple_new(n, r_ptuple);
    PY_RETURN_IF_ERROR(retval);
    
    /* load the next n objs into tuple */
    for (i = 0; i < n; i++)
    {
        retval = obj_loadFromImg(memspace, 
                                 paddr, 
                                 (pPyObj_t *)&(((pPyTuple_t)*r_ptuple)->val[i]));
        PY_RETURN_IF_ERROR(retval);
    }
    return PY_RET_OK;
}


PyReturn_t 
tuple_new(S16 n, pPyObj_t * r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    S16 size = 0;
    
    /* this size tuple not yet supported */
    /* XXX for larger tuple, break into segments */
    if (n > 100)
    {
        return PY_RET_EX_SYS;
    }
    
    /* calc size of struct to hold tuple */
    size = sizeof(PyTuple_t) + (n * sizeof(pPyObj_t));

    /* allocate a tuple */
    retval = heap_getChunk(size, (P_VOID *)r_ptuple);
    PY_RETURN_IF_ERROR(retval);
    (*r_ptuple)->od.od_type = OBJ_TYPE_TUP;
    /* set the number of objs in the tuple */
    ((pPyTuple_t)*r_ptuple)->length = n;
    /* 
     * no need to null the ptrs 
     * because tuple is filled this
     */
    return retval;
}


PyReturn_t
tuple_copy(pPyObj_t ptup, pPyObj_t * r_ptuple)
{
    PyReturn_t retval = PY_RET_OK;
    pPyTuple_t pnew = C_NULL;

    /* ensure type */
    if (ptup->od.od_type != OBJ_TYPE_TUP)
    {
        return PY_RET_EX_SYS;
    }

    /* duplicate src tuple */
    retval = heap_getChunk(ptup->od.od_size, (P_VOID *)&pnew);
    PY_RETURN_IF_ERROR(retval);
    
    mem_copy(MEMSPACE_RAM,
             (P_S8 *)&pnew,
             (P_S8 *)&ptup,
             ptup->od.od_size);
    *r_ptuple = (pPyObj_t)pnew;
    return PY_RET_OK;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
