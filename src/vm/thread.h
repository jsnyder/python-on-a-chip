/*
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 */


#ifndef __THREAD_H__
#define __THREAD_H__


/**
 * VM Thread
 *
 * Encapsulating a frame pointer, a root code object and thread state.
 */


#include "interp.h"


 /** Frequency in Hz to switch threads */
#define THREAD_RESCHEDULE_FREQUENCY    10


/**
 * Interpreter return values
 *
 * Used to control interpreter loop
 * and indicate return value.
 * Negative values indicate erroneous results.
 * Positive values indicate "continue interpreting",
 * but first do something special like reschedule threads
 * or (TBD) sweep the heap.
 */
typedef enum PmInterpCtrl_e
{
    /* other erroneous exits go here with negative values */
    INTERP_CTRL_ERR = -1,   /**< Generic error causes exit */
    INTERP_CTRL_EXIT = 0,   /**< Normal execution exit */
    INTERP_CTRL_CONT = 1,   /**< Continue interpreting */
    INTERP_CTRL_RESCHED = 2 /**< Reschedule threads */
        /* all positive values indicate "continue interpreting" */
} PmInterpCtrl_t, *pPmInterpCtrl_t;

/**
 * Thread obj
 *
 */
typedef struct PmThread_s
{
    /** object descriptor */
    PmObjDesc_t od;

    /** current frame pointer */
    pPmFrame_t pframe;

    /**
     * Interpreter loop control value
     *
     * A positive value means continue interpreting.
     * A zero value means normal interpreter exit.
     * A negative value signals an error exit.
     */
    PmInterpCtrl_t interpctrl;
} PmThread_t,
 *pPmThread_t;


/**
 * Constructs a thread for a root frame.
 *
 * @param pframe Frame object as a basis for this thread.
 * @param r_obj Addr to th newly created thread object.
 * @returns Return status
 */
PmReturn_t thread_new(pPmObj_t pframe, pPmObj_t *r_pobj);

#endif /* __THREAD_H__ */
