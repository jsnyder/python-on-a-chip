/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __CLASS_H__
#define __CLASS_H__

/** Class header. */


/**
 * Class struct
 *
 * This C struct is used for PyMite class objects
 * Note: Exceptions are objects.
 */
typedef struct PmClass_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /** Attributes dict */
    pPmDict_t cl_attrs;
    
    /** Bases tuple */
    pPmTuple_t cl_bases;
} PmClass_t,
 *pPmClass_t;

/** Class instance struct */
typedef struct PmInstance_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /** Class of this instance */
    pPmClass_t cli_class;

    /** Attributes dict */
    pPmDict_t cli_attrs;
} PmInstance_t, 
*pPmInstance_t;

/** Method struct */
typedef struct PmMethod_s
{
    /** Object descriptor */
    PmObjDesc_t od;

    /** Class of this method */
    pPmClass_t m_class;
    
    /** Instance of this method */
    pPmInstance_t m_instance;
    
    /** Func of this method */
    pPmFunc_t m_func;
    
    /** Attributes dict */
    pPmDict_t m_attrs;
} PmMethod_t, 
*pPmMethod_t;


/**
 * Creates a new Class object from the methods dict, bases tuple,
 * and name string.
 *
 * @param   pmeths ptr to methods dict.
 * @param   pbases ptr to bases tuple.
 * @param   pname ptr to name string.
 * @param   r_pclass Return by ref, ptr to new class
 * @return  Return status
 */
PmReturn_t class_new(pPmObj_t pmeths, pPmObj_t pbases, pPmObj_t pname,
                     pPmObj_t *r_pclass);

/**
 * Returns an instance of the given class
 *
 * @param r_pobj The class object as input, instance object as return
 * @return  Return status
 */
PmReturn_t class_instantiate(pPmObj_t pclass, pPmObj_t *r_pobj);

/**
 * Returns an unbound method based on the given inputs
 *
 * @param   pclass ptr to class
 * @param   pinstance ptr to instance
 * @param   pfunc ptr to func
 * @param   r_pmeth Return by ref, ptr to new method
 * @return  Return status
 */
PmReturn_t class_method(pPmObj_t pclass, pPmObj_t pinstance, pPmObj_t pfunc,
                        pPmObj_t *r_pmeth);

/**
 * Returns the first attribute named __init__ in the class' inheritance tree
 *
 * @param   pobj ptr to class or instance to search
 * @param   pname ptr to name of attr to find
 * @param   r_pobj Return by ref, ptr to attr if found, or undetermined
 * @return  Return status
 */
PmReturn_t class_getAttr(pPmObj_t pobj, pPmObj_t pname, pPmObj_t *r_pobj);


#endif /* __CLASS_H__ */
