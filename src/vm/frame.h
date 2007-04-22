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

#ifndef __FRAME_H__
#define __FRAME_H__
/**
 * VM Frame
 *
 * VM frame header.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/12/15   Frame's memspace set to use one byte.
 * 2002/04/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/**
 * the maximum number of local variables
 * a native function can have.
 * This defines the length of the locals array
 * in the native frame struct.
 */
#define NATIVE_NUM_LOCALS   8


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Block Type
 *
 * Numerical values to put in the 'b_type' field
 * of the tPmBlockType struct.
 */
typedef enum PmBlockType_e
{
    /** invalide block type */
    B_INVALID = 0,
    /** loop type */
    B_LOOP,
    /** try type */
    B_TRY
} PmBlockType_t, *pPmBlockType_t;


/**
 * Block
 *
 * Extra info for loops and trys (others?)
 * Frames use linked list of blocks to handle
 * nested loops and try-catch blocks.
 */
typedef struct PmBlock_s
{
    /** obligatory obj descriptor */
    PmObjDesc_t od;
    /** ptr to backup stack ptr */
    pPmObj_t *b_sp;
    /** handler fxn obj */
    uint8_t const *b_handler;
    /** block type */
    PmBlockType_t b_type:8;
    /** next block in stack */
    struct PmBlock_s *next;
} PmBlock_t,
 *pPmBlock_t;


/**
 * Frame
 *
 * A struct that holds the execution frame
 * of a function, including the stack, local vars
 * and pointer to the code object.
 *
 * This struct doesn't declare the stack.
 * frame_new() is responsible for allocating the extra memory
 * at the tail of fo_locals[] to hold both the locals and stack.
 */
typedef struct PmFrame_s
{
    /** obligatory obj descriptor */
    PmObjDesc_t od;
    /** ptr to previous frame obj */
    struct PmFrame_s *fo_back;
    /** ptr to fxn obj */
    pPmFunc_t fo_func;
    /** mem space where func's CO comes from */
    PmMemSpace_t fo_memspace:8;
    /** instrxn ptr (pts into memspace) */
    uint8_t const *fo_ip;
    /** current source line num */
    uint16_t fo_line;
    /** linked list of blocks */
    pPmBlock_t fo_blockstack;
    /** local attributes dict (non-fast locals) */
    pPmDict_t fo_attrs;
    /** global attributes dict (pts to root frame's globals */
    pPmDict_t fo_globals;
    /** points to next empty slot in fo_locals (1 past TOS) */
    pPmObj_t *fo_sp;
    /** frame can be an import-frame that handles RETURN differently */
    uint8_t fo_isImport:1;
    /** array of local vars and stack (space appended at alloc) */
    pPmObj_t fo_locals[0];
} PmFrame_t,
 *pPmFrame_t;

/**
 * Native Frame
 *
 * A struct that holds the execution frame
 * of a native function, including the args and
 * single stack slot, and pointer to the code object.
 *
 * This struct doesn't need an OD because it is only
 * used statically in the globals struct.
 * There's only one native frame, the global one.
 * This happens because a native function is a leaf node
 * in the call tree (a native func can't call python funcs).
 */
typedef struct PmNativeFrame_s
{
    /** ptr to previous frame obj */
    struct PmFrame_s *nf_back;
    /** ptr to fxn obj */
    pPmFunc_t nf_func;
    /** single stack slot */
    pPmObj_t nf_stack;
    /** local vars */
    pPmObj_t nf_locals[NATIVE_NUM_LOCALS];
} PmNativeFrame_t,
 *pPmNativeFrame_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Allocate space for a new frame, fill its fields
 * with respect to the given function object.
 * Return pointer to the new frame.
 *
 * @param   pfunc ptr to Function object.
 * @param   r_pobj Return value; the new frame.
 * @return  Return status.
 */
PmReturn_t frame_new(pPmObj_t pfunc, pPmObj_t *r_pobj);

/**
 * TODO
 * #define PM_FRAME_GET_CONST(pfo, indx)
 * #define PM_FRAME_GET_LOCAL(pfo, indx)
 * #define PM_FRAME_SET_LOCAL(pfo, indx, pod)
 * #define PM_FRAME_GET_ATTR(pfo, namei)
 * #define PM_FRAME_SET_ATTR(pfo, namei, pod)
 */

#endif /* __FRAME_H__ */
