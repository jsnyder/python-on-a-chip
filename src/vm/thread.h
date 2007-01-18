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

#ifndef THREAD_H_
#define THREAD_H_

/**
 * VM Thread
 *
 * Encapsulating a frame pointer, a root code object and thread state.
 *
 * Log
 * ---
 *
 * 2007/01/03   #75: First (P.Adelt)
 */

/***************************************************************
 * Includes
 **************************************************************/
 
#include "interp.h"  

/***************************************************************
 * Constants
 **************************************************************/
 
 /** Frequency in Hz to switch threads */ 
 #define THREAD_RESCHEDULE_FREQUENCY    10
 
/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

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
} PmThread_t, *pPmThread_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Construct a thread for a root frame.
 * 
 * @param pframe Frame object as a basis for this thread.
 * @param r_obj Addr to th newly created thread object.
 * @returns Return status
 */
PmReturn_t thread_new(pPmObj_t pframe, pPmObj_t *r_pobj);

#endif /*THREAD_H_*/
