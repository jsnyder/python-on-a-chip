/*
# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
#
# This file is part of the PyMite VM.
# The PyMite VM is free software: you can redistribute it and/or modify
# it under the terms of the GNU GENERAL PUBLIC LICENSE Version 2.
#
# The PyMite VM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU GENERAL PUBLIC LICENSE Version 2
# is seen in the file COPYING in this directory.
*/


#undef __FILE_ID__
#define __FILE_ID__ 0x01


/**
 * CodeObj Type
 *
 * CodeObj type operations.
 */


#include "pm.h"


PmReturn_t
co_loadFromImg(PmMemSpace_t memspace, uint8_t const **paddr, pPmObj_t *r_pco)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj;
    pPmCo_t pco = C_NULL;
    uint8_t *pchunk;

    /* Store ptr to top of code img (less type byte) */
    uint8_t const *pci = *paddr - 1;

    /* Get size of code img */
    uint16_t size = mem_getWord(memspace, paddr);

    /* Get number of args to the function */
    uint8_t argcount = mem_getByte(memspace, paddr);

    /* Get compiler flags */
    uint8_t flags = mem_getByte(memspace, paddr);

    /* Allocate a code obj */
    retval = heap_getChunk(sizeof(PmCo_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pco = (pPmCo_t)pchunk;

    /* Fill in the CO struct */
    OBJ_SET_TYPE(pco, OBJ_TYPE_COB);
    pco->co_memspace = memspace;
    pco->co_codeimgaddr = pci;
    pco->co_argcount = argcount;
    pco->co_flags = flags;

    /* Load names (tuple obj) */
    *paddr = pci + CI_NAMES_FIELD;
    retval = obj_loadFromImg(memspace, paddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco->co_names = (pPmTuple_t)pobj;

    /* Load consts (tuple obj) assume it follows names */
    retval = obj_loadFromImg(memspace, paddr, &pobj);
    PM_RETURN_IF_ERROR(retval);
    pco->co_consts = (pPmTuple_t)pobj;

    /* Start of bcode always follows consts */
    pco->co_codeaddr = *paddr;

    /* Set addr to point one past end of img */
    *paddr = pci + size;

    *r_pco = (pPmObj_t)pco;
    return PM_RET_OK;
}


PmReturn_t
no_loadFromImg(PmMemSpace_t memspace, uint8_t const **paddr, pPmObj_t *r_pno)
{
    PmReturn_t retval = PM_RET_OK;
    pPmNo_t pno = C_NULL;
    uint8_t *pchunk;

    /* Allocate a code obj */
    retval = heap_getChunk(sizeof(PmNo_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pno = (pPmNo_t)pchunk;

    /* Fill in the NO struct */
    OBJ_SET_TYPE(pno, OBJ_TYPE_NOB);
    pno->no_argcount = mem_getByte(memspace, paddr);

    /* Get index into native fxn table */
    pno->no_funcindx = (int16_t)mem_getWord(memspace, paddr);

    *r_pno = (pPmObj_t)pno;
    return PM_RET_OK;
}
