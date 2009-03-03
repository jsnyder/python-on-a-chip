/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __MISC_H__
#define __MISC_H__

/**
 * VM Misc
 *
 * VM misc header.
 */


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
